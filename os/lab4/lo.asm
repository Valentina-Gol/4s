.Model small

.DATA
HELLO db "Message:$"
IDENTSTR db 13, 10, "Resident loaded$", 13, 10
RESUNSTR db 13, 10, "Resident unloaded$"
RESLSTR db 13, 10, "Resident is already loaded$"
PSP dw ?
isUd db ?
isloaded db ?
count dw 0
KEEP_CS DW ? ; для хранения сегмента
KEEP_IP DW ? ; и смещения вектора прерывания
str_int_mem db 'Обработчик прерывания резидентен в памяти', 0AH, 0DH, '$'
str_in_yes db 'Установлен обработчик прерываний', 0AH, 0DH,'$'
str_in_already db 'Обработчик преывания уже установлен', 0AH, 0DH, '$'
str_unb db 'Обработчик прерываний выгружен из памяти', 0AH, 0DH, '$'
str_empty db '      ', 0AH, 0DH, '$'


.STACK 400h

.CODE
int_vect dd ?
ID dw 0ff00h
;---------------------
ROUT PROC FAR
    jmp run
    signature dw 0ff00h, 0ffffh
    ;count dw 1 
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
    
    mov ax, seg rout
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
ROUT  ENDP  
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
    mov isUd, 1 ; if is unLoading IDent

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
    ;push ds
    mov ax, 351Ch ; функция получения вектора
    int  21h
    ;bx, es
    ;-------------------
    mov  dx, es:[bx+3];---signature
    
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
    ;pop ds
    pop es
    mov isloaded, 1
    mov dx, offset str_in_already
    call write
    jmp ex_
exd:
    ;pop ds
    pop es
ex_:    
    pop dx
    pop bx

    ret
isLoad ENDP
;---------------------
unLoad PROC
    push es
    push dx
    push ax
    mov ax, 351Ch ; функция получения вектора
    int  21H
    mov dx, word ptr es:int_vect
    mov ax, word ptr es:int_vect+2
    mov KEEP_IP, dx
    mov KEEP_CS, ax
    pop ax
    pop dx
    pop es
    cli
    push ds
    push ax
    push dx
    mov  dx, KEEP_IP
    mov  ax, KEEP_CS
    mov  ds, ax
    mov  AH, 25H
    mov  AL, 1CH
    int  21H          ; восстанавливаем вектор
    pop dx
    pop ax
    pop  ds
    sti
    ret
unLoad ENDP
;---------------------
MakeResident PROC
    mov dx, offset IDENTSTR
    call WRITE
    mov dx, offset temp
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
;---------------------
BEGIN   PROC  FAR 
    ;mov ax, ds
    mov ax, @DATA		  
    mov ds, ax
    mov ax, es
    mov PSP, ax ; save PSP addr to var

    call isLoad

    call isunLoad


    cmp isloaded, 1
    je a
    push es
    mov ax, 351Ch ; функция получения вектора
    int  21H
    mov  KEEP_IP, bx  ; запоминание смещения
    mov  KEEP_CS, es  ; и сегмента вектора прерывания
    mov word ptr int_vect+2, es
    mov word ptr int_vect, bx
    pop es

    push ds
    mov dx, OFFSET ROUT ; смещение для процедуры в dx
    mov ax, SEG ROUT    ; сегмент процедуры
    mov ds, ax          ; помещаем в ds
    mov ax, 251Ch         ; функция установки вектора
    int 21h             ; меняем прерывание
    pop  ds
    call MakeResident

    ;call isLoad
    a:
        cmp isud, 1
        jne b
        call unLoad
        mov dx, offset RESUNSTR
        call WRITE
        mov ah, 4Ch                        
        int 21h   
    b:
        mov dx, offset RESLSTR
        call WRITE
        mov ah, 4Ch                        
        int  21h
BEGIN      ENDP
;---------------------
TEMP PROC
TEMP ENDP
;---------------------
END BEGIN
		  
