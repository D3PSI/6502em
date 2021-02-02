cmake_minimum_required(VERSION 3.7)

project(6502em)

if(MSVC)
	add_compile_options(/MP)
	add_compile_options(/W4 /wd4201 /WX)
else()
	add_compile_options(-W -Wall -Werror)
endif()

set(6502_SOURCES
    "main.c")

source_group("src" FILES ${6502_SOURCES})

add_executable(6502em ${6502_SOURCES})
