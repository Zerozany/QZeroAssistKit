# set(QT_QML_GENERATE_QMLLS_INI OFF)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE "$<$<CONFIG:Release>:TRUE>$<$<NOT:$<CONFIG:Release>>:FALSE>"
    WIN32_EXECUTABLE "$<$<CONFIG:Debug>:FALSE>$<$<NOT:$<CONFIG:Debug>>:TRUE>"
)

add_custom_command(TARGET "${PROJECT_NAME}plugin" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}plugin>
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}plugin.dll"
)
