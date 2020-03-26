#include "MainApplication.h"
#include <QTranslator>

MainApplication::MainApplication(int &argc, char **argv, const QString strVersionInfo)
    :QApplication(argc, argv)
{
    
}

/*
 * @func   MainApplication::changeTranslate 
 * @brief  �л������ļ�
 * @param  [in]  const QString & strLanguageName  �����ĸ�����
 * @return void  
 */ 
void MainApplication::changeTranslate(const QString& strLanguageName)
{
    QTranslator translator1;
    QTranslator translator2;
    if (strLanguageName == "cn")
    {
        translator1.load("qttranslateonlinechange_zh.qm");
        translator2.load("childlib_zh.qm");
    }
    else
    {
        translator1.load("qttranslateonlinechange_en.qm");
        translator2.load("childlib_en.qm");
    }

    installTranslator(&translator1);
    installTranslator(&translator2);
    
    emit signalLanguageChange();
}
