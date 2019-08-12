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

   page_start = .;
   page_start = ALIGN(4K);
   
   kernel_after = .;
   
   .bss  : { *(.bss) }

 }