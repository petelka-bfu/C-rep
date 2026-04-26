#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_manager("shields.json", "corrupted_shields.json")
{
    ui->setupUi(this);

    connect(ui->createBtn, &QPushButton::clicked, this, &MainWindow::onCreateShield);
    connect(ui->importBtn, &QPushButton::clicked, this, &MainWindow::onImportFromTxt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateShield()
{
    QString name = ui->nameEdit->text().trimmed();
    QString desc = ui->descEdit->toPlainText().trimmed();
    bool ok;
    double coeff = ui->coeffEdit->text().trimmed().toDouble(&ok);
    QString type = ui->typeCombo->currentText();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название не может быть пустым");
        return;
    }
    if (desc.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Описание не может быть пустым");
        return;
    }
    if (!ok || coeff <= 0) {
        QMessageBox::warning(this, "Ошибка", "Коэффициент защиты должен быть положительным числом");
        return;
    }

    Shield newShield(name, desc, coeff, type);
    m_manager.addShield(newShield);

    QMessageBox::information(this, "Успех", "Щит успешно создан и сохранён");

    ui->nameEdit->clear();
    ui->descEdit->clear();
    ui->coeffEdit->clear();
    ui->typeCombo->setCurrentIndex(0);
}

void MainWindow::onImportFromTxt()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    if (m_manager.importFromTxt(fileName)) {
        QMessageBox::information(this, "Импорт", "Импорт завершён. Данные сохранены.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось импортировать файл");
    }
}
