/* for this homework you want to look into the ld manual
 * specifically look in section 3:
 * https://sourceware.org/binutils/docs/ld/Scripts.html
 */

/* TODO: set the output architecture to arm using OUTPUT_ARCH */

/* TODO: set the output format using OUTPUT_FORMAT */

/* TODO: set the entry point to __reset using ENTRY */

/* memories */
MEMORY {
	/* add the memory region for the bootloader */
	/* TODO: complete */
	BOOTLOADER(rwx) :	ORIGIN = ????, LENGTH = ????
	/* TODO: add memories for FLASH and SRAM */
}

/* sections */
SECTIONS {
	/* add the bootloader section into BOOTLOADER memory */
	.bootloader : {
		/* there will be no references to symbols in this section outside of
		 * it, ensure the linker does not garbage collect us; use KEEP to have
		 * it keep everything it puts here */
		/* TODO: complete, add the contents of the bootloader ssection */
		KEEP(????)
		/* ensure that the end of the section is 256 byte aligned */
		. = ALIGN(256)
	} > BOOTLOADER AT > FLASH
	/* the above mirrors a copy in flash */

	/* provide the symbol __bl2_checksum to be at the end of the load address
	 * of the bootloader in the FLASH memory, minus 4 bytes; we need to use an
	 * external tool to put a checksum in here */
	__bl2_checksum = LOADADDR(.bootloader) + LENGTH(BOOTLOADER) - 4;

	/* TODO: add .vector_table section and its contents to FLASH */
	.vectors : {
		/* TODO: add contents of the vector table, ensure that linker garbage
		 * collection does not eat it away */
	} > ????

	/* TODO: complete the .text section */
	.text : {
		/* TODO: add the contents of the .text section */
		/* provide a hidden symbol to mark the end of the .text section */
		PROVIDE_HIDDEN(__text_end = .);
	} > ????
	/* TODO: above, put it in FLASH */

	/* TODO: place .rodata in FLASH */

	/* TODO: complete the .data section */
	.data : {
		/* ensure the start is 4 byte (word) aligned */
		. = ALIGN(4);
		/* TODO: provide __data_start to point here */
		/* TODO: add the contents of the data section */
		/* TODO: ensure word alignment and provide a symbol for __data_end */
	} > ????
	/* TODO: above, put it in SRAM, don't forget to mirror to FLASH */

	/* TODO: provide symbol for __data_load_start located at the address in
	 * FLASH where the initializataion data is found */

	/* TODO: add the .bss section with the required symbols; ensure alignment
	 * as well as placement in SRAM */

	/* TODO: provide a symbol for __ram_end which points to the end of the SRAM
	 * memory */
}
