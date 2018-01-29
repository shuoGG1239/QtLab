import shuoGG_widget
from PyQt5.QtWidgets import QApplication

if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    mainWindow = shuoGG_widget.ShuoGGWidget()
    mainWindow.show()
    sys.exit(app.exec_())