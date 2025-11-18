#include "recommends.h"
#include <stdio.h>

void recommend(int a, int b, int c, int d, int e, int f){
    char choicearray[5];

    /*
    Chars should have differing suggestions for how to improve/procede in running
    Should props be assigned from a .txt file, or maybe not idk
    Look at Workshop 2 for how it's done there
    */

    int x;
    char y;
/*  */
    /*
    Some code to find x which is used to find the outcome in switch
    Maybe ther should be multiple switch's and then a complete output would be multiple stichted
    together variables? Might be to much of an ask tho...
    */

    switch(x){
        case 1 : 
            y = choicearray[0];
            break;
        case 2 :
            y = choicearray[1];
            break;
        case 3 :
            y = choicearray[2];
            break;
        case 4 :
            y = choicearray[3];
            break;
        case 5 :
            y = choicearray[4];
            break;
        default: printf("Something went wrong");
    }
}
