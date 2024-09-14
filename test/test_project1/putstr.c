#include "kernel.h"

int main()
{
    int c;
    mybuf = WRITEADDR;
    int line = 0;
    char name[MAXLEN];
    while (line < MAXLINE) 
    {
        int i = 0;
        while (i < MAXLEN)
        {
            while ((c = bios_getchar()) == -1) 
                ;
            switch (c) {
            case BACK:
                if(i > 0)
                {
                    i--;
                    bios_putchar('\b');
                    bios_putchar(' ');
                    bios_putchar('\b'); 
                }
                break;
            case ENTER:
                bios_putchar('\n');
                break;
            default:
                name[i++] = c;
                bios_putchar(c);
                break;
            }
            if(c == ENTER) break;
        }
        name[i] = 0;
        for(int j = 0; name[j]; j++)
            mybuf[line][j] = name[j];
        mybuf[line][i] = 0;
        line++;
    }
    bios_putstr("prog 1 output:\n");
    for(int i = 0; i < MAXLINE; i++)
    {
        bios_putstr(mybuf[i]);
        // for(int j = 0; mybuf[i][j]; j++)
        //     bios_putchar(mybuf[i][j]);
        bios_putchar('\n');
    }
    return 0;

}