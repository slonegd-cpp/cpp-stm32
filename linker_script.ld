MEMORY {
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
}

SECTIONS {
    .startup : { KEEP(*(.startup)) } >FLASH
    .text    : {      *(.text)     } >FLASH
}


