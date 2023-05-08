workspace "FactoryGame"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }
--[[
project "Client"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++11"
    libdirs {"lib/"}
    links {"sdl2"}
    targetdir ("bin/%{prj.name}")
    objdir ("obj/%{prj.name}")

    files
    {
        "client/**.hpp",
        "client/*.cpp",
        "client/platform/win32/*.cpp"
    }

    includedirs
    {
        "include/"
    }
--]]
project "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    targetdir ("bin/%{prj.name}")
    objdir ("obj/%{prj.name}")

    files
    {
        "server/**.cpp"
    }