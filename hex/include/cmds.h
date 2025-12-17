#ifndef CMDS_H_
#define CMDS_H_

#include <system.h>
#include <kernel.h>

/* command and parameters of a kernel command */
typedef struct kcmd_s
{
	char cmd[1024];
	char params[1024];
} kcmd_t;

/* define valid return values */
typedef enum
{
	CMD_SUCCESS = 0,
	CMD_FAIL = 1,
	CMD_INVALID = 2,
	CMD_BADPARAM = 3,
	CMD_NODATA = 4,
	CMD_DEPRECATED
} KCMDRET;

#endif /*CMDS_H_*/
