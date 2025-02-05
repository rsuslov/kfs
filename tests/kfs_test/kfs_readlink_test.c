#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_symlink.h>
#include <kfs_read.h>
#include <kfs_readlink.h>
#include <kfs_unlink.h>

#include "test_main.h"

void kfs_readlink_setup(void) {
    main_setup();
}

void kfs_readlink_teardown(void) {
    main_teardown();
}
START_TEST(kfs_readlink_fs_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("source.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("source.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty";
    res = kfs_write("source.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_symlink("source.txt","target.txt");
    ck_assert_int_eq(res,0);
    res = remove(str_concat(LOCAL_DISC_CACHE_PATH,"source.txt"));
    ck_assert_int_eq(res, 0);
    res = kfs_open("target.txt", &fi);
    ck_assert_int_eq(res, -ENOENT);
    char *readlink_buf = "\0";
    char buf_readlink [strlen(readlink_buf)];
    res = kfs_readlink("target.txt", buf_readlink, strlen("target.txt") + 1);
    ck_assert_int_eq(res, 0);
    char *new_buf = "qwerty123\n";
    res = kfs_write("target.txt",new_buf, strlen(new_buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(new_buf));
    char buf_read [strlen(new_buf)];
    res = kfs_read("target.txt", buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    res = kfs_unlink("target.txt");
    remove("/tmp/CACHE/source.txt");
    remove("/tmp/CACHE/target.txt");
    close(create.fh);
    close(fi.fh);
}
END_TEST

Suite *kfs_readlink_suite(void) {
    Suite *suite = suite_create("kfs_readlink()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_readlink_setup, kfs_readlink_teardown);
    tcase_add_test(tcase, kfs_readlink_fs_file);
    suite_add_tcase(suite, tcase);
    return suite;
}
