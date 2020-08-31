# unit test runner based on http://www.throwtheswitch.org/build/make
CLEANUP = rm -f
MKDIR = mkdir -p
TARGET_EXTENSION=out

.PHONY: all
all: clean BUILD_PATHS test

PATHU = libs/unity/src/
PATHS = src/
PATHT = test/
PATHL = libs/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

SRCST = $(wildcard $(PATHT)*.c)
SRCSP = $(wildcard $(PATHS)pool/*.c)
SRCSL = $(wildcard $(PATHL)*.c)
SRCSS = $(wildcard $(PATHS)*.c)

COMPILE=gcc -g -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -I$(PATHL) -DTEST -fPIC

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(SRCST) $(SRCSP) $(SRCSL) $(SRCSS)
	$(BUILD_PATHS)
	$(COMPILE) $(CFLAGS) $(PATHL)list.c               -o $(PATHD)list.o
	$(COMPILE) $(CFLAGS) $(PATHS)pool.c               -o $(PATHO)pool.o
	$(COMPILE) $(CFLAGS) $(PATHS)pool/simple_pool.c   -o $(PATHO)simple_pool.o
	$(COMPILE) $(CFLAGS) $(PATHS)libhercules.c        -o $(PATHO)libhercules.o
	$(COMPILE) $(CFLAGS) $(PATHU)unity.c              -o $(PATHD)unity.o
	$(COMPILE) $(CFLAGS) $(PATHT)Testlibhercules.c    -o $(PATHO)Testlibhercules.o
	$(LINK) -o $(PATHB)Testlibhercules.out $(PATHD)list.o $(PATHO)pool.o $(PATHO)simple_pool.o $(PATHO)libhercules.o $(PATHD)unity.o $(PATHO)Testlibhercules.o
	./$(PATHB)Testlibhercules.out > $(PATHR)Testlibhercules.txt 2>&1
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

BUILD_PATHS:
	$(MKDIR) $(PATHB) $(PATHD) $(PATHO) $(PATHR)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHU)unity.o
	$(CLEANUP) $(PATHB)*.so
	$(CLEANUP) $(PATHD)*.d
	$(CLEANUP) $(PATHD)*.o

#so:
#	$(LINK) libs/list.o $(PATHO)libhercules.o -shared -o build/libhercules.so
#
#static:	$(PATHB)libhercules.a

#$(PATHB)libhercules.a: libs/list.o $(PATHO)libhercules.o
#	ar rcs $@ $^

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
