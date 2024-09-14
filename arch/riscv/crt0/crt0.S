#include <asm.h>

.section ".entry_function","ax"
ENTRY(_start)

  /* TODO: [p1-task3] setup C runtime environment for the user program */
  addi sp, sp, -32
  sd ra, 24(sp)

  la t1, __bss_start    # t1 = i0
  la t2, __BSS_END__    # t2 = n
add1:
  bge  t1, t2, over
  sb   x0, 0(t1)
  addi t1, t1, 1
  j  add1
over:
  /* TODO: [p1-task3] enter main function */
  call main
  /* TODO: [p1-task3] finish task and return to the kernel, replace this in p3-task2! */
  ld ra, 24(sp)
  addi sp, sp, 32
  ret
  # li t0, 0x50201000
  # jr 0(t0)
  /************************************************************/
	/* Do not touch this comment. Reserved for future projects. */
	/************************************************************/
// while(1) loop, unreachable here
loop:
    wfi
    j loop

END(_start)
# .data 
# msg: .string "It's crt0.S\n"
