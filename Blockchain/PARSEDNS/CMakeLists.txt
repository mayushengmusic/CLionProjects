aux_source_directory(. PARSEDNS_LIB_SRCS)
add_library(parsedns ${PARSEDNS_LIB_SRCS})
target_link_libraries(parsedns dns)