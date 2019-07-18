#include "kfs_read.h"

int kfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return pread(fi->fh, buf, size, offset);
}