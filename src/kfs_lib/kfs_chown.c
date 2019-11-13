#include "kfs_chown.h"

int kfs_chown(const char *path, uid_t uid, gid_t gid) {
    log_info("kfs_chown start");
    int res = 0;
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_chown path : %s\n", fpath);
    res = lchown(fpath, uid, gid);
    if (res == -1) {
        log_errorf("Error kfs_chown %s", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_chown(path, uid, gid);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_chown exit result : %d\n", res);
    return res;
}
