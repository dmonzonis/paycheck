#include "registry.h"

#include <vector>
#include <fstream>
#include <QDate>
#include <QTime>

bool Registry::isValid() const
{
    return valid;
}

void Registry::loadData()
{
    // TODO: Search for file in the executable absolute path
    // TODO: Use QFile instead of fstream
    std::ifstream configFile(CONFIG_FILENAME);
    if (!configFile)
    {
        // TODO: Make registry error class
        throw std::runtime_error("Config file not found.");
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

void Registry::writeData() const
{
    if (!isValid())
    {
        // TODO: Make registry error class
        throw std::runtime_error("Registry not initialized.");
    }
    // TODO: Use QFile instead of fstream
    std::ofstream configFile(CONFIG_FILENAME);
    // Iterate through all the config keys and variables, and write them to file
    for (auto it = config.begin(); it != config.end(); ++it)
    {
        configFile << it.key().toStdString() << "=" << it.value().toStdString() << "\n";
    }
}

void Registry::generateDefaultConfigFile() const
{
    std::ofstream configFile(CONFIG_FILENAME);
    // Add default hardcoded values
    // TODO: Make method to format these automatically
    configFile << HOURLY_WAGE.toStdString() << "=" << "6" << "\n";
    configFile << CURRENCY.toStdString() << "=" << "€" << "\n";
    configFile << LANGUAGE.toStdString() << "=" << "es" << "\n";
}

float Registry::getHourlyWage() const
{
    if (!isValid())
    {
        // TODO: Make registry error class
        throw std::runtime_error("Registry not initialized.");
    }
    return config.value(HOURLY_WAGE).toFloat();
}

QString Registry::getCurrency() const
{
    if (!isValid())
    {
        throw std::runtime_error("Registry not initialized.");
    }
    return config.value(CURRENCY);
}

Registry::Language Registry::getLanguage() const
{
    // TODO: Get language from config file and translate to enum
    return Language::ES;
}

void Registry::setHourlyWage(float wage)
{
    config.insert(HOURLY_WAGE, QString::number(wage));
}

void Registry::setCurrency(QString currency)
{
    config.insert(CURRENCY, currency);
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
