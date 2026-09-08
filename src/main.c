#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//opcode
#define NOP 0x00 // "***** chocolate" tagline excluding "eat *****,"
#define LDI 0X01 // Load immediate value to A; like LDI 10, load 10 to A
#define LDB 0X02 // Load immediate value to B 
#define LDA 0X03 // Load A from memory
#define STA 0x04 // Store A to memory
#define ADD 0x05 // A = A + B
#define SUB 0x06 // A = A - B
#define JMP 0x07 // Jump to address
#define JZ  0x08 // Jump is zero
#define OUT 0x0F // Prints A
#define HLT 0xFF // Halts CPU


// CPU
typedef struct CPU{
    uint16_t  A ;     // Accumulator
    uint16_t  B ;     // General-purpose register
    uint16_t PC;     // Program counter
    uint16_t SP;     // Stack pointer
    uint8_t  ZC;     // Zero and Carry flag (used together as minimum size is 8 bits and they only require 1 bit), so 1 is carry, 2 is zero and 3 is both
    uint16_t mem[512]; 
}CPU;

typedef struct INST{
    uint8_t opcode;
    uint8_t param1;

}INST;

CPU cpu1 = {.A   = 0x0,
            .B   = 0x0,
            .PC  = 0x0,
            .SP  = 0x0,
            .ZC  = 0x0,
            .mem = 0x0
};


CPU* cptr = &cpu1;

INST* fetch(INST* inst){

    //fetches instruction
    inst->opcode = cptr->mem[cptr->PC];
    inst->param1 = cptr->mem[cptr->PC+1];

    return inst;
}

void execute(INST* inst){
    switch(inst->opcode){
        case NOP:
            cptr->PC = cptr->PC + sizeof(INST);
            break;

        case LDI:
            cptr->A = inst->param1;
            inst->param1 = 0x0;
            cptr->PC = cptr->PC + sizeof(INST);
            break;

       case LDB:
           cptr->B = inst->param1;
           inst->param1 = 0x0;
           cptr->PC = cptr->PC + sizeof(INST);
           break;

       case LDA:
           // Not working after 0xFF address
            cptr->A = cptr->mem[inst->param1];
            inst->param1 = 0x0;
            cptr->PC = cptr->PC + sizeof(INST);
            break;

       case STA:
            cptr->mem[inst->param1] = cptr->A;
            inst->param1 = 0x0;
            cptr->PC = cptr->PC + sizeof(INST);
            break;

       case ADD:
           cptr->A = cptr->A + cptr->B; 
           cptr->PC = cptr->PC + sizeof(INST);
           break;

       case SUB:
           // currently cpu register is unsigned, -ve number cause underflow
           cptr->A = cptr->A - cptr->B; 
           cptr->PC = cptr->PC + sizeof(INST);
           break;

        case JMP:
            cptr->PC = inst->param1;
            inst->param1 = 0x0;
            break;

        case JZ:
            //Will be implemented after zero flag
            break;

        case OUT:
            printf("%u\n", cptr->A);
            cptr->PC = cptr->PC + sizeof(INST);
            break;

        case HLT:
            //This case needs to git gud using timer and cpu state;
            printf("CPU HALT\n");
            while(1);
            cptr->PC = cptr->PC + sizeof(INST);
            break;
            
        default:
            break;
    }
}

int main(){

    INST ins  = {.opcode = 0x0,
                  .param1 = 0x0,
    };

    INST* instptr = &ins;

    // Storing test code in mem
    cptr->mem[0x0]  = LDI;
    cptr->mem[0x01] = 0x10;
    cptr->mem[0x02] = STA;
    cptr->mem[0x03] = 0xF0;
    cptr->mem[0x04] = LDI;
    cptr->mem[0x05] = 0x1F;
    cptr->mem[0x04] = LDA;
    cptr->mem[0x05] = 0xF0;
    cptr->mem[0x04] = OUT;
    cptr->mem[0x06] = JMP;
    cptr->mem[0x07] = 0x1FF;
    cptr->mem[0xF0]= 0x01;
    cptr->mem[0x1FF]= HLT;
    

    

    //CPU cycle 
    while(1){
        INST* inst = fetch(instptr);
        execute(inst);
    }

    return 0;
}
