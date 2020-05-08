# unit test runner based on http://www.throwtheswitch.org/build/make
CLEANUP = rm -f
MKDIR = mkdir -p
TARGET_EXTENSION=out

.PHONY: clean
.PHONY: test

PATHU = libs/unity/src/
PATHS = src/
PATHT = test/
PATHL = libs/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

#BUILD_PATHS = $(MKDIR) $(PATHB) $(PATHD) $(PATHO) $(PATHR)

SRCT = $(wildcard $(PATHT)*.c)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -I$(PATHL) -DTEST

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

$(PATHR)Test%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o $(wildcard $(PATHD)*.o) #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.o:: $(PATHL)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

BUILD_PATHS:
	$(MKDIR) $(PATHB) $(PATHD) $(PATHO) $(PATHR)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHU)unity.o

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
