CC = gcc
LD = ld
AS = nasm

ASFLAGS = -f elf32
CCFLAGS = -m32 -c
LDFLAGS = -m elf_i386

ODIR = obj
BIN  = bin
IDIR = src

$(ODIR)/%.o: $(IDIR)/%.s
	$(AS) $(ASFLAGS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/%.c
	$(CC) $(CCFLAGS) $^ -o $@ 

S_SOURCES = $(shell find $(IDIR) -type f -name *.s -printf "%f\n")
C_SOURCES = $(shell find $(IDIR) -type f -name *.c -printf "%f\n")

S_OBJECTS = $(patsubst %.s, $(ODIR)/%.o,$(S_SOURCES))
C_OBJECTS = $(patsubst %.c, $(ODIR)/%.o,$(C_SOURCES))

build: $(IDIR)/link.ld $(C_OBJECTS) $(S_OBJECTS)
	$(LD) $(LDFLAGS) -T $(IDIR)/link.ld -o $(BIN)/kernel.bin $(S_OBJECTS) $(C_OBJECTS)

dir: 
	mkdir $(ODIR)/
	mkdir $(BIN)/
	
clean:
	rm -r $(ODIR)
	rm -r $(BIN)
run:
	qemu-system-x86_64 -kernel bin/kernel.bin
