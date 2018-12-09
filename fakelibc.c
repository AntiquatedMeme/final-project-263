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
#include <stdlib.h>
#include <string.h> 

typedef FILE* (*orig_fopen_f_type)(const char *pathname, const char* mode);

FILE* fopen(const char *pathname, const char* mode) {    
    printf("hahaha MOSTEST EVIL!!!!!!1!!!!one!!!!!\n");

    orig_fopen_f_type orig_fopen; 
    orig_fopen = (orig_fopen_f_type)dlsym(RTLD_NEXT,"fopen");
    
    char* product_name = "/sys/class/dmi/id/product_name";

    char resolved_path[4097];
    realpath(pathname, resolved_path); 
    printf("by\n");
    printf("%s\n", resolved_path);
    printf("%s\n", product_name);
    if (strcmp(resolved_path, product_name) == 0) { 
        printf("hi hi\n");

        FILE* pname = fopen("/tmp/pname.txt", "w");
        fprintf(pname, "VMWare VirtualBox QEMU\n");
        fclose(pname);
        printf("triggered\n");
        return orig_fopen("/tmp/pname.txt", mode);
    }
    printf("no evil detected\n");
    return orig_fopen(pathname, mode);

}
