idf_component_register(
    SRCS
        # app
            app/main.c
            
        # tasks
            tasks/task_config.h
            tasks/task_snacky/task_snacky.c
            tasks/task_snacky/task_snacky.h
            #tasks/task_reader/task_reader.c
            #tasks/task_reader/task_reader.h
            #tasks/task_wifi/task_wifi.c
            #tasks/task_wifi/task_wifi.h

        # hal

    INCLUDE_DIRS
        tasks
        tasks/task_snacky
        #tasks/task_reader
        #tasks/task_wifi
)