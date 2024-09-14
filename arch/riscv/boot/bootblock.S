#include <asm/biosdef.h>

// os size location (os_size could be sectors [p1-task3] or bytes [p1-task4])
.equ taskinfo_init_sec_addr, 	0x502001f4
.equ taskinfo_nsec_addr, 		0x502001f6
.equ taskinfo_offset_addr, 		0x502001f8
.equ taskinfo_nums_addr, 		0x502001fa
.equ os_size_loc, 				0x502001fc
.equ taskinfo_load_addr, 		0x59000000

// kernel address (move kernel to here, and jmp here to start kernel)
.equ kernel, 					0x50201000

// BIOS function entry (jump here to use BIOS APIs)
.equ bios_func_entry, 			0x50150000

.text
.global main

main:
	// fence on all memory and I/O
	fence

	// TODO: [p1-task1] call BIOS to print string "It's bootblock!"
	li a7, BIOS_PUTSTR
	la a0, msg
	li t0, bios_func_entry
	jalr ra, 0(t0)
	// TODO: [p1-task2] call BIOS to read kernel in SD card
	li a7, BIOS_SDREAD
	li a2, 1 						# 第二个扇区
	li t1, os_size_loc
	lh a1, 0(t1)					# 录*(short*)os_size_loc个扇区
	li a0, kernel					# 录到kernel所在位置
	jalr ra, 0(t0)
	// TODO: [p1-task4] load task-related arguments and pass them to kernel
	li t1, taskinfo_init_sec_addr
	lh a2, 0(t1)					# 录*(short *)init_sec_addr个扇区
	li t1, taskinfo_nsec_addr
	lh a1, 0(t1)					# 录*(short *)nsec_addr个扇区
	li a0, taskinfo_load_addr		# 录于0x59000000
	jalr ra, 0(t0)


	// TODO: [p1-task2] jump to kernel to start UCAS-OS
	li t0, kernel
	jr t0
	/************************************************************/
	/* Do not touch this comment. Reserved for future projects. */
	/************************************************************/
// while(1) --> stop here
stop:
	j stop
	nop

.data

msg: .string "It's a bootloader...\n\r"

