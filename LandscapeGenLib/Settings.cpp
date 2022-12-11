#include "Settings.h"
#include <QSettings>
#include <QMetaEnum>
//#include <QRegExp>
#include <QRegularExpression>
#include <QStringList>

Settings::Settings()
{
    const QMetaObject &mo = staticMetaObject;
    int idx = mo.indexOfEnumerator("Key");
    keys = mo.enumerator(idx);

    idx = mo.indexOfEnumerator("Section");
    sections = mo.enumerator(idx);
}

QVariant Settings::get(Key k, Section s)
{
    Settings &self = instance();
    QString key = self.keyPath(s, k);
    /*QVariant res2 = self.conf.value(key, self.defaults[key]);     //for QSetting
    QVariant res = self.defaults[key];                              //for Setting.default
    QString str = res.toString();
    int i = res.toInt();
    return res2;*/
    return self.conf.value(key, self.defaults[key]);
}

Settings::ValueRef Settings::set(Key k, Section s)
{
    Settings &self = instance();
    return ValueRef(self, self.keyPath(s, k));
}

void Settings::setDefaults(const QString &str)
{
    Settings &self = instance();

    //section/key : value
    //section - optional
    QRegularExpression rxRecord("^\\s*(((\\w+)/)?(\\w+))\\s*:\\s*([^\\s].{0,})\\b\\s*$");

    //qDebug() << "TEST";

    auto kvs = str.split(QRegularExpression(";\\W*"), Qt::SkipEmptyParts); //key-values
    for(auto kv : kvs)
    {
        QRegularExpressionMatchIterator i = rxRecord.globalMatch(kv);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();

            QString section = match.captured(3);
            QString key = match.captured(4);
            QString value = match.captured(5);

            int iKey = self.keys.keyToValue(key.toLocal8Bit().data());
            if (iKey != -1)
            {
                int iSection = self.sections.keyToValue(section.toLocal8Bit().data());
                if (section.isEmpty() || iSection != -1)
                {
                    self.conf.setValue(match.captured(1), value); //for QSetting
                    self.defaults[match.captured(1)] = value; //for Setting.default
                }
            }
        }
    }
}

//Settings::ValueRef-----------------------------------------------------------
Settings::ValueRef & Settings::ValueRef::operator = (const QVariant &data)
{
    parent.conf.setValue(keyPath, data); //for QSetting
    parent.defaults[keyPath] = data; //for Setting.default
    return *this;
}


//PRIVATE METHODS--------------------------------------------------------------
QString Settings::keyPath(Section s, Key k)
{
    auto szSection = sections.valueToKey(s);
    auto szKey = keys.valueToKey(k);
    return QString(s == General ? "%1" : "%2/%1").arg(szKey).arg(szSection);
}

Settings & Settings::instance()
{
    static Settings singleton;
    return singleton;
}
