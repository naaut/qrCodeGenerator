find_package(Qt6 REQUIRED COMPONENTS
    Core
)

add_library(domain STATIC)

target_include_directories(domain
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(domain
    PUBLIC
        Qt6::Core
)

target_sources(domain
    PRIVATE
        include/domain/IHistoryDataProvider.h
        include/domain/entity/Entity.h
        include/domain/entity/History.h
)
