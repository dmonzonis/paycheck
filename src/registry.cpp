#include "registry.h"

#include <vector>
#include <fstream>
#include <QDate>
#include <QTime>

Registry::Registry()
{
}

bool Registry::isValid() const
{
    return valid;
}

void Registry::loadData()
{
    // TODO: Search for file in the executable absolute path
    std::ifstream configFile(CONFIG_FILENAME);
    if (!configFile)
    {
        // TODO: Make registry error class
        throw std::runtime_error("Error opening config file");
    }
    std::string input, delimiter = "=";
    while (std::getline(configFile, input))
    {
        // Config data is stored as key=value, so we have two parts, one for the key and
        // one for the value
        auto parts = split(input, delimiter);
        config.insert(parts.at(0), parts.at(1));
    }

    valid = true;
}

float Registry::getHourlyWage() const
{
    if (!isValid())
    {
        throw std::runtime_error("Registry not initialized.");
    }
    return config.value("hourly_wage").toFloat();
}

QString Registry::getCurrency() const
{
    if (!isValid())
    {
        throw std::runtime_error("Registry not initialized.");
    }
    return config.value("currency");
}

Registry::Language Registry::getLanguage() const
{
    // TODO: Get language from config file and translate to enum
    return Language::ES;
}

std::vector<QString> split(std::string s, std::string delimiter)
{
    std::vector<QString> result;
    int pos;
    // Split and add to the vector as long as the delimiter is found in the string
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        result.push_back(QString::fromStdString(s.substr(0, pos)));
        s.erase(0, pos + delimiter.length());
    }
    // Push the remains of the string
    result.push_back(QString::fromStdString(s));
    return result;
}