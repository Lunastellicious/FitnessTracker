#Add new c files to core
add_library(core
        core/logic.c
        core/utils.c
        core/linear_regression.c
)

#Add new c files to database
add_library(database
        database/data.c
)

#compiler det i main
add_executable(FitnessTracker main.c
        core/linear_regression.c
        core/logic.c
        core/utils.c
        database/data.c
)



#linker libraries ind i programmet
target_link_libraries(FitnessTracker
        core
        database
)

# gør .h filer synlige for alle targets
target_include_directories(FitnessTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)