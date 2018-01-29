import ui_mywidget
from  PyQt5.QtWidgets import QWidget
from  PyQt5.QtCore import pyqtSignal


class ShuoGGWidget(QWidget):
    signal1 = pyqtSignal()        #定义信号
    signal2 = pyqtSignal(int)     #定义信息
    def __init__(self):
        super(ShuoGGWidget, self).__init__()
        self.mywidgetui = ui_mywidget.Ui_Form()
        self.mywidgetui.setupUi(self)
        self.mywidgetui.pushButton1.clicked.connect(self.__slotHello1)   #信号与槽连接
        self.mywidgetui.pushButton2.clicked.connect(self.__slotHello2)   #信号与槽连接
        self.signal1.connect(self.__slotHello3)                          #信号与槽连接
        self.signal2.connect(self.__slotHelloNum)

    def __slotHello1(self):
        self.mywidgetui.lineEdit.setText("Hello")
        self.signal1.emit()       #发射信号

    def __slotHello2(self):
        self.mywidgetui.plainTextEdit.insertPlainText("world")
        self.signal2.emit(222)    #发射带参数的信号

    def __slotHello3(self):
        self.mywidgetui.plainTextEdit.insertPlainText("received signal1")

    def __slotHelloNum(self, singleNum):    #接收带参数的信号
        self.mywidgetui.plainTextEdit.insertPlainText(str(singleNum))
