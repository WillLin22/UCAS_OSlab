#ifndef __INCLUDE_KERNEL_H__
#define __INCLUDE_KERNEL_H__

#define KERNEL_JMPTAB_BASE 0x51ffff00
#define WRITEADDR 0x58000000
#define MAXLINE 5
#define MAXLEN 64
#define ENTER 13
#define BACK  127
char (*mybuf)[MAXLEN];
typedef enum {
    CONSOLE_PUTSTR,
    CONSOLE_PUTCHAR,
    CONSOLE_GETCHAR,
    NUM_ENTRIES
} jmptab_idx_t;

static inline long call_jmptab(long which, long arg0, long arg1, long arg2, long arg3, long arg4)
{
    unsigned long val = \
        *(unsigned long *)(KERNEL_JMPTAB_BASE + sizeof(unsigned long) * which);
    long (*func)(long, long, long, long, long) = (long (*)(long, long, long, long, long))val;

    return func(arg0, arg1, arg2, arg3, arg4);
}

static inline void bios_putstr(char *str)
{
    call_jmptab(CONSOLE_PUTSTR, (long)str, 0, 0, 0, 0);
}

static inline void bios_putchar(int ch)
{
    call_jmptab(CONSOLE_PUTCHAR, (long)ch, 0, 0, 0, 0);
}

static inline int bios_getchar(void)
{
    return call_jmptab(CONSOLE_GETCHAR, 0, 0, 0, 0, 0);
}


#endif