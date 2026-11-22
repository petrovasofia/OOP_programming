add_executable(lab1
        main.cpp
        trie.cpp
)
target_link_libraries(lab1 PRIVATE gtest)

enable_testing()

add_executable(lab1_tests
        trie_test.cpp
        trie.cpp
)
target_link_libraries(lab1_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)