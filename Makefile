#Makefile for "Application" -- A OpenGL Project
#Created by Murat Thu/Aug/30 2018


CXX = g++ -std=c++11
CC = gcc

Program = Application
Objects = Application.o Render.o Shader.o VertexArray.o VertexBuffer.o IndexBuffer.o VertexBufferLayout.o Texture.o stb_image.o Camera.o GLCall.o glad.o

Source_Dir = Murat/src
Vendor_Dir = Murat/vendor

Include_Flag = -g -Wall -I$(Vendor_Dir)/glfw/include -I$(Vendor_Dir)/assimp/include/ -I$(Vendor_Dir)/glad/include/ -I$(Vendor_Dir)/glfw/deps -I$(Vendor_Dir)/spdlog/include -I$(Vendor_Dir) -I$(Vendor_Dir)/imgui
Link_Flag = *.o $(Vendor_Dir)/glfw/src/libglfw3.a $(Vendor_Dir)/assimp/lib/libassimp.dylib


Platform = ${shell uname}

ifeq ($(Platform), Linux)
	Link_Flag += -lGL -lGLU  -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif
ifeq ($(Platform), Darwin)
	Link_Flag += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif


$(Program) : $(Objects)
	$(CXX)  -o $(Program)  $(Link_Flag)
Application.o : Model.o Texture.o Camera.o imgui.o imgui_draw.o imgui_widgets.o imgui_demo.o imgui_impl_opengl3.o imgui_impl_glfw.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Application.cpp -o Application.o
Model.o: Mesh.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Model.cpp -o Model.o
Mesh.o: Render.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Mesh.cpp -o Mesh.o
Render.o: VertexArray.o IndexBuffer.o Shader.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Render.cpp -o Render.o
VertexArray.o : VertexBuffer.o VertexBufferLayout.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexArray.cpp -o VertexArray.o
Texture.o : stb_image.o GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Texture.cpp -o Texture.o
VertexBufferLayout.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBufferLayout.cpp -o VertexBufferLayout.o
Shader.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Shader.cpp -o Shader.o
VertexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/VertexBuffer.cpp -o VertexBuffer.o
IndexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/IndexBuffer.cpp -o IndexBuffer.o
Camera.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Camera.cpp -o Camera.o
GLCall.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/GLCall.cpp -o GLCall.o
stb_image.o : 
	$(CXX) $(Include_Flag) -c $(Vendor_Dir)/stb_image/stb_image.cpp -o stb_image.o
glad.o :
	$(CC)  $(Include_Flag) -c ${Vendor_Dir}/glad/src/glad.c -o glad.o
imgui_impl_opengl3.o: imgui.o
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/examples/imgui_impl_opengl3.cpp -o imgui_impl_opengl3.o
imgui_impl_glfw.o: imgui.o
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/examples/imgui_impl_glfw.cpp -o imgui_impl_glfw.o
imgui.o:
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/imgui.cpp -o imgui.o
imgui_draw.o:
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/imgui_draw.cpp -o imgui_draw.o
imgui_widgets.o:
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/imgui_widgets.cpp -o imgui_widgets.o
imgui_demo.o:
	$(CXX) $(Include_Flag) -c ${Vendor_Dir}/imgui/imgui_demo.cpp -o imgui_demo.o
init:
	cd ${Vendor_Dir}/glfw && cmake . && make 
	cd ${Vendor_Dir}/assimp && cmake . && make
	cd ${Vendor_Dir}/spdlog && cmake . && make
	mkdir -p bin app 


clean:
	rm -rf Application *.o
