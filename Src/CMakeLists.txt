#Add new c files to core
add_library(core
        core/linear_regression.c
        core/data.c
        core/recommends.c
        core/run_data.c
)

#compiler det i main
add_executable(FitnessTracker main.c
        core/linear_regression.c
        core/data.c
)



#linker libraries ind i programmet
target_link_libraries(FitnessTracker
        core
)

# gør .h filer synlige for alle targets
target_include_directories(FitnessTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)