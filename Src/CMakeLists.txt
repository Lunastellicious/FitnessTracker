#Add new c files to core
add_library(core
        Core/logic.c
        Core/utils.c
)

#Add new c files to database
add_library(database
        database/data.c
)

add_executable(untitled main.c)

target_link_libraries(untitled
        core
        database
)
# gør .h filer synlige for alle targets
target_include_directories(untitled PRIVATE ../include)