/*
    Ideas for LD_PRELOAD:
    -change exec
    -change strstr
    -change fopen
    - 
*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <sys/stat.h>
 
typedef FILE* (*orig_fopen_f_type)(const char *pathname, const char* mode);

int same_file(int fd1, int fd2) {
    struct stat stat1, stat2;
    printf("hi\n");
    if(fstat(fd1, &stat1) < 0) return -1;
    printf("hioi\n");
    if(fstat(fd2, &stat2) < 0) return -1;
        printf("hai\n");
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}

FILE* fopen(const char *pathname, const char* mode) {    
    printf("hahaha MOSTEST EVIL!!!!!!1!!!!one!!!!!\n");
    

    orig_fopen_f_type orig_fopen;
    orig_fopen = (orig_fopen_f_type)dlsym(RTLD_NEXT,"fopen");
    FILE* to_check = orig_fopen(pathname, mode);
    printf("b\n");
    int fd_tc = fileno(to_check);

    FILE* product_name = orig_fopen("/sys/class/dmi/id/product_name", "r");
    printf("by\n");
    int fd_pn = fileno(product_name);
    printf("bye\n");
    if (same_file(fd_tc, fd_pn) == 1) { 
            printf("hi hi\n");

    //     FILE* pname = fopen("/sys/class/dmi/id/pname", "w");
    //     fprintf(pname, "VMWare VirtualBox QEMU\n");
    //     fclose(pname);
    //     fclose(product_name);
    //     fclose(to_check);
        // return orig_fopen("/sys/class/dmi/id/pname", mode);
        printf("triggered\n");
        return to_check;
    }
    return to_check;
}
