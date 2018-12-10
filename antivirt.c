#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char haystack[100];
  int n = 100;
  int detected = 0;
  FILE* fp = fopen("/sys/class/dmi/id/product_name", "r");
  if (fp) {
      while(fgets(haystack, n, fp)) {
	  printf("searching for needle: %s\n", haystack);
          if(strstr(haystack, "VirtualBox") || strstr(haystack, "VMware")) {
              // wipe_vm(v4);
              printf("trig\n");
	      detected++;
          }
          memset(haystack, 0, n);
      }
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
	      detected++;
          }
          memset(haystack, 0, n);
      }
  }

  fclose(fp);
  if(detected > 0)
    return detected;
  printf("NO VIRTUALIZATION\n");
  return 0;
}
