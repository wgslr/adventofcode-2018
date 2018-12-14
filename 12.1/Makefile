run: code
	./code < input

generate: code
	./code generate < moves > classifier.cpp

code: code.cpp
	g++ --std=c++17 $< -o $@
