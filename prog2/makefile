0all: main qsort merge

main: main.c
	gcc -o main main.c

qsort: qsort.c
	gcc -o qsort qsort.c

merge: merge.c
	gcc -o merge merge.c

debug: main.c qsort.c merge.c
	gcc -g -Wall -o main main.c
	gcc -g -Wall -o qsort qsort.c
	gcc -g -Wall -o merge merge.c

test: debug
	@echo "[makefile] Test 1:"
	./main < ./input
	@echo "\n[makefile] Verify that there are no remaining shared memory segments:"
	ipcs -m

clean:
	rm main qsort merge