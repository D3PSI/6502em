#include <stdio.h>
#include <stdlib.h>

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

typedef unsigned char byte;
typedef unsigned short word;

struct cpu {
    word m_program_counter;
    word m_stack_pointer;
    byte m_a, m_x, m_y;
    byte m_status;
} cpu;

struct mem {
    byte m_data[MAX_MEMORY];
} mem;

void init_mem() {
    for (unsigned int i = 0; i < MAX_MEMORY; i++)
        mem.m_data[i] = BYTE_RESET;
}

void reset() {
    cpu.m_program_counter = PC_RESET;
    cpu.m_stack_pointer = SP_RESET;
    cpu.m_a = cpu.m_x = cpu.m_y = cpu.m_status = BYTE_RESET;
    init_mem();
}

int main() {
    reset();
    return 0;
}
