PROJECT = prj4
COURSE = cs220

TARGET = fn-trace

CPPFLAGS = -I $(HOME)/$(COURSE)/include
CFLAGS = -g -Wall -Og -std=c11 -fPIC

LIBDIR = $$HOME/$(COURSE)/lib
LDLIBS =  -l beaengine -ldl -l$(COURSE)
LDFLAGS = -L $(LIBDIR) 

SRC_FILES = \
  fn-trace.c \
  fn-trace.h \
  main.c \
  x86-64_lde.c \
  x86-64_lde.h \
  Makefile \
  README

OBJS = \
  fn-trace.o \
  main.o \
  x86-64_lde.o 

$(TARGET):	$(OBJS)
		$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

clean:		
		rm -f $(OBJS) $(TARGET) fns fns.o *~

$(PROJECT).tar.gz \
dist:		$(SRC_FILES)
		tar -cvf $(PROJECT).tar $(SRC_FILES)
		gzip -f $(PROJECT).tar

DEPENDS:
		gcc $(CPPFLAGS) -MM *.c

fn-trace.o: fn-trace.c fn-trace.h x86-64_lde.h 
main.o: main.c fn-trace.h
x86-64_lde.o: x86-64_lde.c x86-64_lde.h
