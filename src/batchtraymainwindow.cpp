#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QColor>

#include "batchtraymainwindow.h"
#include "ui_batchtraymainwindow.h"


BatchTrayMainWindow::BatchTrayMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BatchTrayMainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->setReadOnly(true);

    setupTrayIcon();

    connect(ui->actionStart, &QAction::triggered, this, &BatchTrayMainWindow::start);
    connect(ui->actionStop, &QAction::triggered, this, &BatchTrayMainWindow::stop);
    connect(ui->actionMinimize, &QAction::triggered, this, &BatchTrayMainWindow::minimize);
}

BatchTrayMainWindow::~BatchTrayMainWindow()
{
    delete ui;
}

void BatchTrayMainWindow::setCommand(const QString &value)
{
    m_command = value;
}

QString BatchTrayMainWindow::command()
{
    return m_command;
}

void BatchTrayMainWindow::setLimit(const int value)
{
    m_log_limit = value;
}

void BatchTrayMainWindow::start()
{
    if (active())
        return;
    if (!valid())
        return;
    connect(&m_process, &QProcess::readyReadStandardOutput, this, &BatchTrayMainWindow::readOutput);
    m_process.setReadChannel(QProcess::StandardOutput);
 // m_process.setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *args) { args->flags |= CREATE_NEW_PROCESS_GROUP; });
    m_process.start(m_command);
    m_process.waitForStarted();
}

void BatchTrayMainWindow::stop()
{
    if (!active())
        return;

    // FAIL | > m_process.terminate();

    // FAIL || > const char ctrl_c = 0x03;
    // FAIL || > m_process.write(&ctrl_c, sizeof(ctrl_c));

    // FAIL ||| #include <windows.h>
    // FAIL ||| > log(QString("Sending `Ctrl+C` to process #%1 (1)").arg(m_process.pid()->dwProcessId));
    // FAIL ||| > log(QString("Sending `Ctrl+C` to process #%1 (2)").arg(m_process.processId()));
    // FAIL ||| > auto success = GenerateConsoleCtrlEvent(CTRL_C_EVENT, m_process.pid()->dwProcessId);
    // FAIL ||| > if (!success) {
    // FAIL ||| >     LPVOID lpMsgBuf;
    // FAIL ||| >     auto err = GetLastError();
    // FAIL ||| >     FormatMessage(
    // FAIL ||| >         FORMAT_MESSAGE_ALLOCATE_BUFFER |
    // FAIL ||| >         FORMAT_MESSAGE_FROM_SYSTEM |
    // FAIL ||| >         FORMAT_MESSAGE_IGNORE_INSERTS,
    // FAIL ||| >         nullptr,
    // FAIL ||| >         err,
    // FAIL ||| >         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    // FAIL ||| >         reinterpret_cast<LPTSTR>(&lpMsgBuf),
    // FAIL ||| >         0, nullptr);
    // FAIL ||| >     auto error_string = QString::fromWCharArray((reinterpret_cast<LPTSTR>(lpMsgBuf)));
    // FAIL ||| >     log(error_string);
    // FAIL ||| >     LocalFree(lpMsgBuf);
    // FAIL ||| > } else {
    // FAIL ||| >     log(QString("Successfully send `Ctrl+C` to process #%1").arg(m_process.pid()->dwProcessId));
    // FAIL ||| > }

    // Can't send Ctrl+C to batch process to carefull finalize it.
    // May be problem in MS-DOS's exit prompt?
    // 'Are you sure terminate batch [Y/N]?'

    m_process.terminate();
    m_process.waitForFinished(7000);

    m_process.close();
}

void BatchTrayMainWindow::minimize()
{
    //
}

bool BatchTrayMainWindow::active()
{
    switch (m_process.state()) {
    case QProcess::Starting:
        log("The process is starting, but the program has not yet been invoked");
        return true;
    case QProcess::Running:
        log("The process is running and is ready for reading and writing");
        return true;
    default: // QProcess::NotRunning
        log("The process is not running");
    }
    return false;
}

bool BatchTrayMainWindow::valid()
{
    if (m_command.isEmpty()) {
        log("Command is empty");
        return false;
    }
    if (!QFile::exists(m_command)) {
        log(QString("Command file doesn't exists (%1)").arg(m_command));
        return false;
    }
    return true;
}

void BatchTrayMainWindow::readOutput()
{
    while(m_process.canReadLine()) {
        const auto line = m_process.readLine();
        log(line);
        qDebug() << line;
    }
}

void BatchTrayMainWindow::logline(QPlainTextEdit *edit, const QString &line)
{
    while (m_log_limit < edit->document()->lineCount()) {
        QTextCursor cursor = edit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, 0);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
    }
    {
        // QTextCursor cursor = edit->textCursor();
        // cursor.movePosition(QTextCursor::End);
        // ui->plainTextEdit->insertPlainText(line);
        ui->plainTextEdit->appendPlainText(line);
    }
}

void BatchTrayMainWindow::log(const QString &line)
{
    logline(ui->plainTextEdit, line);
    qDebug() << line;
}

void BatchTrayMainWindow::on_show_hide(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick: {
        if (isVisible()) {
            hide();
        } else {
            show();
            raise();
            setFocus();
        }
        return;
    }
    default: return;
    }
}

void BatchTrayMainWindow::setupTrayIcon()
{
    auto trayIcon = new QSystemTrayIcon(this);
    // trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    // trayIcon->setIcon(QIcon(":/appicon"));
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::GlobalColor::red);
    trayIcon->setIcon(QIcon(pixmap));
    trayIcon->setToolTip("!!!!");

    QMenu * menu = new QMenu(this);
    QAction * viewWindow = new QAction(trUtf8("Развернуть окно"), this);
    QAction * quitAction = new QAction(trUtf8("Выход"), this);

    connect(ui->actionStop, &QAction::triggered, this, &BatchTrayMainWindow::stop);

    connect(viewWindow, &QAction::triggered, this, &QMainWindow::show);
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();

 // OKAY --    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(trayIcon, &QSystemTrayIcon::activated, this, &BatchTrayMainWindow::on_show_hide);
}

