file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB INCLUDEDIR
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*/"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*/"
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCFILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${INCLUDEDIR}
)
