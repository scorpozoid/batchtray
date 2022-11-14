#ifndef BATCHTRAYMAINWINDOW_H
#define BATCHTRAYMAINWINDOW_H

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif // QT_NO_DEBUG
#include <QMainWindow>
#include <QIcon>
#include <QPixmap>
#include <QColor>
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


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void start();
    void stop();
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
#endif /* BATCHTRAYMAINWINDOW_H */
