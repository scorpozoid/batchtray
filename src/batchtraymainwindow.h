#ifndef BATCHTRAYMAINWINDOW_H
#define BATCHTRAYMAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QString>
#include <QPlainTextEdit>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class BatchTrayMainWindow; }
QT_END_NAMESPACE

class BatchTrayMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BatchTrayMainWindow(QWidget *parent = nullptr);
    ~BatchTrayMainWindow();

    void setCommand(const QString &value);
    QString command();

    void setLimit(const int value);

private slots:
    void start();
    void stop();
    void minimize();
    /// Check process is active
    bool active();
    /// Check settings (command) is valid
    bool valid();

    void readOutput();

    void on_show_hide(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::BatchTrayMainWindow *ui;
    QProcess m_process;
    QString m_command;
    QSystemTrayIcon m_icon;
    int m_log_limit{100};

    void logline(QPlainTextEdit *edit, const QString &line);
    void log(const QString &line);

    void setupTrayIcon();

};
#endif // BATCHTRAYMAINWINDOW_H
