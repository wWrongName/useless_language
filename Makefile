CC=g++

all:
	$(CC) Interpreter.cpp lexer.cpp preproc.cpp parser.cpp -o interpreter
