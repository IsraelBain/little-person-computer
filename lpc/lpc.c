#include <stdio.h>
#include "lpc.h"
//from .h file
int memory[MEMORY_SIZE];
int accumulator;
int programCounter;
int instructionReg;
int opCode;
int operand;

void initialize_memory(){
    for(int i = 0; i < MEMORY_SIZE; i++){
        memory[i] = 0;
    }
}

void initialize_registers(){
    accumulator = 0;
    programCounter = 0;
    instructionReg = 0;
    opCode = 0;
    operand = 0;
}

void load_program(){
    int instruction, index = 0;

    while(scanf("%d", &instruction) != EOF){
        if(instruction == SENTINEL) break;
        if(instruction < MIN_VALUE || instruction > MAX_VALUE){
            printf("***INVALID INSTRUCTION: %d***\n", instruction);
            continue;
        }


        if(index < MEMORY_SIZE){
            memory[index++] = instruction;
        }else{
            break;
        }
    }
}
void memory_dump() {
    printf("\nRegisters: \n");
    printf("accumulator %+05d\n", accumulator);
    printf("program counter %05d\n", programCounter);
    printf("op-code %05d\n", opCode);
    printf("operand %05d\n", operand);

    printf("\n      0    1    2    3    4    5    6    7    8    9 \n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (i % 10 == 0) {
            if (i > 0) printf("\n");
            printf("%2d ", (i / 10) * 10);
        }
        printf("%+05d ", memory[i]);
    }
    printf("\n");
}
void execute_program(){
    printf("***Start LPC Execution***\n");
    while(1){
        instructionReg = memory[programCounter];
        opCode = instructionReg / 100;
        operand = instructionReg % 100;

        switch (opCode) {
            case READ:
                if(scanf("%d", &memory[operand]) == EOF ){
                    printf("***FATAL ERROR - Unexpected EOF during READ***\n");
                    printf("***LPC execution abnormally terminated***\n");
                    memory_dump();
                    return;
                }
                programCounter++;
                break;

            case WRITE:
                printf("Contents of %02d: %d\n", operand, memory[operand]);
                programCounter++;
                break;

            case LOAD:
                accumulator = memory[operand];
                programCounter++;
                break;

            case STORE:
                memory[operand] = accumulator;
                programCounter++;
                break;

            case ADD:
                accumulator += memory[operand];
                programCounter++;
                break;

            case SUBTRACT:
                accumulator -= memory[operand];
                programCounter++;
                break;

            case DIVIDE:
                if (memory[operand] == 0){
                    printf("***FATAL ERROR - Attempt to divide by zero***\n");
                    printf("***LPC execution abnormally terminated***\n");
                    memory_dump();
                    return;
                }
                accumulator /= memory[operand];
                programCounter++;
                break;

            case MULTIPLY:
                accumulator *= memory[operand];
                programCounter++;
                break;

            case JUMP:
                programCounter = operand;
                break;

            case JUMPNEG:
                if (accumulator < 0)
                    programCounter = operand;
                else
                    programCounter++;
                break;

            case JUMPZERO:
                if (accumulator == 0)
                    programCounter = operand;
                else
                    programCounter++;
                break;

            case HALT:
                printf("***End LPC Execution***\n");
                return;

            default:
                printf("***FATAL ERROR: Illegal opCode***\n");
                printf("***LPC execution abnormally terminated***\n");
                memory_dump();
                return;

        }

        //overflow
        if (accumulator < MIN_VALUE || accumulator > MAX_VALUE) {
            printf("***FATAL ERROR - Accumulator Overflow***\n");
            printf("***LPC execution abnormally terminated***\n");
            memory_dump();
            return;
        }
    }
}




int main() {
    initialize_memory();
    initialize_registers();
    load_program();
    execute_program();
    return 0;
}

