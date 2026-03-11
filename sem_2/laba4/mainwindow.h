#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetButton_clicked();
    void on_saveButton_clicked();


private:
    bool validateAuthor(const QString &text);
    bool validateTitle(const QString &text);
    bool validateCode(const QString &text);
    bool validatePages(const QString &text);
    void showError(const QString &message);
    void clearForm();
    Ui::MainWindow *ui;
    size_t counter = 0;
};
#endif // MAINWINDOW_H
