# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 08-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable (FPGA-Judge.out main.c serial.c
	tcp.c game.c common.c)

find_package(PkgConfig)
pkg_check_modules(LIBSERIAL REQUIRED libserialport)

include_directories(${LIBSERIAL_INCLUDE_DIRS})
link_directories(${LIBSERIAL_LIBRARY_DIRS})
target_link_libraries(FPGA-Judge.out ${LIBSERIAL_LIBRARIES})

pkg_check_modules(LIBGLIB REQUIRED glib-2.0)
include_directories(${LIBGLIB_INCLUDE_DIRS})
link_directories(${LIBGLIB_LIBRARY_DIRS})
target_link_libraries(FPGA-Judge.out ${LIBGLIB_LIBRARIES})
