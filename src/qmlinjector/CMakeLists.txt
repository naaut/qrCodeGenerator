find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
)

add_library(qmlinjector STATIC)

target_include_directories(qmlinjector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(qmlinjector
    PUBLIC
        Qt6::Core
        Qt6::Quick
)

target_sources(qmlinjector
    PRIVATE
        include/qmlinjector/qmlinjector.h
        include/qmlinjector/qmlinjectorbuilder.h
        include/qmlinjector/qmlobjectcreator.h

        src/qmlinjector.cpp
        src/qmlobjectcreator.cpp
)
