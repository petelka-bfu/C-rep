#include "book.h"
#include <qdebug.h>

Book::Book(const QString &author, const QString &title, const QString &code,
           const QString &pages, const QString &type, const QString &genre)
    : m_author(author), m_title(title), m_code(code),
    m_pages(pages), m_type(type), m_genre(genre)
{}

void Book::saveToFile(QTextStream &stream) const
{
    stream << "Автор: " << m_author << "\n";
    stream << "Название: " << m_title << "\n";
    stream << "Код: " << m_code << "\n";
    stream << "Наполнение: " << m_pages << "\n";
    stream << "Тип издания: " << m_type << "\n";
    stream << "Жанр: " << m_genre << "\n";
    stream << "------------------------\n";
}
