#include "mainwindow.h"
#include "book.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

// Регулярные выражения согласно варианту
bool MainWindow::validateAuthor(const QString &text) {
    // 1. рус, первая буква 1-го слова капсом потом через пробел 1/2 буквы капсом
    QRegularExpression re("^[А-Я][а-я]+\\s[А-Я]{1,2}$");
    return re.match(text).hasMatch();
}

bool MainWindow::validateTitle(const QString &text) {
    // 2. Обязательно в “...”
    QRegularExpression re("^\".+\"$");
    return re.match(text).hasMatch();
}

bool MainWindow::validateCode(const QString &text) {
    // 3. “123-12345” (цифры-цифры, вторая группа длиннее)
    QRegularExpression re("^\\d{3}-\\d{4,5}$");
    return re.match(text).hasMatch();
}

bool MainWindow::validatePages(const QString &text) {
    // 4. “2/1”, Два числа через разделитель, второе обязательно меньше первого.
    QRegularExpression re("^(\\d+)/(\\d+)$");
    QRegularExpressionMatch match = re.match(text);

    if (!match.hasMatch()) return false;

    int first = match.captured(1).toInt();
    int second = match.captured(2).toInt();

    return (second < first);
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::on_saveButton_clicked()
{
    // 1. Получаем данные из полей
    QString author = ui->authorLineEdit->text().trimmed();
    QString title = ui->titleLineEdit->text().trimmed();
    QString code = ui->codeLineEdit->text().trimmed();
    QString pages = ui->pagesLineEdit->text().trimmed();

    // Тип издания
    QString type;
    if (ui->paperRadio->isChecked())
        type = "Бумажное";
    else if (ui->electronicRadio->isChecked())
        type = "Электронное";
    else {
        showError("Выберите тип издания.");
        return;
    }

    // Жанр (предположим, что можно выбрать только один)
    QString genre;
    if (ui->detectiveCheck->isChecked()) genre = "Детектив";
    else if (ui->fantasyCheck->isChecked()) genre = "Фантастика";
    else if (ui->novelCheck->isChecked()) genre = "Роман";
    else {
        showError("Выберите жанр.");
        return;
    }

    // 2. Валидация
    if (!validateAuthor(author)) {
        showError("Автор должен быть в формате: 'Имя Фамилия ИО' (Пример: Клоц АН)");
        return;
    }
    if (!validateTitle(title)) {
        showError("Название должно быть в кавычках (Пример: \"Выбор\")");
        return;
    }
    if (!validateCode(code)) {
        showError("Код должен быть в формате 123-12345");
        return;
    }
    if (!validatePages(pages)) {
        showError("Наполнение должно быть в формате X/Y, где Y < X (Пример: 102/5)");
        return;
    }

    // 3. Создание объекта и сохранение
    Book newBook(author, title, code, pages, type, genre);

    QFile file("result.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        showError("Не удалось открыть файл для записи.");
        return;
    }

    QTextStream stream(&file);
    newBook.saveToFile(stream);
    file.close();

    QMessageBox::information(this, "Успех", "Данные успешно сохранены в result.txt");


    clearForm();
}
void MainWindow::on_resetButton_clicked()
{
    clearForm();
}

void MainWindow::clearForm()
{
    ui->authorLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->codeLineEdit->clear();
    ui->pagesLineEdit->clear();

    // Сбрасываем радио-кнопки (можно сделать ни одна не выбрана)
    ui->paperRadio->setAutoExclusive(false);
    ui->paperRadio->setChecked(false);
    ui->electronicRadio->setChecked(false);
    ui->paperRadio->setAutoExclusive(true);

    // Сбрасываем чекбоксы
    ui->detectiveCheck->setChecked(false);
    ui->fantasyCheck->setChecked(false);
    ui->novelCheck->setChecked(false);
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::warning(this, "Ошибка ввода", message);
}

MainWindow::~MainWindow()
{
    delete ui;
}
