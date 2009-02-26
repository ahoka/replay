# CMake project file
# Let's avoid autohell at all costs!

add_executable (
	replay

	file.c
	util.c
	in_mp3.c
	out_ao.c
	playlist.c
	curses.c
	playback.c
	replay.c
	)

target_link_libraries (
	replay
	ncurses
	${LIBAO_LIBRARIES}
	${MPG123_LIBRARIES} )
