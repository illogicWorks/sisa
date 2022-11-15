all: compile run
compile: folder
	g++ ../src/main.cpp ../src/params.cpp ../src/assembler.cpp -o ../bin/sisa
run: 
	../bin/sisa ../examples/hey.sisa

clean:
	rm -rf ../bin
	@echo "All clean"

folder:
	mkdir -p ../bin
