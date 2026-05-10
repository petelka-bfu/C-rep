#include "shieldmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QCoreApplication>
#include <algorithm>

ShieldManager::ShieldManager()
{
}

double ShieldManager::parseDouble(const QJsonValue &value) const
{
    if (value.isDouble()) {
        return value.toDouble();
    }

    if (value.isString()) {
        QString str = value.toString().trimmed();

        bool ok;
        double result = str.toDouble(&ok);
        if (ok) return result;

        if (!str.contains('.')) {
            QString cleaned = str;
            while (cleaned.length() > 1 && cleaned.startsWith('0')) {
                cleaned.remove(0, 1);
            }
            result = cleaned.toDouble(&ok);
            if (ok) return result;
        }
    }

    qDebug() << "Не удалось преобразовать в число:" << value;
    return -1.0;
}

bool ShieldManager::loadFromJson(const QString &filePath)
{
    m_allShields.clear();

    qDebug() << "=== ЗАГРУЗКА JSON ===";
    qDebug() << "Путь:" << filePath;

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "Файл НЕ СУЩЕСТВУЕТ!";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "НЕ УДАЛОСЬ ОТКРЫТЬ ФАЙЛ!";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.isEmpty()) {
        qDebug() << "Файл пуст!";
        return false;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "ОШИБКА ПАРСИНГА JSON:" << error.errorString();
        return false;
    }

    if (!doc.isArray()) {
        qDebug() << "Документ НЕ МАССИВ!";
        return false;
    }

    QJsonArray arr = doc.array();
    qDebug() << "Количество элементов в массиве:" << arr.size();

    for (int i = 0; i < arr.size(); ++i) {
        QJsonValue val = arr[i];

        if (!val.isObject()) {
            qDebug() << "Элемент" << i << "не является объектом!";
            continue;
        }

        QJsonObject obj = val.toObject();

        QString name = obj["name"].toString();
        QString description = obj["description"].toString();
        double coeff = parseDouble(obj["defense_coeff"]);
        QString type = obj["defense_type"].toString();

        Shield shield(name, description, coeff, type);
        m_allShields.append(shield);
    }

    qDebug() << "Загружено щитов:" << m_allShields.size();

    // Разделяем и сортируем валидные щиты
    separate();
    sortValidShields();  // ← сортировка перед отображением

    return m_allShields.size() > 0;
}

void ShieldManager::sortValidShields()
{
    // Сортируем валидные щиты в обратном алфавитном порядке
    std::sort(m_validShields.begin(), m_validShields.end());

    qDebug() << "Валидные щиты отсортированы (обратный алфавитный порядок)";
    for (const Shield &s : m_validShields) {
        qDebug() << "  -" << s.getName();
    }
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

void ShieldManager::saveCorruptedToJson(const QString &filePath)
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
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Сохранено битых щитов в" << filePath << ":" << m_corruptedShields.size();
    }
}

QVector<Shield> ShieldManager::getValidShields() const
{
    return m_validShields;  // возвращаем уже отсортированные
}

QVector<Shield> ShieldManager::getCorruptedShields() const
{
    return m_corruptedShields;
}

QVector<Shield> ShieldManager::getAllShields() const
{
    return m_allShields;
}
