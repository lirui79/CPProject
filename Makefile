INCLUDE =  -I./
LIBS = -L./  -lpthread -g
SRCPATH = ./

all:Log.so SurfaceManagerClient.so SurfaceManager.so  WindowManager.so ModuleManager.so main 

SurfaceManagerClient.so:SurfaceManagerClient.cpp SmartObject.cpp Mutex.cpp
	g++ -std=c++11 $(INCLUDE) $(LIBS) -fPIC -shared SurfaceManagerClient.cpp SmartObject.cpp Mutex.cpp -o libSurfaceManagerClient.so

SurfaceManager.so:SurfaceManager.cpp SmartObject.cpp Mutex.cpp
	g++ -std=c++11 $(INCLUDE) $(LIBS) -fPIC -shared SurfaceManager.cpp SmartObject.cpp Mutex.cpp -o libSurfaceManager.so

ModuleManager.so:ModuleManager.cpp SmartObject.cpp Mutex.cpp
	g++ -std=c++11 $(INCLUDE) $(LIBS) -fPIC -shared ModuleManager.cpp SmartObject.cpp Mutex.cpp -ldl -o libModuleManager.so

WindowManager.so:WindowManager.cpp SmartObject.cpp Mutex.cpp
	g++ -std=c++11 $(INCLUDE) $(LIBS) -fPIC -shared WindowManager.cpp SmartObject.cpp Mutex.cpp -o libWindowManager.so

Log.so:Log.cpp SmartObject.cpp Mutex.cpp
	g++ -std=c++11 $(INCLUDE) $(LIBS) -fPIC -shared Log.cpp SmartObject.cpp Mutex.cpp -o libLog.so

main:main.cpp
	g++ -std=c++11 main.cpp -L./  -ldl  -lpthread -lModuleManager -lLog -o main

clean:
	rm *.o *.so main