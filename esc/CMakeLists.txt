set(lib_src
  "src/esc_codes.cpp"
  "src/esc_manip.cpp"
)

set(lib_inc
  "include/esc/esc_codes.hpp"
  "include/esc/esc_manip.hpp"
)

set(src_esc_manip_examples
  "src/esc_manip_examples.cpp"
)

add_library(esc ${lib_src} ${lib_inc})
target_include_directories(esc  PUBLIC include)

add_executable(esc_manip_examples ${src_esc_manip_examples})
target_link_libraries(esc_manip_examples esc)