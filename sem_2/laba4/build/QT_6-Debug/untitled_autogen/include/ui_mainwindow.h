/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *authorLineEdit;
    QLineEdit *titleLineEdit;
    QLineEdit *codeLineEdit;
    QLineEdit *pagesLineEdit;
    QRadioButton *paperRadio;
    QRadioButton *electronicRadio;
    QCheckBox *fantasyCheck;
    QCheckBox *novelCheck;
    QCheckBox *detectiveCheck;
    QPushButton *resetButton;
    QPushButton *saveButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setMinimumSize(QSize(500, 500));
        MainWindow->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        authorLineEdit = new QLineEdit(centralwidget);
        authorLineEdit->setObjectName("authorLineEdit");
        authorLineEdit->setGeometry(QRect(130, 50, 113, 22));
        titleLineEdit = new QLineEdit(centralwidget);
        titleLineEdit->setObjectName("titleLineEdit");
        titleLineEdit->setGeometry(QRect(130, 80, 113, 22));
        codeLineEdit = new QLineEdit(centralwidget);
        codeLineEdit->setObjectName("codeLineEdit");
        codeLineEdit->setGeometry(QRect(90, 110, 91, 22));
        pagesLineEdit = new QLineEdit(centralwidget);
        pagesLineEdit->setObjectName("pagesLineEdit");
        pagesLineEdit->setGeometry(QRect(130, 140, 81, 22));
        paperRadio = new QRadioButton(centralwidget);
        paperRadio->setObjectName("paperRadio");
        paperRadio->setGeometry(QRect(130, 170, 89, 20));
        electronicRadio = new QRadioButton(centralwidget);
        electronicRadio->setObjectName("electronicRadio");
        electronicRadio->setGeometry(QRect(220, 170, 101, 20));
        fantasyCheck = new QCheckBox(centralwidget);
        fantasyCheck->setObjectName("fantasyCheck");
        fantasyCheck->setGeometry(QRect(100, 200, 91, 20));
        novelCheck = new QCheckBox(centralwidget);
        novelCheck->setObjectName("novelCheck");
        novelCheck->setGeometry(QRect(100, 220, 76, 20));
        detectiveCheck = new QCheckBox(centralwidget);
        detectiveCheck->setObjectName("detectiveCheck");
        detectiveCheck->setGeometry(QRect(100, 240, 76, 20));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(50, 290, 75, 51));
        resetButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        resetButton->setStyleSheet(QString::fromUtf8("background-color: lightcoral;\n"
""));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(190, 290, 81, 51));
        saveButton->setStyleSheet(QString::fromUtf8("background-color:lightgreen;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 50, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 80, 61, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 110, 49, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 170, 81, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 200, 49, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 140, 81, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 500, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\320\275\320\270\320\263\320\260", nullptr));
        titleLineEdit->setText(QString());
        paperRadio->setText(QCoreApplication::translate("MainWindow", "\320\221\321\203\320\274\320\260\320\266\320\275\320\276\320\265", nullptr));
        electronicRadio->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\272\321\202\321\200\320\276\320\275\320\275\320\276\320\265", nullptr));
        fantasyCheck->setText(QCoreApplication::translate("MainWindow", "\321\204\320\260\320\275\321\202\320\260\321\201\321\202\320\270\320\272\320\260", nullptr));
        novelCheck->setText(QCoreApplication::translate("MainWindow", "\321\200\320\276\320\274\320\260\320\275", nullptr));
        detectiveCheck->setText(QCoreApplication::translate("MainWindow", "\320\264\320\265\321\202\320\265\320\272\321\202\320\270\320\262", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\221\320\240\320\236\320\241\320\230\320\242\320\254", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\245\320\240\320\220\320\235\320\230\320\242\320\254", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\264", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\270\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
