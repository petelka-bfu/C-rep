#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_manager("shields.json", "corrupted_shields.json")
{
    ui->setupUi(this);

    connect(ui->createBtn, &QPushButton::clicked, this, &MainWindow::onCreateShield);
    connect(ui->importBtn, &QPushButton::clicked, this, &MainWindow::onImportFromTxt);
    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshTables);

    // Загружаем существующие данные
    refreshTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTables()
{
    qDebug() << "=== refreshTables() вызван ===";

    // Перезагружаем данные из файлов
    m_manager.loadFromJson();

    // Получаем валидные и битые щиты
    QVector<Shield> valid = m_manager.getValidShields();
    QVector<Shield> corrupted = m_manager.getCorruptedShields();

    qDebug() << "Валидных щитов:" << valid.size();
    qDebug() << "Битых щитов:" << corrupted.size();

    // Очищаем таблицы
    ui->validTable->clearContents();
    ui->corruptedTable->clearContents();

    // Обновляем таблицы
    updateTable(ui->validTable, valid);
    updateTable(ui->corruptedTable, corrupted);

    // Принудительно обновляем отображение
    ui->validTable->viewport()->update();
    ui->corruptedTable->viewport()->update();
}

void MainWindow::updateTable(QTableWidget *table, const QVector<Shield> &shields)
{
    qDebug() << "updateTable: количество строк =" << shields.size();

    table->setRowCount(shields.size());

    for (int i = 0; i < shields.size(); ++i) {
        const Shield &s = shields[i];

        qDebug() << "Строка" << i << ":" << s.getName() << "|" << s.getDescription() << "|" << s.getDefenseCoeff() << "|" << s.getDefenseType();

        table->setItem(i, 0, new QTableWidgetItem(s.getName()));
        table->setItem(i, 1, new QTableWidgetItem(s.getDescription()));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(s.getDefenseCoeff())));
        table->setItem(i, 3, new QTableWidgetItem(s.getDefenseType()));
    }

    table->resizeColumnsToContents();
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
    refreshTables();  // Обновляем таблицы после добавления

    QMessageBox::information(this, "Успех", "Щит успешно создан");

    ui->nameEdit->clear();
    ui->descEdit->clear();
    ui->coeffEdit->clear();
    ui->typeCombo->setCurrentIndex(0);
}

void MainWindow::onImportFromTxt()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    qDebug() << "Импорт из файла:" << fileName;

    if (m_manager.importFromTxt(fileName)) {
        qDebug() << "Импорт успешен, обновляем таблицы...";
        refreshTables();  // Обновляем таблицы после импорта

        // Дополнительная проверка: сколько строк в таблицах?
        qDebug() << "Строк в таблице валидных:" << ui->validTable->rowCount();
        qDebug() << "Строк в таблице битых:" << ui->corruptedTable->rowCount();

        QMessageBox::information(this, "Импорт", "Импорт завершён. См. таблицы.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось импортировать файл");
    }
}
