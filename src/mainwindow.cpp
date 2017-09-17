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
#include <QMenu>
#include <QMenuBar>

#include "editorwidget.h"
#include "mainwindow.h"
#include "server.h"
#include "serverdialog.h"

MainWindow::MainWindow()
    : mStartServer(new QAction(tr("St&art server..."), this)),
      mStopServer(new QAction(tr("St&op server"), this)),
      mEditor(new EditorWidget),
      mServer(new Server(this))
{
    connect(mStartServer, &QAction::triggered, this, &MainWindow::startServer);
    connect(mStopServer, &QAction::triggered, this, &MainWindow::stopServer);

    mStopServer->setDisabled(true);

    // Create the menu
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(mStartServer);
    file->addAction(mStopServer);
    file->addSeparator();
    file->addAction(tr("&Quit"), this, &MainWindow::close);

    // Create the central widget
    setCentralWidget(mEditor);

    // Set the window title and geometry
    setWindowTitle(tr("ldclient"));
    resize(640, 480);
    move(QApplication::desktop()->availableGeometry().center() - rect().center());
}

void MainWindow::startServer()
{
    ServerDialog().exec();
}

void MainWindow::stopServer()
{
    //...
}
