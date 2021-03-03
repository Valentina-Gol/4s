stacks segment  STACK
    db 256 dup(?)
stacks ends  

data segment

 ; хранится в обработчике прерываний
    KEEP_CS DW 0 ; для хранения сегмента
    KEEP_IP DW 0 ; и смещения вектора прерывания

isBoot dw 0
isUnBoot dw 0
memAdrPsp dw 0
vect dd 0
PSP dw 0

str_int_mem db 'Обработчик прерывания резидентен в памяти', 0AH, 0DH, '$'
str_in_yes db 'Установлен обработчик прерываний', 0AH, 0DH,'$'
str_in_already db 'Обработчик преывания уже установлен', 0AH, 0DH, '$'
str_unb db 'Обработчик прерываний выгружен из памяти', 0AH, 0DH, '$'
str_empty db '      ', 0AH, 0DH, '$'

data ends


code segment

    ASSUME CS:code, DS:data, SS:stacks

;---------------------
interrupt_handler PROC FAR
jmp run
    signature dw 0ff00h, 0ffffh
    count dw 1 
    str_time db 'Произошёл сигнал таймера, всего сигналов: ', '$';42
    
run:

    push ax
    push bx
    push cx
    push dx
    
    ;mem a cursor position
    mov ah, 03
    mov bh, 00
    int 10h
    
    push dx;--------cursor position in dx
    
;print a string of information  
    push ds
    push es
    
    mov ax, seg interrupt_handler
    mov ds, ax
    
    mov dx, offset str_time
    mov bp, dx

    ;es - указывает на начало процедуры
    mov ax, ds
    mov es, ax 
    
    ;print a string
    mov ah,13h
    mov al,1 ;sub function code
    ;1 = use attribute in BL; leave cursor an end of string
    mov bh,0
    mov bl, 2
    mov dh,0;
    mov dl,0
    mov cx, 42
    int 10h

    pop es
    pop ds
    
;------------------------	
    inc count
    cmp count, 0ffffh
    jne ifn
    mov count, 1
    
ifn:
    
    mov cl, 43
    mov [di], cl

    mov ax, count
    ;----preparing ax
    mov bx,1h
    mul bx

    ;dx:ax - number
    mov bx,0Ah
    xor cx,cx
    divis:
    div bx
    push dx
    inc cx
    xor dx,dx
    cmp ax,0
    jne divis

    print_simb:

    pop dx

    push cx
    push dx

    ;------change cursor position
    mov cl, [di]
    inc cl
    mov [di], cl
    
    ;put symbol into al

    add dl, 30h
    ;print a symbol in dl
    mov al, dl

    ;set curs
    mov ah, 02
    mov bh, 00
    mov dh, 0
    mov dl, [di]
    int 10h
    
    pop dx
    ;in dl - digit for print

    mov ah, 09h   ;писать символ в текущей позиции курсора
    mov bh, 0     ;номер видео страницы
    mov cx, 1     ;число экземпляров символа для записи
    int 10h      ;выполнить функцию

    pop cx
    loop print_simb
  

    ;return curs postition
    
    pop dx
    mov ah, 02
    mov bh, 00

    int 10h

;------end		

    pop dx
    pop cx
    pop bx 
    pop ax

    mov al, 20h
    out  20h, al
    iret			
interrupt_handler  ENDP  
;---------------------
isunLoad PROC
    push es
    push ax
    mov ax, PSP
    mov es, ax
    mov cl, es:[80h]
    mov dl, cl
    xor ch, ch
    test cl, cl	
    jz ex2
    xor di, di
    readChar:
    inc di
    mov al, es:[81h+di]
    inc di

    cmp al, '/'
    jne ex2
    mov al, es:[81h+di]
    inc di
    cmp al, 'u'
    jne ex2
    mov al, es:[81h+di]
    cmp al, 'n'
    jne ex2
    mov isUnBoot, 1 ; if is unLoading IDent

    ex2:
    pop ax
    pop es
    ret
isunLoad ENDP

;---------------------
isLoad PROC
    push bx
    push dx
    push es
    push ds
    mov ax, 351Ch ; функция получения вектора
    int  21h
    ;bx, es
    ;-------------------
    mov  dx, es:[bx+3];---signature
    pop ds
    pop es
    ;mov bx, offset signature
    ;mov ax, ds:[bx]
    mov ax, 0ff00h
    cmp dx, ax
    jne exd
    mov  dx, es:[bx+4];---signature
    mov ax, 0ffffh
    cmp dx, ax
    je ad
    jmp exd

    ad:
    mov isBoot, 1
    mov dx, offset str_in_already
    call write
    exd:
    pop dx
    pop bx
