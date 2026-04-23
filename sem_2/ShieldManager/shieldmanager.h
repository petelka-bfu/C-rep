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

    void loadFromJson();
    void saveToJson();
    void saveCorruptedToJson();
    void addShield(const Shield &shield);

    QVector<Shield> getValidShields() const;
    QVector<Shield> getCorruptedShields() const;

    bool importFromTxt(const QString &txtFilePath);

private:
    QString m_jsonFilePath;
    QString m_corruptedFilePath;
    QVector<Shield> m_allShields;

    void separateValidAndCorrupted(QVector<Shield> &valid, QVector<Shield> &corrupted) const;
};

#endif // SHIELDMANAGER_H
