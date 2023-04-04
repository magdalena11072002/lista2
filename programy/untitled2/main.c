#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

void handler(int dummy) {
    signal(SIGCHLD, handler);
    waitpid(0, NULL, WNOHANG);
}

char** splitAtSpacesButNotIfInsideApostrophes(char* line) {
    char** result = malloc(10*sizeof(char*));
    int index = 0;
    int newindex = 0;

    for (int i = 0; i < 10; i++) {
        result[i] = NULL;
    }

    bool singleApostroph = false;
    bool doubleApostroph = false;

    result[index] = malloc(100 * sizeof(char));

    for(int i = 0; i < strlen(line); i++) {
        if(!singleApostroph && !doubleApostroph) {
            if (line[i] == ' ') {
                index++;
                result[index] = malloc(100 * sizeof(char));
                newindex = 0;
                continue;
            }
        }

        if (line[i] == '\'') {
            singleApostroph = !singleApostroph;
        } else if (line[i] == '"') {
            doubleApostroph = !doubleApostroph;
        } else {
            result[index][newindex++]=line[i];
        }
    }

    return result;
}

int main() {

    signal(SIGCHLD, handler);


    while(1) {
        printf("lsh: ");
        fflush(stdout);
        fflush(stdin);

        char *line = NULL;
        size_t len = 0;

        if(getline(&line, &len, stdin) == -1) {
            return 0;
        }

        line[strlen(line) - 1] = '\0';

        char **argv = NULL;

        argv = splitAtSpacesButNotIfInsideApostrophes(line);

        bool isExit = true;
        bool isCd = true;
        bool hasToWait = true;

        for(int i = 0; i < 10; i++) {
            if(argv[i] != NULL) {
                if(argv[i][0] == '&') {
                    argv[i] = NULL;
                    hasToWait = false;
                }
            }
        }

        for(int i = 0; i < strlen(argv[0]); i++) {
            if(argv[0][i] != "exit"[i]) {
                isExit = false;
            }
        }

        for(int i = 0; i < strlen(argv[0]); i++) {
            if(argv[0][i] != "cd"[i]) {
                isCd = false;
            }
        }

        if (isExit) {
            exit(0);
        } else if (isCd) {
            chdir(argv[1]);
        } else {
            pid_t child;

            child = fork();

            if(child == 0) {
                execvp(argv[0], argv);
                return 0;
            }

            if(hasToWait) {
                waitpid(child, NULL, 0);
            }
        }
    }
}
