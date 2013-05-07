add_subdirectory (tscgi)

# add excutable target
add_executable (tinyscgi tinyscgi.c)
target_link_libraries (tinyscgi tscgi)

# install executable target
install (TARGETS tinyscgi
         DESTINATION "bin")
