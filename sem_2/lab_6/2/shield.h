#ifndef SHIELD_H
#define SHIELD_H

#include <QString>
#include <QStringList>
#include <QDebug>

class Shield
{
public:
    Shield();
    Shield(const QString &name, const QString &description,
           double defenseCoeff, const QString &defenseType);

    QString getName() const;
    QString getDescription() const;
    double getDefenseCoeff() const;
    QString getDefenseType() const;

    void setName(const QString &name);
    void setDescription(const QString &description);
    void setDefenseCoeff(double coeff);
    void setDefenseType(const QString &type);

    bool isValid() const;
    void print() const;

private:
    QString m_name;
    QString m_description;
    double m_defenseCoeff;
    QString m_defenseType;

    bool isValidName() const;
    bool isValidDescription() const;
    bool isValidDefenseCoeff() const;
    bool isValidDefenseType() const;
};

#endif // SHIELD_H
