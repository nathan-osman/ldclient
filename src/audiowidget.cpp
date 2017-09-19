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

#include <QFileInfo>
#include <QLabel>
#include <QMediaPlayer>
#include <QSlider>
#include <QVBoxLayout>

#include "audiowidget.h"

AudioWidget::AudioWidget()
    : mPlayer(new QMediaPlayer(this)),
      mLabel(new QLabel),
      mSlider(new QSlider)
{
    mLabel->setText(tr("No audio file loaded"));

    mSlider->setEnabled(false);
    mSlider->setOrientation(Qt::Horizontal);

    connect(mPlayer, &QMediaPlayer::durationChanged, this, &AudioWidget::onDurationChanged);
    connect(mPlayer, &QMediaPlayer::positionChanged, this, &AudioWidget::onPositionChanged);

    QVBoxLayout * vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(mLabel);
    vboxLayout->addWidget(mSlider);
    setLayout(vboxLayout);
}

void AudioWidget::loadFile(const QString &filename)
{
    mPlayer->setMedia(QUrl::fromLocalFile(filename));
    mLabel->setText(QFileInfo(filename).baseName());
}

void AudioWidget::start()
{
    mPlayer->play();
}

void AudioWidget::stop()
{
    mPlayer->stop();
    mPlayer->setPosition(0);
}

void AudioWidget::onDurationChanged(qint64 duration)
{
    mSlider->setMaximum(duration);
}

void AudioWidget::onPositionChanged(qint64 position)
{
    mSlider->setValue(position);
}
