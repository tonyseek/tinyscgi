#!/usr/bin/env sh

version="0.10.3"
url="https://github.com/joyent/libuv/archive/v$version.tar.gz"
build_dir="/tmp/libuv-$version"

(
    mkdir -p $build_dir && cd $build_dir
    wget $url -O $version.tar.gz
    tar -zxf $version.tar.gz
    cd "libuv-$version"
    make
    cp libuv.* /usr/lib
    cp include/uv.h /usr/include/uv.h
    cp -r include/uv-private /usr/include/uv-private
    rm -rf $build_dir
)
