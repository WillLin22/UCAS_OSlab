#include <os/task.h>
#include <os/string.h>
#include <os/kernel.h>
#include <type.h>
#define PROGRAM_LOAD_ADDR      0x52000000   /* 程序加载内存位置 */
#define PROGRAM_ALLOC_SIZE     0x10000
#define SPACE 32
uint64_t load_task_img(char *name, short tasknum, int *taskidx, int *baseaddrs)
{
    /**
     * TODO:
     * 1. [p1-task3] load task from image via task id, and return its entrypoint
     * 2. [p1-task4] load task via task name, thus the arg should be 'char *taskname'
     */
    int tsknum = 0;
    char *last = name;
    int program_ldaddr = PROGRAM_LOAD_ADDR;
    for(; tsknum < TASK_MAXNUM; name++)
    {
        if(*name == 32 || *name == 0)
        {
            char c = *name;
            *name = 0;
            while(*(name + 1) == 32) *(++name) = 0;
            int i;
            for(i = 0; i < tasknum; i++)
                if(strcmp(last, tasks[i].name) == 0)
                {
                    program_ldaddr += i * PROGRAM_ALLOC_SIZE;
                    sd_read(program_ldaddr, tasks[i].nsec, tasks[i].init_sec);
                    taskidx[tsknum] = i;
                    baseaddrs[tsknum] = program_ldaddr;
                    program_ldaddr = PROGRAM_LOAD_ADDR;
                    tsknum++;
                    break;
                }
            if(i >= tasknum)
            {
                bios_putstr("Error: executable file not found!\n");
                return 0;//直接退出 而不是执行成功匹配程序
            }
            last = name + 1;
            if(c == 0) break;
        }
        if(*last == 0) break;
    }
    if(tsknum >= TASK_MAXNUM) 
    {
        bios_putstr("Error: too much executable files!\n");
        return 0;
    }
    return tsknum;
}