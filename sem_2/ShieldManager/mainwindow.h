#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shieldmanager.h"
#include <QTableWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateShield();
    void onImportFromTxt();
    void refreshTables();

private:
    void updateTable(QTableWidget *table, const QVector<Shield> &shields);

    Ui::MainWindow *ui;
    ShieldManager m_manager;
};

#endif // MAINWINDOW_H
