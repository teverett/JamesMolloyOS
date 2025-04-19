ENTRY(start)

STACK_SIZE = 0x100;

SECTIONS
{
    .mbheader 0x100000 :
    {
        *(.mbheader)
    }
    .text :
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
        . = ALIGN(4096);
    }

    .stack (NOLOAD):
    {
        . = ALIGN(8);
        stack_bottom = .;
        . = . + STACK_SIZE;
        stack_top = .;
        . = ALIGN(8);
    } 

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }


    end = .; _end = .; __end = .;
}
