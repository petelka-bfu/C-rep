#include "shieldmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>

// Конструктор
ShieldManager::ShieldManager(const QString &jsonFilePath,
                             const QString &corruptedFilePath)
    : m_jsonFilePath(jsonFilePath)
    , m_corruptedFilePath(corruptedFilePath)
{

}

// Разделение щитов на валидные и битые
void ShieldManager::separateValidAndCorrupted(QVector<Shield> &valid,
                                              QVector<Shield> &corrupted) const
{
    valid.clear();
    corrupted.clear();

    for (const Shield &s : m_allShields) {
        if (s.isValid()) {
            valid.append(s);
        } else {
            corrupted.append(s);
        }
    }
}

// Сохранение только валидных щитов в файл
void ShieldManager::saveToJson()
{
    QVector<Shield> valid, corrupted;
    separateValidAndCorrupted(valid, corrupted);

    QJsonArray jsonArray;
    for (const Shield &s : valid) {
        QJsonObject obj;
        obj["name"] = s.getName();
        obj["description"] = s.getDescription();
        obj["defense_coeff"] = s.getDefenseCoeff();
        obj["defense_type"] = s.getDefenseType();
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);
    QFile file(m_jsonFilePath);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи:" << m_jsonFilePath;
        return;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "Сохранено валидных щитов:" << valid.size();
}

// Сохранение только битых щитов в отдельный файл
void ShieldManager::saveCorruptedToJson()
{
    QVector<Shield> valid, corrupted;
    separateValidAndCorrupted(valid, corrupted);

    QJsonArray jsonArray;
    for (const Shield &s : corrupted) {
        QJsonObject obj;
        obj["name"] = s.getName();
        obj["description"] = s.getDescription();
        obj["defense_coeff"] = s.getDefenseCoeff();
        obj["defense_type"] = s.getDefenseType();
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);
    QFile file(m_corruptedFilePath);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи:" << m_corruptedFilePath;
        return;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "Сохранено битых щитов:" << corrupted.size();
}

// Добавление нового щита
void ShieldManager::addShield(const Shield &shield)
{
    m_allShields.append(shield);
    saveToJson();
    saveCorruptedToJson();

    qDebug() << "Добавлен щит:" << shield.getName()
             << "Валидный:" << shield.isValid();
}

// Импорт из TXT файла
bool ShieldManager::importFromTxt(const QString &txtFilePath)
{
    QFile file(txtFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть TXT файл:" << txtFilePath;
        return false;
    }

    QTextStream stream(&file);
    int importedCount = 0;
    int corruptedCount = 0;

    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split('|');

        QString name = parts.size() > 0 ? parts[0].trimmed() : "";
        QString description = parts.size() > 1 ? parts[1].trimmed() : "";
        double coeff = -1.0;
        QString type = "";

        if (parts.size() >= 3) {
            coeff = parts[2].trimmed().toDouble();
        }
        if (parts.size() >= 4) {
            type = parts[3].trimmed();
        }

        Shield newShield(name, description, coeff, type);
        m_allShields.append(newShield);

        if (newShield.isValid()) {
            importedCount++;
            qDebug() << "Импортирован корректный щит:" << name;
        } else {
            corruptedCount++;
            qDebug() << "Импортирован битый щит:" << name;
        }
    }
    file.close();

    // Сохраняем все щиты в файлы
    saveToJson();
    saveCorruptedToJson();

    qDebug() << "Импорт завершён. Корректных:" << importedCount
             << "Битых:" << corruptedCount;

    return true;
}

// Получение всех щитов (для отладки)
QVector<Shield> ShieldManager::getAllShields() const
{
    return m_allShields;
}
