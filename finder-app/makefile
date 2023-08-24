# Select Toolchaing (CROSS_COMPILE or NATIVE)
ifeq ($(PLATFORM),CROSS_COMPILE)
    CC=aarch64-none-linux-gnu-gcc -print-sysroot
else
    CC=gcc
endif

# Set debugging flag
ifeq ($(DEBUG),YES)
    DBG=-g
else
    DBG=
endif

CFLAGS=-I -g # Compilation flags
DEPS= # Dependecies (i.e. header files) 
LIBS= -lc


# Dependency on the include files. If you were to make a change to a header file for example, make would not recompile the .c files,
# even though they needed to be. In order to fix this, we need to tell make that all .c files depend on certain .h files. We can do
# this by writing a simple rule and adding it to the makefile.

all: writer

writer:
	$(CC) -o writer writer.c $(LIBS) $(DBG)

clean:
	rm -rf *.o writer
	
rebuild: clean writer
	
