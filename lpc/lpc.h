#ifndef LPC_H
#define LPC_H
//MEMORY SIZE
#define MEMORY_SIZE 100
#define MIN_VALUE -9999
#define MAX_VALUE 9999
//OPCODE
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define JUMP 40
#define JUMPNEG 41
#define JUMPZERO 42
#define HALT 43
//ERROR MESSAGES
#define ERR_DIV_BY_ZERO "***FATAL ERROR - ATTEMPT TO DIVIDE BY ZERO***"
#define ERR_INVALID_OPCODE "***FATAL ERROR - INVALID OPCODE***"
#define ERR_OVERFLOW "***FATAL ERROR - ACCUMULATOR OVERFLOW***"

#define SENTINEL -99999
#define TRUE 1
#define FALSE 0

extern int memory[MEMORY_SIZE];
extern int accumulator;
extern int programCounter;
extern int instructionReg;
extern int opCode;
extern int operand;

void initialize_memory();
void initialize_registers();
void load_program();
void execute_program();
void memory_dump();
void handle_error(const char *error_message);



#endif
