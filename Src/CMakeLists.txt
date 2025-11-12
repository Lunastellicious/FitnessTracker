# CORE LIBRARY
add_library(core
        Core/logic.c
        Core/utils.c
        core/run_data.c
)

# DATABASE LIBRARY
add_library(database
        database/data.c
)

#MAIN EXECUTEABLE
add_executable(FitnessTracker main.c)
add_executable(FitnessTracker core/run_data.c) #tester
add_executable()

# LINK LIBRARIES
target_link_libraries(FitnessTracker
        core
        database
)

# gør .h filer synlige for alle targets
target_include_directories(FitnessTracker PRIVATE ../include)