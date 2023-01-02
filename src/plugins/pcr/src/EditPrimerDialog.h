/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2023 UniPro <ugene@unipro.ru>
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

#ifndef _U2_EDIT_PRIMER_DIALOG_H_
#define _U2_EDIT_PRIMER_DIALOG_H_

#include <QDialog>

#include <U2Core/Primer.h>

#include "ui_EditPrimerDialog.h"

namespace U2 {

class EditPrimerDialog : public QDialog, private Ui_EditPrimerDialog {
    Q_OBJECT
public:
    EditPrimerDialog(QWidget* parent);
    EditPrimerDialog(QWidget* parent, const Primer& editPrimer);

    Primer getPrimer() const;

private slots:
    void sl_onPrimerChanged(const QString& primerSequence);
    void sl_validate();

private:
    void init();
    void validate(bool isValid);
};

}  // namespace U2

#endif  // _U2_EDIT_PRIMER_DIALOG_H_
