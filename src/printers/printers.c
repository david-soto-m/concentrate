#include <translate.h>
#include <stdio.h>

void err_non_zero_int(char *str) {
    printf(_("%s needs to be a non zero int \n"), str);
}

void err_path(char *str) {
    printf(_("%s is not accessible or existant\n"), str);
}

void file_create() {
    printf(_("Creating file:\n"));
}

void dir_create() {
    printf(_("Making directory\n"));
}

void inv_setting() {
    printf(_("Invalid setting\n"));
}

void err_settings() {
    printf(_(
"ERROR: SETTINGS not right. Please take a look at error message.\n\
Modify accordingly ~/.config/concentrate/settings\n"));
}

void inv_argument() {
    printf(_("Invalid argument\n"));
}

void err_dir() {
    printf(_("No directory found\n"));
}

void block_announcement() {
    printf(_("I will block:\n"));
}

void seconds_announcement(long int sec) {
    printf(_("I will block them every %ld seconds\n"), sec);
}

void act_help() {
    printf(
        "Actions:\n\
        q var?: Quits\n\
        t var: Time Off\n\
        n var: Sets Next Period\n");
}

void display_help() {
    printf(_(
"Concentrate: Concentrate [OPTIONS] \n\
This is a distraction free mode developed by David. An idiot. It may block\n\
sources of distractions. Bugs are to be expected. Any resemblace to\n\
functionality is an accident and probably wont ever happen again.\n\
Because David is an idiot\n\
\n\
Options:\n\
-f: (n) [FILE]\n\
\tSigkills every instance of processes in the file.It's unsafe. Be \n\
\tcareful. It probably allows code injection through input files. The\n\
\tvalidation scheme only checks if the char is used in process names.\n\
\t Provide n paths either relative or absolute\n\
-N:\n\
\tDisables the printing of an exit in a file.\n"));
    act_help();
}

void interact_msg() {
    printf(_("\nInteracting:\t"));
}

void exit_msg() {
    printf(_("exiting\n"));
}

void delay_msg() {
    printf(_("\nAre you using delaying tactics?\n"));
}

void break_msg() {
    printf(_("starting break\n"));
}

void finish_msg() {
    printf(_("Finished handling\n"));
}
