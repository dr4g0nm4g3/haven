#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <cmds.h>
#include <idt.h>

/* Some screen stuff. */
/* The number of columns. */
#define COLUMNS 80
/* The number of lines. */
#define LINES 24
/* The attribute of an character. */
#define ATTRIBUTE 7
/* The video memory address. */
#define VIDEO 0xB8000

/* # of columns devoted to the first debug vertical partition */
#define DBG_VSEC1_COLS 75
/* # of columns devoted to the second debug vertical partition */
#define DBG_VSEC2_COLS 25
/* # of lines available for first debug horizontal partition */
#define DBG_HSEC1_LINES 12
/* # of lines available for second debug horizontal partition, minus the line devoted to the prompt */
#define DBG_HSEC2_LINES 11

#define CMD_PROMPT "| HEX - 0.0.2 |>"

/* enumeration describing the possible keyboard modifiers */
typedef enum
{
	NONE = 0x0,
	CAPSLOCK = 0x1,
	RSHIFT = 0x2,
	LSHIFT = 0x4,
	RCTRL = 0x8,
	LCTRL = 0x10,
	RALT = 0x20,
	LALT = 0x40,
	SCRLLOCK = 0x80,
	NUMLOCK = 0x100,
	INSERT = 0x200,
	FNLOCK = 0x400
} EKbModifiers;

/* scan codes that will represent these keys in kdbus[]. A keyboard handler
 *	reading the values from the keyboard port will need to recognize these key values
 */
#define LEFT_SHIFT 13
#define RIGHT_SHIFT 14
#define LEFT_ALT 15
#define RIGHT_ALT 16
#define LEFT_CTRL 17
#define RIGHT_CTRL 18
#define INSERT_KEY 19
#define HOME_KEY 20
#define END_KEY 21
#define L_ARROW_KEY 22
#define R_ARROW_KEY 23
#define UP_ARROW_KEY 24
#define DOWN_ARROW_KEY 25
#define DELETE_KEY 26
#define PAGE_UP 27
#define PAGE_DOWN 28
#define F1 29
#define F2 30
#define F3 31
#define F4 32
#define F5 33
#define F6 34
#define F7 35
#define F8 36
#define F9 37
#define F10 38
#define F11 39
#define F12 40
#define CAPS_LOCK 41
#define NUM_LOCK 42
#define SCROLL_LOCK 43
#define ESC_KEY 44
#define BACKSPACE '\b'
#define NEWLINE '\n'
#define LINEFEED '\r'
#define TAB_KEY '\t'

/* IRQ function handler for keyboard interrupts */
void kb_handler(isr_context_t * r);

void cls(void);
void scroll_up(int n);
void scroll_down(int n);
void display_char(int c);
/*
 * Return the key pressed in pKey.
 * Returns true if a key was pressed
 * Returns false if a key couldn't be read.
 */
bool readkb(char * pKey);
int kprint(char * str);
int kprintf(char  * fmt, ...);

void exec_cmd(kcmd_t * cmd);

#endif /*CONSOLE_H_*/
