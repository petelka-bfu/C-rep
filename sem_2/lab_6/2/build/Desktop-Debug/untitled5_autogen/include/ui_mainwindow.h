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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *validTab;
    QVBoxLayout *verticalLayout_2;
    QLabel *validLabel;
    QTableWidget *validTable;
    QWidget *corruptedTab;
    QVBoxLayout *verticalLayout_3;
    QLabel *corruptedLabel;
    QTableWidget *corruptedTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *infoLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(950, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        validTab = new QWidget();
        validTab->setObjectName("validTab");
        verticalLayout_2 = new QVBoxLayout(validTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        validLabel = new QLabel(validTab);
        validLabel->setObjectName("validLabel");
        QFont font;
        font.setBold(true);
        validLabel->setFont(font);

        verticalLayout_2->addWidget(validLabel);

        validTable = new QTableWidget(validTab);
        if (validTable->columnCount() < 4)
            validTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        validTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        validTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        validTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        validTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        validTable->setObjectName("validTable");
        validTable->setColumnCount(4);
        validTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(validTable);

        tabWidget->addTab(validTab, QString());
        corruptedTab = new QWidget();
        corruptedTab->setObjectName("corruptedTab");
        verticalLayout_3 = new QVBoxLayout(corruptedTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        corruptedLabel = new QLabel(corruptedTab);
        corruptedLabel->setObjectName("corruptedLabel");
        corruptedLabel->setFont(font);

        verticalLayout_3->addWidget(corruptedLabel);

        corruptedTable = new QTableWidget(corruptedTab);
        if (corruptedTable->columnCount() < 4)
            corruptedTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        corruptedTable->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        corruptedTable->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        corruptedTable->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        corruptedTable->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        corruptedTable->setObjectName("corruptedTable");
        corruptedTable->setColumnCount(4);
        corruptedTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(corruptedTable);

        tabWidget->addTab(corruptedTab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        refreshBtn = new QPushButton(centralwidget);
        refreshBtn->setObjectName("refreshBtn");
        refreshBtn->setMinimumSize(QSize(200, 35));

        horizontalLayout->addWidget(refreshBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(infoLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 950, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200\321\211\320\270\320\272 \321\211\320\270\321\202\320\276\320\262", nullptr));
        validLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \321\211\320\270\321\202\321\213:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = validTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = validTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = validTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204.", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = validTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\321\211\320\270\321\202\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(validTab), QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \321\211\320\270\321\202\321\213", nullptr));
        corruptedLabel->setText(QCoreApplication::translate("MainWindow", "\302\253\320\221\320\270\321\202\321\213\320\265\302\273 \321\211\320\270\321\202\321\213 (\320\275\320\265\320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265):", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = corruptedTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = corruptedTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = corruptedTable->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204.", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = corruptedTable->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\321\211\320\270\321\202\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(corruptedTab), QCoreApplication::translate("MainWindow", "\320\221\320\270\321\202\321\213\320\265 \321\211\320\270\321\202\321\213", nullptr));
        refreshBtn->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", nullptr));
        refreshBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #4CAF50; color: white; font-weight: bold; border-radius: 5px;", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "\320\247\320\270\321\202\320\260\320\265\321\202 \321\204\320\260\320\271\320\273\321\213: shields.json \320\270 corrupted_shields.json (\321\201\320\276\320\267\320\264\320\260\321\216\321\202\321\201\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271 ShieldCreator)", nullptr));
        infoLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: gray; font-size: 10pt;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
