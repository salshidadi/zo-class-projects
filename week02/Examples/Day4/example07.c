#include <stdio.h>

int main(){
    unsigned char values[8] = {
                0x32,
                0xee,
                0xf8,
                0x91,
                0x6a,
                0xdc,
                0xb4,
                0xab
    };

    FILE *fh = fopen("information.pmb", "wb");
    if(fh != NULL){
      fwrite(values, sizeof(values), 1, fh);
      fclose(fh);
    }
    return 0;
}