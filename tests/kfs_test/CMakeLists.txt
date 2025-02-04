find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

# Since Check uses Threads to paralelize the tests, it's mandatory
# add pthread as a dependency, alongside the Check libraries.
add_executable(
        kfs_fuse
        test_main.c
        kfs_common_test.c
        kfs_access_test.c
        kfs_read_test.c
        kfs_mkdir_test.c
        kfs_open_test.c
        kfs_rmdir_test.c
        kfs_create_test.c
        kfs_write_test.c
        kfs_release_test.c
        kfs_chmod_test.c
        kfs_link_test.c
        kfs_unlink_test.c
        kfs_rename_test.c
        kfs_symlink_test.c
        kfs_flush_test.c
        kfs_truncate.c
        kfs_ftruncate_test.c
        kfs_readlink_test.c
        kfs_fsync_test.c
        kfs_opendir_test.c
        kfs_releasedir_test.c
        kfs_mknod_test.c
        kfs_readdir_test.c
)

target_include_directories(kfs_fuse PUBLIC includes)

target_link_libraries(kfs_fuse fuse_cache ${CHECK_LIBRARIES} pthread)

add_test(NAME kfs_fuse COMMAND kfs_fuse WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
# Create testing target and redirect its output to `Testing` folder
set_tests_properties(kfs_fuse PROPERTIES TIMEOUT 30)


# Fuse specific params
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26")