stacks segment  STACK
    db 256 dup(?)
stacks ends    

data segment  
 ; хранится в обработчике прерываний
    KEEP_CS DW 0 ; для хранения сегмента
    KEEP_IP DW 0 ; и смещения вектора прерывания
; количество сигналов таймера
isBoot dw 0
isUnBoot dw 0
memAdrPsp dw 0
vect dd 0


str_seg1 db 0DH, 0AH, '0000h - свободный участок',0DH, 0AH,'$'
str_seg2 db 0DH, 0AH, '0006h - участок принадлежит драйверу OS XMS UMB',0DH, 0AH,'$'
str_seg3 db 0DH, 0AH, '0007h - участок является исключенной верхней памятью драйверов',0DH, 0AH,'$'
str_seg4 db 0DH, 0AH, '0008h - участок принадлежит MS DOS',0DH, 0AH,'$'
str_seg5 db 0DH, 0AH, 'FFFAh - участок занят управляющим блоком 386MAX UMB',0DH, 0AH,'$'
str_seg6 db 0DH, 0AH, 'FFFDh - участок заблокирован 386MAX',0DH, 0AH,'$'
str_seg7 db 0DH, 0AH, 'FFFEh - участок принадлежит 386MAX UMB',0DH, 0AH,'$'
str_wr db 0DH, 0AH, 'Пользовательский участок',0DH, 0AH,'$'
str_size_b db 'Размер участка в байтах: ', '$'
str_sequ db 'Последовательность символов: ', '$'
str_ent db ' ', 0DH, 0AH, '$'
str_div db 0DH, 0AH, '------------------------------------', 0DH, 0AH, '$'

str_in_no db 'Прерывание не установлено', 0AH, 0DH,'$'
str_int_mem db 'Прерывание резидентно в памяти', 0AH, 0DH, '$'
str_in_yes db 'Установлен обработчик прерываний', 0AH, 0DH,'$'
str_unb db 'Обработчик прерываний выгружен из памяти', 0AH, 0DH, '$'
str_need_unboot db 'Требуется выгрузить обработчик прерывания из памяти', 0AH, 0DH,'$'



data ends

code segment

    ASSUME CS:code, DS:data, SS:stacks
    
  


interr proc far
;ds указывает на адрес начала
;dx - смещение
    jmp beg
    
    ;db 256 dup(0)
    counter dw 10
    str_time db 'Произошёл сигнал таймера, всего сигналов:       ', '$';32
    
;save registers
  
;return registers
    
    
    ;call getCurs
    
beg:    
    push ax
    push bx
    push cx

    ;get cursor
    mov ah,03h
    mov bh,0
    int 10h
    push bx
    push dx; parametrs of cursor
    
    
    ;mov ah, 02h
    ;inc dh
    ;push dx
    
   
    push ds
    push es
    
    mov ax, seg interr
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
    ;call outputBP
    pop es
    pop ds
    ;pop dx

    inc counter
    
    push cx
    
    ;mov cl, 6
    ;mov [di], cl
    ;mov cl, 42
    ;mov [si], cl
    ;mov cl, 48
    mov di, 48
    pop cx
    
loop_div:    
    
    mov ax, counter
    cmp ax, 0ffffh
    ;cmp al, 10
    jne n
    mov counter, 0
    
n:    

    mov bl, 10
    div bl
    push ax
    ;in al - res 
    ;in ah - surplus
    ;call setCurs
    ;push ax
    mov ah,02h
    mov bh,0
    mov dh,0
    ;mov dl, [si]
    
    mov dx, [di]; столбец на экране
    ;mov bl, dl
    dec di
     
    int 10h
    
    pop ax
    ;mov bh, ah
    
    ;print al
    ;add al, 30h
    push ax
    mov al, ah
    ;or al, 9h
    add al, 30h
    
    mov ah,09h ;писать символ с текущей позиции курсора
    mov bh,0 ;номер видео страницы
    mov cx,1 ;число экземпляров символа для записи
    
    int 10h ;выполнить функцию
    pop ax
    ;mov al, ah
    ;call outputAL
    
    ;pop ax
    
    ;push dx
    
    
    ;mov ah, 02h
    ;inc dl
    ;mov dx, es
    ;int 10h
    
    ;pop dx
    
    cmp al, 0h
    jne loop_div
    
    
    
    pop dx
    pop bx
    
    call setCurs

    pop cx
    pop bx  
    pop ax
   


    mov al, 20h
    out 20h, al
  
        
    iret
interr endp

setCurs proc 
; Установка ПОЗИЦИИ курсора
; установка на строку 25 Делает курсор невидимым
    push ax
    push bx
    push dx
    push CX
    mov ah,02h
    mov bh,0
    mov dh,22
    int 10h
    pop CX
    pop dx
    pop bx
    pop ax
    ret
setCurs endp

getCurs proc 
    push ax
    push bx
    push dx
    push CX
    mov ah,03h
    mov bh,0
    int 10h
    pop CX
    pop dx
    pop bx
    pop ax
    ret
