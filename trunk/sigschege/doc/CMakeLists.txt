
include(FindDoxygen)

find_package(Doxygen)

if(DOXYGEN_FOUND)

configure_file(${sigschege_SOURCE_DIR}/doc/doxygen_sigschege.cfg.in ${sigschege_BINARY_DIR}/doc/doxygen_sigschege.cfg @ONLY)

add_custom_target(sigschege_doc ALL ${DOXYGEN_EXECUTABLE} doxygen_sigschege.cfg)

endif(DOXYGEN_FOUND)
