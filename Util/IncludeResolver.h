#ifndef SPACEINVADERS_INCLUDERESOLVER_H
#define SPACEINVADERS_INCLUDERESOLVER_H

/*Dependendo do sistema operativo em que o programa for compilado
 * incluir ou o PDCurses(Windows), ou o NCurses(Unix)*/

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGWIN__)
#include <curses.h>
#elif defined(__unix__)
#include <ncurses.h>
#endif

#endif
