#!/bin/bash

# go 0.0.1_r14
#
# Just one command for building and executing Qt applications.
#
# Adds the following rules to the Makefile:
#
#	cleanall	Remove all generated files
#	distrib		Create ready to share distributive

# Settings
# ----------------------------------------------------------------------

	# --------------------
	# Application Settings
	# --------------------

# Name of the application
application=gpra

# Version of the application (vx.y.z_r<revision>)
version=`git tag | grep ^v[0-9]\\\\+ | tail -n1 | cut -dv -f2`_r`git log | grep ^commit | wc -l`

# Name of the organization which developed this application
organization=vladimir.barbarosh@gmail.com

	# -------------------------------------------
	# Qt Modules for general software development
	# -------------------------------------------

QtCore=yes
QtGui=yes
QtMultimedia=no
QtNetwork=no
QtOpenGL=no
# Not Supported by 'go' utility
# QtOpenVG=no
QtScript=no
QtScriptTools=no
QtSql=yes
QtSvg=no
QtWebKit=no
QtXml=no
QtXmlPatterns=no
Phonon=no
Qt3Support=no

	# --------------------------------------
	# Qt Modules for working with Qt's tools
	# --------------------------------------

QtDesigner=no
QtUiTools=no
QtHelp=no
QtTest=no

	# ---------------------------------
	# Qt Modules for Windows developers
	# ---------------------------------

# Not Supported by 'go' utility
# QAxContainer=no
# QAxServer=no

	# ------------------------------
	# Qt Modules for Unix developers
	# ------------------------------

QtDBus=no

# Implementation Details
# ----------------------------------------------------------------------

godir=$(dirname $(readlink --canonicalize "$0"))
pushd "$godir"

# 1.  Generate 'go_settings.inc' file

rm -f go_settings.new

echo "app.setApplicationName(\"$application\");" >> go_settings.new
echo "app.setApplicationVersion(\"$version\");" >> go_settings.new
echo "app.setOrganizationName(\"$organization\");" >> go_settings.new

if ! diff go_settings.{inc,new} &> /dev/null; then
	mv go_settings.new go_settings.inc
else
	rm go_settings.new
fi

# 2.  Generate Qt project file
qmake -project -o "$application".pro
cat >> "${application}.pro" << EOF

VERSION = ${version}

# -------------------------------------------
# Qt Modules for general software development
# -------------------------------------------

$(if [[ "$QtCore" == "no" ]]; then echo QT -= core; fi)
$(if [[ "$QtGui" == "no" ]]; then echo QT -= gui; fi)
$(if [[ "$QtMultimedia" == "yes" ]]; then echo QT += multimedia; fi)
$(if [[ "$QtNetwork" == "yes" ]]; then echo QT += network; fi)
$(if [[ "$QtOpenGL" == "yes" ]]; then echo QT += opengl; fi)
$(if [[ "$QtScript" == "yes" ]]; then echo QT += script; fi)
$(if [[ "$QtScriptTools" == "yes" ]]; then echo QT += scripttools; fi)
$(if [[ "$QtSql" == "yes" ]]; then echo QT += sql; fi)
$(if [[ "$QtSvg" == "yes" ]]; then echo QT += svg; fi)
$(if [[ "$QtWebKit" == "yes" ]]; then echo QT += webkit; fi)
$(if [[ "$QtXml" == "yes" ]]; then echo QT += xml; fi)
$(if [[ "$QtXmlPatterns" == "yes" ]]; then echo QT += xmlpatterns; fi)
$(if [[ "$Phonon" == "yes" ]]; then echo QT += phonon; fi)
$(if [[ "$Qt3Support" == "yes" ]]; then echo QT += qt3support; fi)

# --------------------------------------
# Qt Modules for working with Qt's tools
# --------------------------------------

$(if [[ "$QtDesigner" == "yes" ]]; then echo QT += designer; fi)
$(if [[ "$QtUiTools" == "yes" ]]; then echo QT += uitools; fi)
$(if [[ "$QtHelp" == "yes" ]]; then echo QT += help; fi)
$(if [[ "$QtTest" == "yes" ]]; then echo QT += qtestlib; fi)

# ------------------------------
# Qt Modules for Unix developers
# ------------------------------

$(if [[ "$QtDBus" == "yes" ]]; then echo QT += dbus; fi)

EOF

# 3.  Generate Makefile
qmake

	# 3.1.  Add 'cleanall' rule to the Makefile
	cat >> Makefile <<EOF
cleanall: distclean
	rm -f "${application}.pro"
	rm -f go_settings.inc
	rm -f "${application}-${version}.tar.gz"

EOF

	# 3.2  Add 'distrib' rule to the Makefile
	cat >> Makefile <<EOF
distrib_pre:
	rm -rf "/tmp/${application}-${version}"
	mkdir  "/tmp/${application}-${version}"

	# Make "release" .pro file
	echo >> "${application}.pro"
	echo "CONFIG += release" >> "${application}.pro"

	# Preserve some generated files
	cp "${application}.pro" go_settings.inc "/tmp/${application}-${version}"

distrib: distrib_pre cleanall
	cp -r . "/tmp/${application}-${version}"
	rm -rf  "/tmp/${application}-${version}/.git"
	rm -rf  "/tmp/${application}-${version}/.gitignore"

	rm -rf "${application}-${version}"
	mv "/tmp/${application}-${version}" "${application}-${version}"

	tar cavf "${application}-${version}.tar.gz" "${application}-${version}"
	rm -rf "${application}-${version}"

EOF

# 4.  Compile
if make; then
	execute=1
else
	execute=0
fi

# 5.  Execute
popd
if (( execute )); then
	"$godir/$application"
fi
