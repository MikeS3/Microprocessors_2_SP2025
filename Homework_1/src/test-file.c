/* use GCC extension to put this function in the .bootloader section */
__attribute__((.section(".bootloader")))
void __bootloader(void) {
	/* we are only using this for testing! */
	while(1) { ; }
}

/* the entry point for C programs */
int main(void) {
	return 0;
}

