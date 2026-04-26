#include "shieldmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

ShieldManager::ShieldManager(const QString &inputFilePath,
                             const QString &validFilePath,
                             const QString &corruptedFilePath)
    : m_inputFilePath(inputFilePath)
    , m_validFilePath(validFilePath)
    , m_corruptedFilePath(corruptedFilePath)
{
    loadFromJson();
    separate();
    splitAndSave();
}

void ShieldManager::loadFromJson()
{
    m_allShields.clear();

    QFile file(m_inputFilePath);
    if (!file.exists()) {
        qDebug() << "Файл не существует:" << m_inputFilePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл для чтения:" << m_inputFilePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "Некорректный JSON в файле:" << m_inputFilePath;
        return;
    }

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

    qDebug() << "Загружено щитов из" << m_inputFilePath << ":" << m_allShields.size();
}

void ShieldManager::separate()
{
    m_validShields.clear();
    m_corruptedShields.clear();

    for (const Shield &s : m_allShields) {
        if (s.isValid()) {
            m_validShields.append(s);
        } else {
            m_corruptedShields.append(s);
        }
    }

    qDebug() << "Разделение: валидных =" << m_validShields.size()
             << ", битых =" << m_corruptedShields.size();
}

void ShieldManager::saveValidToJson()
{
    QJsonArray jsonArray;
    for (const Shield &s : m_validShields) {
        QJsonObject obj;
        obj["name"] = s.getName();
        obj["description"] = s.getDescription();
        obj["defense_coeff"] = s.getDefenseCoeff();
        obj["defense_type"] = s.getDefenseType();
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);
    QFile file(m_validFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи:" << m_validFilePath;
        return;
    }
    file.write(doc.toJson());
    file.close();

    qDebug() << "Сохранено валидных щитов в" << m_validFilePath << ":" << m_validShields.size();
}

void ShieldManager::saveCorruptedToJson()
{
    QJsonArray jsonArray;
    for (const Shield &s : m_corruptedShields) {
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

    qDebug() << "Сохранено битых щитов в" << m_corruptedFilePath << ":" << m_corruptedShields.size();
}

void ShieldManager::splitAndSave()
{
    saveValidToJson();
    saveCorruptedToJson();
    qDebug() << "Разделение и сохранение завершены";
}

QVector<Shield> ShieldManager::getValidShields() const
{
    return m_validShields;
}

QVector<Shield> ShieldManager::getCorruptedShields() const
{
    return m_corruptedShields;
}
