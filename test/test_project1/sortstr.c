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
void swap(char *str1, char *str2)
{
    char temp[MAXLEN];
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}
int main()
{
    mybuf = WRITEADDR;
    for(int i = 1; i < MAXLINE; i++)
    {
        char temp[MAXLEN];
        strcpy(temp, mybuf[i]);
        int j;
        for(j = i - 1; j >= 0 && strcmp(mybuf[j], temp) > 0; j--)
        {
            strcpy(mybuf[j + 1], mybuf[j]);
        }
        strcpy(mybuf[j + 1], temp);
    }
    bios_putstr("prog 2 output:\n");
    for(int i = 0; i < MAXLINE; i++)
    {
        bios_putstr(mybuf[i]);
        bios_putchar('\n');
    }
    return 0;
}

