// Copyright: not something I am interested in

#ifndef GLOBAL_H_
    #define GLOBAL_H_
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <unistd.h>
    #include <malloc.h>
    #include <stdlib.h>
    #include <time.h>
    #include <dirent.h>
    #include <errno.h>
    #include <sys/stat.h>
    typedef struct sigaction sigact;

    typedef struct {
        char killlist[100][100];
        int length;
        unsigned int short errorstatus :1;
        struct timespec timerep;
        // FromSettings
        char exit;
        int nextjump;
        char defaults_path[100], exit_path[100];
        struct timespec time_default;
        int info_time;
    } context;
#endif  // GLOBAL_H_
