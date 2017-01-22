include makefile.conf
NAME=minimum
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main -D__NO_SYSTEM_INIT

LDSCRIPTS=-L. -T gcc.ld
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

$(NAME)-$(CORE).axf: $(NAME).c $(STARTUP)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

clean: 
	rm -f $(NAME)*.axf *.map *.o
