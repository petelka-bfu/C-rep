#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    setWindowTitle("Просмотрщик щитов");
    resize(950, 650);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Метка с информацией о файле
    m_fileLabel = new QLabel("Файл не выбран");
    m_fileLabel->setAlignment(Qt::AlignCenter);
    m_fileLabel->setStyleSheet("color: blue; font-weight: bold; padding: 5px;");
    mainLayout->addWidget(m_fileLabel);

    // Вкладки
    m_tabWidget = new QTabWidget();

    // Вкладка с корректными щитами
    QWidget *validTab = new QWidget();
    QVBoxLayout *validLayout = new QVBoxLayout(validTab);
    QLabel *validLabel = new QLabel("Корректные щиты (в обратном алфавитном порядке):");
    validLabel->setStyleSheet("font-weight: bold;");
    validLayout->addWidget(validLabel);

    m_validTable = new QTableWidget();
    m_validTable->setColumnCount(4);
    m_validTable->setHorizontalHeaderLabels({"Название", "Описание", "Коэф.", "Тип защиты"});
    m_validTable->horizontalHeader()->setStretchLastSection(true);
    validLayout->addWidget(m_validTable);
    m_tabWidget->addTab(validTab, "Корректные щиты");

    // Вкладка с битыми щитами
    QWidget *corruptedTab = new QWidget();
    QVBoxLayout *corruptedLayout = new QVBoxLayout(corruptedTab);
    QLabel *corruptedLabel = new QLabel("«Битые» щиты (некорректные данные):");
    corruptedLabel->setStyleSheet("font-weight: bold;");
    corruptedLayout->addWidget(corruptedLabel);

    m_corruptedTable = new QTableWidget();
    m_corruptedTable->setColumnCount(4);
    m_corruptedTable->setHorizontalHeaderLabels({"Название", "Описание", "Коэф.", "Тип защиты"});
    m_corruptedTable->horizontalHeader()->setStretchLastSection(true);
    corruptedLayout->addWidget(m_corruptedTable);
    m_tabWidget->addTab(corruptedTab, "Битые щиты");

    mainLayout->addWidget(m_tabWidget);

    // Кнопки
    QHBoxLayout *btnLayout = new QHBoxLayout();

    m_openBtn = new QPushButton("Выбрать JSON файл");
    m_openBtn->setMinimumSize(200, 35);
    m_openBtn->setStyleSheet("background-color: #2196F3; color: white; font-weight: bold;");

    m_refreshBtn = new QPushButton("Обновить таблицы");
    m_refreshBtn->setMinimumSize(200, 35);
    m_refreshBtn->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;");
    m_refreshBtn->setEnabled(false);

    btnLayout->addWidget(m_openBtn);
    btnLayout->addWidget(m_refreshBtn);
    mainLayout->addLayout(btnLayout);

    QLabel *infoLabel = new QLabel("Выберите JSON файл с щитами для просмотра и разделения");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("color: gray; font-size: 10pt;");
    mainLayout->addWidget(infoLabel);

    connect(m_openBtn, &QPushButton::clicked, this, &MainWindow::onOpenFile);
    connect(m_refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshTables);

    statusBar();
}

QStringList MainWindow::getInvalidFields(const Shield &shield)
{
    QStringList invalid;

    if (shield.getName().trimmed().isEmpty())
        invalid.append("Название");

    if (shield.getDescription().trimmed().isEmpty())
        invalid.append("Описание");

    if (shield.getDefenseCoeff() <= 0)
        invalid.append("Коэффициент");

    QStringList validTypes = {"Физическая", "Магическая", "Огненная", "Ледяная"};
    if (!validTypes.contains(shield.getDefenseType()))
        invalid.append("Тип защиты");

    return invalid;
}

void MainWindow::setCellColor(QTableWidgetItem *item, bool isError)
{
    if (isError) {
        item->setBackground(QColor(255, 200, 200));
        item->setForeground(QColor(255, 0, 0));
        item->setToolTip("Ошибка: поле некорректно");
    } else {
        item->setBackground(QColor(255, 255, 255));
        item->setForeground(QColor(0, 0, 0));
    }
}

