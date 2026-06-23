#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#--------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#--------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#--------------------------------------------------------------------------------
# Include project headers
#--------------------------------------------------------------------------------

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  include_directories("/usr/local/include/c++/v1")
endif()

include_directories("${MODULE_WEBCORE_MVC_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_webcore/lib/cxx/include")

#--------------------------------------------------------------------------------
# Build object library
#--------------------------------------------------------------------------------

if(NOT TARGET ${MODULE_WEBCORE_MVC_OBJ_TARGET})
  set(MODULE_WEBCORE_MVC_LIB_SOURCES "${MODULE_WEBCORE_MVC_ROOT_DIR}/lib/cxx/src/*.*")
  set(MODULE_WEBCORE_MVC_ENABLE_FILE_EXPORT TRUE)

  create_object_library(${MODULE_WEBCORE_MVC_OBJ_TARGET} ${MODULE_WEBCORE_MVC_LIB_SOURCES} ${MODULE_WEBCORE_MVC_ENABLE_FILE_EXPORT})
  enable_cxx17(${MODULE_WEBCORE_MVC_OBJ_TARGET})
endif()

#--------------------------------------------------------------------------------
# Definitions
#--------------------------------------------------------------------------------

set_compile_definitions(${MODULE_WEBCORE_MVC_PROJ_NAME} ${MODULE_WEBCORE_MVC_OBJ_TARGET})

#--------------------------------------------------------------------------------
# Build libraries
#--------------------------------------------------------------------------------

if(NOT MODULE_WEBCORE_MVC_LIB_TYPE STREQUAL "object")
  if(GLOB_EMSCRIPTEN_PLATFORM)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-no-whole-archive")
    create_emscripten_library(${MODULE_WEBCORE_MVC_LIB_TARGET} ${MODULE_WEBCORE_MVC_ENVIRONMENT} ${MODULE_WEBCORE_MVC_COMPILATION} OUTPUT_TARGET_NAME_LIST)

    foreach(target IN LISTS OUTPUT_TARGET_NAME_LIST)
      target_link_options(${target} PUBLIC 
        "SHELL:-s STRICT=1"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME=\"create_webcore_mvc_module\""
        "SHELL:-s EXPORTED_RUNTIME_METHODS=@${MODULE_WEBCORE_MVC_LIB_DIR}/runtime-exports.json")

      if(NOT GLOB_EMSCRIPTEN_USE_BINDINGS)
        if(MODULE_WEBCORE_MVC_ALL_EXPORT)
          target_link_options(${target} PUBLIC "SHELL:-s LINKABLE=1") # Полный экспорт
        else()
          target_link_options(${target} PUBLIC "SHELL:-s EXPORTED_FUNCTIONS=@${MODULE_WEBCORE_MVC_LIB_DIR}/exports.json") # Частичный экспорт
        endif()
      endif()

      printf_link_options(${target})
    endforeach()
  else()
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      set(CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang")
    endif()

    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc")
    create_clang_library(${MODULE_WEBCORE_MVC_LIB_TARGET})
  endif()
endif()
