add_executable(test_list_app Testlist.c)
 
target_link_libraries(test_list_app list_library unity)
 
add_test(test_list test_list_app)

