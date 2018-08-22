CC = gcc
LD = ld
AS = nasm

ASFLAGS = -f elf32
CCFLAGS = -m32 -ffreestanding -c
LDFLAGS = -m elf_i386

ODIR = obj
BIN  = bin
IDIR = src

all: $(ODIR) $(BIN) build

$(ODIR):
		mkdir $(ODIR)
$(BIN):
		mkdir $(BIN)

$(ODIR)/s_%.o: $(IDIR)/%.s
	$(AS) $(ASFLAGS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/%.c
	$(CC) $(CCFLAGS) $^ -o $@

S_SOURCES = $(shell find $(IDIR) -type f -name *.s -printf "%f\n")
C_SOURCES = $(shell find $(IDIR) -type f -name *.c -printf "%f\n")

S_OBJECTS = $(patsubst %.s, $(ODIR)/s_%.o,$(S_SOURCES))
C_OBJECTS = $(patsubst %.c, $(ODIR)/%.o,$(C_SOURCES))

build: $(IDIR)/link.ld $(C_OBJECTS) $(S_OBJECTS)
	$(LD) $(LDFLAGS) -T $(IDIR)/link.ld -o $(BIN)/nexcorp.bin $(S_OBJECTS) $(C_OBJECTS)

clean:
	rm -r $(ODIR)
	rm -r $(BIN)
run: all
	qemu-system-x86_64 -kernel bin/nexcorp.bin
install: bin/nexcorp.bin
	sudo cp $^ /boot/nexcorp.bin
