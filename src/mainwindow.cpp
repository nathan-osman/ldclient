/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>

#include "audiowidget.h"
#include "editorwidget.h"
#include "mainwindow.h"
#include "server.h"

MainWindow::MainWindow()
    : mStartServer(new QAction(tr("St&art server..."), this)),
      mStopServer(new QAction(tr("St&op server"), this)),
      mAudio(new AudioWidget),
      mEditor(new EditorWidget),
      mServer(new Server(this))
{
    connect(mStartServer, &QAction::triggered, this, &MainWindow::startServer);
    connect(mStopServer, &QAction::triggered, this, &MainWindow::stopServer);

    connect(mServer, &Server::audioStarted, mAudio, &AudioWidget::start);
    connect(mServer, &Server::audioStopped, mAudio, &AudioWidget::stop);
    connect(mServer, &Server::stateChanged, mEditor, &EditorWidget::setState);

    mStopServer->setDisabled(true);

    // Create the menus

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(mStartServer);
    file->addAction(mStopServer);
    file->addSeparator();
    file->addAction(tr("&Quit"), this, &MainWindow::close);

    QMenu *audio = menuBar()->addMenu(tr("&Audio"));
    audio->addAction(tr("&Load..."), this, &MainWindow::loadAudio);

    // Create the central widget
    QWidget *widget = new QWidget;
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(mAudio);
    vboxLayout->addWidget(mEditor);
    widget->setLayout(vboxLayout);
    setCentralWidget(widget);

    // Set the window title and geometry
    setWindowTitle(tr("ldclient"));
    resize(640, 480);
    move(QApplication::desktop()->availableGeometry().center() - rect().center());
}

void MainWindow::startServer()
{
    bool ok = false;
    int port = QInputDialog::getInt(
        this,
        tr("Start Server"),
        tr("Port:"),
        8000,
        1,
        65535,
        1,
        &ok
    );

    if (ok) {
        if (mServer->start(port)) {
            mStartServer->setEnabled(false);
            mStopServer->setEnabled(true);
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Unable to bind to port."));
        }
    }
}

void MainWindow::stopServer()
{
    mServer->stop();
    mStartServer->setEnabled(true);
    mStopServer->setEnabled(false);
}

void MainWindow::loadAudio()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load File"));
    if (!filename.isNull()) {
        mAudio->loadFile(filename);
    }
}
