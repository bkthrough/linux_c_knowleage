#
# Makefile for lib
#

CC     = gcc
RM     = rm -fr

ROOT   = $(shell pwd)
HEAD   = $(ROOT)/../head
FLAGS  = -shared -fpic
INCLD  = -I$(HEAD)

LIBNAME = libmultip.so

$(LIBNAME)  : Smultip_user.c
	$(CC) $(FLAGS) -o $@ $+ $(INCLD)

.PHONY     : clean
clean:
	$(RM) $(OBJ) $(LIBNAME)
