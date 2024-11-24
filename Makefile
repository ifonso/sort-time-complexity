generate:
	gcc generate.c -o gen_out && ./gen_out && rm gen_out

mergesort:
	gcc main.c ./src/mergesort.c ./src/quicksort.c ./src/heapsort.c -o out && ./out mergesort

quicksort:
	gcc main.c ./src/mergesort.c ./src/quicksort.c ./src/heapsort.c -o out && ./out quicksort

heapsort:
	gcc main.c ./src/mergesort.c ./src/quicksort.c ./src/heapsort.c -o out && ./out heapsort
