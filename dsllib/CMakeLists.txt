add_library(dsllib INTERFACE)
target_include_directories(dsllib INTERFACE src/)
target_compile_options(dsllib INTERFACE -fsanitize=address)
target_link_options(dsllib INTERFACE -fsanitize=address)