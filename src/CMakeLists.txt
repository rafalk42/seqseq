add_executable(seqseq
    main.cpp
    parser.h parser.cpp
    engine.h engine.cpp
    element.h element.cpp
    standard.h standard.cpp
    state.h state.cpp
    seqseq.h
)

target_link_libraries(seqseq TCLAP)
