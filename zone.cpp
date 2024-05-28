#include <ncurses.h>
#include "zone.h"

Zone::Zone(int goalWidth) : goalWidth(goalWidth) {}

void Zone::initialize() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

void Zone::draw() {
    clear();
    attron(COLOR_PAIR(1));
    for (int i = (COLS - goalWidth) / 2; i < (COLS + goalWidth) / 2; i++) {
        mvprintw(0, i, "-");
        mvprintw(LINES - 1, i, "-");
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for (int i = 0; i < LINES; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, COLS-1, "|");
    }
    attroff(COLOR_PAIR(2));

    for (auto& obs : obstacles) {
        obs.draw();
    }

    refresh();
}

void Zone::addObstacle(int x, int y) {
    obstacles.push_back(Obstacle(x, y));
}

std::vector<Obstacle>& Zone::getObstacles() {
    return obstacles;
}
