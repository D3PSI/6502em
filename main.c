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

#define INSTR_LDA_IM 0x00A9

#define MAX_MEMORY 1024 * 64

#define ASM_SEP ';'
#define ASM_INSTR_BUF_SIZE 4095

#define NULL_TERM '\0'

typedef unsigned char byte;
typedef unsigned short word; // technically only a "half-word" as this is 2 bytes on most platforms instead of 4 bytes
                             // which one would normally call a "word", but that is okay for now

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

void parse(char* _statement) {}

void compile_and_load() {
    char statement[ASM_INSTR_BUF_SIZE];
    while (get_statement(statement) > 0 && validate(statement)) {
        parse(statement);
    }
}

byte fetch() {
    byte data = mem.m_data[cpu.m_program_counter];
    cpu.m_program_counter++;
    return data;
}

void interpret(byte _instr) {
    switch (_instr) {
    case INSTR_LDA_IM:
        cpu.m_a = fetch();
        if (!cpu.m_a)
            cpu.m_status &= ZERO_FLAG;
        if (cpu.m_a & 0x0080)
            cpu.m_status &= NEGATIVE_FLAG;
        break;
    default:
        break;
    }
}

void run() {
    while (1) {
        byte instr = fetch();
        interpret(instr);
    }
}

int main() {
    reset();
    compile_and_load();
    run();
    return 0;
}
