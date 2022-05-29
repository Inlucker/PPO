//#include "mainwindow.h"
#include "BaseWindow.h"
#include "Settings.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Устанавливаем конфиг файл
    QApplication::setOrganizationName("Organization name");
    QApplication::setApplicationName("App name");
    QFile cfgDefaults(FILENAME);
    cfgDefaults.open(QIODevice::ReadOnly);
    Settings::setDefaults(cfgDefaults.readAll());
    /*qDebug() << Settings::get(Settings::DBHost, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    qDebug() << Settings::get(Settings::DBName, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBUser, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBPass, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::Schema, Settings::DataBase).toString();*/

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("./logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    //MainWindow w;
    BaseWindow w;
    w.show();
    return a.exec();
}

// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    //case QtInfoMsg:     out << "UAC "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    //case QtWarningMsg:  out << "EXC "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << "\n";
    out.flush();    // Очищаем буферизированные данные
}
