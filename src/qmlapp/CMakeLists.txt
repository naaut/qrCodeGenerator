set(QT_NO_STANDARD_PROJECT_SETUP ON)

find_package(Qt6 6.5 REQUIRED
    COMPONENTS
        Core
        Gui
        Qml
        Quick
        Svg
        PrintSupport
)


qt_standard_project_setup()

qt_add_executable(QrCodeGenerator
    main.cpp
    core/Entity.h
    core/Painter.h
    core/Painter.cpp
    presentation/QrCodePresenter.cpp
    presentation/QrCodePresenter.h
    usecase/GenerationUsecase.cpp
    usecase/GenerationUsecase.h
    usecase/PrintingUsecase.cpp
    usecase/PrintingUsecase.h
)

qt_add_qml_module(QrCodeGenerator
    URI QmlInjectorCore
    VERSION 1.0
    RESOURCE_PREFIX /
    RESOURCES
)

qt_target_qml_sources(QrCodeGenerator
    QML_FILES
    qml/Entity/TemplatesModel.qml
    qml/MainScreen.qml
    qml/Popups/CryptoPopup.qml
    qml/Popups/EmailPopup.qml
    qml/Popups/GeoPopup.qml
    qml/Popups/PopupLoader.qml
    qml/Popups/PopupTemplate.qml
    qml/Popups/SmsPopup.qml
    qml/Popups/SocialMediaPopup.qml
    qml/Popups/UrlPopup.qml
    qml/Popups/VCardPopup.qml
    qml/Popups/VEventPopup.qml
    qml/Popups/WifiPopup.qml
    qml/TemplatesScreen.qml
    qml/main.qml
)

target_link_libraries(QrCodeGenerator
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Svg
        Qt6::PrintSupport
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
