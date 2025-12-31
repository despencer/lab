#!/usr/bin/python3
import curses

class CursesInput:
    def __init__(self):
        self.history = []

    def open(self):
        self.cout = curses.newwin(curses.LINES-3, curses.COLS, 0, 0)
        self.ccmd = curses.newwin(3, curses.COLS, curses.LINES-3, 0)
        self.cout.border()
        self.ccmd.border()
        self.cout.refresh()
        self.ccmd.addstr(1, 1, '>')
        self.ccmd.move(1, 2)

    def loop(self, stdscr):
        self.open()
        while True:
            line = ''
            while True:
                key = self.ccmd.getkey()
                if key == '\n':
                    break
                self.ccmd.addstr(1, 2+len(line), key)
                line += key
                self.ccmd.refresh()
            if line == 'quit':
                break
            self.addline(line)
            self.ccmd.addstr(1, 1, '>' + ' ' * (curses.COLS-3))
            self.ccmd.move(1, 2)

    def shell(self):
        curses.wrapper(self.loop)

    def addline(self, line):
        self.history.append(line)
        wnd = curses.LINES-5
        for i in range(wnd):
            if i < len(self.history):
                self.cout.addstr(wnd-i, 1, self.history[ -i-1 ].ljust(curses.COLS-2) )
        self.cout.refresh()

if __name__ == '__main__':
    CursesInput().shell()
