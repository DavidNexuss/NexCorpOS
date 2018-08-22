/*
*  link.ld
*/
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

/*
 * Heap Size
 */

heap_size = 0x100000;

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

   .bss  : { *(.bss) }

   kernel_after = .;
 }
