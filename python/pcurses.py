#!/usr/bin/python3
import curses

def main(stdscr):
    cout = curses.newwin(curses.LINES-3, curses.COLS, 0, 0)
    ccmd = curses.newwin(3, curses.COLS, curses.LINES-3, 0)
    cout.border()
    ccmd.border()
    cout.refresh()
    ccmd.addstr(1, 1, '>')
    ccmd.move(1, 2) 
#    ccmd.border()
#    stdscr.refresh()
#    ccmd.refresh()
    i = 0
    while True:
        k = ccmd.getkey()
        if k == '\n':
            k = '*'
        cout.addstr(i+1, 1, k)
        ccmd.addstr(1, i+2, k)
        cout.refresh()
        ccmd.refresh()
        i += 1

if __name__ == '__main__':
    curses.wrapper(main)