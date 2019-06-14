target("console")
  set_languages("cxx11")
  
  add_includedirs("..")
  add_includedirs("../third/OSPlatformUtil/src")

  if not is_os("windows") then
    add_links("pthread")
  end

  set_kind("binary")
  
  add_files("console.cc")

target_end()

target("base")
  set_languages("cxx11")

  add_includedirs("..")
  add_includedirs("../third/OSPlatformUtil/src")

  set_kind("binary")
  
  add_files("base.cc")

target_end()