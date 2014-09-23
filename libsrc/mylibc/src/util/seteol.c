/*
 * Copyright(C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/seteol.c - seteol() implementation.
 */

/*
 * End of line character.
 */
char eol = '\n';

/*
 * Set end of line character.
 */
char seteol(char c)
{
	char old;
	
	old = eol;
	eol = c;
	
	return (old);
}
