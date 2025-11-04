#Add new c files to core
add_library(core
        core/logic.c
        core/utils.c
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