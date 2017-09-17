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

#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "editorwidget.h"
#include "lightwidget.h"

EditorWidget::EditorWidget()
    : mVBoxLayout(new QVBoxLayout),
      mLightNumber(1)
{
    QPushButton *pushButton = new QPushButton(tr("Add Light"));
    connect(pushButton, &QPushButton::clicked, this, &EditorWidget::onAddLight);

    mVBoxLayout->addWidget(pushButton);
    mVBoxLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mVBoxLayout);
}

void EditorWidget::setState(const QString &name, bool state)
{
    LightWidget *widget = mLights.value(name);
    if (widget) {
        widget->setLit(state);
    }
}

void EditorWidget::onAddLight()
{
    LightWidget *lightWidget = new LightWidget(tr("light%1").arg(mLightNumber++));

    connect(lightWidget, &LightWidget::renamed, this, &EditorWidget::onLightRenamed);
    connect(lightWidget, &LightWidget::deleted, this, &EditorWidget::onLightDeleted);

    mVBoxLayout->insertWidget(mVBoxLayout->count() - 2, lightWidget);
    mLights.insert(lightWidget->name(), lightWidget);
}

void EditorWidget::onLightRenamed(const QString &oldName, const QString &newName)
{
    mLights.insert(newName, mLights.take(oldName));
}

void EditorWidget::onLightDeleted(const QString &name)
{
    LightWidget *widget = mLights.value(name);
    if (widget) {
        mVBoxLayout->removeWidget(widget);
        widget->deleteLater();
        mLights.remove(name);
    }
}
