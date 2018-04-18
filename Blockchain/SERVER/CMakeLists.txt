aux_source_directory(. SERVER_LIB_SRCS)
add_library(server ${SERVER_LIB_SRCS})
target_link_libraries(server parsedns)