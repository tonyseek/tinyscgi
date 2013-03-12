bin_PROGRAMS = tinyscgi
lib_LTLIBRARIES = libtinyscgi.la
include_scgi_HEADERS = scgi/netstring.h scgi/header.h scgi/request.h

include_scgidir = $(includedir)/tinyscgi/scgi
include_serverdir = $(includedir)/tinyscgi/server

tinyscgi_SOURCES = tinyscgi.c
tinyscgi_LDADD = libtinyscgi.la

libtinyscgi_la_SOURCES = scgi/netstring.c scgi/header.c scgi/request.c
