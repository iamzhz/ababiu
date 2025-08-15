set_toolset("cxx", "g++")

target("ababiu")
    set_kind("binary")
    add_files("src/*.cc", "src/*/*.cc")
    set_languages("c++20")
    add_cxxflags("-g", "-Wall", "-Wextra", "-Wpedantic")
    add_defines("DEBUG")
    add_ldflags("-g")

target("clean")
    set_kind("phony")
    on_run(function (target)
        os.rm("src/*.o", "src/*/*.o", "ababiu")
    end)

set_default("ababiu")
