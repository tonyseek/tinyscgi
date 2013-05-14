# include headers
include_directories (.)

# add library target
add_library (tscgi buffer.c header.c netstring.c request.c)

# install library target
install (TARGETS tscgi
         DESTINATION "lib")
install (FILES errors.h buffer.h header.h netstring.h request.h
         DESTINATION "include/tscgi")
