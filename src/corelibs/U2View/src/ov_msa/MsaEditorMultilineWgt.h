/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2021 UniPro <ugene@unipro.ru>
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

#ifndef _U2_MSA_EDITOR_MULTILINE_WGT_H_
#define _U2_MSA_EDITOR_MULTILINE_WGT_H_

#include "view_rendering/MaEditorMultilineWgt.h"

namespace U2 {

class GObjectViewWindow;
class MSADistanceMatrix;
class MSAEditor;
class MsaEditorAlignmentDependentWidget;
class MSAEditorMultiTreeViewer;
class MSAEditorMultilineOverviewArea;
class MsaEditorStatusBar;
class MsaEditorSimilarityColumn;
class MSAEditorTreeViewer;
class SimilarityStatisticsSettings;

class U2VIEW_EXPORT MsaEditorMultilineWgt : public MaEditorMultilineWgt {
    Q_OBJECT

public:
    MsaEditorMultilineWgt(MSAEditor *editor);

    MSAEditor *getEditor() const;
    MaEditorMultilineOverviewArea *getOverview();
    MaEditorStatusBar *getStatusBar();

private slots:

protected:
    void initOverviewArea(MaEditorMultilineOverviewArea *overviewArea = nullptr);
    void initStatusBar(MaEditorStatusBar *_statusBar = nullptr);
    void initChildrenArea();

private:

};

}  // namespace U2

#endif  // _U2_MSA_EDITOR_MULTILINE_WGT_H_
