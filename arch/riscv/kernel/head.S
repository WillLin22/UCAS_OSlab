/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 */

#include <asm.h>
#include <csr.h>

#define KERNEL_STACK		0x50500000

.section ".entry_function","ax"
ENTRY(_start)
  /* Mask all interrupts */
  csrw CSR_SIE, zero
  csrw CSR_SIP, zero

  /* TODO: [p1-task2] clear BSS for flat non-ELF images */
  la t1, __bss_start    # t1 = i0
  la t2, __BSS_END__    # t2 = n
add1:
  bgeu  t1, t2, over
  sb   x0, 0(t1)
  addi t1, t1, 1
  j  add1
over:
  /* TODO: [p1-task2] setup C environment */
  li  sp, KERNEL_STACK

  # li  a7, 9
  # la  a0, msg
  # li  t0, 0x50150000
  # jalr  ra, 0(t0)

  call main

loop:
  wfi
  j loop

END(_start)

.data 
msg: .string "It's head.S\n"