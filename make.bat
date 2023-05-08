@echo off
rem Make Client
rem windres -i client/winres/res.rc -o client/winres/res.o
rem g++ client/*.cpp client/platform/win32/*.cpp common/sockets/windows/*.c common/buffer/*.c client/winres/res.o -o bin/Client/client.exe -g -Iinclude/ -static-libgcc -static-libstdc++ -Llib/ -lsdl2 -lws2_32 -mwindows -mconsole
rem Make Server
g++ server/*.cpp -o bin/Server/server.exe -g -static-libgcc -static-libstdc++ -lws2_32 -mwindows -mconsole
rem Build Complete
echo Build Complete!
