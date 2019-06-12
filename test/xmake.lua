target("base")
  add_includedirs("..")
  set_languages("cxx11")

  set_kind("binary")
  
  add_files("base.cc")

target_end()