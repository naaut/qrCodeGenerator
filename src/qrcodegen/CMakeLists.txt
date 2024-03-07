add_library(qrcodegen STATIC)

target_include_directories(qrcodegen
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(qrcodegen
    PRIVATE
        include/qrcodegen/qrcodegen.hpp
        src/qrcodegen.cpp
)
