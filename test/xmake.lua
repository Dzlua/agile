target("console")
  set_languages("cxx11")
  
  add_includedirs("..")
  add_includedirs("../third/OsPlatformUtil/src")

  set_kind("binary")
  
  add_files("console.cc")

target_end()

target("base")
  set_languages("cxx11")

  add_includedirs("..")
  add_includedirs("../third/OsPlatformUtil/src")

  set_kind("binary")
  
  add_files("base.cc")

target_end()