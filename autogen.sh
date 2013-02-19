#!/usr/bin/env sh

aclocal
libtoolize
autoheader
autoconf
automake --add-missing --copy
