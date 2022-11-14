#ifndef BATCHTRAYMAINWINDOW_H
#define BATCHTRAYMAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class BatchTrayMainWindow; }
QT_END_NAMESPACE

class BatchTrayMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BatchTrayMainWindow(QWidget *parent = nullptr);
    ~BatchTrayMainWindow();

private slots:
    void start();
    void readOutput();

private:
    Ui::BatchTrayMainWindow *ui;
    QProcess m_process;

};
#endif // BATCHTRAYMAINWINDOW_H
