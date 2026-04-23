#include "shieldmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>

ShieldManager::ShieldManager(const QString &jsonFilePath, const QString &corruptedFilePath)
    : m_jsonFilePath(jsonFilePath), m_corruptedFilePath(corruptedFilePath)
{
    loadFromJson();
}

void ShieldManager::separateValidAndCorrupted(QVector<Shield> &valid, QVector<Shield> &corrupted) const
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

void ShieldManager::loadFromJson()
{
    m_allShields.clear();

    // Загружаем валидные щиты
    QFile validFile(m_jsonFilePath);
    if (validFile.exists() && validFile.open(QIODevice::ReadOnly)) {
        QByteArray data = validFile.readAll();
        validFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray arr = doc.array();
            for (const QJsonValue &val : arr) {
                if (val.isObject()) {
                    QJsonObject obj = val.toObject();
                    Shield shield(
                        obj["name"].toString(),
                        obj["description"].toString(),
                        obj["defense_coeff"].toDouble(),
                        obj["defense_type"].toString()
                        );
                    m_allShields.append(shield);
                }
            }
        }
    }

    // Загружаем битые щиты
    QFile corruptedFile(m_corruptedFilePath);
    if (corruptedFile.exists() && corruptedFile.open(QIODevice::ReadOnly)) {
        QByteArray data = corruptedFile.readAll();
        corruptedFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray arr = doc.array();
            for (const QJsonValue &val : arr) {
                if (val.isObject()) {
                    QJsonObject obj = val.toObject();
                    Shield shield(
                        obj["name"].toString(),
                        obj["description"].toString(),
                        obj["defense_coeff"].toDouble(),
                        obj["defense_type"].toString()
                        );
                    m_allShields.append(shield);
                }
            }
        }
    }

    qDebug() << "loadFromJson: загружено щитов:" << m_allShields.size();
}

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
}

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
}

void ShieldManager::addShield(const Shield &shield)
{
    m_allShields.append(shield);
    saveToJson();
    saveCorruptedToJson();

    // Отладка: выводим информацию о добавленном щите
    qDebug() << "Добавлен щит:" << shield.getName()
             << "Валидный:" << shield.isValid();
}

QVector<Shield> ShieldManager::getValidShields() const
{
    QVector<Shield> valid, corrupted;
    separateValidAndCorrupted(valid, corrupted);

    qDebug() << "Корректных щитов:" << valid.size();
    return valid;
}

QVector<Shield> ShieldManager::getCorruptedShields() const
{
    QVector<Shield> valid, corrupted;
    separateValidAndCorrupted(valid, corrupted);

    qDebug() << "Битых щитов:" << corrupted.size();
    for (const Shield &s : corrupted) {
        qDebug() << "  -" << s.getName() << "причина:";
        if (s.getName().isEmpty()) qDebug() << "    пустое имя";
        if (s.getDescription().isEmpty()) qDebug() << "    пустое описание";
        if (s.getDefenseCoeff() <= 0) qDebug() << "    неверный коэффициент:" << s.getDefenseCoeff();
        QStringList validTypes = {"Физическая", "Магическая", "Огненная", "Ледяная"};
        if (!validTypes.contains(s.getDefenseType())) qDebug() << "    неверный тип:" << s.getDefenseType();
    }

    return corrupted;
}

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

        // Проверяем количество полей
        if (parts.size() < 4) {
            qDebug() << "Недостаточно полей (битый):" << line;
            // Создаём битый щит с пустыми полями
            QString name = parts.size() > 0 ? parts[0].trimmed() : "";
            QString desc = parts.size() > 1 ? parts[1].trimmed() : "";
            double coeff = parts.size() > 2 ? parts[2].trimmed().toDouble() : -1;
            QString type = parts.size() > 3 ? parts[3].trimmed() : "";
            Shield brokenShield(name, desc, coeff, type);
            addShield(brokenShield);
            corruptedCount++;
            continue;
        }

        QString name = parts[0].trimmed();
        QString description = parts[1].trimmed();
        bool ok;
        double coeff = parts[2].trimmed().toDouble(&ok);
        QString type = parts[3].trimmed();

        Shield newShield(name, description, coeff, type);
        addShield(newShield);

        if (newShield.isValid()) {
            importedCount++;
            qDebug() << "Импортирован корректный щит:" << name;
        } else {
            corruptedCount++;
            qDebug() << "Импортирован битый щит:" << name;
        }
    }
    file.close();

    qDebug() << "Импорт завершён. Корректных:" << importedCount << "Битых:" << corruptedCount;
    return true;
}
