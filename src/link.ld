/*
*  link.ld
*/
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

/*
 * Heap Size
 */

heap_size = 0x100000;
secure_offset = 0x10000;
SECTIONS
 {
   . = 0x100000;
   kernel_start = .;

   .text : { *(.text) }
   .data : { *(.data) }

   .heap : {
      heap_bottom = .;
	    . = . + heap_size;
	    heap_top = .;
   }

   kernel_after = .;
   
   .bss  : { *(.bss) }

 }