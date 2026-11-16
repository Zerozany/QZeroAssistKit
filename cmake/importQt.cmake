find_package(Qt6 REQUIRED
    COMPONENTS
    Quick
    Qml
    Core
    QuickControls2
)

qt_policy(SET QTP0005 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0003 NEW)
qt_policy(SET QTP0002 NEW)
qt_policy(SET QTP0001 NEW)

qt_standard_project_setup(
    REQUIRES 6.8
)

qt_add_qml_module(${PROJECT_NAME}
    URI "${PROJECT_NAME}"
    VERSION 1.0
    SHARED
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Qml
)
