CC = gcc
GCC = g++
LD = ld
AS = nasm

ASFLAGS = -f elf32
CCFLAGS = -fno-stack-protector -m32 -ffreestanding -c -I include/
GCCFLAGS = -fno-rtti -fno-stack-protector -m32 -ffreestanding -c -I include/
LDFLAGS = -m elf_i386

ODIR = obj
BIN  = bin
IDIR = src
SDIR = as
ISO = iso

KERNEL_NAME = nexcorp.bin
KERNEL = $(BIN)/$(KERNEL_NAME)
KERNEL_IMAGE= nexcorp.iso

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

$(ODIR)/%.o: $(IDIR)/%.cpp
	$(GCC) $(GCCFLAGS) $^ -o $@

$(SDIR)/%.s : $(IDIR)/%.c
	$(CC) -g -o $@ $(CCFLAGS) -S $^

$(SDIR)/%.s : $(IDIR)/%.cpp
	$(CC) -g -o $@ $(CCFLAGS) -S $^


$(ODIR)/s_%.o: $(IDIR)/**/%.s
	$(AS) $(ASFLAGS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/**/%.c
	$(CC) $(CCFLAGS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/**/%.cpp
	$(GCC) $(GCCFLAGS) $^ -o $@

$(SDIR)/%.s : $(IDIR)/**/%.c
	$(CC) -g -o $@ $(CCFLAGS) -S $^

$(SDIR)/%.s : $(IDIR)/**/%.cpp
	$(CC) -g -o $@ $(CCFLAGS) -S $^

S_SOURCES = $(shell find $(IDIR) -type f -name *.s -printf "%f\n")
C_SOURCES = $(shell find $(IDIR) -type f -name *.c -printf "%f\n")
CPP_SOURCES = $(shell find $(IDIR) -type f -name *.cpp -printf "%f\n")

S_OBJECTS = $(patsubst %.s, $(ODIR)/s_%.o,$(S_SOURCES))
C_OBJECTS = $(patsubst %.c, $(ODIR)/%.o,$(C_SOURCES))
CPP_OBJECTS = $(patsubst %.cpp, $(ODIR)/%.o,$(CPP_SOURCES))

S_CODE = $(patsubst %.c, $(SDIR)/%.s,$(C_SOURCES))
S_CODE += $(patsubst %.cpp, $(SDIR)/%.s,$(CPP_SOURCES))
$(KERNEL): $(IDIR)/link.ld $(CPP_OBJECTS) $(C_OBJECTS) $(S_OBJECTS) 
	$(LD) $(LDFLAGS) -T $(IDIR)/link.ld -o $(KERNEL) $(S_OBJECTS) $(C_OBJECTS) $(CPP_OBJECTS)

clean:
	rm -rf $(ODIR)
	rm -rf $(BIN)
	rm -rf $(SDIR)
	rm -rf $(ISO)
run: all
	qemu-system-x86_64 -kernel $(KERNEL)
install: all
	sudo cp $(KERNEL) /boot/$(KERNEL_NAME)

iso: all
	rm -rf $(ISO)
	mkdir $(ISO)
	mkdir $(ISO)/boot
	mkdir $(ISO)/boot/grub
	cp $(KERNEL) $(ISO)/boot/
	echo 'set timeout=20' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "NexCorp OS"' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/$(KERNEL_NAME)' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(KERNEL_IMAGE) iso
	rm -rf $(ISO)
	mkdir $(ISO)
	mv $(KERNEL_IMAGE) $(ISO)/
runvm: iso
	VBoxManage startvm "NexCorpOS"
install-pen: iso
	sudo dd if=$(ISO)/$(KERNEL_IMAGE) of=/dev/$(shell lsblk -d | grep 'sd' | tail -n +3 |rofi -dmenu | awk '{print $$1}')
dis: all $(SDIR) $(S_CODE)

flist: all
	nm "$(KERNEL)" | grep 'T' | awk '{print $$3}'
