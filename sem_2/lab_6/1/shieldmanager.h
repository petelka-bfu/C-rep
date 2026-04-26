#ifndef SHIELDMANAGER_H
#define SHIELDMANAGER_H

#include <QVector>
#include <QString>
#include "shield.h"

class ShieldManager
{
public:
    ShieldManager(const QString &jsonFilePath = "shields.json",
                  const QString &corruptedFilePath = "corrupted_shields.json");

    // Сохранение в JSON файлы
    void saveToJson();
    void saveCorruptedToJson();

    // Добавление нового щита
    void addShield(const Shield &shield);

    // Импорт из TXT файла
    bool importFromTxt(const QString &txtFilePath);

    // Получение всех щитов (для отладки)
    QVector<Shield> getAllShields() const;

private:
    QString m_jsonFilePath;        // путь к файлу с валидными щитами
    QString m_corruptedFilePath;   // путь к файлу с битыми щитами
    QVector<Shield> m_allShields;  // все щиты (и валидные, и битые)

    // Разделение щитов на валидные и битые
    void separateValidAndCorrupted(QVector<Shield> &valid,
                                   QVector<Shield> &corrupted) const;
};

#endif // SHIELDMANAGER_H
