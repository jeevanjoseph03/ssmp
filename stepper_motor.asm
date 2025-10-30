; --- Initialization ---
MOV AX, 0000
MOV DX, 0FFE6    ; 8255 Control Word Register (CWR)
MOV AL, 80H      ; Control word to set Port A as output
OUT DX, AL       ; Send control word to 8255

MOV DX, 0FFE0    ; Port A address
MOV AL, 11H      ; Initial step value (0001 0001B)

; --- Main Loop ---
U1:
    OUT DX, AL       ; Send step value to Port A (to the motor)
    CALL DELAY       ; Wait for the motor to move
    
    ; --- This is the key instruction ---
    RCR AL, 1        ; For CLOCKWISE rotation
    ; R CL AL, 1     ; For ANTI-CLOCKWISE rotation (use this or RCR, not both)
    
    JMP U1           ; Repeat the loop

; --- Delay Procedure ---
DELAY:
    MOV CX, 0800H  ; Load a large number for the delay
L2:
    LOOP L2        ; Loop to waste time
    RET            ; Return from CALL