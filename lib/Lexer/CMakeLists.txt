add_library(tcLexer
  Lexer.cpp
)

target_include_directories(tcLexer
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tcLexer
  PUBLIC
    tcSupport
)