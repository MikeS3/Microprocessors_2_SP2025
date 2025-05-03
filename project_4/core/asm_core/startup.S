.syntax unified
.thumb
.cpu cortex-m0plus

.section .text.__reset
.type __reset, %function
.global __reset
__reset:
    /* copy data */
    ldr r0, =__data_start
    ldr r1, =__data_end
    ldr r2, =__data_load_start
1:  cmp r0, r1
    beq 1f
    ldr r3, [r2]
    str r3, [r0]
    adds r2, #4
    adds r0, #4
    b 1b
    /* clear bss */
1:  ldr r0, =__bss_start
    ldr r1, =__bss_end
    eors r2, r2
1:  cmp r0, r1
    beq 1f
    str r2, [r0]
    adds r0, #4
    b 1b
    /* constructors array */
1:  ldr r4, =__ctors_start
    ldr r5, =__ctors_end
1:  cmp r4, r5
    beq 1f
    ldr r6, [r4]
    blx r6
    adds r4, #4
    b 1b
    /* call kmain */
1:  bl kmain
    /* destructors array */
    ldr r4, =__dtors_start
    ldr r5, =__dtors_end
1:  cmp r4, r5
    beq 1f
    ldr r6, [r4]
    blx r6
    adds r4, #4
    b 1b
    /* idle loop */
1:  wfe
    b 1b
.size __reset, . - __reset

.section .text.__bad_interrupt
.type __bad_interrupt, %function
.global __bad_interrupt
__bad_interrupt:
1:  wfe
    b 1b
.size __bad_interrupt, . - __bad_interrupt

.macro vector_stub number
    .weak __vector_\number
    .set __vector_\number, __bad_interrupt
.endm

/* core vectors */
.irp vect,2,3,11,14,15
    .weak __vector_\vect
    .set __vector_\vect, __bad_interrupt
.endr

/* external vectors */
vector_stub 16
vector_stub 17
vector_stub 18
vector_stub 19
vector_stub 20
vector_stub 21
vector_stub 22
vector_stub 23
vector_stub 24
vector_stub 25
vector_stub 26
vector_stub 27
vector_stub 28
vector_stub 29
vector_stub 30
vector_stub 31
vector_stub 32
vector_stub 33
vector_stub 34
vector_stub 35
vector_stub 36
vector_stub 37
vector_stub 38
vector_stub 39
vector_stub 40
vector_stub 41
vector_stub 42
vector_stub 43
vector_stub 44
vector_stub 45
vector_stub 46
vector_stub 47