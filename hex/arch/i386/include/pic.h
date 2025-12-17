#ifndef PIC_H_
#define PIC_H_

/* data strutures and function prototypes that relate to the PIC (programmable interrupt controller) */

#define PIC1							0x20							/* IO base address for master PIC */
#define PIC2						0xA0							/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA			(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA			(PIC2+1)
#define PIC_EOI					0x20							/* End-of-interrupt command code */

void send_eoi(unsigned char irq);

/**
 * new master PIC vectors will be master_offset...master_offset + 7
 * new slave PIC vector will be slave_offset...slave_offset + 7
 */
void remap_pic(unsigned int master_offset, unsigned int slave_offset);

#endif /*PIC_H_*/
