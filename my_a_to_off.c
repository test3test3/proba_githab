
//   /home/test/SI/SI/parser_int/parser_off.c
//   cd /home/test/SI/SI/parser_int/
//   gcc parser_off.c -o parser_off.cgi -Wall -Werror -O3
//   ./parser_off.cgi

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//------------------- my_a_to_off ---------------------
off_t
my_a_to_off(const char *str, int *err)
{
    off_t  s, d;
    const char *p1;
    int sig=0, digit;
    off_t MY_MIN_OFF_T, MY_MAX_OFF_T = 1;

    //while((MY_MAX_OFF_T << 1) > 0){ MY_MAX_OFF_T = (MY_MAX_OFF_T << 1) | 1;}
    //MY_MIN_OFF_T = -MY_MAX_OFF_T;

    int i, bits = sizeof(off_t) * 8;
    for(i=0; i < (bits - 2); i++){ MY_MAX_OFF_T = (MY_MAX_OFF_T << 1) | 1;}
    MY_MIN_OFF_T = -MY_MAX_OFF_T;

    *err = 0;
    p1=str;
    s=0;
    while(*p1==' ') p1++;
    if(*p1=='-'){ sig=1; p1++;}
    else if(*p1=='+') p1++;
    if(sig==0){
        d = MY_MAX_OFF_T / 10;
        while(*p1>='0' && *p1<='9'){
            digit = ((*p1++) - '0');
            if(s > d){ *err = 1; break;}
            s = (s * 10);
            if((MY_MAX_OFF_T - s) < digit){ *err = 1; break;}
            s += digit;
        }
    }
    else{
        d = MY_MIN_OFF_T / 10;
        while(*p1>='0' && *p1<='9'){
            digit = ((*p1++) - '0');
            if(s < d){ *err = 1; break;}
            s = (s * 10);
            if((MY_MIN_OFF_T - s) > (-digit)){ *err = 1; break;}
            s -= digit;
        }
    }
    return(s);
}

//----------------- main -----------------------

int main()
{
    off_t d;
    int err;
    const char *ptr;
    char str[200];

    while(1){
        ptr = fgets(str, sizeof(str), stdin);
        if(ptr==NULL) exit(0);

        d = my_a_to_off(str, &err);
        printf("%lld; err = %d\n\n", (long long int)d, err);
    }
    exit(0);
}

// 9223372036854775807  max off_t
//-9223372036854775808  min off_t
// 2147483647 max off_t
