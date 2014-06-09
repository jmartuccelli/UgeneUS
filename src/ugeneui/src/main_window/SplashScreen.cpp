/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "SplashScreen.h"

#include <QtGui/QMovie>
#include <QtGui/QLayout>
#include <QtGui/QLabel>

namespace U2{

SplashScreen::SplashScreen( QWidget *parent /*= NULL*/ ):QDialog(parent) {
    setEnabled(false);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#ifdef Q_OS_WIN
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
#endif
    setWindowModality(Qt::ApplicationModal);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    QFrame *frame = new QFrame(this);
    mainLayout->addWidget(frame);

    QHBoxLayout* frameLayout = new QHBoxLayout();
    frameLayout->setMargin(0);
    frame->setContentsMargins(0, 0, 0, 0);
    frame->setLayout(frameLayout);

    QMovie *movie = new QMovie(":ugene/images/ugene_splash.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();

    QVBoxLayout* aWLayout = (QVBoxLayout*)frame->layout();
    aWLayout->insertWidget(0, processLabel);
}

}
