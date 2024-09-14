#include <common.h>
#include <asm.h>
#include <os/kernel.h>
#include <os/task.h>
#include <os/string.h>
#include <os/loader.h>
#include <type.h>

#define ENTER 13
#define BACKSPACE 127
#define SPACE 32

#define VERSION_BUF 50
#define BASE_ADDR 0x50200000
#define SECSZ 512
#define TASKINFO_INIT_SEC_ADDR 0x1f4        /* 起始扇区(short) */
#define TASKINFO_NSEC_ADDR     0x1f6        /* 所占扇区数量(short) */
#define TASKINFO_OFFSET_ADDR   0x1f8        /* 起始扇区偏移(short) */
#define TASKINFO_NUMS_ADDR     0x1fa        /* taskinfo任务数(short) */
#define OS_SIZE_LOC            0x1fc        /* kernel扇区数(short) */
#define PROGRAM_LOAD_ADDR      0x52000000   /* 程序加载内存位置 */
#define TASKINFO_LOAD_ADDR     0x59000000   /* taskinfo所在扇区位置 */
int version = 2; // version must between 0 and 9
char buf[VERSION_BUF];

// Task info array
task_info_t tasks[TASK_MAXNUM];
short tasknum;

static int bss_check(void)
{
    for (int i = 0; i < VERSION_BUF; ++i)
    {
        if (buf[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}

static void init_jmptab(void)
{
    volatile long (*(*jmptab))() = (volatile long (*(*))())KERNEL_JMPTAB_BASE;

    jmptab[CONSOLE_PUTSTR]  = (long (*)())port_write;
    jmptab[CONSOLE_PUTCHAR] = (long (*)())port_write_ch;
    jmptab[CONSOLE_GETCHAR] = (long (*)())port_read_ch;
    jmptab[SD_READ]         = (long (*)())sd_read;
}

static void init_task_info(void)
{
    // TODO: [p1-task4] Init 'tasks' array via reading app-info sector
    // NOTE: You need to get some related arguments from bootblock first
    task_info_t *p = TASKINFO_LOAD_ADDR + *(short *)(BASE_ADDR + TASKINFO_OFFSET_ADDR);
    tasknum = *(short *)(TASKINFO_NUMS_ADDR + BASE_ADDR);
    memcpy(tasks, p, tasknum * sizeof(tasks[0]));
}

/************************************************************/
/* Do not touch this comment. Reserved for future projects. */
/************************************************************/

char buffer[MAXBUFSIZE];
int main(void)
{
    // Check whether .bss section is set to zero
    int check = bss_check();
    
    // Init jump table provided by kernel and bios(ΦωΦ)
    init_jmptab();

    // Init task information (〃'▽'〃)
    init_task_info();

    // Output 'Hello OS!', bss check result and OS version
    char output_str[] = "bss check: _ version: _\n\r";
    char output_val[2] = {0};
    int i, output_val_pos = 0;

    output_val[0] = check ? 't' : 'f';
    output_val[1] = version + '0';
    for (i = 0; i < sizeof(output_str); ++i)
    {
        buf[i] = output_str[i];
        if (buf[i] == '_')
        {
            buf[i] = output_val[output_val_pos++];
        }
    }

    bios_putstr("Hello OS!\n\r");
    bios_putstr(buf);

    // TODO: Load tasks by either task id [p1-task3] or task name [p1-task4],
    //   and then execute them.

    // Infinite while loop, where CPU stays in a low-power state (QAQQQQQQQQQQQ)
    while (1)
    {
        int c;
        int i = 0;
        while(i < MAXBUFSIZE)
        {
            while((c = bios_getchar()) == -1)
                ;
            switch (c) {
            case ENTER:
                bios_putchar('\n');
                break;
            case BACKSPACE:
                if(i > 0)
                {
                    i--;
                    bios_putchar('\b');
                    bios_putchar(' ');
                    bios_putchar('\b'); 
                }
                break;
            default:
                buffer[i] = c;
                bios_putchar(c);
                i++;
                break;
            }
            if(c == ENTER) break;
        }
        if(i >= MAXBUFSIZE) bios_putstr("max len exceeded!\n");
        buffer[i] = 0;
        int taskidx[TASK_MAXNUM];
        int baseaddrs[TASK_MAXNUM];
        int num = load_task_img(buffer, tasknum, taskidx, baseaddrs);
        for(int i = 0; i < num; i++)
        {
            int addr;
            addr = baseaddrs[i] + tasks[taskidx[i]].init_offset;
            void (*call_prog)() = (void (*)())addr;
            call_prog();
            // asm volatile(
            //     "jalr ra, 0(%0)"
            //     :
            //     :"r"(addr)
            // );
        }
        // int addr;
        // addr = baseaddrs[0] + tasks[taskidx[0]].init_offset;
        // void (*call_prog)() = (void (*)())addr;
        // call_prog();
        // void (*entry)(void) = (void (*)(void))(baseaddrs[0])
    }

    return 0;
}
