
include(FindDoxygen)

find_package(Doxygen)

if(DOXYGEN_FOUND)

configure_file(${libsigschege_SOURCE_DIR}/doc/doxygen_libsigschege.cfg.in ${libsigschege_BINARY_DIR}/doc/doxygen_libsigschege.cfg @ONLY)

add_custom_target(libsigschege_doc ALL ${DOXYGEN_EXECUTABLE} doxygen_libsigschege.cfg)

endif(DOXYGEN_FOUND)
