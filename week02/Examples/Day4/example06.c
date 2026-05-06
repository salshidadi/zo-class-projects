#include <stdio.h>

union info{
  char v1;
  char v2;
  short v3;
  int v4;
  float v5;
};

int main(){
  union info data;
  data.v1 = 'C';
  int data_size = sizeof(data);
  printf("data.size = %d\n", data_size);
  printf("data=%p, v1=%p, v2=%p, v3=%p, v4=%p, v5=%p\n",
   &data, &data.v1, &data.v2, &data.v3, &data.v4, &data.v5);
     
  char *ptr = (char*)&data;
  *ptr = 'T';

  printf("data.v1 = %c, data.v2=%c\n",
     data.v1, data.v2);
  return 0;
}