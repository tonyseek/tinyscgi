#!/usr/bin/env sh

aclocal
libtoolize
autoconf
automake --add-missing --copy
