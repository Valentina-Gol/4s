code    segment
        assume cs:code, ds:code, ss:nothing
        org 100h

start: 
jmp begin

str_install db 'loading interruption',0dh,0ah,'$'
str_already_install db 'interraption is already loaded',0dh,0ah,'$'
str_not_install db 'interruption is not installed',0dh,0ah,'$'
str_restore db 'unloading interruption',0dh,0ah,'$'       

my_interrupt proc far              
    jmp my_interrupt_begin

my_interrupt_data:
signature dw 6666h
my_interrupt_stack db 100h dup(0)
keep_ip dw 0
my_interrupt_keep_int_cs dw 0
keep_ss dw 0
keep_sp dw 0

        ; code
my_interrupt_begin:
    push ds
    push ax
    mov ax, cs
    mov ds, ax

    mov keep_ss, ss
    mov keep_sp, sp

    mov ax, cs
    mov ss, ax
    mov sp, offset my_interrupt_stack
    add sp, 100h

    push es
    push bp
    push cx
    push bx
    push dx
    push di
    push si
    
    in al, 60h
    cmp al, 11h
    je my_interrupt_w
    cmp al, 12h
    je my_interrupt_e
    cmp al, 13h
    je my_interrupt_r
    jmp my_interrupt_default
    my_interrupt_default:
    pushf
    call dword ptr keep_ip
    jmp finish

my_interrupt_w:
    mov cl, '1'
    jmp handler
my_interrupt_e:
    mov cl, '2'
    jmp handler
my_interrupt_r:
    mov cl, '3'
    jmp handler    

handler:
    in al, 61h
    mov ah, al
    or al, 80h
    out 61h, al
    xchg ah, al
    out 61h, al
    mov al, 20h
    out 20h, al
    
    mov ah, 05h 
    mov ch, 00h
    int 16h
    jmp finish

finish:
    pop si
    pop di
    pop dx
    pop bx
    pop cx
    pop bp
    pop es

    mov ss, keep_ss
    mov sp, keep_sp
    pop ax
    pop ds

    mov al, 20h
    out 20h, al
    iret
my_interrupt endp                


wrd_to_dec proc near            
	push bx
    push dx
    push di
    push si
    push ax

  	mov bx, 10
  	loop1:
    div bx
    add dl, '0'
    mov [di], dl
    xor dx, dx
    dec di
    cmp ax, 0
    jne loop1

    cmp si, 0
    je wrd_to_dec_end
    cmp si, di
    jge wrd_to_dec_end
    wrd_to_dec_prefix_loop:
    mov dl, '0'
    mov [di], dl
    dec di
    cmp di, si
    jl wrd_to_dec_prefix_loop

wrd_to_dec_end:
    pop ax
    pop si
    pop di
    pop dx
	pop bx
  	ret
wrd_to_dec endp          


load_in_memory_int proc near             
    mov ah, 35h
    mov al, 09h
    int 21h
    mov keep_ip, bx
    mov my_interrupt_keep_int_cs, es

    mov dx, offset my_interrupt
    mov ah, 25h
    mov al, 09h
    int 21h

    mov dx, offset last_byte
    mov cl, 4
    shr dx, cl
    inc dx
    mov ah, 31h
    int 21h
load_in_memory_int endp 


reload_in_memory_int proc near  
    push dx
    push ds
    push es
    push bx

    mov ah, 35h
    mov al, 09h
    int 21h

    mov ax, es
    mov ds, ax
    mov dx, keep_ip
    mov ax, my_interrupt_keep_int_cs
    mov ds, ax
    mov ah, 25h
    mov al, 09h
    int 21h

    push es
    mov ax, es:[2ch]
    mov es, ax
    mov ah, 49h
    int 21h
    pop es
    int 21h

    pop bx
    pop es
    pop ds
    pop dx
    ret
reload_in_memory_int endp                

chech_is_load proc near   
    push ax
    push bx
    push es

    mov ah, 35h
    mov al, 09h
    int 21h

    push ds
    mov ax, es
    mov ds, ax
    mov ax, signature
    cmp ax, 6666h
    pop ds

    pop es
    pop bx
    pop ax
    ret
chech_is_load endp


begin:
    cmp byte ptr es:[81h+1], '\'
    jne need_load
    cmp byte ptr es:[81h+2], 'u'
    jne need_load
    cmp byte ptr es:[81h+3], 'n'
    jne need_load

    call chech_is_load
    jne int_not_loaded
    call reload_in_memory_int
    mov dx, offset str_restore
    mov ah, 09h
    int 21h
    jmp eeend

int_not_loaded:
    mov dx, offset str_not_install
    mov ah, 09h
    int 21h
    jmp eeend

need_load:
    call chech_is_load
    je inst
    mov dx, offset str_install
    mov ah, 09h
    int 21h
    call load_in_memory_int
    jmp eeend

inst:
    mov dx, offset str_already_install
    mov ah, 09h
    int 21h
    jmp eeend

eeend:
    xor     al,al
    mov     ah,4ch
    int     21h   
 
last_byte:
code    ends
end start
