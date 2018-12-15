run: code
	./code 20 < input

test: code sample
	./code 20 < sample

.PHONY: generate
generate: classifier.cpp

classifier.cpp: code moves
	./code generate < moves > $@

sampleclassifier.cpp: code samplemoves
	./code generate < samplemoves > $@

code: code.cpp
	g++ --std=c++17 $< -o $@ -O3
