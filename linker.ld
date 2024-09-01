ENTRY(_start)

SECTIONS {
    . = 2M; /* code starting address */
    .boot : {
        KEEP(*(.multiboot_header))
    }
    .text : {
        *(.text)
    }
}