ret
isLoad ENDP
;---------------------
Load proc
    push ax
    push dx
    push bx
    
    mov dx, offset str_in_yes
    call WRITE
    
    push es
    mov ax, 351Ch ; функция получения вектора
    int  21H
    mov  KEEP_IP, bx  ; запоминание смещения
    mov  KEEP_CS, es  ; и сегмента вектора прерывания
    mov word ptr vect+2, es
    mov word ptr vect, bx
    pop es

    push ds
    mov dx, OFFSET interrupt_handler ; смещение для процедуры в dx
    mov ax, SEG interrupt_handler   ; сегмент процедуры
    mov ds, ax          ; помещаем в ds
    mov ax, 251Ch         ; функция установки вектора
    int 21h             ; меняем прерывание
    pop  ds

    pop bx
    pop dx
    pop ax
ret
Load endp
;---------------------
unLoad PROC
    push es
    mov ax, 351Ch ; функция получения вектора
    int  21H
    
    mov dx, word ptr es:[vect]
    mov ax, word ptr es:[vect+2]
    mov KEEP_IP, dx
    mov KEEP_CS, ax
    pop es
    cli
    push ds
    mov  dx, KEEP_IP
    mov  ax, KEEP_CS
    mov  ds, ax
    mov  AH, 25H
    mov  AL, 1CH
    int  21H          ; восстанавливаем вектор
    pop  ds
    sti
    ret
unLoad ENDP
;---------------------
MakeResident PROC
    mov dx, offset str_in_yes
    call WRITE
    mov dx, offset eeend
    sub dx, PSP
    mov cl, 4
    shr dx, cl
    mov ax, 3100h
    int 21h
    ret
MakeResident ENDP
;---------------------
WRITE   PROC
        push ax
        mov ah, 09h
        int 21h
        pop ax
        ret
WRITE   ENDP

TETR_TO_HEX PROC near
    and AL, 0Fh
    cmp AL, 09
    jbe NEXT
    add AL, 07
NEXT: add AL, 30h
    ret
TETR_TO_HEX ENDP
;-------------------------------
BYTE_TO_HEX PROC near
;byte AL translate in two symbols on 16cc numbers in AX
    push CX
    mov AH,AL
    call TETR_TO_HEX
    xchg AL,AH
    mov CL, 4
    shr AL,CL
    call TETR_TO_HEX
    pop CX
ret
BYTE_TO_HEX ENDP
;-------------------------------
WRD_TO_HEX PROC near
;translate in 16cc a 16 discharge number
;in AL - number, DI - the address of the last symbol  
    push BX
    mov BH,AH
    call BYTE_TO_HEX
    mov [DI],AH
    dec DI
    mov [DI],AL
    dec DI
    mov AL,BH
    call BYTE_TO_HEX
    mov [DI],AH
    dec DI
    mov [DI],AL
    pop BX
ret
WRD_TO_HEX ENDP

;---------------------
BEGIN   PROC  FAR 
    mov AX, data
    mov DS, AX
    
    mov ax, es
    mov PSP, ax ; save PSP address


    mov ax, 351ch
    int 21h
    mov  ax, es:[bx+3];---signature
    
    mov di, offset str_empty
    add di, 4
    
    call WRD_TO_HEX
    mov dx, offset str_empty
    mov ah, 09h
    int 21h
    
    call isLoad
    call isunLoad
    
    


    cmp isBoot, 1
    je a
    call Load
    
    ;mov ax, 351Ch ; функция получения вектора
    ;int  21h
    ;mov  dx, es:[bx+3];---signature
    
    
    ;call isLoad
    
    ;MakeResident
    ;-----------------------
    mov dx, offset str_int_mem
    call WRITE
    mov dx, offset eeend
    ;sub dx, PSP
    mov cl, 4
    shr dx, cl
    mov ax, 3100h
    int 21h
    ;-------------------
    
    ;mov ax, 351Ch ; функция получения вектора
    ;int  21h
    
    
    
    ;-------------
     ;mov  dx, es:[bx+3];---signature
    
    
    ;---------------
    ;es, bx
    ;call isLoad
    
a:
    cmp isUnBoot, 1
    jne b
    call unLoad
    mov dx, offset str_unb
    ;call WRITE
    jmp wr
    ;mov ah, 4Ch                        
    ;int 21h   
b:
    mov dx, offset str_in_already
    ;call WRITE
    
wr:    
    call WRITE
    
    xor AL,AL
    mov AH,4Ch
    int 21H
   
begin endp 


eeend: 
code    ENDS
          END begin
		  
