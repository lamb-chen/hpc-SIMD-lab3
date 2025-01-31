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

EXE=matvec

CC=icx
CFLAGS= -Ofast -qopenmp -march=broadwell -qopt-report=3 -o matvec

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $^ 

.PHONY: all clean

clean:
	rm -f $(EXE)
