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

#ifndef _U2_TEMP_CALC_DELEGATE_H_
#define _U2_TEMP_CALC_DELEGATE_H_

#include <U2Lang/ConfigurationEditor.h>

#include <QToolButton>

namespace U2 {

class TempCalcDelegate : public PropertyDelegate {
    Q_OBJECT
public:
    TempCalcDelegate(QObject* parent = nullptr);

    QVariant getDisplayValue(const QVariant& value) const override;
    PropertyDelegate* clone() override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    PropertyWidget* createWizardWidget(U2OpStatus& os, QWidget* parent) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private slots:
    void sl_commit();

};

}

#endif
