workspace "minecraft-clone"
    architecture "x64"
    location "build"
    configurations { "Release", "Debug" }

project "minecraft-clone"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files { 
        "src/**.cpp", 
        "src/**.hpp", 
        "src/**.h", 
        "shaders/**",
        
        "libraries/ImGui/**.cpp", 
        "libraries/stb/**.cpp", 
        "libraries/glad/src/glad.c"
    }

    includedirs { "libraries/*" }
    libdirs "libraries/lib"
    links { "opengl32", "glfw3" }

    filter "configurations:Release"
        optimize "Full"
        defines "RELEASE"

    filter "configurations:Debug"
        defines "DEBUG"