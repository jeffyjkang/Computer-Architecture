#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cpu.h"

#define DATA_LEN 6

/**
 * Read / Write ram
 */

// function to read cpu ram, takes cpu struct and int address
unsigned char cpu_ram_read(struct cpu *cpu, int address)
{
  // return cpu ram value at address
  return cpu->ram[address];
}
// function to write cpu ram, takes cpu struct, int address, value, no return
void cpu_ram_write(struct cpu *cpu, int address, unsigned char value)
{
  // assign value to cpu ram at address
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
// update cpu_load to accept second arg filename
void cpu_load(struct cpu *cpu, char *filename)
{
  // char data[DATA_LEN] = {
  //     // From print8.ls8
  //     0b10000010, // LDI R0,8
  //     0b00000000,
  //     0b00001000,
  //     0b01000111, // PRN R0
  //     0b00000000,
  //     0b00000001 // HLT
  // };

  // int address = 0;

  // for (int i = 0; i < DATA_LEN; i++)
  // {
  //   cpu->ram[address++] = data[i];
  // }

  // TODO: Replace this with something less hard-coded
}

// /**
//  * ALU
//  */
// void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
// {
//   switch (op)
//   {
//   case ALU_MUL:
//     // TODO
//     break;

//     // TODO: implement more ALU ops
//   }
// }

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction
  // init

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // init instruction register to the return value of cpu ram read function
    // pass in cpu and cpu pc register memory address
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);
    // read bytes at pc+1 pass to operandA
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    // read bytes at pc+2 pass to operandB
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);
    // 2. Figure out how many operands this next instruction requires
    // switch statement for Instruction register
    switch (IR)
    {
      //for case halt, halt cpu and exit the emulator
    case HLT:
      // change value of running to stop the while loop
      running = 0;
      //
      // cpu->pc += 1;
      // exit code
      exit(1);
      // break
      break;
      // case LDI, load immediate, stor value in register
    case LDI:
      // value in cpu registers operandA or pc ram address 1, assign to pc ram address 2
      cpu->registers[operandA] = operandB;
      // move to ram address 3
      cpu->pc += 3;
      // break
      break;
      // case print
    case PRN:
      // print value of cpu registers cpu->pc +1 address
      printf("%d\n", cpu->registers[operandA]);
      // move to address 3
      cpu->pc += 2;
      // break
      break;
      // default case
    default:
      // error for unknown instructions
      printf("Unrecognized instruction\n");
      //exit code
      exit(1);
      // break
      break;
    }
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  // memset syntax = ptr, value, number of bytes
  // init cpu pc to 0
  cpu->pc = 0;
  // init cpu registers to 0
  memset(cpu->registers, 0, 8);
  // init cpu ram to 0
  memset(cpu->ram, 0, 256);
}
