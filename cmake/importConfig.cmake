target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    QZeroAssistKit
)

set(QT_QML_GENERATE_QMLLS_INI OFF)

set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QMLCACHEGEN_ARGUMENTS "--verbose" # "--direct-calls" "--verbose"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Z7>"
    )

    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
        "/FS"
    )
endif()
