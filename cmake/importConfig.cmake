target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    QZeroAssistKit
)

set(QT_QML_GENERATE_QMLLS_INI OFF)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "$<$<CONFIG:Debug>:/Z7>"
        "/utf-8"
        "/FS"
    )
endif()
