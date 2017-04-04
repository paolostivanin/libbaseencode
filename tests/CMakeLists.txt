#add_executable (test_base32 ../src/base32.c test-base32-encode.c test-base32-decode.c)
#add_executable (test_base64 ../src/base64.c test-base64-encode.c test-base64-decode.c)

add_executable (test_all ../src/base32.c ../src/base64.c test-base32-encode.c test-base32-decode.c test-base64-encode.c test-base64-decode.c)

#target_link_libraries (test_base32 -lcriterion)
#target_link_libraries (test_base64 -lcriterion)

target_link_libraries (test_all -lcriterion)

add_test (NAME TestAll COMMAND test_all)