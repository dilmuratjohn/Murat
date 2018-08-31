#Makefile for "Application" -- A C++ OpenGL Project
#Created by Collin Thu/Aug/30 2018


Prog = app/Application
CXX = g++
CC = gcc
Objs = Application.o Render.o Shader.o VertexArray.o VertexBuffer.o IndexBuffer.o VertexBufferLayout.o GLCall.o glad.o
Source_Dir = src
CFLAG = -g -Wall -Ideps/glfw/include -Ideps/glfw/deps
CPPFLAG = -g -Wall -Ideps/glfw/include -Ideps/glfw/deps -std=c++11
Lib_GLFW = -Ldeps/glfw/bin/src -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo




$(Prog) : $(Objs)
	$(CXX) $(Lib_GLFW) -o $(Prog) bin/*.o

Application.o : Render.o Shader.o VertexArray.o VertexBuffer.o IndexBuffer.o VertexBufferLayout.o GLCall.o glad.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/Application.cpp -o bin/Application.o

Render.o: VertexArray.o IndexBuffer.o Shader.o GLCall.o glad.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/Render.cpp -o bin/Render.o

Shader.o : GLCall.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/Shader.cpp -o bin/Shader.o

VertexArray.o : VertexBuffer.o VertexBufferLayout.o GLCall.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/VertexArray.cpp -o bin/VertexArray.o

VertexBuffer.o : GLCall.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/VertexBuffer.cpp -o bin/VertexBuffer.o

IndexBuffer.o : GLCall.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/IndexBuffer.cpp -o bin/IndexBuffer.o

VertexBufferLayout.o : GLCall.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/VertexBufferLayout.cpp -o bin/VertexBufferLayout.o

GLCall.o : glad.o
	$(CXX) $(CPPFLAG) -c $(Source_Dir)/GLCall.cpp -o bin/GLCall.o

glad.o :
	$(CC) $(CFLAG) -c deps/glfw/deps/glad.c -o bin/glad.o




init:
	mkdir deps/glfw/bin && cd deps/glfw/bin && cmake ../. && make && cd - && mkdir -p {bin,app}

clean:
	rm -rf deps/glfw/bin && rm -rf bin && rm -rf app

