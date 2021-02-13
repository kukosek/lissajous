file(GLOB_RECURSE sourcelist
  *.c
  *.cc
  *.cpp
  *.cxx)
string(REGEX REPLACE "${RDIR}/" "" relative_sources "${sourcelist}")
string(REPLACE ";" "\n" sources_string "${relative_sources}")
set(sources_string "set(sources\n${sources_string})")
file(WRITE sources.cmake "${sources_string}")
