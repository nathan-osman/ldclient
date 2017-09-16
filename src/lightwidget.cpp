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

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRadialGradient>

#include "lightwidget.h"

LightWidget::LightWidget(QWidget *parent)
    : QWidget(parent),
      mLit(false)
{
}

bool LightWidget::lit() const
{
    return mLit;
}

void LightWidget::setLit(bool lit)
{
    mLit = lit;
    repaint();
}

void LightWidget::paintEvent(QPaintEvent *)
{
    QPoint p(width() / 2, height() / 2);
    int circleRad = qMin(p.x(), p.y()) - 4;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRadialGradient gradient(p.x(), p.y(), circleRad * 2, p.x(), p.y());
    gradient.setColorAt(0, mLit ?
        QColor::fromRgbF(1, 0.25, 0.25) :
        QColor::fromRgbF(0.3, 0.3, 0.3)
    );
    gradient.setColorAt(1, Qt::black);

    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(p, circleRad, circleRad);
}
