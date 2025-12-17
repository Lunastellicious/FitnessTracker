#Add new c files to core
add_library(core
        core/linear_regression.c
        core/run_data.c
        core/data.c
        core/generate_run.c
)

#Add new c files to database
add_library(run_output
        run_output/recommends.c
)

#compiler det i main
add_executable(FitnessTracker main.c
        core/linear_regression.c
        core/data.c
)



#linker libraries ind i programmet
target_link_libraries(FitnessTracker
        core
        run_output
)

# gør .h filer synlige for alle targets
target_include_directories(FitnessTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)