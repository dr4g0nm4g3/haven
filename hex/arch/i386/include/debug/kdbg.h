/*
 * kdbg.h
 * 	function declarations for kernel debugging
 *
 *  Created on: Jun 7, 2009
 *      Author: dragon
 */

#ifndef KDBG_H_
#define KDBG_H_

#include <system.h>
#include <idt.h>

/**
 * 	\brief turn debugging on or off
 * 	\details this function controls setting and clearing the trace flag
 *
 * @param[in] bOn 0 means turn debugging off, 1 means on
 */
void set_trace(int bOn);

/**
 * 	\brief causes a breakpoint exception and pauses execution
 * 	\details calls int 3
 */
void dbg_break();

/**
 *	\brief single step to the next instruction and pause execution
 *	\details calls int 1
 */
void step();

/**
 *	\brief prints out debugging information
 *
 * @param[in] r pointer to an isr_context_t structure containing the current state of registers
 */
void print_dbg_info(isr_context_t * r);

/**
 *	\brief prints out a stack trace
 *
 * @param[in] r pointer to an isr_context_t structure containing the current state of the registers
 */
void print_stack_trace(isr_context_t * r);

/**
 *	\brief pauses execution until a key is pressed to execute the next instruction
 */
void pause();

/**
 *	\brief translates an unsigned int eflags value into the string representation of EFLAGS
 *
 * @param[in] eflags unsigned int value to convert into a string
 * @return the string representation of EFLAGS
 */
char * eflags_to_string(unsigned int eflags, char * outBuf);

/**
 *	\brief translates an instruction pointer into a string
 *
 * @param[in] eip unsigned int pointing to an instruction
 * @return the string representation of the instruction pointed to by eip
 */
char * eip_to_string(unsigned int eip, char * outBuf);

/**
 * 	\brief log debug strings to a file
 * 	\details writes the debug messages to the COM 4 port
 *
 * @param message char array of a string to write to the log file
 */
void kdbg_log(char * message, ...);

#endif /* KDBG_H_ */
