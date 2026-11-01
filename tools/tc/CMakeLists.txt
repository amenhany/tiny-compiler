add_executable(tc
  main.cpp
)

target_link_libraries(tc
  PRIVATE
    tcLexer
    tcSupport
)