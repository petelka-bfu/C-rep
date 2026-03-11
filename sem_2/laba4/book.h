#ifndef BOOK_H
#define BOOK_H
#include <QtDebug>
#include <QString>
#include <QTextStream>

class Book
{
public:
    // Конструктор для заполнения полей
    Book(const QString &author, const QString &title, const QString &code,
         const QString &pages, const QString &type, const QString &genre);

    // Метод записи в файл
    void saveToFile(QTextStream &stream) const;

private:
    QString m_author;
    QString m_title;
    QString m_code;
    QString m_pages;      // Формат "102/5"
    QString m_type;        // "Бумажное" или "Электронное"
    QString m_genre;       // "Детектив", "Фантастика" или "Роман"
};

#endif // BOOK_H
