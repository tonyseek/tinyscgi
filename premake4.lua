solution "tinyscgi"
    language "C"
    location "build"
    targetdir "target"
    includedirs { "include" }
    configurations { "debug", "release" }

    configuration "debug"
        defines "_DEBUG"
        flags { "Symbols" }

    configuration "release"
        defines "NDEBUG"
        flags { "Optimize" }

    libdirs {
        os.findlib("uv"),
    }

-- tinyscgi core library
project "tscgi"
    kind "SharedLib"
    targetname "tscgi"
    files {
        "include/tscgi/*.h",
        "src/tscgi/*.c",
    }

-- tinyscgi server library
project "tscgisrv"
    kind "SharedLib"
    targetname "tscgisrv"
    files {
        "include/tscgisrv/*.h",
        "src/tscgisrv/*.c",
    }
    links { "tscgi", "uv" }

-- tinyscgi command line interface
project "tinyscgi"
    kind "ConsoleApp"
    targetname "tinyscgi"
    files {
        "src/tinyscgi.c",
    }
    links { "tscgi", "tscgisrv", "uv" }
