generate:
	gcc generate.c -o gen_out && ./gen_out && rm gen_out

quick:
	gcc main.c ./src/mergesort.c -o out