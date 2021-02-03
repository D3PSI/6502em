#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PC_RESET 0xFFFC
#define SP_RESET 0x0100
#define BYTE_RESET 0x0000

#define CARRY_FLAG 0x0001
#define ZERO_FLAG 0x0002
#define INTERRUPT_DISABLE_FLAG 0x0004
#define DECIMAL_FLAG 0x0008
#define BREAK_FLAG 0x0010
#define OVERFLOW_FLAG 0x0040
#define NEGATIVE_FLAG 0x0080

#define MAX_MEMORY 1024 * 64

#define ASM_SEP ';'
#define ASM_INSTR_BUF_SIZE 4095

#define NULL_TERM '\0'

typedef unsigned char byte;
typedef unsigned short word; // technically only a "half-word" as this is 2 bytes on most platforms instead of 4 bytes
                             // which one would normally call a "word", but that is okay for now

enum instructions {
    LDA, LDX, LDY,
    STA, STX, STY,
    TAX, TAY, TXA,
    TYA, TSX, TXS,
    PHA, PHP, PLA,
    PLP, AND, EOR,
    ORA, BIT, ADC,
    SBC, CMP, CMX,
    CMY, INC, INX,
    INY, DEC, DEX,
    DEY, ASL, LSR,
    ROL, ROR, JMP,
    JSR, RTS, BCC,
    BCS, BEQ, BMI,
    BNE, BPL, BVC,
    BVS, CLC, CLD,
    CLI, CLV, SEC,
    SED, SEI, BRK,
    NOP, RTI
};

enum addressing_mode {
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y
};

struct cpu {
    word m_program_counter;
    word m_stack_pointer;   // this should actually be half the size of the program counter but whatever
    // there is no need for an instruction register here as we execute instructions on the fly even if they take more than one cycle
    byte m_a, m_x, m_y;
    byte m_status;
} cpu;

struct mem {
    byte m_data[MAX_MEMORY];
} mem;

void reset() {
    cpu.m_program_counter = PC_RESET;
    cpu.m_stack_pointer = SP_RESET;
    cpu.m_a = cpu.m_x = cpu.m_y = cpu.m_status = BYTE_RESET;
    for (unsigned int i = 0; i < MAX_MEMORY; i++)
        mem.m_data[i] = BYTE_RESET;
}

int get_instr(char* _buf) {
    int c, i;
    for (i = 0; i < ASM_INSTR_BUF_SIZE - 1 && (c = getchar()) != ASM_SEP; i++)
        _buf[i] = c;
    _buf[i] = NULL_TERM;
    return i;
}

int validate(char* _instr) {
    // TODO: Implement assembly validation, for now assume everything is just about fine
    return 1;
}

void parse_and_execute(char* _instr) {

}

void execute() {
    char instr[ASM_INSTR_BUF_SIZE];
    while (get_instr(instr) > 0 && validate(instr)) {
        parse_and_execute(instr);
    }
}

int main() {
    reset();
    execute();
    return 0;
}
