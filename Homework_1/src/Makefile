TGT := binary.elf

# add all C source files
SRC := $(wildcard *.c)

# add vectors and C runtime
SRC += rp2040-vectors.S rp2040-crt.S

# linker script(s) to use
LDSCRIPTS := rp2040.ld

# object files
OBJ := $(SRC:%.c=%.o)
OBJ := $(OBJ:%.S=%.o)

# set the cross compiler toolchain prefix
CROSS_COMPILE ?= arm-none-eabi-

# and the tools for building
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)gcc
SIZE := $(CROSS_COMPILE)size

# set the compiler flags
CFLAGS := 	-mcpu=cortex-m0plus \
			-ffunction-sections \
			-fdata-sections \
			-Os \
			-mno-thumb-interwork

# set assebler flags
ASFLAGS :=	$(CFLAGS)

# hax to keep make happy and myself unhappy
COMMA=,

# set linker flags
LDFLAGS :=	-Wl,--gc-sections \
			-nostdlib \
			$(addprefix -Wl$(COMMA)-T,$(LDSCRIPTS))

# phony targets are not files
.PHONY: all clean

# the all target depends on the binary we want to build
all: $(TGT)
	$(SIZE) $(TGT)

# the clean target unconditionally removes all build products
# the - in front of the command means ignore any errors the
# command may produce
clean:
	-rm -f $(TGT) $(OBJ)

# the target binary depends on the object files
$(TGT): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# object files from C files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# object files from assembly files
%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $<
