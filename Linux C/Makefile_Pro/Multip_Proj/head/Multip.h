/*
 Multiplication Computing Program.
 This is Head file.
 struct and macro is defined here.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <curses.h>
#include <ncurses.h>


#define Mul_OK 0
#define Mul_NG -1

#define COL_OFFSET 6
#define ONELINEMAX COLS
#define MAXLEN     100
#define MULRUN     1

/* Multiplier era */
struct Multiplier {
    int    elem            ;/* number     */
    struct Multiplier *next;/* next point */
};

/* Input Stack */
struct Multi_input {
    struct Multiplier *top ;/* stack's top  */
    struct Multiplier *base;/* stack;s base */
    int cnt                ;/* counter      */
};

/* Computed result era */
struct Reslt {
    int    elem       ;/* number     */
    struct Reslt *next;/* next point */
    struct Reslt *head;/* pre point  */

}parameter;

/* Output Stack */
struct Multi_output {
    struct Reslt *top ;/* stack's top  */
    struct Reslt *base;/* stack;s base */
    int cnt           ;/* counter      */
};

/************************ file end *************************/

