add_executable(DumpFrames DumpFrames.cpp)
target_link_libraries(DumpFrames Avideo)

add_executable(Playback Playback.cpp)
target_link_libraries(Playback Avideo SDL2)
