void lift_uart_and_io_bank0_reset(void) {
    // Step 1: Clear reset bits for UART0 and IO_BANK0
    RESETS.reset &= ~((1 << RESETS_uart0) | (1 << RESETS_reset_io_bank0));

    // Step 2: Wait until reset is done
    while (!(RESETS.reset_done & (1 << RESETS_reset_done_io_bank0))) {
        tight_loop_contents();
    }
}
