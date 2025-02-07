	.section .vector_table
__vector_table:
	/* Section B1.5.2 of the ARMv6-M Architecture Reference Manual */
	.word	__ram_end /* loaded into msp by the bootloader */
	.word	__reset		/* reset vector */
	.word	__vector_2	/* Non-Maskable Interrupt */
	.word	__vector_3/* TODO: core vector 3, HardFault */
	/* from 3 to 10: vectors are reserved, point to __bad_interrupt */
	.word	/* TODO: core vector 12, SVCall */
	/* TODO: fill in missing 13 to 15 */

	/* TODO: add external vectors 16 to 47 */
	/* HINT: use .altmacro, .macro, and .rept to ease your workload */
