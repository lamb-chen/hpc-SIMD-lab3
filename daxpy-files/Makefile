# Makefile

# EXE=daxpy

# CC=icx
# CFLAGS= -Ofast -fiopenmp -march=broadwell -qopt-report=3 -o d2q9-bgk

# all: $(EXE)

# $(EXE): $(EXE).c
# 	$(CC) $(CFLAGS) $^ 

# .PHONY: all clean

# clean:
# 	rm -f $(EXE)

EXE=daxpy

CC=icx
CFLAGS= -Ofast -no-vec -fiopenmp -march=broadwell -qopt-report=3 -o daxpy

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $^ 

.PHONY: all clean

clean:
	rm -f $(EXE)
