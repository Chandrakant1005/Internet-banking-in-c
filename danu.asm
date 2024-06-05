section .data
    msg db 'Hello, World!', 0xA  ; Our message and a newline character
    len equ $ - msg              ; Length of the message

section .text
    global main            ; Entry point for the program

main:
    ; Write the message to stdout
    mov     eax, 4              ; syscall number for sys_write
    mov     ebx, 1              ; file descriptor 1 (stdout)
    mov     ecx, msg            ; pointer to the message
    mov     edx, len            ; message length
    int     0x80                ; call kernel

    ; Exit the program
    mov     eax, 1              ; syscall number for sys_exit
    xor     ebx, ebx            ; exit code 0
    int     0x80                ; call kernel