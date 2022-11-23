#!/usr/bin/python3

import sys
from PyQt5.QtWidgets import QApplication, QWidget

app = QApplication(sys.argv)

win = QWidget()
win.setWindowTitle('Hello')
win.resize(250,250)
win.show()

sys.exit(app.exec_())
