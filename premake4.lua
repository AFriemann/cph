solution "cph"
  configurations { "Release" , "Debug" }

  -- if _ACTION == "clean" then
  --   os.rmdir("bin")
  --   os.rmdir("obj")
  -- end

project "cph"
  kind "ConsoleApp"
  language "C"
  targetdir "bin"
  files { "src/core/*.h", "src/core/*.c" }
  --links { "gtk+-3.0", "libgcrypt" }
  buildoptions { "`pkg-config --cflags --libs gtk+-3.0`", "`libgcrypt-config --cflags --libs`" }
  linkoptions { "`pkg-config --cflags --libs gtk+-3.0`", "`libgcrypt-config --cflags --libs`" }

  configuration "Release"
    flags { "Optimize" }

  configuration "Debug"
    flags { "Symbols", "ExtraWarnings" }

project "test"
  kind "ConsoleApp"
  language "C"
  targetdir "test"
  files { "src/**.h", "src/**.c" }
  --links { "gtk+-3.0", "libgcrypt" }
  buildoptions { "`pkg-config --cflags --libs cunit gtk+-3.0`", "`libgcrypt-config --cflags --libs`" }
  linkoptions { "`pkg-config --cflags --libs gtk+-3.0`", "`libgcrypt-config --cflags --libs`" }
