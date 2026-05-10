#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include "shieldmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenFile();
    void refreshTables();

private:
    void setupUI();
    void updateTable(QTableWidget *table, const QVector<Shield> &shields, bool isCorruptedTable);
    void loadAndDisplayFile(const QString &filePath);
    void updateFileLabel(const QString &filePath);
    QStringList getInvalidFields(const Shield &shield);
    void setCellColor(QTableWidgetItem *item, bool isError);

    QTabWidget *m_tabWidget;
    QTableWidget *m_validTable;
    QTableWidget *m_corruptedTable;
    QPushButton *m_openBtn;
    QPushButton *m_refreshBtn;
    QLabel *m_fileLabel;

    ShieldManager m_manager;
    QString m_currentFilePath;
};

#endif // MAINWINDOW_H
