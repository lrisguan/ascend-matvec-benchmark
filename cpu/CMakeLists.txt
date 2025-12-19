add_executable(matvec_cpu main_cpu.cpp)
target_link_libraries(matvec_cpu)

install(TARGETS matvec_cpu
        RUNTIME DESTINATION bin)
