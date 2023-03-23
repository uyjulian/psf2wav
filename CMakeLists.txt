
cmake_minimum_required(VERSION 2.8)

project(psf2wav)

set(CMAKE_C_FLAGS_RELEASE "-Wall -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")
set(CMAKE_C_FLAGS_DEBUG "-Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")

add_definitions(-DEMU_COMPILE)
add_definitions(-DEMU_LITTLE_ENDIAN)

add_executable(psf2wav
        src/psf2wav.cpp

        # sexy psf
        # sexypsf_/PsxBios.c
        # sexypsf_/PsxCounters.c
        # sexypsf_/PsxDma.c
        # sexypsf_/Spu.c
        # sexypsf_/PsxHw.c
        # sexypsf_/PsxMem.c
        # sexypsf_/Misc.c
        # sexypsf_/R3000A.c
        # sexypsf_/PsxInterpreter.c
        # sexypsf_/PsxHLE.c
        # sexypsf_/spu/spu.c
        sexypsf/psxbios.c
        sexypsf/psxcounters.c
        sexypsf/psxdma.c
        sexypsf/spu.c
        sexypsf/psxhw.c
        sexypsf/psxmem.c
        sexypsf/misc.c
        sexypsf/r3000a.c
        sexypsf/psxinterpreter.c
        sexypsf/psxhle.c
        sexypsf/spu/spu.c


        # highly experimental
        highly_experimental/psf.cpp
        highly_experimental/psflib/psflib.c
        highly_experimental/psflib/psf2fs.c
        highly_experimental/Highly_Experimental/Core/bios.c
        highly_experimental/Highly_Experimental/Core/iop.c
        highly_experimental/Highly_Experimental/Core/ioptimer.c
        highly_experimental/Highly_Experimental/Core/psx.c
        highly_experimental/Highly_Experimental/Core/r3000.c
        highly_experimental/Highly_Experimental/Core/spu.c
        highly_experimental/Highly_Experimental/Core/spucore.c
        highly_experimental/Highly_Experimental/Core/vfs.c
        highly_experimental/Highly_Experimental/Core/mkhebios.c
)

target_link_libraries(psf2wav z)


