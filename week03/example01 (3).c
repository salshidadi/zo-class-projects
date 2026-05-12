int action(unsigned char d, unsigned char e){
    // local variables
    unsigned char a = 0xef, b = 0x8b, c=0x6a;
    a = a + d;
    b = b + e;
    // unsigned short s = 0xf201;
    // unsigned long l = 0x10L;
    // unsigned char d = 0x5d;
    // unsigned int i = 0xeeeebbbb;
    a = b - 1;
    c = a + 1;

    return 0x5e5d;
}

// 1 2 3 6 10 11 18
// 1 2 3 6 7 c 18
// action();
// action();
//1 [rbp - 0x10] 0
//2 [rbp - 0x18] 11
//3 [rbp - 0xf3] 1
//4 [rbp - 0x12] 3
