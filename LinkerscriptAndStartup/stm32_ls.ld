/*Specifying the firmware's entry point*/
ENTRY(Reset_Handler)

/*Detailing the available memory*/
MEMORY
{
	FLASH(rx) : ORIGIN = 0x8000000, LENGTH = 512K
	SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/*Specifiying the necessary heap and stack sizes*/

_max_heap_size = 0x200;
_max_stack_size = 0x400;

/*Defining output sections*/
SECTIONS
{
	.text : 
	{
		. = ALIGN(4);
		 *(.isr_vector_tbl) /*merge all .isr_vector_tbl sections of input files*/
		 *(.text)           /*merge all .text sections of input files*/
		 *(.rodata)         /*merge all .rodata sections of input files*/
		 . = ALIGN(4);
		_etext = .;         /*create a global symbol to hold end of text section*/  
	}>FLASH
	
	.data : 
	{
		. = ALIGN(4);
		_sdata = .;     /*Create a global symbol ot hold the start of data*/
		*(.data)
		. = ALIGN(4);   /*Create a global symbol to hold end of data*/
		_edata  = .;
	} > SRAM AT > FLASH /* >(vma) AT > (lma) */
	
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;		
	}>SRAM
	
}