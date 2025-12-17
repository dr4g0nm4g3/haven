/**
 * console.c - functions for the input and output of the text based console
 *
 * @author Jeff DiClemente
 * @date 07/27/2008
 * */

#include <common.h>
#include <console.h>
#include <portio.h>
#include <kmm.h>
#include <kdbg.h>

/* Save the X position. */
static int xpos;
/* Save the Y position. */
static int ypos;
/* Point to the video memory. */
static volatile unsigned char *video;

/* binary mask that tells which keys are currently held down */
static volatile unsigned long kb_modifiers;

/* console command line buffer */
kcmd_t g_command_buffer;

// define commands
static const char * CLEAR_CMD = "clear";
static const char * PRINT_MEM_CMD = "showmem";
static const char * HELP_CMD = "help";

/* 0 = the previous key pressed was not an escape code
 *  1 = the previous key pressed was an escape code, treat the next scan code differently
 */
//static unsigned int escaped;

/* The US Keyboard Map */
char kbdus[128] = {
										    0,  ESC_KEY, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
										  '9', '0', '-', '=', '\b',	/* Backspace */
										  '\t',			/* Tab */
										  'q', 'w', 'e', 'r',	/* 19 */
										  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
										    LEFT_CTRL,			/* 29   - Control */
										  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
										 '\'', '`',   LEFT_SHIFT,		/* Left shift */
										 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
										  'm', ',', '.', '/',   RIGHT_SHIFT,				/* Right shift */
										  '*',
										    LEFT_ALT,	/* Alt */
										  ' ',	/* Space bar */
										    CAPS_LOCK,	/* Caps lock */
										    F1,	/* 59 - F1 key ... > */
										    F2, F3, F4, F5, F6, F7, F8, F9, F10, 	/* < ... F10 */
										    NUM_LOCK,	/* 69 - Num lock*/
										    SCROLL_LOCK,	/* Scroll Lock */
										    HOME_KEY,	/* Home key */
										    UP_ARROW_KEY,	/* Up Arrow */
										    PAGE_UP,	/* Page Up */
										  '-',
										    L_ARROW_KEY,	/* Left Arrow */
										    0,
										    R_ARROW_KEY,	/* Right Arrow */
										  '+',
										    END_KEY,	/* 79 - End key*/
										    DOWN_ARROW_KEY,	/* Down Arrow */
										    PAGE_DOWN,	/* Page Down */
										    INSERT_KEY,	/* Insert Key */
										    DELETE_KEY,	/* Delete Key */
										    0,   0,   0,
										    F11,	/* F11 Key */
										    F12,	/* F12 Key */
										    0,	/* All other keys are undefined */
};

/* The US Keyboard Map when the Shift key is held */
char kbdus_shift[128] = {
											0,  ESC_KEY, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
										  '(', ')', '_', '+', '\b',	/* Backspace */
										  '\t',			/* Tab */
										  'Q', 'W', 'E', 'R',	/* 19 */
										  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
										    LEFT_CTRL,			/* 29   - Control */
										  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
										 '"', '~',   LEFT_SHIFT,		/* Left shift */
										 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
										  'M', '<', '>', '?',   RIGHT_SHIFT,				/* Right shift */
										  '*',
										    LEFT_ALT,	/* Alt */
										  ' ',	/* Space bar */
										    CAPS_LOCK,	/* Caps lock */
										    F1,	/* 59 - F1 key ... > */
										    F2, F3, F4, F5, F6, F7, F8, F9, F10, 	/* < ... F10 */
										    NUM_LOCK,	/* 69 - Num lock*/
										    SCROLL_LOCK,	/* Scroll Lock */
										    HOME_KEY,	/* Home key */
										    UP_ARROW_KEY,	/* Up Arrow */
										    PAGE_UP,	/* Page Up */
										  '-',
										    L_ARROW_KEY,	/* Left Arrow */
										    0,
										    R_ARROW_KEY,	/* Right Arrow */
										  '+',
										    END_KEY,	/* 79 - End key*/
										    DOWN_ARROW_KEY,	/* Down Arrow */
										    PAGE_DOWN,	/* Page Down */
										    INSERT_KEY,	/* Insert Key */
										    DELETE_KEY,	/* Delete Key */
										    0,   0,   0,
										    F11,	/* F11 Key */
										    F12,	/* F12 Key */
										    0,	/* All other keys are undefined */
};

