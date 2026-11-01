add_library(tcSupport
  SourceMgr.cpp
  MemoryBuffer.cpp
)

target_include_directories(tcSupport
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
