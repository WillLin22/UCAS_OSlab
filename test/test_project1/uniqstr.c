#include "kernel.h"
int strcmp(const char *str1, const char *str2)
{
    int i;
    for(i = 0; str1[i] && str2[i] && str1[i] == str2[i]; i++)
        ;
    return str1[i] - str2[i];
}
void strcpy(char *dest, const char *src)
{
    int i;
    for(i = 0; src[i]; i++)
        dest[i] = src[i];
    dest[i] = 0;
}
int main()
{
    mybuf = WRITEADDR;
    for(int i = 0; i < MAXLINE - 1; i++)
        for(int j = i + 1; j < MAXLINE; j++)
            if(strcmp(mybuf[i], mybuf[j]) == 0)
                mybuf[j][0] = 0;
    bios_putstr("prog 3 output:\n");
    for(int i = 0; i < MAXLINE; i++)
    {
        bios_putstr(mybuf[i]);
        bios_putchar('\n');
    }
    return 0;
}