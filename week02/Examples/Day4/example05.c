#include <stdio.h>

int main(){
  char *sptr = "Welcome to C";
  char target = *(sptr+4); // (sptr+4)

  printf("sptr = %s\n", sptr);

  printf("target.address = %p\nsptr+4.address = %p\n", 
    &target,
    (sptr+4));

  printf("sptr = %s\n", (sptr+4));
  printf("sptr = %s\n", &target); // problem

  
  return 0;
}