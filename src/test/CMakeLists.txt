include_directories(${PROJECT_SOURCE_DIR}/src/lib)
set(APP_SRC main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${APP_SRC})