/**
* UGENE - Integrated Bioinformatics Tools.
* Copyright (C) 2008-2013 UniPro <ugene@unipro.ru>
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

#ifndef _U2_DATASET_WIDGET_H_
#define _U2_DATASET_WIDGET_H_

#include <U2Core/U2OpStatus.h>

#include "UrlItem.h"

#include "ui_DatasetWidget.h"

class QVBoxLayout;

namespace U2 {

class OptionsPopup;

class DatasetWidget : public QWidget, public Ui::DatasetWidget {
    Q_OBJECT
public:
    DatasetWidget(QWidget *parent = NULL);

    void addUrlItem(UrlItem *urlItem);
    void deleteDataset();
    void renameDataset(const QString &current);

signals:
    void si_datasetDeleted();
    void si_addUrl(const QString &url, U2OpStatus &os);
    void si_replaceUrl(UrlItem *item, int newUrlPos);
    void si_renameDataset(const QString &newName, U2OpStatus &os);
    void si_datasetRenamed(const QString &newName);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void sl_addFileButton();
    void sl_addDirButton();
    void sl_downButton();
    void sl_upButton();
    void sl_deleteButton();
    void sl_itemChecked();
    void sl_selectAll();

private:
    void addUrl(const QString &url);
    void reset();

private:
    OptionsPopup *popup;
};

class OptionsPopup : public QFrame {
public:
    OptionsPopup(QWidget *parent);

    void showOptions(QWidget *options, const QPoint &pos);
    void hideOptions();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void removeOptions();

private:
    QVBoxLayout *l;
};

} // U2

#endif // _U2_DATASET_WIDGET_H_
