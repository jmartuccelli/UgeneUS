/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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
 
#ifndef _U2_GUI_MAFFT_SUPPORT_RUN_DIALOG_FILLER_H_
#define _U2_GUI_MAFFT_SUPPORT_RUN_DIALOG_FILLER_H_
 
#include <base_dialogs/GTFileDialog.h>
#include <utils/GTUtilsDialog.h>

namespace U2 {
using namespace HI;

class MAFFTSupportRunDialogFiller : public Filler {
public:
    class Parameters {
    public:
        Parameters();

        bool ckeckBox_gapOpenCheckBox_checked;
        double doubleSpin_gapOpenSpinBox_value;
        bool ckeckBox_gapExtCheckBox_checked;
        double doubleSpin_gapExtSpinBox_value;
        bool ckeckBox_maxNumberIterRefinementCheckBox_checked;
        int spin_maxNumberIterRefinementSpinBox_value;
    };

    MAFFTSupportRunDialogFiller(GUITestOpStatus &os, Parameters* parameters);
    MAFFTSupportRunDialogFiller(GUITestOpStatus &os, CustomScenario *scenario);

    void commonScenario();

private:

    Parameters* parameters;

};

}   // namespace U2

#endif // _U2_GUI_MAFFT_SUPPORT_RUN_DIALOG_FILLER_H_
