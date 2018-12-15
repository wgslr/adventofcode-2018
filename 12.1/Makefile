run: code
	./code < input

.PHONY: generate
generate: classifier.cpp

classifier.cpp: code moves
	./code generate < moves > $@

code: code.cpp
	g++ --std=c++17 $< -o $@
