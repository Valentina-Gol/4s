stacks segment  STACK
    db 256 dup(?)
stacks ends    

data segment  
; ������⢮ ᨣ����� ⠩���
isBoot dw 0
isUnBoot dw 0
memAdrPsp dw 0
vect dw 0, 0


str_in_no db '���뢠��� �� ��⠭������', 0AH, 0DH,'$'
str_int_mem db '���뢠��� १����⭮ � �����', 0AH, 0DH, '$'
str_in_yes db '��⠭����� ��ࠡ��稪 ���뢠���', 0AH, 0DH,'$'
str_unb db '��ࠡ��稪 ���뢠��� ���㦥� �� �����', 0AH, 0DH, '$'
str_need_unboot db '�ॡ���� ���㧨�� ��ࠡ��稪 ���뢠��� �� �����', 0AH, 0DH,'$'
str_in_already db '���뢠��� 㦥 ��⠭������', 0DH, 0AH, '$'
str_ax db 'AX=     ', 0DH, 0AH, '$'
len equ $ - str_ax


data ends

code segment

    ASSUME CS:code, DS:data, SS:stacks
    
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


interr proc far
jmp run
    signature dw 0ff00h, 0ffffh
    count dw 1 
    str_time db '�ந���� ᨣ��� ⠩���, �ᥣ� ᨣ�����: ', '$';42
    
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
    
    mov ax, seg interr
    mov ds, ax
    
    mov dx, offset str_time
    mov bp, dx

    ;es - 㪠�뢠�� �� ��砫� ��楤���
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

    mov ah, 09h   ;����� ᨬ��� � ⥪�饩 ����樨 �����
    mov bh, 0     ;����� ����� ��࠭���
    mov cx, 1     ;�᫮ ������஢ ᨬ���� ��� �����
    int 10h      ;�믮����� �㭪��

    pop cx
    loop print_simb
  

    ;return curs postition
    
    pop dx
    mov ah, 02
    mov bh, 00
    int 10h

;------end		
    
    mov al, 20h
    out  20h, al
    
    pop dx
    pop cx
    pop bx 
    pop ax
    
    iret
interr endp

;--------------------------
resident proc
    ;��⠢�塞 ��楤��� ���뢠��� १����⭮�
    ;AH - ����� �㭪樨 31h;
    ;AL - ��� �����襭�� �ணࠬ��;
    ;DX - ࠧ��� ����� � ��ࠣ���, �ॡ㥬� १����⭮� �ணࠬ��.
    push ax
    push dx
    push cx
    push bx
    
    mov dx, offset str_int_mem
    mov ah, 09h
    int 21h
   

    mov AX, memAdrPsp
    mov BX, seg code
    sub BX, AX
    mov DX,offset eeend; ࠧ��� � ����� �� ��砫� ᥣ����
    mov CL,4 ; ��ॢ�� � ��ࠣ���
    shr DX,CL
    inc DX ; ࠧ��� � ��ࠣ���
    add DX, BX
    mov AH,31h
    mov al, 00h
    int 21h  
    
    pop bx
    pop cx
    pop dx
    pop ax


    ret
resident endp

;------------------------
setInterr proc

    push ax
    push dx
    push bx
    
    mov dx, offset str_in_yes
    mov ah, 09h
    int 21h

    ;  � �ணࠬ�� �� ����㧪� ��ࠡ��稪� ���뢠���
    MOV AH, 35H ; �㭪�� ����祭�� �����
    MOV AL, 1CH ; ����� �����
    INT 21H

    
    ;��࠭塞 ����� ��室���� ��ࠡ��稪� ���뢠��� ⠩���
    mov word ptr vect+2, es
    mov word ptr vect, bx

    ;⥯��� ��⠭�������� �� ��� ���� ��� ��ࠡ��稪
       
    PUSH DS
    MOV DX, OFFSET interr ;ᬥ饭�� ��� ��楤��� � dx
    ;����� � ds ᥣ���� ��楤���
    MOV AX, SEG interr ;ᥣ���� ��楤���
    MOV DS, AX ;����頥� � ds
    
    MOV AH, 25H ;�㭪�� ��⠭���� ����� ���뢠���
    MOV AL, 1CH ;����� �����
    
    INT 21H ;���塞 ���뢠���
    POP DS
    
    pop bx
    pop dx
    pop ax


    ret
