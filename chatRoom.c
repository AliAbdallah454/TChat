#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void renderInputWindow(WINDOW *inputWindow, int inputWindowHeight){
    werase(inputWindow);
    box(inputWindow, 0, 0);
    wmove(inputWindow, (int)(inputWindowHeight / 2), 1);
    wprintw(inputWindow, ">> ");
    wrefresh(inputWindow);
}

void send(WINDOW *messageWindow,char *name, char *message){
    char newShit[500] = {0};
    strcat(newShit, name);
    strcat(newShit, " >> ");
    strcat(newShit, message);

    wprintw(messageWindow, "%s\n", newShit);
    box(messageWindow, 0, 0);
    wrefresh(messageWindow);

}

int main(){

    initscr();

        // windows Initialization

        int maxX = 0;
        int maxY = 0;
        getmaxyx(stdscr, maxY, maxX);

        int messageWindowHeight = 0.8 * maxY;
        int messageWindowWidth = 0.7 * maxX;
        WINDOW *messagesWindow = newwin(messageWindowHeight, messageWindowWidth, 0, 0);\

        int inputWindowHeight = 0.2 * maxY;
        int inputWindowWidth = 1 * maxX;
        WINDOW *inputWindow = newwin(inputWindowHeight, inputWindowWidth, messageWindowHeight, 0);

        int sideWindowHeight = 0.8 * maxY;
        int sideWindowWidth = 0.3 * maxX;
        WINDOW *sideWindow = newwin(sideWindowHeight, sideWindowWidth, 0, messageWindowWidth);

        refresh();
        box(messagesWindow, 0, 0);
        box(inputWindow, 0, 0);
        box(sideWindow, 0, 0);
        wrefresh(messagesWindow);
        wrefresh(inputWindow);
        wrefresh(sideWindow);

        // End of windows Initialization

        char ip[255] = {0};
        char name[255] = {0};

        renderInputWindow(inputWindow, inputWindowHeight);
        wprintw(inputWindow, "Enter name : ");
        wgetstr(inputWindow, name);

        int y = 1;
        wmove(messagesWindow, y++, 1);
        wrefresh(messagesWindow);

        char buffer[255] = {0};
        while(1){

            renderInputWindow(inputWindow, inputWindowHeight);
            wgetstr(inputWindow, buffer);

            if(!strcmp(buffer, "exit")){
                break;
            }
            else if(!strcmp(buffer, "")){
                wmove(inputWindow, (int)(inputWindowHeight / 2), 4);
                continue;
            }

            renderInputWindow(inputWindow, inputWindowHeight);
            send(messagesWindow, name, buffer);

            wmove(messagesWindow, y++, 1);
            wrefresh(messagesWindow);

        }

    endwin();

    return 0;

}