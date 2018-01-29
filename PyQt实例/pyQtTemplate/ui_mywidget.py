# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui_mywidget.ui'
#
# Created: Sun Jun 18 16:31:23 2017
#      by: PyQt5 UI code generator 5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(319, 296)
        self.pushButton1 = QtWidgets.QPushButton(Form)
        self.pushButton1.setGeometry(QtCore.QRect(230, 10, 75, 23))
        self.pushButton1.setObjectName("pushButton1")
        self.lineEdit = QtWidgets.QLineEdit(Form)
        self.lineEdit.setGeometry(QtCore.QRect(10, 10, 211, 20))
        self.lineEdit.setObjectName("lineEdit")
        self.plainTextEdit = QtWidgets.QPlainTextEdit(Form)
        self.plainTextEdit.setGeometry(QtCore.QRect(10, 40, 211, 241))
        self.plainTextEdit.setObjectName("plainTextEdit")
        self.pushButton2 = QtWidgets.QPushButton(Form)
        self.pushButton2.setGeometry(QtCore.QRect(230, 40, 75, 241))
        self.pushButton2.setObjectName("pushButton2")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.pushButton1.setText(_translate("Form", "Button1"))
        self.pushButton2.setText(_translate("Form", "Button2"))

