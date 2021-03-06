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

#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

class QLabel;

class LEDWidget;

/**
 * @brief LED light that can be renamed
 */
class LightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool lit READ lit WRITE setLit)
    Q_PROPERTY(QString name READ name WRITE setName)

public:

    LightWidget(const QString &name);

    bool lit() const;
    void setLit(bool lit);

    QString name() const;
    void setName(const QString &name);

Q_SIGNALS:

    void renamed(const QString &oldName, const QString &newName);
    void deleted(const QString &name);

private Q_SLOTS:

    void onRenameClicked();
    void onDeleteClicked();

private:

    QString mName;

    LEDWidget *mLEDWidget;
    QLabel *mLabel;
};

#endif // LIGHTWIDGET_H
