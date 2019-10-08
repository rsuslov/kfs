#include "kfs_rmdir.h"

int kfs_rmdir(const char* path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = rmdir(fpath);
    printf("KFS_RMDIR execute result : %d  ", res);
    if(res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_rmdir(path);
        printf("XGLFS_RMDIR execute result : %d  ", ret);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}

