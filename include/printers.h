#ifndef INCLUDE_PRINTERS_H_
    #define INCLUDE_PRINTERS_H_

    void display_help();
    void act_help();

    void err_non_zero_int();
    void err_path();
    void err_dir();

    void file_create();
    void dir_create();

    void inv_setting();
    void err_settings();

    void inv_argument();

    void block_announcement();
    void seconds_announcement(long int secs);

    void exit_msg();
    void break_msg();
    void interact_msg();
    void delay_msg();
    void finish_msg();

#endif  // INCLUDE_PRINTERS_H_
