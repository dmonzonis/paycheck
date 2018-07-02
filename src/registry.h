#ifndef REGISTRY_H
#define REGISTRY_H

#include <QHash>
#include <QString>

#include "schedule.h"

const std::string CONFIG_FILENAME = "paycheck.config";
const std::string DATA_FILENAME = "schedule.data";
const QString DATE_FORMAT = "dd/MM/yyyy";
const QString TIME_FORMAT = "hh:mm";

class Registry
{
public:
    enum Language {ES};

public:
    Registry();
    bool isValid() const;
    void loadData();
    // Getters for config variables
    float getHourlyWage() const;
    QString getCurrency() const;
    Language getLanguage() const;

private:
    QHash<QString, QString> config;
    bool valid = false;
};

std::vector<QString> split(std::string s, std::string delimiter);

#endif // REGISTRY_H
