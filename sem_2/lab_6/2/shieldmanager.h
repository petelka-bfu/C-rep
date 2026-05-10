#ifndef SHIELDMANAGER_H
#define SHIELDMANAGER_H

#include <QVector>
#include <QString>
#include "shield.h"

class ShieldManager
{
public:
    ShieldManager();

    // Загрузка из JSON файла
    bool loadFromJson(const QString &filePath);

    // Сохранение битых щитов в отдельный файл
    void saveCorruptedToJson(const QString &filePath);

    // Получение щитов (уже отсортированных)
    QVector<Shield> getValidShields() const;
    QVector<Shield> getCorruptedShields() const;
    QVector<Shield> getAllShields() const;

private:
    QVector<Shield> m_allShields;
    QVector<Shield> m_validShields;
    QVector<Shield> m_corruptedShields;

    void separate();
    void sortValidShields();  // ← новый метод для сортировки

    double parseDouble(const QJsonValue &value) const;
};

#endif // SHIELDMANAGER_H
