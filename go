#!/bin/bash

# go 0.0.1.10
#
# Just one command for building and executing Qt applications.
#
# Adds the following rules to the Makefile:
#
#	cleanall	Remove all generated files
#	distrib		Create ready to share distributive

# Settings
# ----------------------------------------------------------------------

# Name of the application
application=gpra

# Version of the application (must be tagged with vx.y.z tags)
version=`git tag | grep ^v[0-9]\\\\+ | tail -n1 | cut -dv -f2`.`git log | grep ^commit | wc -l`

# Name of the organization which developed this application
organization=vladimir.barbarosh@gmail.com

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
