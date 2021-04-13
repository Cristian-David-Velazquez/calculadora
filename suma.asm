%include "asm_io.inc"
segment .data


segment .text 
    global asm_sum_int, asm_rest_int
; función asm_sum_int
; copia un bloque de memoria114
; prototipo de C
; void asm_copy( void * dest, const void * src, unsigned sz);
; parámetros:
; dest - apuntador del búfer para copiar a
; src - apuntador del búfer para copiar desde
; sz - número de bytes a copiar
; A continuación, se definen algunos sı́mbolos útiles

%define param1  [ebp+8]
%define param2  [ebp+12]
;%define sz      [ebp+16]

asm_sum_int:
    enter   0, 0

    mov     eax, param1       ; Variable 1 recibida
    add     eax, param2       ; Variable 2 recibida
    ;call    print_int	  ; //Esta funcion que es de C, esta en asm_io.asm
    jo      short desborde ;es short porque voy a un label dentro del mismo archivo
    ;call    print_string
    leave
    ret

desborde:
    mov     eax, -1
    leave
    ret


%define param1  [ebp+8]
%define param2  [ebp+12]

asm_rest_int:
    enter   0, 0

    mov      eax, param1       ; Variable 1 recibida
    sub      eax, param2       ; Variable 2 recibida  
    jo       short desborde 
    ;call    print_string
    leave
    ret




    ;mov     eax, [ebp+8]       ; Variable 2 recibida
    ;call    print_int	  ; //Esta funcion que es de C, esta en asm_io.asm

        
    ;push    esi
    ;push    edi
    ;mov     esi, src    ; esi = dirección del búfer para copiar desde
    ;mov     edi, dest   ; edi = dirección del búfer para copia a
    ;mov     ecx, sz     ; ecx = número de bytes a copiar
    
    ;cld                 ; borrar la bandera de dirección
    ;rep     movsb       ; ejecute movsb ECX veces
    
    ;pop     edi
    ;pop     esi

;
;
;
;
;
;
;
;
;
;
;
;
;function _asm_find
;Busca en la memoria un byte dado
;void * asm_find( const void * src, char target, unsigned sz);
;parámetros
;   src - apuntador al lugar dónde buscar
;   target - valor del byte a buscar
;   sz - tamaño en bytes de dónde se busca
;valor de retorno
;   si target se encuentra, apunta a la primera ocurrencia de target
;
;   si no
;        retorna NULL
