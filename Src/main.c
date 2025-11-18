#include <stdio.h>
#include "./database/data.h"

int main(void)
{
    Database current;
    set_HRmax(&current, 195);
    printf("Hello, World!\n");
    printf("Also\nCongratulations your code is not borked: %d\n", current.HRmax);
    return 0;
}