stacks segment  STACK
    db 256 dup(?)
stacks ends    

data segment  
 ; �࠭���� � ��ࠡ��稪� ���뢠���
    KEEP_CS DW 0 ; ��� �࠭���� ᥣ����
    KEEP_IP DW 0 ; � ᬥ饭�� ����� ���뢠���
; ������⢮ ᨣ����� ⠩���
isBoot dw 0
isUnBoot dw 0
memAdrPsp dw 0
vect dd 0


str_seg1 db 0DH, 0AH, '0000h - ᢮����� ���⮪',0DH, 0AH,'$'
str_seg2 db 0DH, 0AH, '0006h - ���⮪ �ਭ������� �ࠩ���� OS XMS UMB',0DH, 0AH,'$'
str_seg3 db 0DH, 0AH, '0007h - ���⮪ ���� �᪫�祭��� ���孥� ������� �ࠩ��஢',0DH, 0AH,'$'
str_seg4 db 0DH, 0AH, '0008h - ���⮪ �ਭ������� MS DOS',0DH, 0AH,'$'
str_seg5 db 0DH, 0AH, 'FFFAh - ���⮪ ����� �ࠢ���騬 ������ 386MAX UMB',0DH, 0AH,'$'
str_seg6 db 0DH, 0AH, 'FFFDh - ���⮪ �������஢�� 386MAX',0DH, 0AH,'$'
str_seg7 db 0DH, 0AH, 'FFFEh - ���⮪ �ਭ������� 386MAX UMB',0DH, 0AH,'$'
str_wr db 0DH, 0AH, '���짮��⥫�᪨� ���⮪',0DH, 0AH,'$'
str_size_b db '������ ���⪠ � �����: ', '$'
str_sequ db '��᫥����⥫쭮��� ᨬ�����: ', '$'
str_ent db ' ', 0DH, 0AH, '$'
str_div db 0DH, 0AH, '------------------------------------', 0DH, 0AH, '$'

str_in_no db '���뢠��� �� ��⠭������', 0AH, 0DH,'$'
str_int_mem db '���뢠��� १����⭮ � �����', 0AH, 0DH, '$'
str_in_yes db '��⠭����� ��ࠡ��稪 ���뢠���', 0AH, 0DH,'$'
str_unb db '��ࠡ��稪 ���뢠��� ���㦥� �� �����', 0AH, 0DH, '$'
str_need_unboot db '�ॡ���� ���㧨�� ��ࠡ��稪 ���뢠��� �� �����', 0AH, 0DH,'$'



data ends

code segment

    ASSUME CS:code, DS:data, SS:stacks
    
  


interr proc far
;ds 㪠�뢠�� �� ���� ��砫�
;dx - ᬥ饭��
    jmp beg
    
    ;db 256 dup(0)
    counter dw 10
    str_time db '�ந���� ᨣ��� ⠩���, �ᥣ� ᨣ�����:       ', '$';32
    
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
    
    mov dx, [di]; �⮫��� �� �࠭�
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
    
    mov ah,09h ;����� ᨬ��� � ⥪�饩 ����樨 �����
    mov bh,0 ;����� ����� ��࠭���
    mov cx,1 ;�᫮ ������஢ ᨬ���� ��� �����
    
    int 10h ;�믮����� �㭪��
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
; ��⠭���� ������� �����
; ��⠭���� �� ��ப� 25 ������ ����� ��������
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
;�뢮� �� �࠭ ���ଠ樨 ��ࠡ��稪�� ���뢠��� �����⢫���� � �������
;�㭪権 ���뢠��� 10h.
;�㭪�� �뢮�� ᨬ���� �� AL
outputAL proc 
    push ax
    push bx
    push cx
    mov ah,09h ;����� ᨬ��� � ⥪�饩 ����樨 �����
    mov bh,0 ;����� ����� ��࠭���
    mov cx,1 ;�᫮ ������஢ ᨬ���� ��� �����
    int 10h ;�믮����� �㭪��
    pop cx
    pop bx
    pop ax
    ret
outputAL endp
;-------------------------------------    
    
;�㭪�� �뢮�� ��ப� �� ����� �S:�� �� �࠭
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
    ;��⠢�塞 ��楤��� ���뢠��� १����⭮�
    ;AH - ����� �㭪樨 31h;
    ;AL - ��� �����襭�� �ணࠬ��;
    ;DX - ࠧ��� ����� � ��ࠣ���, �ॡ㥬� १����⭮� �ணࠬ��.
    push ax
    push dx
    push cx
    
    mov dx, offset str_int_mem
    mov ah, 09h
    int 21h
   

    mov DX,offset eeend; ࠧ��� � ����� �� ��砫� ᥣ����
    mov CL,4 ; ��ॢ�� � ��ࠣ���
    shr DX,CL
    inc DX ; ࠧ��� � ��ࠣ���
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

    ;  � �ணࠬ�� �� ����㧪� ��ࠡ��稪� ���뢠���
    MOV AH, 35H ; �㭪�� ����祭�� �����
    MOV AL, 1CH ; ����� �����
    INT 21H

    
    
    ;MOV KEEP_IP, BX ; ����������� ᬥ饭��
    ;MOV KEEP_CS, ES ; � ᥣ���� 
    
    ;��࠭塞 ����� ��室���� ��ࠡ��稪� ���뢠��� ⠩���
    mov word ptr vect, es
	mov word ptr vect+2, bx
	
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
    
    pop dx
    pop ax


ret
setInterr endp
;------------------------
isBootFunc proc
    push ax
    push bx
    push es

    MOV AH, 35H ; �㭪�� ����祭�� �����
    MOV AL, 1CH ; ����� �����
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
	mov ax, 351Ch ; �㭪�� ����祭�� �����
	int  21H
	;mov dx, word ptr es:vect
	;mov ax, word ptr es:vect+2
	;mov KEEP_IP, dx
	;mov KEEP_CS, ax
	;pop es

    ;  � �ணࠬ�� �� ���㧪� ��ࠡ��稪� ���뢠���
    CLI
    PUSH DS
    ;MOV DX, KEEP_IP
    ;����� � ds cs
    ;MOV AX, KEEP_CS
    mov dx, word ptr es:vect+2
	mov ax, word ptr es:vect
    
    MOV DS, AX
    MOV AH, 25H ;��⠭�������� ����� ���뢠���
    MOV AL, 1CH
    INT 21H ; ����⠭�������� �����
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
