set(SOURCES
    image.cpp
    algorithms/canny.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include>)
