#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CMD_LEN 10


void catch_fire(char*, int);
char check_cmd(char*, char*);



int main(int argc, char *argv[]){


    int size = 0;
    char **arg_list, *cmd;



    if(argc >= 2){
        arg_list = malloc( sizeof(char *) * (argc + 1) );
        char *cmd = malloc(CMD_LEN * sizeof(char));
    }

    else
        execl("/usr/bin/pacman", "pacman", "-Syu", NULL);


    if(!strchr(argv[1], '-')){
        if( check_cmd(argv[1], cmd) ){
            free(cmd);
            free(arg_list);
            catch_fire("Unknown command\n", 1);
        }
    }
    else
        strcpy(cmd, argv[1]);


    arg_list[argc] = NULL;
    arg_list[0] = "pacman";
    arg_list[1] = cmd;



    for(int i = 2; i < argc; i++)
        arg_list[i] = argv[i];

    execv("/usr/bin/pacman", arg_list);



    free(arg_list);
    free(cmd);

    return 1;
}






char check_cmd(char *src, char *dest){

    static const char *command_table[][2] = {
        { "install",  "-S"},
        { "remove",   "-R"},
        { "update",   "-Syu"},
        { "purge",    "-Rns"},
        { "search",   "-Ss"},
        { "query",    "-Q"},
        { "amputate", "-Rdd"}
    };

    int i = 0;
    while (i < sizeof(command_table) && strcmp(command_table[i][0], src)) {
        i++;
    }

    if (i == sizeof(command_table))
        return 1;
    else {
        strcpy(dest, command_table[i][1]);
        return 0;
    }

}






void catch_fire(char *string, int error) {
  fprintf(stderr, "%s\n", string);
  exit(error);
}
