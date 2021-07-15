#include <translate.h>
#include <stdio.h>

void err_fopen(const char *file) {
    printf(_("Error opening file %s\n"), file);
}

void err_perm_exist(const char *file) {
    printf(_(
    "File %s not existant or not accesible with your current permissions\n"),
    file);
}

void err_nextjump() {
    printf(_("NEXTJUMP needs to be a non zero int \n"));
}

void err_defaults_path() {
    printf(_("DEFAULTS_PATH is not accessible or existant\n"));
}

void err_path() {
    printf(_("Path is not pointing to an existing directory for the file\n"));
}

void err_perm_def() {
    printf(_(
        "You need a file pointed by a path by DEFAULTS_PATH and permission to\
        access it.\n"));
}

void file_create() {
    printf(_("Creating file:\n"));
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
\tvalidation scheme only checks if the char is used asdf in process names.\n\
\t Provide n paths either relative or absolute\n\
-N:\n\
\tDisables the printing of an exit in a file.\n\
\n\
Actions:\n\
q var?: Quits\n\
t var: Time Off\n\
n var: Sets Next Period\n"));
}
