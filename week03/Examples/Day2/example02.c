int action(){
    char values [] = "ABCDEFG.HI.G";
    char *message  = "ABCDEFGH.HI.G";
    char *message2  = "ABCDEFGH.HI.G";

    // values[0] = 'A';
    message[0] = 'A'; // err

    return 0;
}

int main(){
    int result = action();
    return 0;
}
