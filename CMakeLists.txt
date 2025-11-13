#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#--------------------------------------------------------------------------------
# Project directories
#--------------------------------------------------------------------------------

set(MODULE_WEBCORE_MVC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_WEBCORE_MVC_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_WEBCORE_MVC_LIB_DIR "${MODULE_WEBCORE_MVC_ROOT_DIR}/lib")
set(MODULE_WEBCORE_MVC_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
set(MODULE_WEBCORE_MVC_CMAKE_DIR "${MODULE_WEBCORE_MVC_ROOT_DIR}/submodules/sway.module_core/cmake_modules")

#--------------------------------------------------------------------------------
# Include CMake modules
#--------------------------------------------------------------------------------

include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/options.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/set_compile_definitions.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/enable_coverage.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/create_object_library.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/create_interface.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_WEBCORE_MVC_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#--------------------------------------------------------------------------------
# Options
#--------------------------------------------------------------------------------

set_glob_options()

option(MODULE_WEBCORE_MVC_ENVIRONMENT "Environment variable" OFF)
option(MODULE_WEBCORE_MVC_COMPILATION "Compilation variable" OFF)

#--------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#--------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#--------------------------------------------------------------------------------
# Project
#--------------------------------------------------------------------------------

project_metadata("webcore_mvc" 0.2.0)
project(${MODULE_WEBCORE_MVC_PROJ_NAME} VERSION ${MODULE_WEBCORE_MVC_VERSION} LANGUAGES CXX)

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)
add_submodule("module_webcore" submodules/sway.module_webcore)

#--------------------------------------------------------------------------------
# Executable output path
#--------------------------------------------------------------------------------

set_output_dir(${MODULE_WEBCORE_MVC_BIN_DIR})

#--------------------------------------------------------------------------------
# Include directories
#--------------------------------------------------------------------------------

include_directories("${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_webcore/lib/include")

#--------------------------------------------------------------------------------
# Library
#--------------------------------------------------------------------------------

add_subdirectory(lib)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_COMPILER "emcc")

# # Добавляем пути для поиска хедеров
# include_directories("/home/apriori85/emsdk/emscripten/incoming/system/include")
# include_directories(${MODULE_WEBCORE_MVC_LIST_DIR}/lib/include)
# include_directories(${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_core/lib/include)
# include_directories(${MODULE_WEBCORE_MVC_LIST_DIR}/submodules/sway.module_webcore/lib/include)

# # Получаем пути ко всем хедерам и исходникам библиотеки
# file(GLOB_RECURSE MODULE_HEADERS ${MODULE_WEBCORE_MVC_LIST_DIR}/lib/include/*.*)
# file(GLOB_RECURSE MODULE_SOURCES ${MODULE_WEBCORE_MVC_LIST_DIR}/lib/src/*.*)

# # Добавляем в проект цель для сборки статической библиотеки
# add_library(${META_LIB_NAME} STATIC ${MODULE_SOURCES})
# set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
# set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
# set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".a.${META_VERSION}")

# target_link_libraries(${META_LIB_NAME} libmodule_webcore)
