// Copyright: Not a thing I want to do

#include "../global.h"

void ignore() {}

void user_inter_handler() {
    extern context cont;
    // REGION SIGNALS
        struct sigaction
            actionset = {
                .sa_handler = ignore,
                .sa_flags = 0,
            };
        sigset_t sensible_set_handler, unsensible_set_handler, oset;
        sigemptyset(&sensible_set_handler);
        sigfillset(&unsensible_set_handler);
        sigaddset(&sensible_set_handler, SIGRTMIN);
        sigdelset(&unsensible_set_handler, SIGRTMIN);
        sigprocmask(SIG_UNBLOCK, &sensible_set_handler, &oset);
        sigprocmask(SIG_BLOCK, &unsensible_set_handler, NULL);
        sigaction(SIGRTMIN, &actionset, NULL);
    // ENDREGION
    // REGION STATIC
        static char flag = 0;
        static struct timespec time_last_act = {.tv_sec = 0, .tv_nsec = 0};
        if (flag == 0) {
            clock_gettime(CLOCK_REALTIME, &time_last_act);
        }
    // ENDREGION
    // REGION TIMER BUILD
        timer_t temp;
        struct timespec
            time1 = {
                .tv_sec = 10,
                .tv_nsec = 0,
            },
            time0 = {
                .tv_sec = 0,
                .tv_nsec = 0,
            },
            time_curr_act;
        clock_gettime(CLOCK_REALTIME, &time_curr_act);

        struct itimerspec a = {
                .it_value = time1,
                .it_interval = time0,
            };

        struct sigevent event = {
                .sigev_signo = SIGRTMIN,
                .sigev_notify = SIGEV_SIGNAL,
                .sigev_value.sival_ptr = (void *)&temp,
            };

        timer_create(CLOCK_REALTIME, &event, &temp);
    // ENDREGION
    timer_settime(temp, 0, &a, NULL);
    // Runs timer to cancel scaning for a long time

    char buff[15];
    int mins;
    int timesig = 0;
    if (time_curr_act.tv_sec - time_last_act.tv_sec > cont.nextjump) {
        printf("\nInteracting:\t");
        timesig = scanf("%10s %d", buff, &mins);
    }
    if (timesig == 1) {
        if (strcmp(buff, "q") == 0) {
            printf("exiting\n");
            char instruction[180];
            if (cont.exit == 1) {
                sprintf(instruction, "%s %s", "sed -i '$d'", cont.exit_path);
                // No way to delete a closed folder
                system(instruction);
            }
            exit(0);
        } else {
            printf("Actions:\n");
            printf("\tq var?: Quits\n");
            printf("\tt var: Time Off\n");
            printf("\tn var: Sets Next Period\n");
        }
    } else if (timesig == 2) {
        a.it_value = time0;
        a.it_interval = time0;
        // Cancel the timer
        timer_settime(temp, 0, &a, NULL);

        if (strcmp(buff, "t") == 0) {
            printf("starting break\n");
            int time_rest = mins*60;
            while (time_rest) {
                time_rest = sleep(time_rest);
                // It will recieve the interruptions of the regular killer timer
            }
        } else if (strcmp(buff, "n") == 0) {
            cont.nextjump = mins * 60;
        } else if (strcmp(buff, "q") == 0) {
            printf("exiting\n");
            char instruction[180];
            if (cont.exit == 1) {
                sprintf(instruction, "%s %s", "sed -i '$d'", cont.exit_path);
                // No way to delete a closed folder
                system(instruction);
            }
            exit(0);
        } else {
            printf("Actions:\n");
            printf("\tq var?:\tQuits\n");
            printf("\tt var:\tTime Off\n");
            printf("\tn var:\tSets Next Period\n");
        }
    } else {
        if (flag != 0) {
            printf("\nAre you using delaying tactics?\n");
        }
    }
    if (flag != 0) {
        printf("Finished handling\n");
    }
    flag = 1;
    sigprocmask(SIG_SETMASK, &oset, NULL);
    clock_gettime(CLOCK_REALTIME, &time_last_act);
}
