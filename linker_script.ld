SECTIONS {
    .startup 0x08000000 : { KEEP(*(.startup)) }
    .text               : {      *(.text)     }
}


