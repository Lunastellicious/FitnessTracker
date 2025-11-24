#Add new c files to core
add_library(core
        core/logic.c
        core/utils.c
)

#Add new c files to database
add_library(database
        database/data.c
)

#compiler det i main
add_executable(fitnesstracker main.c)

#linker libraries ind i programmet
target_link_libraries(fitnesstracker
        core
        database
)

# gør .h filer synlige for alle targets
target_include_directories(fitnesstracker PRIVATE ../include)