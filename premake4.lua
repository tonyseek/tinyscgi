solution "tinyscgi"
    language "C"
    location "build"
    targetdir "target"
    configurations { "debug", "release" }

    configuration "debug"
        defines "_DEBUG"
        flags { "Symbols" }

    configuration "release"
        defines "NDEBUG"
        flags { "Optimize" }

    libdirs {
        os.findlib("uv")
    }

project "tscgi"
    kind "SharedLib"
    targetname "tscgi"
    includedirs { "src/tscgi" }
    files {
        "src/tscgi/*.c",
        "src/tscgi/*.h",
    }

project "tscgi-server"
    kind "SharedLib"
    targetname "tscgi-server"
    includedirs { "src/tscgi-server" }
    files {
        "src/tscgi-server/*.c",
        "src/tscgi-server/*.h",
    }
    links { "tscgi", "uv" }

project "tscgi-demo"
    kind "ConsoleApp"
    targetname "tscgi-demo"
    files {
        "src/*.c",
    }
    links { "tscgi", "tscgi-server", "uv" }
