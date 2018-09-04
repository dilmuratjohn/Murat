#Makefile for "Application" -- A C++ OpenGL Project
#Created by Collin Thu/Aug/30 2018


CXX = g++ -std=c++11
CC = gcc

Program = app/Application
Objects = Application.o Render.o Shader.o VertexArray.o VertexBuffer.o IndexBuffer.o VertexBufferLayout.o Texture.o stb_image.o Camera.o GLCall.o glad.o

Source_Dir = src
GLAD_Dir = deps/glfw/deps

Include_Flag = -g -Wall -Ideps/glfw/include -Ideps/assimp/include/ -Ideps/glfw/deps -Isrc/vendor
Link_Flag = bin/*.o deps/glfw/src/libglfw3.a deps/assimp/lib/libassimp.dylib


Platform = ${shell uname}

ifeq ($(Platform), Linux)
	Link_Flag += -lGL -lGLU  -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif
ifeq ($(Platform), Darwin)
	Link_Flag += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif


$(Program) : $(Objects)
	$(CXX)  -o $(Program)  $(Link_Flag)
Application.o : Render.o Texture.o Camera.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Application.cpp -o bin/Application.o
Render.o: VertexArray.o IndexBuffer.o Shader.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Render.cpp -o bin/Render.o
VertexArray.o : VertexBuffer.o VertexBufferLayout.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexArray.cpp -o bin/VertexArray.o
Texture.o : stb_image.o GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Texture.cpp -o bin/Texture.o
VertexBufferLayout.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBufferLayout.cpp -o bin/VertexBufferLayout.o
Shader.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Shader.cpp -o bin/Shader.o
VertexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBuffer.cpp -o bin/VertexBuffer.o
IndexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/IndexBuffer.cpp -o bin/IndexBuffer.o
Camera.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Camera.cpp -o bin/Camera.o
GLCall.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/GLCall.cpp -o bin/GLCall.o
stb_image.o : 
	$(CXX) $(Include_Flag) -c $(Source_Dir)/vendor/stb_image/stb_image.cpp -o bin/stb_image.o
glad.o :
	$(CC)  $(Include_Flag) -c ${GLAD_Dir}/glad.c -o bin/glad.o


init:
	cd deps/glfw && cmake . && make 
	cd deps/assimp && cmake . && make
	mkdir -p bin app 


clean:
	rm -rf bin && rm -rf app
