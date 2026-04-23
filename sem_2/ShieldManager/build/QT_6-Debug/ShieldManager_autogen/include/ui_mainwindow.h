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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *createTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_name;
    QLineEdit *nameEdit;
    QLabel *label_desc;
    QTextEdit *descEdit;
    QLabel *label_coeff;
    QLineEdit *coeffEdit;
    QLabel *label_type;
    QComboBox *typeCombo;
    QHBoxLayout *horizontalLayout;
    QPushButton *createBtn;
    QPushButton *importBtn;
    QSpacerItem *verticalSpacer;
    QWidget *viewTab;
    QVBoxLayout *verticalLayout_3;
    QLabel *validLabel;
    QTableWidget *validTable;
    QLabel *corruptedLabel;
    QTableWidget *corruptedTable;
    QPushButton *refreshBtn;
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
        createTab = new QWidget();
        createTab->setObjectName("createTab");
        verticalLayout_2 = new QVBoxLayout(createTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(createTab);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label_name = new QLabel(groupBox);
        label_name->setObjectName("label_name");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_name);

        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        label_desc = new QLabel(groupBox);
        label_desc->setObjectName("label_desc");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_desc);

        descEdit = new QTextEdit(groupBox);
        descEdit->setObjectName("descEdit");
        descEdit->setMaximumSize(QSize(16777215, 80));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, descEdit);

        label_coeff = new QLabel(groupBox);
        label_coeff->setObjectName("label_coeff");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_coeff);

        coeffEdit = new QLineEdit(groupBox);
        coeffEdit->setObjectName("coeffEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, coeffEdit);

        label_type = new QLabel(groupBox);
        label_type->setObjectName("label_type");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_type);

        typeCombo = new QComboBox(groupBox);
        typeCombo->addItem(QString());
        typeCombo->addItem(QString());
        typeCombo->addItem(QString());
        typeCombo->addItem(QString());
        typeCombo->setObjectName("typeCombo");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, typeCombo);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        createBtn = new QPushButton(createTab);
        createBtn->setObjectName("createBtn");

        horizontalLayout->addWidget(createBtn);

        importBtn = new QPushButton(createTab);
        importBtn->setObjectName("importBtn");

        horizontalLayout->addWidget(importBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(createTab, QString());
        viewTab = new QWidget();
        viewTab->setObjectName("viewTab");
        verticalLayout_3 = new QVBoxLayout(viewTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        validLabel = new QLabel(viewTab);
        validLabel->setObjectName("validLabel");
        QFont font;
        font.setBold(true);
        validLabel->setFont(font);

        verticalLayout_3->addWidget(validLabel);

        validTable = new QTableWidget(viewTab);
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

        verticalLayout_3->addWidget(validTable);

        corruptedLabel = new QLabel(viewTab);
        corruptedLabel->setObjectName("corruptedLabel");
        corruptedLabel->setFont(font);

        verticalLayout_3->addWidget(corruptedLabel);

        corruptedTable = new QTableWidget(viewTab);
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

        refreshBtn = new QPushButton(viewTab);
        refreshBtn->setObjectName("refreshBtn");

        verticalLayout_3->addWidget(refreshBtn);

        tabWidget->addTab(viewTab, QString());

        verticalLayout->addWidget(tabWidget);

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\320\265\320\264\320\266\320\265\321\200 \321\211\320\270\321\202\320\276\320\262", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\263\320\276 \321\211\320\270\321\202\320\260", nullptr));
        label_name->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", nullptr));
        label_desc->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265:", nullptr));
        label_coeff->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\267\320\260\321\211\320\270\321\202\321\213 (>0):", nullptr));
        coeffEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: 0.75", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\321\211\320\270\321\202\321\213:", nullptr));
        typeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\320\244\320\270\320\267\320\270\321\207\320\265\321\201\320\272\320\260\321\217", nullptr));
        typeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\320\234\320\260\320\263\320\270\321\207\320\265\321\201\320\272\320\260\321\217", nullptr));
        typeCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\320\236\320\263\320\275\320\265\320\275\320\275\320\260\321\217", nullptr));
        typeCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\320\233\320\265\320\264\321\217\320\275\320\260\321\217", nullptr));

        createBtn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\211\320\270\321\202", nullptr));
        importBtn->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202 \320\270\320\267 TXT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(createTab), QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 / \320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        validLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \321\211\320\270\321\202\321\213:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = validTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = validTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = validTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204.", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = validTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\321\211\320\270\321\202\321\213", nullptr));
        corruptedLabel->setText(QCoreApplication::translate("MainWindow", "\302\253\320\221\320\270\321\202\321\213\320\265\302\273 \321\211\320\270\321\202\321\213 (\320\275\320\265\320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265):", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = corruptedTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = corruptedTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = corruptedTable->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204.", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = corruptedTable->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\321\211\320\270\321\202\321\213", nullptr));
        refreshBtn->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(viewTab), QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \321\211\320\270\321\202\320\276\320\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
