message("libqrencode")

sdk_generate_library()
set(SOURCES qrencode.c
    qrencode.c
    qrinput.c
    bitstream.c
    qrspec.c
    rsecc.c
    split.c
    mask.c
    mqrspec.c
    mmask.c)
set(QRENCODE_HDRS qrencode_inner.h
    qrinput.h
    bitstream.h
    qrspec.h
    rsecc.h
    split.h
    mask.h
    mqrspec.h
    mmask.h)
sdk_library_add_sources(${SOURCES} ${QRENCODE_HDRS})
sdk_add_include_directories(.)