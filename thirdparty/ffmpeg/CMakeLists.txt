include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

include(CheckSymbolExists)
add_definitions(-DHAVE_AV_CONFIG_H)

if(UNIX)
    set(CMAKE_REQUIRED_LIBRARIES "m")
endif()

check_symbol_exists(atanf "math.h" HAVE_ATANF)
check_symbol_exists(atan2f "math.h" HAVE_ATAN2F)
check_symbol_exists(cbrt "math.h" HAVE_CBRT)
check_symbol_exists(cbrtf "math.h" HAVE_CBRTF)
check_symbol_exists(copysign "math.h" HAVE_COPYSIGN)
check_symbol_exists(cosf "math.h" HAVE_COSF)
check_symbol_exists(erf "math.h" HAVE_ERF)
check_symbol_exists(exp2 "math.h" HAVE_EXP2)
check_symbol_exists(exp2f "math.h" HAVE_EXP2F)
check_symbol_exists(expf "math.h" HAVE_EXPF)
check_symbol_exists(hypot "math.h" HAVE_HYPOT)
check_symbol_exists(isfinite "math.h" HAVE_ISFINITE)
check_symbol_exists(isinf "math.h" HAVE_ISINF)
check_symbol_exists(isnan "math.h" HAVE_ISNAN)
check_symbol_exists(ldexpf "math.h" HAVE_LDEXPF)
check_symbol_exists(llrint "math.h" HAVE_LLRINT)
check_symbol_exists(llrintf "math.h" HAVE_LLRINTF)
check_symbol_exists(log2 "math.h" HAVE_LOG2)
check_symbol_exists(log2f "math.h" HAVE_LOG2F)
check_symbol_exists(log10f "math.h" HAVE_LOG10F)
check_symbol_exists(lrint "math.h" HAVE_LRINT)
check_symbol_exists(lrintf "math.h" HAVE_LRINTF)
check_symbol_exists(powf "math.h" HAVE_POWF)
check_symbol_exists(rint "math.h" HAVE_RINT)
check_symbol_exists(round "math.h" HAVE_ROUND)
check_symbol_exists(roundf "math.h" HAVE_ROUNDF)
check_symbol_exists(sinf "math.h" HAVE_SINF)
check_symbol_exists(trunc "math.h" HAVE_TRUNC)
check_symbol_exists(truncf "math.h" HAVE_TRUNCF)

configure_file(config.h.in config.h)
configure_file(config_components.h.in config_components.h)

add_subdirectory(libavutil)
add_subdirectory(libavcodec)
add_subdirectory(libavformat)
