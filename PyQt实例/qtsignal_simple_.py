from PyQt5.QtWidgets import QPushButton, QWidget, QApplication


def shuoPrint():
    print("Button clicked")

if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    myWidget  = QWidget()
    myWidget.resize(200,200)
    mybutton = QPushButton(myWidget)
    mybutton.setText("MyButton")
    mybutton.clicked.connect(shuoPrint)   # slot函数在py就是普通函数或方法, 连引用都可以不用   

    myWidget.show()
    sys.exit(app.exec_())



	

