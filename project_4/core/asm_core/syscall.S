#include <interrupt.h>

	.syntax unified
	.thumb

/* !!!: \reg2 gets trashed */
.macro get_sp_and_offset reg1, reg2
	ldr \reg1, [sp, #0]	/* value of lr is now in \reg1 */
	movs \reg2, #(1 << 2)	/* bit 2 is the S bit */
	tst \reg1, \reg2	/* check which stack we are using as return */
	bne 1f
	mrs \reg1, psp		/* we are using psp */
	b 2f
1:	mrs \reg1, msp		/* we are using msp instead */
2:
.endm


/** syscall()
 *	r12:		syscall number
 *	r0 - r3:	arguments
 */
ISR SVCALL_vect
	push {r4, r5, lr}
	mov r4, r12
	ldr r5, .Lsyscall_table_size
	cmp r4, r5
	blx .Lvalid_syscall          /* valid syscall index */
	/* conditionally dispatch syscall */
	/* TODO: ensure that the system call number is valid and dispatch it */
	/* TODO: if the system call is not valid ensure we return -1 */
	/* set up return in stack */
	

	movs    r0, #0
	mvns    r0, r0		//set r0 to -1 without syntrax error
	b .Lreturn_from_svc

.Lvalid_syscall:                 // Label for valid syscall path
	ldr r5, =.Lsyscall_table     // r5 ← address of syscall table
	lsls r4, 12              // r12 has syscall# in it
	adds r5, r5, r4              // r5 = base address + offset r4 is being used as offset
	ldr r5, [r5, r4]                 // r5 ← contents at that address (i.e. function pointer)
	blx r5                       // branch to function in r5 (syscall function)


.Lreturn_from_svc:
	
	get_sp_and_offset r4, r5	/* r4 contains the stack we are using */
	str r0, [r4, #12]	/* the stack frame at this point has:
						 * +00: lr
						 * +04: r5
						 * +08: r4
						 * +0c: r0
						 * ...
						 * we overwrite r0
						 */
	/* and return */
	pop {r4, r5, pc}

	.align 4
	.Lsyscall_table:
#include <syscall_list.h>
	.Lsyscall_table_size: .word (. - .Lsyscall_table)

endisr SVCALL_vect
