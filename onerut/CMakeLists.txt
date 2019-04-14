message("...................................")
get_filename_component(TARGET_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
message("Processing: ${TARGET_NAME}")

file(GLOB src "src/*.cpp")
message("  Auto detected src files for target ${TARGET_NAME}: ")
foreach(loop_var ${src})
  message("    ${loop_var}")
endforeach(loop_var)
if(NOT src)
  message("    <no files>")
endif()

file(GLOB inc "include/${TARGET_NAME}/*.hpp")
message("  Auto detected hpp files for target ${TARGET_NAME}: ")
foreach(loop_var ${inc})
  message("    ${loop_var}")
endforeach(loop_var)
if(NOT inc)
  message("    <no files>")
endif()

add_executable("${TARGET_NAME}" ${src} ${inc})
target_include_directories("${TARGET_NAME}" PUBLIC include)
target_link_libraries("${TARGET_NAME}"
  onerut_parser
  #onerut_normal_operator
  esc
  /usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a  # Will not be necessary in the future.
  #stdc++fs # Will not be necessary in the future.
  Boost::boost
  Boost::program_options
  #armadillo lapack blas
)

get_target_property(x ${TARGET_NAME} LINK_DIRECTORIES)
  message("  \${TARGET_NAME}.LINK_DIRECTORIES:      ${x}")
get_target_property(x ${TARGET_NAME} INTERFACE_LINK_DIRECTORIES)
  message("  \${TARGET_NAME}.INTERFACE_LINK_DIRECTORIES:      ${x}")