/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2018 UniPro <ugene@unipro.ru>
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

#ifndef _U2_URL_AND_DATASET_WIZARD_CONTROLLER_H_
#define _U2_URL_AND_DATASET_WIZARD_CONTROLLER_H_

#include <U2Designer/DatasetsController.h>

#include <U2Lang/WizardWidget.h>

#include "WidgetController.h"

namespace U2 {

class UrlAndDatasetWizardController : public WidgetController {
    Q_OBJECT
public:
    UrlAndDatasetWizardController(WizardController *wc, UrlAndDatasetWidget *widget);
    virtual ~UrlAndDatasetWizardController();

    virtual QWidget * createGUI(U2OpStatus &os);

private slots:
    void sl_datasetsChanged();

private:
    UrlAndDatasetWidget *widget;
    UrlAndDatasetController *dsc;
};

} // U2

#endif // _U2_URL_AND_DATASET_WIZARD_CONTROLLER_H_
