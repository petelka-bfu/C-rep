#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_manager("shields.json")
{
    ui->setupUi(this);

    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshTables);

    // Устанавливаем заголовки таблиц
    ui->validTable->setHorizontalHeaderLabels({"Название", "Описание", "Коэф.", "Тип защиты"});
    ui->corruptedTable->setHorizontalHeaderLabels({"Название", "Описание", "Коэф.", "Тип защиты"});

    // Растягиваем последнюю колонку
    ui->validTable->horizontalHeader()->setStretchLastSection(true);
    ui->corruptedTable->horizontalHeader()->setStretchLastSection(true);

    // Загружаем данные при запуске
    refreshTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTables()
{
    qDebug() << "=== Обновление таблиц ===";

    // Загружаем данные из JSON файлов
    m_manager.loadFromJson();

    // Получаем валидные и битые щиты
    QVector<Shield> valid = m_manager.getValidShields();
    QVector<Shield> corrupted = m_manager.getCorruptedShields();

    qDebug() << "Валидных щитов:" << valid.size();
    qDebug() << "Битых щитов:" << corrupted.size();

    // Обновляем таблицы
    updateTable(ui->validTable, valid);
    updateTable(ui->corruptedTable, corrupted);

    // Показываем статус в строке состояния
    statusBar()->showMessage(QString("Загружено: %1 валидных, %2 битых щитов")
                                 .arg(valid.size())
                                 .arg(corrupted.size()), 3000);
}

void MainWindow::updateTable(QTableWidget *table, const QVector<Shield> &shields)
{
    // Очищаем таблицу
    table->clearContents();
    table->setRowCount(0);

    // Устанавливаем количество строк
    table->setRowCount(shields.size());

    // Заполняем таблицу данными
    for (int i = 0; i < shields.size(); ++i) {
        const Shield &s = shields[i];

        table->setItem(i, 0, new QTableWidgetItem(s.getName()));
        table->setItem(i, 1, new QTableWidgetItem(s.getDescription()));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(s.getDefenseCoeff())));
        table->setItem(i, 3, new QTableWidgetItem(s.getDefenseType()));
    }

    // Подгоняем ширину колонок
    table->resizeColumnsToContents();
}
