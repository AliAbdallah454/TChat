#include <ncurses.h>
#include "chatRoom.cpp"

void renderInputWindow(WINDOW *inputWindow, int inputWindowHeight){
    werase(inputWindow);
    box(inputWindow, 0, 0);
    wmove(inputWindow, (int)(inputWindowHeight / 2), 1);
    wprintw(inputWindow, ">> ");
    wrefresh(inputWindow);
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

        renderInputWindow(inputWindow, inputWindowHeight);

        getchar();

        // char name[256] = "Ali";
        // char buffer[256] = {0};
        // char message[256] = {0};
    //     while(1){

    //         renderInputWindow(inputWindow, inputWindowHeight);
    //         wgetstr(inputWindow, buffer);

    //         if(!strcmp(buffer, "exit")){
    //             // pthread_cancel(printThread);
    //             break;
    //         }
    //         else if(!strcmp(buffer, "")){
    //             wmove(inputWindow, (int)(inputWindowHeight / 2), 4);
    //             continue;
    //         }

    //         renderInputWindow(inputWindow, inputWindowHeight);

    //         sendMessage(socket, name, buffer);

    //     }

    endwin();

}