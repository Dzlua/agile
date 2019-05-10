-- add rules: debug/release
add_rules("mode.debug", "mode.release")

target("agile")

  set_kind("shared")

  add_headerfiles("src/core/(**.h)")

  add_defines("AGILE_EXPORTS")

  add_files("src/agile/**.cc")

target_end()
  
--test
add_subdirs("test")