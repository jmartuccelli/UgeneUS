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

#ifndef _U2_BASE_TEMP_CALC_
#define _U2_BASE_TEMP_CALC_

#include <QString>
#include <QMap>
#include <QVariant>

#include <U2Core/global.h>

namespace U2 {

struct U2ALGORITHM_EXPORT TempCalcSettings {
    virtual QMap<QString, QVariant> toVariantMap() const;
    virtual void fromVariantMap(const QMap<QString, QVariant>& mapSettings);

    QString id;

    static const QString KEY_ID;
};

class U2ALGORITHM_EXPORT BaseTempCalc {
public:
    BaseTempCalc(TempCalcSettings* settings);
    ~BaseTempCalc();

    virtual double getMeltingTemperature(const QByteArray& sequence) = 0;
    double getAnnealingTemperature(const QByteArray& product, const QByteArray& forwardPrimer, const QByteArray& reversePrimer);
    TempCalcSettings* getSettings() const;

protected:
    TempCalcSettings* settings = nullptr;
    static constexpr double INVALID_TM = -1.0;

private:
    static bool isNucleotideSequence(const QByteArray& sequence);
    double getMeltingTemperature(const QByteArray& initialPrimer, const QByteArray& alternativePrimer);

};

}

#endif