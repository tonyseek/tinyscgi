TESTS = check_tinyscgi
check_PROGRAMS = check_tinyscgi

check_tinyscgi_SOURCES = check_tinyscgi.c
check_tinyscgi_SOURCES += test_netstring.c test_header.c test_request.c
check_tinyscgi_CFLAGS = @CHECK_CFLAGS@
check_tinyscgi_LDADD = $(top_builddir)/src/libtinyscgi.la @CHECK_LIBS@
EXTRA_DIST = data
