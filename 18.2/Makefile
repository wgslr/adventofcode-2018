run: code
	./code 1000 < input

test: code.test sample
	./code.test < sample

code.test: code.c
	gcc  $< -o $@ -O0 -g -DTEST

code: code.c
	gcc  $< -o $@ -O3
