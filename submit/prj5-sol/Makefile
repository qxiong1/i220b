PROJECT = prj5
COURSE = cs220

TARGET = cache-sim

CPPFLAGS = -I $(HOME)/$(COURSE)/include
CFLAGS = -g -Wall -std=c11

LIBDIR = $$HOME/$(COURSE)/lib
LIB = cs220

LDFLAGS = -L $(LIBDIR)
LDLIBS = -l$(LIB)

SRC_FILES = \
  cache-sim.c \
  cache-sim.h \
  main.c \
  Makefile \
  README

OBJS = \
  cache-sim.o \
  main.o 

$(TARGET):	$(OBJS)
		$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -Wl,-rpath=$(LIBDIR) -o $@
clean:		
		rm -f $(OBJS) $(TARGET) fns fns.o *~


