# sway.module_webcore.mvc

```console
cmake -D CMAKE_BUILD_TYPE=Debug \
      -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googletest \
      -D GLOB_GTEST_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D GLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_EMSCRIPTEN_PLATFORM=ON \
      -D MODULE_CORE_LIB_TYPE=object \
      -D MODULE_CORE_ENVIRONMENT=web \
      -D MODULE_CORE_COMPILATION=async \
      -D MODULE_CORE_ENABLE_TESTS=OFF \
      -D MODULE_WEBCORE_MVC_ENVIRONMENT=web \
      -D MODULE_WEBCORE_MVC_COMPILATION=async \
      -D MODULE_WEBCORE_ENABLE_TESTS=OFF \
      ../
```

```console
cmake --build ./
```
