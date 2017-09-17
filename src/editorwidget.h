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

#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QMap>
#include <QWidget>

class QVBoxLayout;

class LightWidget;

/**
 * @brief Editor for adding and removing named lights
 */
class EditorWidget : public QWidget
{
    Q_OBJECT

public:

    EditorWidget();

public Q_SLOTS:

    void setState(const QString &name, bool state);

private Q_SLOTS:

    void onAddLight();
    void onLightRenamed(const QString &oldName, const QString &newName);
    void onLightDeleted(const QString &name);

private:

    QVBoxLayout *mVBoxLayout;

    int mLightNumber;
    QMap<QString, LightWidget*> mLights;
};

#endif // EDITORWIDGET_H
