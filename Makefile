#
# Sample Program
#

#H8_PREFIX = /usr/localsv/crossgcc/h8300-hitachi-hms/bin/h8300-hitachi-hms-
H8_PREFIX = /usr/local/h8/bin/h8300-hms-

CC     = $(H8_PREFIX)gcc
OBJCP  = $(H8_PREFIX)objcopy

CFLAGS = -Wall -nostartfiles -mh -mrelax -O2

SOURCES = $(shell find * -name *.c)
TARGET = main

LDSCRIPT    = lib/h8300h.x
STARTUPFILE = lib/crt0.S


all: $(TARGET).srec

$(TARGET).srec: $(SOURCES) Makefile
	$(CC) -T $(LDSCRIPT) $(CFLAGS) -o $(TARGET).coff $(STARTUPFILE) $(SOURCES)
	$(OBJCP) -O srec $(TARGET).coff $@
	rm -f $(TARGET).coff
	@echo ''

clean:
	-rm -f $(TARGET).coff $(TARGET).srec *~ core
	@echo ''
	
program:
	@echo 'Program write start.'
	@h8write -3048 $(TARGET).srec /dev/ttyS0 &> /dev/null
	@echo 'End.'
	@echo ''