setInterr endp
;------------------------
isBootFunc proc
    push ax
    push bx
    push dx
    push es

    mov ax, 351Ch ;
    int  21h
    ;bx, es
    ;-------------------
    add bx, offset signature - offset interr
    mov  dx, es:[bx];---signature

    mov ax, 0ff00h
    cmp dx, ax
    jne e_i_s
    mov  dx, es:[bx+2];---signature

    mov ax, 0ffffh
    cmp dx, ax
    je ad
    jmp e_i_s
    
ad:

    pop es
    mov isBoot, 1
    mov dx, offset str_in_already
    mov ah, 09h
    int 21h
    jmp ex_
e_i_s:
    ;pop ds
    pop es
ex_:    
    pop dx
    pop bx
    pop ax
    ret
isBootFunc endp    

;-------------------------
isUnBootFunc proc
    push es
    push ax
    push dx
    push cx
    
    mov ax, memAdrPsp
    mov es, ax
    mov cl, es:[80h]
    
    cmp cl, 4h
    jl non
    
    mov dl, es:[81h]
    cmp dl, ' '
    jne non

    mov dl, es:[81h+1]
    cmp dl, '/'
    jne non
    
    mov dl, es:[81h+2h]
    cmp dl, 'u'
    jne non
    
    mov dl, es:[81h+3h]
    cmp dl, 'n'
    jne non
    
    mov isUnBoot, 1h
    
    mov dx, offset str_need_unboot
    mov ah, 09h
    int 21h

non:
    pop cx
    pop dx
    pop ax
    pop es
    ret
isUnBootFunc endp   
;-------------------------

UnBootFunc proc
    
    push dx
    push ax
    push es
    push bx
    mov dx, offset str_unb
    mov ah, 09h
    int 21h
    
    mov ax, seg data
    mov bx, seg code
    
    sub bx, ax

    push es
    push bx
    
    mov ah, 35h
    mov al, 1Ch; 
    int  21h 
    ;es, bx in resident
    pop bx
    push es;---memAdrCode
    mov ax, es
    
    sub ax, bx
    mov es, ax
    
    mov bx, offset vect; �� ds
    
    ; � �ணࠬ�� �� ���㧪� ��ࠡ��稪� ���뢠���
    CLI
    PUSH DS
    
    mov dx, es:[bx];---bx
    mov ax, es:[bx+2];--es
    MOV DS, AX
    
    MOV AH, 25H ;��⠭�������� ����� ���뢠���
    MOV AL, 1CH
    INT 21H ; ����⠭�������� �����
    ;pop es
    pop ds
    
    ;---free memory
    pop es
    mov bx, es;---code in resident
    pop es
    mov ax, es;---now es
    
    mov dx, seg code;--seg adress now program
    sub dx, ax ;---defference
    sub bx, dx;--es in resident
    mov es, bx

    push es
    
    mov ax, es:[2Ch]
    mov es, ax
    
    mov ah, 49h
    int 21h
    
    pop es
    
    
    mov ah, 49h
    int 21h
     
    pop bx 
    pop es
    pop ax
    pop dx
    STI 
    
    ret
UnBootFunc endp  
;-------------------------

    
BEGIN proc far

    mov AX, data
    mov DS, AX
    
    mov bx, es
    mov memAdrPsp, bx
    
    
    call isBootFunc
    call isUnBootFunc
    
    cmp isBoot, 1h
    je mayunboot
;-------------------------------   
boot:
    call setInterr
    call resident
;-------------------------------
mayunboot:
    cmp isUnBoot, 1h
    jne end_pr
    call UnBootFunc
;-------------------------------
    
end_pr:    
    xor AL,AL
    mov AH,4Ch
    int 21H
   
begin endp 


eeend: 
code    ENDS
          END begin
