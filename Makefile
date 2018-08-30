#Makefile for "Application" -- A C++ OpenGL Project
#Created by Collin Thu/Aug/30 2018


Prog = app/Application
CC = g++
Objs = Application.o glad.o


CPPFLAG = -g -Wall -Ideps/glfw/include -Ideps/glfw/deps
Lib_GLFW = -Ldeps/glfw/bin/src -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
Source_Dir = src



$(Prog) : $(Objs)
	$(CC) $(Lib_GLFW) -o $(Prog) bin/*.o

Application.o : glad.o
	$(CC) $(CPPFLAG) -c $(Source_Dir)/Application.cpp -o bin/Application.o

glad.o :
	$(CC) $(CPPFLAG) -c deps/glfw/deps/glad.c -o bin/glad.o




init:
	mkdir deps/glfw/bin && cd deps/glfw/bin && cmake ../. && make && cd - && mkdir -p {bin,app}

clean:
	rm -rf deps/glfw/bin && rm -rf bin && rm -rf app

