/*
 * serial.c
 * 	implementation of functions to read and write to serial ports
 *
 *  Created on: Sep 27, 2009
 *      Author: dragon
 */

#include <serial.h>

void init_serial(unsigned short port)
{
	outportb(port + 1, 0x00);    // Disable all interrupts
	outportb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outportb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outportb(port + 1, 0x00);    //                  (hi byte)
	outportb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	outportb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outportb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

char read_serial(unsigned short port)
{
	while((inportb(port + 5) & 1) == 0);

	return (char)inportb(port);
}

void write_serial(unsigned short port, char byte)
{
	while((inportb(port + 5) & 0x20) == 0);

	outportb(port, (unsigned char)byte);
}

void serial_handler(isr_context_t * r)
{

}