void kb_handler(isr_context_t * r)
{
	char key = '\0';
	bool bReadValidKey = readkb(&key);

	if(bReadValidKey)
	{
		display_char(key);

		if(key == NEWLINE || key == LINEFEED)
		{	// execute the command stored in the command buffer
			exec_cmd(&g_command_buffer);
			kprint(CMD_PROMPT);
		}
		else
		{
			// append the character to the command buffer,
			// but don't append it if its a return as that
			// indicates the command is to be parsed and executed.
			// FIXME: we are using strncat instead of strcat and
			//	specifying the exact number of characters since
			//	the stack variable, key, isn't terminated and it
			//	sits in memory right next to the bReadValidKey
			//	stack variable. When strcat appends 'key' to
			//	the command buffer, it appends both the value stored
			//	in 'key' and the value stored in 'bReadValidKey'.

			// issue #3: handle case where 'backspace' is pressed.
			//	need to remove the last character out of the command
			//	buffer.
			if(key == BACKSPACE)
			{
				unsigned long last_char_index = strlen(g_command_buffer.cmd);
				if(last_char_index > 0)
					last_char_index--;
				g_command_buffer.cmd[last_char_index] = '\0';
			}
			else
				strncat(g_command_buffer.cmd, &key, 1);
		}
    }
}

