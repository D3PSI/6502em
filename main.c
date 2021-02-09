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
#define INSTR_LDA_ZP 0x00A5
#define INSTR_LDA_ZPX 0x00B5
#define INSTR_JSR_AB 0x0020

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

byte fetchm(byte _address) {
    // TODO: Handle overflow
    return mem.m_data[_address];
}

byte writem(byte _address, byte _value) { return mem.m_data[_address] = _value; }

byte fetchb() {
    // TODO: Handle overflow
    byte data = mem.m_data[cpu.m_program_counter];
    cpu.m_program_counter++;
    return data;
}

byte writeb(byte _address, byte _value) { return mem.m_data[_address] = _value; }

word fetchw() {
    // 6502 is little endian
    word data = fetchm(cpu.m_program_counter++);
    data |= (fetchm(cpu.m_program_counter++) << 8);
    // swap bytes here to handle endianness
    return data;
}

word writew(byte _address, word _value) {
    mem.m_data[_address] = _value & 0x00FF;
    mem.m_data[_address + 1] = (_value >> 8);
    return _value;
}

void set_load_accumulator_status() {
    if (!cpu.m_a)
        cpu.m_status &= ZERO_FLAG;
    if (cpu.m_a & 0x0080)
        cpu.m_status &= NEGATIVE_FLAG;
}

void interpret(byte _instr) {
    switch (_instr) {
    case INSTR_LDA_IM: {
        cpu.m_a = fetchb();
        set_load_accumulator_status();
    } break;
    case INSTR_LDA_ZP: {
        byte zero_page_address = fetchb();
        cpu.m_a = fetchm(zero_page_address);
        set_load_accumulator_status();
    } break;
    case INSTR_LDA_ZPX: {
        byte zero_page_address = fetchb();
        zero_page_address += cpu.m_x;
        cpu.m_a = fetchm(zero_page_address);
        set_load_accumulator_status();
    } break;
    case INSTR_JSR_AB: {
        word sub_addr = fetchw();
        writew(cpu.m_stack_pointer, cpu.m_program_counter - 1);
        cpu.m_program_counter = sub_addr;
        cpu.m_stack_pointer++;
    } break;
    default: {
    } break;
    }
}

void run() {
    while (1) {
        byte instr = fetchb();
        interpret(instr);
    }
}

int main() {
    reset();
    compile_and_load();
    run();
    return 0;
}
