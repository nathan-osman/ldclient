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

#include <QApplication>
#include <QCheckBox>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QStyle>
#include <QWidget>

#include "lightwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(tr("ldclient"));
    resize(640, 480);
    move(QApplication::desktop()->availableGeometry().center() - rect().center());

    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    LightWidget *lightWidget = new LightWidget;
    QCheckBox *checkBox = new QCheckBox;

    connect(checkBox, &QCheckBox::toggled, lightWidget, &LightWidget::setLit);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lightWidget, 0, 0, 1, 1);
    mainLayout->addWidget(checkBox, 1, 0, 1, 1);
    centralWidget->setLayout(mainLayout);
}
