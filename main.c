/*
 * a tiny utility to launch $SHELL as a login shell (for kde & the
 * BIZARRE inability of konsole to launch a login shell by itself)
 *
 * Public domain code; do with it as thou wilt.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/*
 * A lot of unices don't have basename(), so do my own and give it
 * a different name so it won't clash with a basename() on one that
 * does.
 */
char *
mybasename(char *path)
{
    char *slash = strrchr(path, '/');

    return slash ? slash : path;
}


/* grab $SHELL (/bin/sh if none), pick out the program name from the
 * command line, prefix it with -, then exec $SHELL with the prefixed
 * program name as argv[0] and no other arguments.
 */
int /*sigh*/
main(argc,argv)
char **argv;
{

    char *shell = getenv("SHELL");
    char *pgm, *arg0;


    if ( !shell ) shell="/bin/sh";

    pgm = mybasename(shell);

    if ( (arg0 = malloc(2+strlen(pgm))) ) {
	sprintf(arg0, "-%s", pgm);
	execl(shell, arg0, 0);
	perror("execl");
    }
    else
	perror("malloc");
    exit(1);
}
