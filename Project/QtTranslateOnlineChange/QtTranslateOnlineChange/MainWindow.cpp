#include "MainWindow.h"
#include <QTranslator>
#include "MainApplication.h"
#include "../Childlib//MyWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_pChildWindow = new MyWindow(this);
    m_pChildWindow->show();

    connect(ui.pushButton, &QPushButton::clicked, [&]
    {
        static bool bcn{ false };
        static_cast<MainApplication*>(MainApplication::instance())->changeTranslate(bcn ? "en" : "cn");
        bcn = !bcn;
    });

    // ����������app�������ź� ִ����Ӧ�ķ����ִ���������
    connect(qApp, SIGNAL(signalLanguageChange()), this, SLOT(onLanguageChange()));
}

/*
 * @func   MainWindow::onLanguageChange
 * @brief  �յ���������Ϣ�����¼��ط����ִ�����ۺ���
 * @return void
 */
void MainWindow::onLanguageChange()
{
    ui.retranslateUi(this);
}
