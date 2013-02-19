TESTS = check_tinyscgi
check_PROGRAMS = check_tinyscgi
include_HEADERS = tcases.h

check_tinyscgi_SOURCES = check_tinyscgi.c test_request.c test_netstring.c
check_tinyscgi_CFLAGS = @CHECK_CFLAGS@
check_tinyscgi_LDADD = $(top_builddir)/src/libtinyscgi.la @CHECK_LIBS@
EXTRA_DIST = data
