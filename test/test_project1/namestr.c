#include "kernel.h"
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
    char temp[MAXLINE][MAXLEN];
    for(int i = 0; i < MAXLINE; i++)
        strcpy(temp[i], mybuf[i]);
    for(int i = 0; i < MAXLINE; i++)
    {
        mybuf[i][0] = i + '0' + 1;
        mybuf[i][1] = ':';
        strcpy(&mybuf[i][2], temp[i]);
    }
    bios_putstr("prog 4 output:\n");
    for(int i = 0; i < MAXLINE; i++)
    {
        bios_putstr(mybuf[i]);
        bios_putchar('\n');
    }
    bios_putstr("Work by WU Molin\n");
    return 0;
}