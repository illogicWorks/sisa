all: compile run
compile: folder
	g++ ../src/*.cpp -o ../bin/sisa
run: 
	../bin/sisa ../examples/hey.sisa

clean:
	rm -rf ../bin
	@echo "All clean"

folder:
	mkdir -p ../bin
