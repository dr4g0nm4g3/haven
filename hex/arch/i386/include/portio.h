#ifndef PORTIO_H_
#define PORTIO_H_

unsigned char inportb (unsigned short _port);
unsigned short inportw(unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif /*PORTIO_H_*/
