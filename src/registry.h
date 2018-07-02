#ifndef REGISTRY_H
#define REGISTRY_H

#include <QHash>
#include <QString>

#include "schedule.h"

// Filename constants for config and save files
const std::string CONFIG_FILENAME = "paycheck.config";
const std::string DATA_FILENAME = "schedule.data";
// Format constants for saved data
const QString DATE_FORMAT = "dd/MM/yyyy";
const QString TIME_FORMAT = "hh:mm";
// Names for config variables
const QString HOURLY_WAGE = "wage";
const QString CURRENCY = "curr";
const QString LANGUAGE = "lang";

/**
 * @brief The Registry class retrieves and holds information about the configuration variables
 * of the program.
 *
 * The registry is invalid until it loads data from a config file. Then, it will store all that
 * information for as long as it lives. Information can be retrieved in the adequate format
 * with the use of the implemented getters.
 */
class Registry
{
public:
    /**
     * @brief The Language enum represents a language for the program to be shown in.
     */
    enum Language {ES};

public:

    Registry() = default;

    /**
     * @brief Return whether the registry is valid or not.
     *
     * The registry is invalid until it has loaded data from the config file, at which point
     * it becomes valid.
     */
    bool isValid() const;

    /**
     * @brief Loads data from the config file.
     *
     * The filename of the config file is given by a constant and cannot be changed.
     * If there's any problem finding or opening the config file, it will throw an error.
     *
     * After all the data has been successfully loaded, the registry becomes valid.
     */
    void loadData();

    /**
     * @brief Writes the current registry's data to the config file, overwriting the old config
     * file.
     *
     * The registry needs to be valid, otherwise it will throw an error.
     */
    void writeData() const;

    // Getters for config variables
    float getHourlyWage() const;
    QString getCurrency() const;
    Language getLanguage() const;

    // Setters for the config variables
    void setHourlyWage(float wage);
    void setCurrency(QString currency);

private:
    QHash<QString, QString> config;
    bool valid = false;
};

/**
 * @brief Utility function to split a string into pieces by using a delimiter, similar to
 * Python's split method, but it will also convert the parts to QString.
 * @param s Original string to be split.
 * @param delimiter Delimiter at which to split the string. The delimiter will not be included in
 * any of the parts.
 * @return A vector of QStrings with all the parts after the splitting.
 */
std::vector<QString> split(std::string s, std::string delimiter);

#endif // REGISTRY_H
