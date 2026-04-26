#ifndef SHIELDMANAGER_H
#define SHIELDMANAGER_H

#include <QVector>
#include <QString>
#include "shield.h"

class ShieldManager
{
public:
    ShieldManager(const QString &inputFilePath = "shields.json",
                  const QString &validFilePath = "valid_shields.json",
                  const QString &corruptedFilePath = "corrupted_shields.json");

    // Загрузка из исходного файла
    void loadFromJson();

    // Разделение и сохранение в два файла
    void splitAndSave();

    // Получение разделённых щитов
    QVector<Shield> getValidShields() const;
    QVector<Shield> getCorruptedShields() const;

private:
    QString m_inputFilePath;      // shields.json (входной файл)
    QString m_validFilePath;      // valid_shields.json (выходной)
    QString m_corruptedFilePath;  // corrupted_shields.json (выходной)

    QVector<Shield> m_allShields;
    QVector<Shield> m_validShields;
    QVector<Shield> m_corruptedShields;

    void separate();
    void saveValidToJson();
    void saveCorruptedToJson();
};

#endif // SHIELDMANAGER_H
