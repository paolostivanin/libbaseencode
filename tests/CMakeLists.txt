
IF(BUILD_TESTING)
    add_executable (test_all ../src/base32.c ../src/base64.c test-base32-encode.c test-base32-decode.c test-base64-encode.c test-base64-decode.c)

    target_link_libraries (test_all -lcriterion)

    add_test (NAME TestAll COMMAND test_all)
ENDIF(BUILD_TESTING)
