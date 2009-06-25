
include(FindDoxygen)

find_package(Doxygen)

if(DOXYGEN_FOUND)

configure_file(${YaVec_SOURCE_DIR}/doc/doxygen_yavec.cfg.in ${YaVec_BINARY_DIR}/doc/doxygen_yavec.cfg @ONLY)

add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} doxygen_yavec.cfg)

endif(DOXYGEN_FOUND)
