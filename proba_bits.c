
//-------------- print_bits ----------------
// Распечатать число в двоичном виде. len -длина(бит).
int print_bits(int val, int len)
{
    int i, maska = 1 << (len - 1);
    //if((val >> len) != 0) printf("Error: val=%d; len=%d; ", val, len);
    for(i=0; i<len; i++){
        if((val & maska) != 0) printf("1");
        else printf("0");
        maska = maska >> 1;
    }
    return(0);
}

//------------- print_bit_text -------------

int print_bit_text(int val, int len, const char *text)
{
    printf("%s   ", text);
    print_bits(val, len);
    printf("\n");
    return(0);
}
