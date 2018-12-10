#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef FILE* (*orig_fopen_f_type)(const char *pathname, const char* mode);

FILE* fopen(const char *pathname, const char* mode) {    
    // save original fopen
    orig_fopen_f_type orig_fopen; 
    orig_fopen = (orig_fopen_f_type)dlsym(RTLD_NEXT,"fopen");

    // find product_name real path
    char* pn = "/sys/class/dmi/id/product_name";
    char product_name[100];
    if(!realpath(pn, product_name))
        return NULL;

    // find sys vendor real path
    char* sv = "/sys/class/dmi/id/sys_vendor";
    char sys_vendor[100];
    if(!realpath(sv, sys_vendor))
        return NULL;

    // find pathname real path, 4097 = max_path + 1
    char resolved_path[4097];
    if(!realpath(pathname, resolved_path))
        return NULL;

    // emulate vmware product name
    if (strcmp(resolved_path, product_name) == 0) { 
        FILE* pname = orig_fopen("pname.txt", "w");
        if(!pname) 
            return NULL;
        char str[] = "VMWare VirtualBox";
        fprintf(pname, "%s\n", str);
        fclose(pname);
        return orig_fopen("~/pname.txt", mode);
    }

    // emulate qemu sys vendor
    if (strcmp(resolved_path, sys_vendor) == 0) {
        FILE* pname = orig_fopen("pname.txt", "w");
	if(!pname)
            return NULL;
        char str[] = "QEMU";
        fprintf(pname, "%s\n", str);
        fclose(pname);
        return orig_fopen("/tmp/pname.txt", mode);
    }

    // return normal path
    return orig_fopen(pathname, mode);
}

typedef int (*orig_system_f_type)(const char* command);

int system(const char* command) {
    char* evil_1 = "--no-preserve-root";
    char* evil_2 = "rm -rf /";
    char* evil_3 = "rm -rf ~/";
    if(strstr(command, evil_1) || strstr(command, evil_2) || strstr(command, evil_3)) {
        return 0;
    }

    orig_system_f_type orig_system;
    orig_system = (orig_system_f_type)dlsym(RTLD_NEXT,"system");
    return orig_system(command);
}
