TARGET = bits-to-ints

OFILES = \
  main.o \
  bits-to-ints.o \
  errors.o

CFLAGS = -g -Wall -std=c11

$(TARGET): 	$(OFILES)
		$(CC) $(OFILES) $(LDFLAGS) -o $@

.phony:		clean

clean:
		rm -f *~ $(OFILES) $(TARGET) 


bits-to-ints.o: bits-to-ints.c bits-to-ints.h errors.h

