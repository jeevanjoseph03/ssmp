ASSUME CS:CODE, DS:DATA
DATA SEGMENT
    LIST DW 0003H, 0004H, 0001H, 0009H, 0000H
    N    DW 0005H
DATA ENDS

CODE SEGMENT
START:
    ; --- Initialize Data Segment (DS) ---
    MOV AX, DATA
    MOV DS, AX
    
    ; --- Bubble Sort Logic ---
    MOV CX, N
    DEC CX           ; Outer loop runs N-1 times
OUTER:
    MOV SI, OFFSET LIST ; Reset SI to start of list
    MOV BX, CX          ; Inner loop counter
INNER:
    MOV AX, [SI]        ; Get the first number (e.g., 3)
    CMP AX, [SI+2]    ; Compare it to the next number (e.g., 4)
    JC  L1            ; Jump if Carry (if AX < [SI+2], it's in order)
    
    ; --- Swap if out of order ---
    XCHG AX, [SI+2]   ; Swap the number in memory with AX
    MOV [SI], AX      ; Put the smaller number back
L1:
    ADD SI, 02H       ; Move SI to the next element
    DEC BX
    JNZ INNER         ; Repeat inner loop
    
    DEC CX
    JNZ OUTER         ; Repeat outer loop

    ; --- Display Logic ---
DISPLAY:
    LEA SI, LIST      ; Point SI to the start of the (now sorted) list
    MOV CX, N         ; Load CX with 5 (total numbers to print)
PRINT:
    MOV DX, [SI]      ; Get the number (e.g., 0000H)
    ADD DX, 30H       ; Convert it to an ASCII character (0 + '0' = '0')
    MOV AH, 02H       ; DOS function: Print Character
    INT 21H           ; Call DOS
    
    ADD SI, 02H       ; Move to the next number in the list
    LOOP PRINT        ; Decrement CX and loop back to PRINT
    
    ; --- Exit Program ---
    MOV AH, 4CH       ; DOS function: Terminate Program
    INT 21H
CODE ENDS
END START