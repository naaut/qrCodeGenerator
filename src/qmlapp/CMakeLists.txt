set(QT_NO_STANDARD_PROJECT_SETUP ON)

find_package(Qt6 6.5 REQUIRED
    COMPONENTS
        Core
        Gui
        Qml
        Quick
        Svg
)


qt_standard_project_setup()

qt_add_executable(QrCodeGenerator
    main.cpp
    presentation/QrCodePresenter.h
    presentation/QrCodePresenter.cpp
    usecase/QrCodeUsecase.h
    usecase/QrCodeUsecase.cpp
)

qt_add_qml_module(QrCodeGenerator
    URI QmlInjectorCore
    VERSION 1.0
    RESOURCE_PREFIX /
    RESOURCES
)

qt_target_qml_sources(QrCodeGenerator
    QML_FILES
    qml/main.qml
)

target_link_libraries(QrCodeGenerator
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Svg
        qmlinjector
        qrcodegen
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(QrCodeGenerator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQmlInjectorCore
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QrCodeGenerator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
