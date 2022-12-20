/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2022 UniPro <ugene@unipro.ru>
 * http://ugene.net
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

#include "TempCalcDialog.h"
#include "TempCalcWidget.h"


#include <QDialogButtonBox>
#include <QLayout>

namespace U2 {

TempCalcDialog::TempCalcDialog(QWidget* parent, TempCalcSettings* currentSettings)
    : QDialog(parent) {
    setWindowTitle(tr("Melting temperature"));
    setLayout(new QVBoxLayout);
    tempCalcWidget = new TempCalcWidget(this);
    tempCalcWidget->init(currentSettings);
    layout()->addWidget(tempCalcWidget);
    auto dbb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    connect(dbb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(dbb, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout()->addWidget(dbb);
}

TempCalcSettings* TempCalcDialog::getSettings() const {
    return tempCalcWidget->getSettings();
}

}