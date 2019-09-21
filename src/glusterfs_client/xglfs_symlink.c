#include "xglfs_symlink.h"

int xglfs_symlink(const char* source_path, const char* target_path) {
    int res = glfs_symlink(XGLFS_STATE->fs, source_path, target_path);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return res;
}