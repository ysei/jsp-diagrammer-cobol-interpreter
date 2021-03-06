
/*===================================*
 *             ALFILE.H              *
 * declarations of simplified file   *
 * initiation routines               *
 *===================================*/

#ifndef ALFILE
#define ALFILE

#include <stdio.h>

extern FILE *open_input(char *);
extern FILE *open_output(char *);
extern void close_file(FILE *);

#endif

