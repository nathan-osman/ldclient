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

#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>

#include "ledwidget.h"
#include "lightwidget.h"

LightWidget::LightWidget(const QString &name)
    : mName(name),
      mLEDWidget(new LEDWidget),
      mLabel(new QLabel(name))
{
    QPushButton *renameButton = new QPushButton(tr("Rename"));
    QPushButton *deleteButton = new QPushButton(tr("Delete"));

    connect(renameButton, &QPushButton::clicked, this, &LightWidget::onRenameClicked);
    connect(deleteButton, &QPushButton::clicked, this, &LightWidget::onDeleteClicked);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(mLEDWidget);
    hboxLayout->addWidget(mLabel);
    hboxLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    hboxLayout->addWidget(renameButton);
    hboxLayout->addWidget(deleteButton);
    setLayout(hboxLayout);
}

bool LightWidget::lit() const
{
    return mLEDWidget->lit();
}

void LightWidget::setLit(bool lit)
{
    mLEDWidget->setLit(lit);
}

QString LightWidget::name() const
{
    return mName;
}

void LightWidget::setName(const QString &name)
{
    emit renamed(mName, name);
    mLabel->setText(mName = name);
}

void LightWidget::onRenameClicked()
{
    QString name = QInputDialog::getText(
        nullptr,
        tr("Rename"),
        tr("Name:"),
        QLineEdit::Normal,
        mName
    );

    if (!name.isNull()) {
        setName(name);
    }
}

void LightWidget::onDeleteClicked()
{
    emit deleted(mName);
}
