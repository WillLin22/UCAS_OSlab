#ifndef __INCLUDE_LOADER_H__
#define __INCLUDE_LOADER_H__

#include <type.h>

uint64_t load_task_img(char *name, int tasknum, int *taskidx, int *baseaddrs);

#endif