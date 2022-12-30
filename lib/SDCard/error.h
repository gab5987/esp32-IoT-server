#ifndef __ERROR__
#define __ERROR__

// error codes
#define ERROR_FILE_OPEN 0x00001
#define ERROR_FILE_WRITE 0x00002
#define ERROR_FILE_APPEND 0x00003
#define ERROR_FILE_READ 0x00004
#define ERROR_FILE_RENAME 0x00005
#define ERROR_FILE_DELETE 0x00006
#define ERROR_FILE_TEST 0x00007
#define ERROR_FILE_LIST 0x00008
#define ERROR_FILE_CREATE 0x00009
#define ERROR_FILE_REMOVE 0x00010
#define ERROR_FILE_TESTDIR 0x00011
#define ERROR_FILE_RUN 0x00012

// messages
#define ERROR_FILE_OPEN_MSG "Failed to open file for writing"
#define ERROR_FILE_WRITE_MSG "Write failed"
#define ERROR_FILE_APPEND_MSG "Failed to open file for appending"
#define ERROR_FILE_READ_MSG "Read failed"
#define ERROR_FILE_RENAME_MSG "Rename failed"
#define ERROR_FILE_DELETE_MSG "Delete failed"
#define ERROR_FILE_TEST_MSG "Test failed"
#define ERROR_FILE_LIST_MSG "List failed"
#define ERROR_FILE_CREATE_MSG "Create failed"
#define ERROR_FILE_REMOVE_MSG "Remove failed"
#define ERROR_FILE_TESTDIR_MSG "Testdir failed"
#define ERROR_FILE_RUN_MSG "Run failed"

#endif