#!/bin/sh

TOOL=$1

# check presence
$TOOL --version >/dev/null 2>&1
if test $? -ne 0; then
	printf "$TOOL not found.\n"
	printf "Check that PATH is set right and $TOOL is installed at all\n"
	exit 127
fi

have_version=`$TOOL --version | head -n 1 | sed -e 's;[A-Za-z() ]*; ;'`
wanted_version=$2
required_version=$wanted_version

have_version=`echo $have_version | tr -s '[\-A-Za-z]' '.'`
wanted_version=`echo $wanted_version | tr -s '[\-A-Za-z]' '.'`

# debug
##echo "have version: $have_version"
##echo "wanted version: $wanted_version"

# Test major version
have_major_version=`echo $have_version | cut -d"." -f1`
wanted_major_version=`echo $wanted_version | cut -d"." -f1`

# debug
##echo "have_major_version: $have_major_version"
##echo "wanted_major_version: $wanted_major_version"

if test $have_major_version -lt $wanted_major_version; then
	echo "$TOOL $required_version is required"
	exit 63
fi
if test $have_major_version -gt $wanted_major_version; then
        exit 0
fi

# Test minor version
have_minor_version=`echo $have_version | cut -d"." -f2`
wanted_minor_version=`echo $wanted_version | cut -d"." -f2`

# debug
##echo "have_minor_version: $have_minor_version"
##echo "wanted_minor_version: $wanted_minor_version"

if test $have_minor_version -lt $wanted_minor_version; then
	echo "$TOOL $required_version is required"
	exit 63
fi
if test $have_minor_version -gt $wanted_minor_version; then
        exit 0
fi

# Test patch version
have_patch_version=`echo $have_version | cut -d"." -f3`
wanted_patch_version=`echo $wanted_version | cut -d"." -f3`

if test -z "$have_patch_version"; then
	have_patch_version=0
fi
if test -z "$wanted_patch_version"; then
	wanted_patch_version=0
fi

# debug
##echo "have_patch_version: $have_patch_version"
##echo "wanted_patch_version: $wanted_patch_version"

if test $have_patch_version -lt $wanted_patch_version; then
	echo "$TOOL $required_version is required"
	exit 63
fi
if test $have_patch_version -gt $wanted_patch_version; then
        exit 0
fi

exit 0
