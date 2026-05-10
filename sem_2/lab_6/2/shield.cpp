#include "shield.h"

static const QStringList VALID_TYPES = {"Физическая", "Магическая", "Огненная", "Ледяная"};

Shield::Shield()
    : m_name("")
    , m_description("")
    , m_defenseCoeff(0.0)
    , m_defenseType("")
{
}

Shield::Shield(const QString &name, const QString &description,
               double defenseCoeff, const QString &defenseType)
    : m_name(name)
    , m_description(description)
    , m_defenseCoeff(defenseCoeff)
    , m_defenseType(defenseType)
{
}

QString Shield::getName() const { return m_name; }
QString Shield::getDescription() const { return m_description; }
double Shield::getDefenseCoeff() const { return m_defenseCoeff; }
QString Shield::getDefenseType() const { return m_defenseType; }

void Shield::setName(const QString &name) { m_name = name; }
void Shield::setDescription(const QString &description) { m_description = description; }
void Shield::setDefenseCoeff(double coeff) { m_defenseCoeff = coeff; }
void Shield::setDefenseType(const QString &type) { m_defenseType = type; }

bool Shield::isValidName() const
{
    return !m_name.trimmed().isEmpty();
}

bool Shield::isValidDescription() const
{
    return !m_description.trimmed().isEmpty();
}

bool Shield::isValidDefenseCoeff() const
{
    return m_defenseCoeff > 0.0;
}

bool Shield::isValidDefenseType() const
{
    return VALID_TYPES.contains(m_defenseType);
}

bool Shield::isValid() const
{
    return isValidName() && isValidDescription() &&
           isValidDefenseCoeff() && isValidDefenseType();
}

void Shield::print() const
{
    qDebug() << "Щит:" << m_name
             << "| Описание:" << m_description
             << "| Коэф. защиты:" << m_defenseCoeff
             << "| Тип:" << m_defenseType
             << "| Валидный:" << isValid();
}

// Оператор сравнения для сортировки в ОБРАТНОМ алфавитном порядке
// (чем больше буква в алфавите, тем раньше элемент в списке)
bool Shield::operator<(const Shield &other) const
{
    // Для обратного порядка: сравниваем названия в обратном направлении
    return QString::localeAwareCompare(m_name, other.m_name) > 0;
}
