#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>

/**
  @brief Синглтон для доступа к конфигурации

  Usage:
  @code
    ...
    ...
    //пердварительная настройка (должен быть где-нибуль в main)
    QApplication::setOrganizationName("Organization name");
    QApplication::setApplicationName("App name");
    ...
    ...
    //установка значений по умолчанию (строка может быть многострочной)
    Settings::setDefaults("SomeKey: value1; SomeSection/SomeKey: value2");

    //или так
    QFile f(":/defaults/config");
    f.open(QIODevice::ReadOnly);
    Settings::setDefaults(f.readAll());
    ...
    ...
    void fun(){
        ...
        QVariant val1 = Settings::get(Settings::SomeKey);
        Settings::set(Settings::SomeKey) = "new val1";
        ...
        QVariant val2 = Settings::get(Settings::SomeKey, Settings::SomeSection);
        Settings::set(Settings::SomeKey, Settings::SomeSection) = "new val2";
        ...
    }
  @endcode
*/

class Settings
{
    Q_GADGET
    Q_ENUMS(Section)
    Q_ENUMS(Key)
public:
    enum Section
    {
        General,
        DataBase
    };

    enum Key
    {
        DBHost,
        DBPort,
        DBName,
        DBUser,
        DBPass,
        Schema
    };

    class ValueRef
    {
    public:
        ValueRef(Settings &st, const QString &kp) :
            parent(st), keyPath(kp){}
        ValueRef & operator = (const QVariant &d);
    private:
        Settings &parent;
        const QString keyPath;
    };

    static void setDefaults(const QString &str);
    static QVariant get(Key, Section /*s*/ = General);
    static ValueRef set(Key, Section /*s*/ = General);

private:
    QString keyPath(Section, Key);

    static Settings & instance();
    QMetaEnum keys;
    QMetaEnum sections;
    QMap<QString, QVariant> defaults;
    QSettings conf;

    Settings();
    Settings(const Settings &);
    Settings & operator = (const Settings &);
};

#endif // SETTINGS_H
