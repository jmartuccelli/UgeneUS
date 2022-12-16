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

#ifndef _U2_ROUGHT_TEMP_CALC_WIDGET_
#define _U2_ROUGHT_TEMP_CALC_WIDGET_

#include <QWidget>

//#include <U2Core/BaseTempCalc.h>

#include "ov_sequence/temperature/BaseTempCalcWidget.h"

namespace U2 {

class RoughTempCalcWidget : public BaseTempCalcWidget {
    Q_OBJECT
public:
    RoughTempCalcWidget(QWidget* parent, const QString& id);

    TempCalcSettings* getSettings() const override;

private:
};

}

#endif // TEMPCALCWIDGET_H
