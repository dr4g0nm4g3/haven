/*
 * serial.h
 * 	functions for accessing the serial ports
 *
 *  Created on: Jul 18, 2009
 *      Author: dragon
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <portio.h>
#include <idt.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void init_serial(unsigned short port);
char read_serial(unsigned short port);
void write_serial(unsigned short port, char byte);
void serial_handler(isr_context_t * r);

#endif /* SERIAL_H_ */