void MainWindow::updateTable(QTableWidget *table, const QVector<Shield> &shields, bool isCorruptedTable)
{
    table->clearContents();
    table->setRowCount(0);
    table->setRowCount(shields.size());

    for (int i = 0; i < shields.size(); ++i) {
        const Shield &s = shields[i];

        QStringList invalidFields;
        if (isCorruptedTable) {
            invalidFields = getInvalidFields(s);
        }

        QTableWidgetItem *nameItem = new QTableWidgetItem(s.getName());
        if (isCorruptedTable && invalidFields.contains("Название")) {
            setCellColor(nameItem, true);
            nameItem->setToolTip("Ошибка: название не может быть пустым");
        }
        table->setItem(i, 0, nameItem);

        QTableWidgetItem *descItem = new QTableWidgetItem(s.getDescription());
        if (isCorruptedTable && invalidFields.contains("Описание")) {
            setCellColor(descItem, true);
            descItem->setToolTip("Ошибка: описание не может быть пустым");
        }
        table->setItem(i, 1, descItem);

        QString coeffStr = QString::number(s.getDefenseCoeff());
        QTableWidgetItem *coeffItem = new QTableWidgetItem(coeffStr);
        if (isCorruptedTable && invalidFields.contains("Коэффициент")) {
            setCellColor(coeffItem, true);
            if (s.getDefenseCoeff() <= 0) {
                coeffItem->setToolTip("Ошибка: коэффициент должен быть > 0 (текущее значение: " + coeffStr + ")");
            }
        }
        table->setItem(i, 2, coeffItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(s.getDefenseType());
        if (isCorruptedTable && invalidFields.contains("Тип защиты")) {
            setCellColor(typeItem, true);
            typeItem->setToolTip("Ошибка: тип защиты должен быть: Физическая, Магическая, Огненная или Ледяная");
        }
        table->setItem(i, 3, typeItem);
    }

    table->resizeColumnsToContents();
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выберите JSON файл с щитами",
                                                    "",
                                                    "JSON файлы (*.json);;Все файлы (*)");

    if (fileName.isEmpty()) return;

    loadAndDisplayFile(fileName);
}

void MainWindow::loadAndDisplayFile(const QString &filePath)
{
    if (!m_manager.loadFromJson(filePath)) {
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось загрузить файл.\n"
                             "Проверьте формат JSON файла.");
        return;
    }

    // Сохраняем битые щиты в отдельный файл
    QString corruptedFilePath = QFileInfo(filePath).absolutePath() + "/corrupted_shields.json";
    m_manager.saveCorruptedToJson(corruptedFilePath);

    // Обновляем таблицы (валидные щиты уже отсортированы в loadFromJson)
    updateTable(m_validTable, m_manager.getValidShields(), false);
    updateTable(m_corruptedTable, m_manager.getCorruptedShields(), true);

    updateFileLabel(filePath);
    m_refreshBtn->setEnabled(true);

    QFileInfo fileInfo(filePath);
    int total = m_manager.getAllShields().size();
    int valid = m_manager.getValidShields().size();
    int corrupted = m_manager.getCorruptedShields().size();

    statusBar()->showMessage(QString("Загружено: всего %1, валидных %2, битых %3 (отсортировано по убыванию названия)")
                                 .arg(total).arg(valid).arg(corrupted), 5000);
}

void MainWindow::refreshTables()
{
    if (m_currentFilePath.isEmpty()) {
        QMessageBox::information(this, "Информация", "Сначала выберите JSON файл");
        return;
    }

    loadAndDisplayFile(m_currentFilePath);
}

void MainWindow::updateFileLabel(const QString &filePath)
{
    m_currentFilePath = filePath;
    QFileInfo fileInfo(filePath);

    int valid = m_manager.getValidShields().size();
    int corrupted = m_manager.getCorruptedShields().size();

    m_fileLabel->setText(QString("Текущий файл: %1 | Корректных: %2 | Битых: %3 (отсортировано по убыванию названия)")
                             .arg(fileInfo.fileName())
                             .arg(valid)
                             .arg(corrupted));
    m_fileLabel->setStyleSheet("color: green; font-weight: bold; padding: 5px; background-color: #E8F5E9;");
}
