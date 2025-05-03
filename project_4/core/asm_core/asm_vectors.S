.syntax unified
.thumb
.cpu cortex-m0plus

.section .vector_table, "a"
.global __vector_table
__vector_table:
    .word __ram_end
    .word __reset
    .word __vector_2
    .word __vector_3
.rept 7
    .word __bad_interrupt
.endr
    .word __vector_11
    .word __bad_interrupt
    .word __bad_interrupt
    .word __vector_14
    .word __vector_15

    .word __vector_16
    .word __vector_17
    .word __vector_18
    .word __vector_19
    .word __vector_20
    .word __vector_21
    .word __vector_22
    .word __vector_23
    .word __vector_24
    .word __vector_25
    .word __vector_26
    .word __vector_27
    .word __vector_28
    .word __vector_29
    .word __vector_30
    .word __vector_31
    .word __vector_32
    .word __vector_33
    .word __vector_34
    .word __vector_35
    .word __vector_36
    .word __vector_37
    .word __vector_38
    .word __vector_39
    .word __vector_40
    .word __vector_41
    .word __vector_42
    .word __vector_43
    .word __vector_44
    .word __vector_45
    .word __vector_46
    .word __vector_47

.size __vector_table, . - __vector_table