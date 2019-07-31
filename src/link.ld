/*
*  link.ld
*/
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

/*
 * Heap Size
 */

heap_size = 0x100000;
page_directory_size = 0x400;
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
   
   .page : {
     page_bottom = .;
     . = . + page_directory_size;
     page_top = .;
   }

   page_start = .;
   page_start = ALIGN(4K);
   
   kernel_after = .;
   
   .bss  : { *(.bss) }

 }