getCurs endp
;-----------------------------------------
;Вывод на экран информации обработчиком прерываний осуществляется с помощью
;функций прерывания 10h.
;функция вывода символа из AL
outputAL proc 
    push ax
    push bx
    push cx
    mov ah,09h ;писать символ с текущей позиции курсора
    mov bh,0 ;номер видео страницы
    mov cx,1 ;число экземпляров символа для записи
    int 10h ;выполнить функцию
    pop cx
    pop bx
    pop ax
    ret
outputAL endp
;-------------------------------------    
    
;функция вывода строки по адресу ЕS:ВР на экран
outputBP proc 
    push ax
    push bx
    push dx
    push CX
    mov ah,13h
    mov al,1 ;sub function code
    ;1 = use attribute in BL; leave cursor an end of string
    mov bh,0
    mov dh,0;
    mov dl,0
    int 10h
    pop CX
    pop dx
    pop bx
    pop ax
    ret
outputBP endp
;------------------------------

;--------------------------
resident proc
    ;оставляем процедуру прерывания резидентной
    ;AH - номер функции 31h;
    ;AL - код завершения программы;
    ;DX - размер памяти в параграфах, требуемый резидентной программе.
    push ax
    push dx
    push cx
    
    mov dx, offset str_int_mem
    mov ah, 09h
    int 21h
   

    mov DX,offset eeend; размер в байтах от начала сегмента
    mov CL,4 ; перевод в параграфы
    shr DX,CL
    inc DX ; размер в параграфах
    mov AH,31h
    mov al, 00h
    int 21h  
    
    pop cx
    pop dx
    pop ax


ret
resident endp

;------------------------
setInterr proc

    push ax
    push dx

    mov dx, offset str_in_yes
    mov ah, 09h
    int 21h

    ;  в программе при загрузке обработчика прерывания
    MOV AH, 35H ; функция получения вектора
    MOV AL, 1CH ; номер вектора
    INT 21H

    
    
    ;MOV KEEP_IP, BX ; запоминание смещения
    ;MOV KEEP_CS, ES ; и сегмента 
    
    ;сохраняем вектор исходного обработчика прерывания таймера
    mov word ptr vect, es
	mov word ptr vect+2, bx
	
	;теперь устанавливаем на его место наш обработчик
       
    PUSH DS
    MOV DX, OFFSET interr ;смещение для процедуры в dx
    ;кладём в ds сегмент процедуры
    MOV AX, SEG interr ;сегмент процедуры
    MOV DS, AX ;помещаем в ds
    
    MOV AH, 25H ;функция установки вектора прерывания
    MOV AL, 1CH ;номер вектора
    
    INT 21H ;меняем прерывание
    POP DS
    
    pop dx
    pop ax


ret
setInterr endp
;------------------------
isBootFunc proc
    push ax
    push bx
    push es

    MOV AH, 35H ; функция получения вектора
    MOV AL, 1CH ; номер вектора
    INT 21H
    
    mov ax, es:[bx]
    

    pop es
    pop bx
    pop ax

    ret
isBootFunc endp    

;-------------------------
isUnBootFunc proc

    push dx
    push ax
    
    mov dl, ds:[81h]
    cmp dl, '/'
    jne non
    
    mov dl, ds:[81h+1h]
    cmp dl, 'u'
    jne non
    
    mov dl, ds:[81h+2h]
    cmp dl, 'n'
    jne non
    
    mov dl, ds:[81h+3h]
    cmp dl, ' '
    jne non
    mov isBoot, 1h
    
    mov dx, offset str_need_unboot
    mov ah, 09h
    int 21h

non:
    pop ax
    pop dx
    ret
isUnBootFunc endp   
;-------------------------

UnBootFunc proc
    
    push dx
    push ax
    mov dx, offset str_unb
    mov ah, 09h
    int 21h
    
    ;push es
	mov ax, 351Ch ; функция получения вектора
	int  21H
	;mov dx, word ptr es:vect
	;mov ax, word ptr es:vect+2
	;mov KEEP_IP, dx
	;mov KEEP_CS, ax
	;pop es

    ;  в программе при выгрузке обработчика прерываний
    CLI
    PUSH DS
    ;MOV DX, KEEP_IP
    ;кладём в ds cs
    ;MOV AX, KEEP_CS
    mov dx, word ptr es:vect+2
	mov ax, word ptr es:vect
    
    MOV DS, AX
    MOV AH, 25H ;устанавливаем вектор прерывания
    MOV AL, 1CH
    INT 21H ; восстанавливаем вектор
    pop ds
    STI   
    
    pop ax
    pop dx

    ret
UnBootFunc endp  
;-------------------------

    
BEGIN proc far

    mov AX, data
    mov DS, AX
    
    ;mov word ptr 
    
    ;mov bx, es
    ;mov memAdrPsp, bx
    
    ;call isBootFunc
    ;call isUnBootFunc
    
    ;cmp isBoot, 1h
    ;je mayunboot
;-------------------------------   
boot:
    call interr
    ;call setInterr
    ;call resident

;-------------------------------
mayunboot:
    ;cmp isUnBoot, 1h
    ;jne end_pr
    ;call UnBootFunc
;-------------------------------
    
    
end_pr:    
    xor AL,AL
    mov AH,4Ch
    int 21H
   
begin endp 


eeend: 
code    ENDS
          END begin
