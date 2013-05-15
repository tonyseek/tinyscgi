solution "tinyscgi"
    language "C"
    location "build"
    targetdir "target"
    includedirs { "include", "deps/uthash/src" }
    configurations { "debug", "release" }

    configuration "debug"
        defines "_DEBUG"
        flags { "Symbols" }

    configuration "release"
        defines "NDEBUG"
        flags { "Optimize" }

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

-- tinyscgi lua support library
project "tscgilua"
    kind "StaticLib"
    targetname "tscgilua"
    files {
        "include/tscgilua/*.h",
        "src/tscgilua/*.c",
    }
    links { "tscgi", "lua" }

-- tinyscgi command line interface
project "tinyscgi"
    kind "ConsoleApp"
    targetname "tinyscgi"
    files {
        "src/tinyscgi.c",
    }
    links { "tscgi", "tscgisrv", "uv" }

-- tinyscgi lua application server
project "tinyscgi-lua"
    kind "ConsoleApp"
    targetname "tinyscgi-lua"
    files {
        "src/tinyscgi-lua.c",
    }
    links { "tscgi", "tscgisrv", "tscgilua", "uv", "lua" }

-- tinyscgi tests
project "tests"
    kind "ConsoleApp"
    targetname "tests"
    files {
        "tests/*.c"
    }
    links { "check", "tscgi", "tscgilua" }
