#pragma once

#include "common/consts.h"
#include "disk/disk.h"

namespace hybridfs {

void DiskFormatting() {
    int fd = open(METADATA_DISK.c_str(), O_RDWR);
    if (fd == -1) {
        perror("Error");
        exit(1);
    }
    char buffer[PAGE_SIZE];
    memset(buffer, 0, PAGE_SIZE);
    for (size_t i = 0; i < DISK_SIZE; i++) {
        off_t off = i * PAGE_SIZE;
        if (lseek(fd, off, SEEK_SET) == -1) {
            perror("Error");
            exit(1);
        }
        if (write(fd, buffer, PAGE_SIZE) == -1) {
            perror("Error");
            exit(1);
        }
    }
}

}