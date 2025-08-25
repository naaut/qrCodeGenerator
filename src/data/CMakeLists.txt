find_package(Qt6 REQUIRED COMPONENTS
    Core
    # Test
)

add_library(data STATIC)

target_include_directories(data
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(data
    PUBLIC
        Qt6::Core
        domain
        # utils
        # core_warnings
)

target_sources(data
    PRIVATE
        include/data/HistoryDataProvider.h

        src/HistoryDataProvider.cpp
)

# enable_testing()

# add_executable(test_MsgRepoImpl
#     test/repo/test_MsgRepoImpl.cpp
# )

# add_test(NAME test_MsgRepoImpl COMMAND test_MsgRepoImpl)

# target_link_libraries(test_MsgRepoImpl
#     PRIVATE
#         Qt6::Test
#         data
#         domain
#         utils
# )

# add_executable(test_MsgParser
#     test/test_MsgParser.cpp
# )

# add_test(NAME test_MsgParser COMMAND test_MsgParser)

# target_link_libraries(test_MsgParser
#     PRIVATE
#         Qt6::Test
#         data
#         domain
#         utils
# )

# add_executable(test_MessageBuilder
#     test/test_MessageBuilder.cpp
# )

# add_test(NAME test_MessageBuilder COMMAND test_MessageBuilder)

# target_link_libraries(test_MessageBuilder
#     PRIVATE
#         Qt6::Test
#         data
#         domain
#         utils
# )

# add_executable(test_AppPropertyParser
#     test/test_AppPropertyParser.cpp
# )

# add_test(NAME test_AppPropertyParser COMMAND test_AppPropertyParser)

# target_link_libraries(test_AppPropertyParser
#     PRIVATE
#         Qt6::Test
#         data
#         domain
#         utils
# )
