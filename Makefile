CC = gcc
LD = ld
AS = nasm

ASFLAGS = -f elf32
CCFLAGS = -fno-stack-protector -m32 -ffreestanding -c
LDFLAGS = -m elf_i386

ODIR = obj
BIN  = bin
IDIR = src
SDIR = as

KERNEL_NAME = nexcorp.bin
KERNEL = $(BIN)/$(KERNEL_NAME)

all: $(ODIR) $(BIN) $(KERNEL)

$(ODIR):
		mkdir $(ODIR)
$(BIN):
		mkdir $(BIN)
$(SDIR):
		mkdir $(SDIR)

$(ODIR)/s_%.o: $(IDIR)/%.s
	$(AS) $(ASFLAGS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/%.c
	$(CC) $(CCFLAGS) $^ -o $@

$(SDIR)/%.s : $(IDIR)/%.c
	$(CC) -g -o $@ $(CCFLAGS) -S $^

S_SOURCES = $(shell find $(IDIR) -type f -name *.s -printf "%f\n")
C_SOURCES = $(shell find $(IDIR) -type f -name *.c -printf "%f\n")

S_OBJECTS = $(patsubst %.s, $(ODIR)/s_%.o,$(S_SOURCES))
C_OBJECTS = $(patsubst %.c, $(ODIR)/%.o,$(C_SOURCES))
S_CODE = $(patsubst %.c, $(SDIR)/%.s,$(C_SOURCES))

$(KERNEL): $(IDIR)/link.ld $(C_OBJECTS) $(S_OBJECTS)
	$(LD) $(LDFLAGS) -T $(IDIR)/link.ld -o $(BIN)/nexcorp.bin $(S_OBJECTS) $(C_OBJECTS)

clean:
	rm -rf $(ODIR)
	rm -rf $(BIN)
	rm -rf $(SDIR)
run: all
	qemu-system-x86_64 -kernel bin/nexcorp.bin
install: all
	sudo cp $(KERNEL) /boot/$(KERNEL_NAME)
dis: all $(SDIR) $(S_CODE)
