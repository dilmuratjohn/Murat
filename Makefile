#Makefile for "Application" -- A OpenGL Project
#Created by Murat Thu/Aug/30 2018


CXX = g++ -std=c++11
CC = gcc

Program = Application
Objects = Application.o Render.o Shader.o VertexArray.o VertexBuffer.o IndexBuffer.o VertexBufferLayout.o Texture.o stb_image.o Camera.o GLCall.o glad.o

Source_Dir = Murat/src
Vendor_Dir = Murat/vendor

Include_Flag = -g -Wall -Wformat -I$(Vendor_Dir)/glfw/include -I$(Vendor_Dir)/assimp/include/ -I$(Vendor_Dir)/glad/include/ -I$(Vendor_Dir)/glfw/deps -I$(Vendor_Dir)/spdlog/include -I$(Source_Dir) -I$(Vendor_Dir) -I$(Vendor_Dir)/imgui
Link_Flag = *.o $(Vendor_Dir)/glfw/src/libglfw3.a $(Vendor_Dir)/assimp/lib/libassimp.dylib


Platform = ${shell uname -s}

ifeq ($(Platform), Linux)
	ECHO_MESSAGE = "Linux"
	Link_Flag += -lGL -lGLU  -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
endif
ifeq ($(Platform), Darwin)
	ECHO_MESSAGE = "Mac OS X"
	Link_Flag += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif
ifeq ($(Platform), MINGW)
	ECHO_MESSAGE = "Windows"
	Link_Flag += -lgdi32 -lopengl32 -limm32
	CFLAGS = $(CXXFLAGS)
endif


$(Program) : $(Objects)
	$(CXX)  -o $(Program)  $(Link_Flag)
Application.o : Model.o Camera.o MyImGuiClearColor.o Render.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Application.cpp -o Application.o

Model.o: Mesh.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/model/Model.cpp -o Model.o
Mesh.o: Render.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/model/Mesh.cpp -o Mesh.o

MyImGuiClearColor.o: MyImGui.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/imgui/MyImGuiClearColor.cpp -o MyImGuiClearColor.o
MyImGui.o: Render.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/imgui/MyImGui.cpp -o MyImGui.o

Render.o: VertexArray.o IndexBuffer.o FrameBuffer.o RenderBuffer.o Shader.o Texture.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/Render.cpp -o Render.o
VertexArray.o : VertexBuffer.o VertexBufferLayout.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/VertexArray.cpp -o VertexArray.o
VertexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/VertexBuffer.cpp -o VertexBuffer.o
VertexBufferLayout.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/VertexBufferLayout.cpp -o VertexBufferLayout.o
IndexBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/IndexBuffer.cpp -o IndexBuffer.o
FrameBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/FrameBuffer.cpp -o FrameBuffer.o
RenderBuffer.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/RenderBuffer.cpp -o RenderBuffer.o
Shader.o : GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/Shader.cpp -o Shader.o
Texture.o : stb_image.o GLCall.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/render/Texture.cpp -o Texture.o
Camera.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/Camera.cpp -o Camera.o
GLCall.o : glad.o
	$(CXX) $(Include_Flag) -c $(Source_Dir)/GLCall.cpp -o GLCall.o

stb_image.o : 
	$(CXX) $(Include_Flag) -c $(Vendor_Dir)/stb_image/stb_image.cpp -o stb_image.o
glad.o :
	$(CC)  $(Include_Flag) -c ${Vendor_Dir}/glad/src/glad.c -o glad.o

imgui_impl_opengl3.o: imgui.o imgui_draw.o imgui_widgets.o imgui_demo.o
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/examples/imgui_impl_opengl3.cpp -o imgui_impl_opengl3.o
imgui_impl_glfw.o: imgui.o
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/examples/imgui_impl_glfw.cpp -o imgui_impl_glfw.o
imgui.o:
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/imgui.cpp -o imgui.o
imgui_draw.o:
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/imgui_draw.cpp -o imgui_draw.o
imgui_widgets.o:
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/imgui_widgets.cpp -o imgui_widgets.o
imgui_demo.o:
	$(CXX) $(Include_Flag) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c ${Vendor_Dir}/imgui/imgui_demo.cpp -o imgui_demo.o

install:
	cd ${Vendor_Dir}/glfw && cmake . && make 
	cd ${Vendor_Dir}/assimp && cmake . && make
	cd ${Vendor_Dir}/spdlog && cmake . && make
	mkdir -p bin app 

clean:
	rm -rf Application *.o