void cls(void)
{
	int i;
	video = (unsigned char *) VIDEO;
	for (i = 0; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;

	xpos = 0;
	ypos = 0;
}

/*
  * scroll the screen down by n lines
  */
void scroll_down(int n)
{
	int i = 0;
	video = (unsigned char *) VIDEO;
	for(i = 0; i < COLUMNS * LINES * 2; i++)
	{	// translate the new x,y position of the byte to overwrite the old one in video memory
		*(video + (i * 2)) = *(video + ((i * 2) + (COLUMNS * 2)));
		*(video + ((i * 2) + 1)) = *(video + ((i * 2) + (COLUMNS * 2)) + 1);
	}
	// set cursor position to the last (now blank) line
	xpos = 0;
	ypos = LINES - n;
}

/*
  * scroll the screen up by n lines
  */
void scroll_up(int n)
{

}

bool readkb(char * pKey)
{
	/* Read from the keyboard's data buffer */
	unsigned char scancode = inportb(0x60);

	// can't return a key to the caller...
	if(pKey == NULL)
		return false;

	/* translate scan code to key on the keyboard */
	*pKey = kbdus[scancode];

	/* If the top bit of the byte we read from the keyboard is
	 *  set, that means that a key has just been released */
	if (scancode & 0x80)
	{
		/* You can use this one to see if the user released the
		*  shift, alt, or control keys... */

		// subtract 0x80 from the scancode to get the index into the keyboard map, kbdus[]
		char c = kbdus[scancode - 0x80];

		switch(c)
		{
			case LEFT_CTRL:
				kb_modifiers = kb_modifiers ^LCTRL;
			break;
			case RIGHT_CTRL:
				kb_modifiers = kb_modifiers ^RCTRL;
			break;
			case LEFT_ALT:
				kb_modifiers = kb_modifiers ^ LALT;
			break;
			case RIGHT_ALT:
				kb_modifiers = kb_modifiers ^ RALT;
			break;
			case LEFT_SHIFT:
				kb_modifiers = kb_modifiers ^ LSHIFT;
			break;
			case RIGHT_SHIFT:
				kb_modifiers = kb_modifiers ^ RSHIFT;
			break;
			default:
				break;
		}

		/*
		 * In this case, a key was released, so we tell the caller
		 * that no key was read. We don't count key releases on the
		 * keyboard as reading a valid key from the keyboard.
		 */
		return false;
	}
	else
	{
		/* Here, a key was just pressed. Please note that if you
		*  hold a key down, you will get repeated key press
		*  interrupts. */
		switch(*pKey)
		{
			case LEFT_CTRL:
				kb_modifiers |= LCTRL;
			break;
			case RIGHT_CTRL:
				kb_modifiers |= RCTRL;
			break;
			case LEFT_ALT:
				kb_modifiers |= LALT;
			break;
			case RIGHT_ALT:
				kb_modifiers |= RALT;
			break;
			case LEFT_SHIFT:
				kb_modifiers |= LSHIFT;
			break;
			case RIGHT_SHIFT:
				kb_modifiers |= RSHIFT;
			break;
			case CAPS_LOCK:
			case NUM_LOCK:
			case SCROLL_LOCK:
				break;
			default:
			{
				if((kb_modifiers & RSHIFT) == RSHIFT ||
					(kb_modifiers & LSHIFT) == LSHIFT)
					*pKey = kbdus_shift[scancode];

				return true;
			}
		}
	}

	return false;
}

/* write the parameter c to the screen. */
void display_char(int c)
{
	int character = c;
	if (c == NEWLINE || c == LINEFEED || xpos >= COLUMNS)
	{	// write a newline onto the screen
		xpos = 0;
		ypos++;
		if (ypos >= LINES)
			scroll_down(1);//ypos = 0;
		return;
	}
	else if(c == BACKSPACE)
	{
		character = 0;
		int prompt_len = strlen(CMD_PROMPT);
		if(xpos > prompt_len)
			xpos--;
	}
	else if(ypos >= LINES)
	{
		scroll_down(1);
	}

	// write the character and increment the cursor position
	*(video + (xpos + ypos * COLUMNS) * 2) = character & 0xFF;
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

	if(c != BACKSPACE)
		xpos++;
}

int kprint(char * str)
{
	int num = 0;
	while(*str)
	{
		display_char(*str);
		num++;
		str++;
	}

	return num;
}

int kprintf(char * fmt, ...)
{
	__builtin_va_list va;
	__builtin_va_start(va, fmt);

	char *str;

	while(*fmt)
	{
		char buffer[256];
		switch(*fmt)
		{
			case '%':
				fmt++;
				switch(*fmt)
				{
					case 'c':
						display_char(__builtin_va_arg(va, int));
						break;
					case 'd':
						itoa(__builtin_va_arg(va ,int), 10, buffer);
						kprint(buffer);
						break;
					case 'x':
						uitoa(__builtin_va_arg(va ,unsigned int), 16, buffer);
						kprint(buffer);
						break;
					case 'l':
						uitoa(__builtin_va_arg(va ,unsigned int), 10, buffer);
						kprint(buffer);
						break;
					case 'f':	/* this is not keeping with the traditional printf format */
						ui64toa(__builtin_va_arg(va ,unsigned long long), 16, buffer);
						kprint(buffer);
						break;
					case 's':
						str = (char *)__builtin_va_arg(va, int);
						kprint(str);
						break;
				}
				break;
			default:
				display_char(*fmt);
				break;
		}
		fmt++;
	}
	__builtin_va_end(va);
	return 0;
}

void showhelp()
{
	kprintf("List of commands:\n\n%s\n%s\n%s\n", CLEAR_CMD, PRINT_MEM_CMD, HELP_CMD);
}

void exec_cmd(kcmd_t * cmd)
{
	if(cmd && strlen(cmd->cmd) > 0)
	{
		if(0 == strcmp(cmd->cmd, CLEAR_CMD))
			cls();
		else if(0 == strcmp(cmd->cmd, PRINT_MEM_CMD))
			kdbg_printmem();
		else if(0 == strcmp(cmd->cmd, HELP_CMD))
			showhelp();
		else
			kprintf("Unknown command. Type \"help\"\n");
	}

	// reset the command buffer
	memset(cmd->cmd, '\0', 1024);
}
