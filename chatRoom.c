#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

        int y = 1;
        wmove(messagesWindow, y++, 1);
        wmove(inputWindow, (int)(inputWindowHeight / 2), 1);
        wprintw(inputWindow, ">> ");

        char buffer[255] = {0};
        while(1){

            if(!strcmp(buffer, "exit")){
                break;
            }
            // else if(!strcmp(buffer, ""))
            wgetstr(inputWindow, buffer);
            wprintw(messagesWindow, "%s", buffer);
            wmove(messagesWindow, y++, 1);
            wrefresh(messagesWindow);
            
            werase(inputWindow);
            box(inputWindow, 0, 0);
            wmove(inputWindow, (int)(inputWindowHeight / 2), 1);
            wprintw(inputWindow, ">> ");
            wrefresh(inputWindow);
        }

    endwin();

    return 0;

}