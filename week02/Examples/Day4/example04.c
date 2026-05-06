#include <stdio.h>

struct info{
  short v1;
  char v2;
  char v3;
  int v4;
};

int main(){
  struct info data;
  data.v1 = 20;
  data.v2 = 'C';
  data.v3 = 'D';
  data.v4 = 120;

  unsigned char *ptr = (unsigned char*)&data;
  printf("data.address = %p\nptr=%p\n", &data, ptr);

  char target = *(ptr+3);
  printf("target= %c, target=%c\n", target, data.v3);

  return 0;
}