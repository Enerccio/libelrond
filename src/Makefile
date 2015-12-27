PREFIX?=
LIBDIR?=$(PREFIX)/lib

MODE ?=debug
ARCH ?=x86_64

include  $(MODE).mk
include  $(ARCH).mk

CFLAGS:= -ffreestanding -std=c99 -Wall -Wextra \
	-fmessage-length=0 -nostdlib \
	 $(MODE_CFLAGS) $(ARCH_CFLAGS) $(CFLAGS_FOR_TARGET) 
CPPFLAGS = $(MODE_CPPFLAGS) $(ARCH_CPPFLAGS) $(CPPFLAGS_FOR_TARGET)

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEP    := $(SRC:.c=.d)
-include $(DEP)

.PHONY: all clean elrond

all: libelrond.a

elrond: libelrond.a

clean:
	-rm -f $(OBJ)
	-rm -f $(wildcard *.d)
ifeq ($(MODE),user)
	-rm -f "$(ADAPTER)"
endif

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -I"../" $< -MM -MF $(patsubst %.o,%.d,$@)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -I"../" $< -o $@
	
libelrond.a: $(OBJ)
	$(AR) -rcs $(LIBDIR)/$@ $(OBJ)