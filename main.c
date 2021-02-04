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

typedef enum {
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
} addressing_mode;

struct cpu {
    word m_program_counter;
    word m_stack_pointer; // this should actually be half the size of the program counter but whatever
    // there is no need for an instruction register here as we execute instructions on the fly even if they take more
    // than one cycle
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

int get_statement(char* _buf) {
    int c, i;
    for (i = 0; i < ASM_INSTR_BUF_SIZE - 1 && (c = getchar()) != ASM_SEP; i++)
        _buf[i] = c;
    _buf[i] = NULL_TERM;
    return i;
}

int validate(char* _statement) {
    // TODO: Implement assembly validation, for now assume everything is just about fine
    return 1;
}

void execute(char* _instruction) {
    if (!strcmp("LDA", _instruction)) {
    }
    if (!strcmp("LDX", _instruction)) {
    }
    if (!strcmp("LDY", _instruction)) {
    }
    if (!strcmp("STA", _instruction)) {
    }
    if (!strcmp("STX", _instruction)) {
    }
    if (!strcmp("STY", _instruction)) {
    }
    if (!strcmp("TAX", _instruction)) {
    }
    if (!strcmp("TAY", _instruction)) {
    }
    if (!strcmp("TXA", _instruction)) {
    }
    if (!strcmp("TYA", _instruction)) {
    }
    if (!strcmp("TSX", _instruction)) {
    }
    if (!strcmp("TXS", _instruction)) {
    }
    if (!strcmp("PHA", _instruction)) {
    }
    if (!strcmp("PHP", _instruction)) {
    }
    if (!strcmp("PLA", _instruction)) {
    }
    if (!strcmp("PLP", _instruction)) {
    }
    if (!strcmp("AND", _instruction)) {
    }
    if (!strcmp("EOR", _instruction)) {
    }
    if (!strcmp("ORA", _instruction)) {
    }
    if (!strcmp("BIT", _instruction)) {
    }
    if (!strcmp("ADC", _instruction)) {
    }
    if (!strcmp("SBC", _instruction)) {
    }
    if (!strcmp("CMP", _instruction)) {
    }
    if (!strcmp("CMX", _instruction)) {
    }
    if (!strcmp("CMY", _instruction)) {
    }
    if (!strcmp("INC", _instruction)) {
    }
    if (!strcmp("INX", _instruction)) {
    }
    if (!strcmp("INY", _instruction)) {
    }
    if (!strcmp("DEC", _instruction)) {
    }
    if (!strcmp("DEX", _instruction)) {
    }
    if (!strcmp("DEY", _instruction)) {
    }
    if (!strcmp("ASL", _instruction)) {
    }
    if (!strcmp("LSR", _instruction)) {
    }
    if (!strcmp("ROL", _instruction)) {
    }
    if (!strcmp("ROR", _instruction)) {
    }
    if (!strcmp("JMP", _instruction)) {
    }
    if (!strcmp("JSR", _instruction)) {
    }
    if (!strcmp("RTS", _instruction)) {
    }
    if (!strcmp("BCC", _instruction)) {
    }
    if (!strcmp("BCS", _instruction)) {
    }
    if (!strcmp("BEQ", _instruction)) {
    }
    if (!strcmp("BMI", _instruction)) {
    }
    if (!strcmp("BNE", _instruction)) {
    }
    if (!strcmp("BPL", _instruction)) {
    }
    if (!strcmp("BVC", _instruction)) {
    }
    if (!strcmp("BVS", _instruction)) {
    }
    if (!strcmp("CLC", _instruction)) {
    }
    if (!strcmp("CLD", _instruction)) {
    }
    if (!strcmp("CLI", _instruction)) {
    }
    if (!strcmp("CLV", _instruction)) {
    }
    if (!strcmp("SEC", _instruction)) {
    }
    if (!strcmp("SED", _instruction)) {
    }
    if (!strcmp("SEI", _instruction)) {
    }
    if (!strcmp("BRK", _instruction)) {
    }
    if (!strcmp("NOP", _instruction)) {
    }
    if (!strcmp("RTI", _instruction)) {
    }
}

void parse_and_execute(char* _statement) {
    // TODO: strip labels etc.
    // for now we know we only give bare instructions
    execute(_statement);
}

void run() {
    char statement[ASM_INSTR_BUF_SIZE];
    while (get_statement(statement) > 0 && validate(statement)) {
        parse_and_execute(statement);
    }
}

int main() {
    reset();
    run();
    return 0;
}
