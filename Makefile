#Makefile for "Application" -- A C++ OpenGL Project
#Created by Collin Thu/Aug/30 2018


CXX = g++ -std=c++11
CC = gcc

Program = app/Application
Objects = bin/Application.o bin/Render.o bin/Shader.o bin/VertexArray.o bin/VertexBuffer.o bin/IndexBuffer.o bin/VertexBufferLayout.o bin/Texture.o bin/stb_image.o bin/Camera.o bin/GLCall.o bin/glad.o

Source_Dir = src
GLAD_Dir = deps/glad/src

Include_Flag = -g -Wall -Ideps/glfw/include -Ideps/assimp/include/ -Ideps/glad/include/ -Ideps/glfw/deps -Isrc/vendor
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
bin/Application.o : bin/Model.o bin/Texture.o bin/Camera.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Application.cpp -o bin/Application.o
bin/Model.o: bin/Mesh.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Model.cpp -o bin/Model.o
bin/Mesh.o: bin/Render.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Mesh.cpp -o bin/Mesh.o
bin/Render.o: bin/VertexArray.o bin/IndexBuffer.o bin/Shader.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Render.cpp -o bin/Render.o
bin/VertexArray.o : bin/VertexBuffer.o bin/VertexBufferLayout.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexArray.cpp -o bin/VertexArray.o
bin/Texture.o : bin/stb_image.o bin/GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Texture.cpp -o bin/Texture.o
bin/VertexBufferLayout.o : bin/GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBufferLayout.cpp -o bin/VertexBufferLayout.o
bin/Shader.o : bin/GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Shader.cpp -o bin/Shader.o
bin/VertexBuffer.o : bin/GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBuffer.cpp -o bin/VertexBuffer.o
bin/IndexBuffer.o : bin/GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/IndexBuffer.cpp -o bin/IndexBuffer.o
bin/Camera.o : bin/glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Camera.cpp -o bin/Camera.o
bin/GLCall.o : bin/glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/GLCall.cpp -o bin/GLCall.o
bin/stb_image.o : 
	$(CXX) $(Include_Flag) -c $(Source_Dir)/vendor/stb_image/stb_image.cpp -o bin/stb_image.o
bin/glad.o :
	$(CC)  $(Include_Flag) -c ${GLAD_Dir}/glad.c -o bin/glad.o


init:
	cd deps/glfw && cmake . && make 
	cd deps/assimp && cmake . && make
	mkdir -p bin app 


clean:
	rm -rf bin && rm -rf app
