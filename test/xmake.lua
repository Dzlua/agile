target("test1")
  set_kind("binary")

  -- 添加依赖目标
  add_deps("agile")
  add_links("agile")
  add_linkdirs("$(buildir)")
  add_includedirs("../src")
  
  add_files("test1.cc")

target_end()