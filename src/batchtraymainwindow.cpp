#include <vector>
#include <memory>
#include <array>
#include <fstream>
#include <sstream>
//       <iostream>
//       <cstdio>

#include <QDebug>

#include "batchtraymainwindow.h"
#include "ui_batchtraymainwindow.h"

static const std::string CERR_REDIRECT = "2>&1";

#if defined(WIN32) || defined(WIN64) || defined(Q_OS_WIN) || defined(_WIN32) || defined(__WIN23__) || defined(_WIN64) || defined(__WIN64__)
#define WINXX
#else  /* WINXX */
#define PCLOSE pclose
#define POPEN popen
#endif /* WINXX */

#ifdef WINXX
#define PCLOSE _pclose
#define POPEN _popen
#else  /* WINXX */
#define PCLOSE pclose
#define POPEN popen
#endif /* WINXX */

#ifdef WINXX
#include <windows.h>    // GetModuleFileNameW
#else /* WINXX */
#include <limits.h>
#include <unistd.h>     // readlink
#endif /* WINXX */

BatchTrayMainWindow::BatchTrayMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BatchTrayMainWindow)
{
    ui->setupUi(this);

    connect(ui->actionStart, &QAction::triggered, this, &BatchTrayMainWindow::start);

}

BatchTrayMainWindow::~BatchTrayMainWindow()
{
    delete ui;
}

void BatchTrayMainWindow::start()
{
    connect(&m_process, &QProcess::readyReadStandardOutput, this, &BatchTrayMainWindow::readOutput);

    m_process.start("C:\\home\\ark\\devel\\nig\\dfpost\\db.git\\src\\utils\\herzutils\\batchtray\\pgsql\\batchtray-pgsql.bat");
    // m_process.waitForFinished(); // Assuming that you do want t


/* * * * * *
 *
 *  [!] OPENS TERMINAL WINDOW
 *
    // https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
    std::array<char, 128> buffer;
    std::string result;

    std::string cmd = "C:\\home\\ark\\devel\\nig\\dfpost\\db.git\\src\\utils\\herzutils\\batchtray\\pgsql\\batchtray-pgsql.bat";
    std::unique_ptr<FILE, decltype(&PCLOSE)> pipe(POPEN(cmd.c_str(), "r"), PCLOSE);
    // if (!pipe)
    //     throw std::runtime_error("popen() failed!"); -- #include <stdexcept>
    if (pipe) {
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            result = buffer.data();
            QString line = QString::fromStdString(result);
            ui->plainTextEdit->insertPlainText(line);
            qDebug() << line;
            // if (nullptr != terminateCallback) {
            //     const auto z = terminateCallback();
            //    if (0 > z) {
            //        // debug("Terminate command received");
            //        return std::string();
            //    }
            //}
        }
    } else {
        // error("Can't open pipe: " + cmd);
        // return std::string();
    }
    // return result;

    * * * * * * */

}

void BatchTrayMainWindow::readOutput()
{
    while(m_process.canReadLine()) {
        const auto line = m_process.readLine();
        ui->plainTextEdit->insertPlainText(line);
        qDebug() << line;
    }
}

