/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2020 UniPro <ugene@unipro.ru>
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

#include <drivers/GTKeyboardDriver.h>
#include <primitives/GTMenu.h>
#include <primitives/PopupChooser.h>

#include "GTTestsRegressionScenarios_7001_8000.h"
#include "GTUtilsMdi.h"
#include "GTUtilsMsaEditor.h"
#include "GTUtilsMsaEditorSequenceArea.h"
#include "GTUtilsTaskTreeView.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/ExtractSelectedAsMSADialogFiller.h"

namespace U2 {

namespace GUITest_regression_scenarios {
using namespace HI;

GUI_TEST_CLASS_DEFINITION(test_7014) {
    // The test checks 'Save subalignment' in the collapse (virtual groups) mode.
    GTFileDialog::openFile(os, testDir + "_common_data/nexus", "DQB1_exon4.nexus");
    GTUtilsMsaEditor::checkMsaEditorWindowIsActive(os);

    // Enable collapsing.
    GTUtilsMsaEditor::toggleCollapsingMode(os);

    // Expand collapsed group.
    GTUtilsMsaEditor::toggleCollapsingGroup(os, "LR882519 exotic DQB1");

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(1, 1), QPoint(5, 4));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Save subalignment", GTGlobals::UseMouse));
    auto saveSubalignmentDialogFiller = new ExtractSelectedAsMSADialogFiller(os, sandBoxDir + "test_7014.aln");
    saveSubalignmentDialogFiller->setUseDefaultSequenceSelection(true);
    GTUtilsDialog::waitForDialog(os, saveSubalignmentDialogFiller);
    GTMenu::showContextMenu(os, GTUtilsMsaEditor::getSequenceArea(os));
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsMdi::closeWindow(os, "DQB1_exon4 [DQB1_exon4.nexus]");
    GTUtilsMsaEditor::checkMsaEditorWindowIsActive(os);

    // Expected state: the saved sub-alignment is opened. Check the content.
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    QStringList expectedNameList = QStringList() << "LR882519 exotic DQB1"
                                                 << "LR882531 local DQB1"
                                                 << "LR882507 local DQB1"
                                                 << "LR882509 local DQB1";
    CHECK_SET_ERR(nameList == expectedNameList, "Unexpected name list in the exported alignment: " + nameList.join(","));

    int msaLength = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(msaLength == 5, "Unexpected exported alignment length: " + QString::number(msaLength));
}

GUI_TEST_CLASS_DEFINITION(test_7044) {
    // The test checks 'Save subalignment' in the collapse (virtual groups) mode after reordering.
    GTFileDialog::openFile(os, testDir + "_common_data/nexus", "DQB1_exon4.nexus");
    GTUtilsMsaEditor::checkMsaEditorWindowIsActive(os);

    // Enable collapsing.
    GTUtilsMsaEditor::toggleCollapsingMode(os);

    // Rename the last two sequences in 'seqA' and 'seqB'.
    GTUtilsMSAEditorSequenceArea::renameSequence(os, "LR882509 local DQB1", "seqA");
    GTUtilsMSAEditorSequenceArea::renameSequence(os, "LR882503 local DQB1", "seqB");

    // Copy seqA.
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "seqA");
    GTKeyboardDriver::keyClick('c', Qt::ControlModifier);

    // Select first collapsed mode and 'Paste before'.
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "LR882520 exotic DQB1");
    GTKeyboardDriver::keyPress(Qt::Key_Control);
    GTKeyboardDriver::keyClick('v', Qt::AltModifier);
    GTKeyboardDriver::keyRelease(Qt::Key_Control);

    // Cut seqB.
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "seqB");
    GTKeyboardDriver::keyClick('x', Qt::ControlModifier);

    // Select the first sequence and 'Paste before'
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "seqA_1");
    GTKeyboardDriver::keyPress(Qt::Key_Control);
    GTKeyboardDriver::keyClick('v', Qt::AltModifier);
    GTKeyboardDriver::keyRelease(Qt::Key_Control);

    // Select seqB and seqA_1 (a group of seqA_1 and seqA).
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "seqA_1");
    GTKeyboardDriver::keyPress(Qt::Key_Shift);
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "seqB");
    GTKeyboardDriver::keyRelease(Qt::Key_Shift);

    // Export -> Save subalignment.
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Save subalignment", GTGlobals::UseMouse));
    auto saveSubalignmentDialogFiller = new ExtractSelectedAsMSADialogFiller(os, sandBoxDir + "test_7044.aln");
    saveSubalignmentDialogFiller->setUseDefaultSequenceSelection(true);
    GTUtilsDialog::waitForDialog(os, saveSubalignmentDialogFiller);
    GTMenu::showContextMenu(os, GTUtilsMsaEditor::getSequenceArea(os));
    GTUtilsTaskTreeView::waitTaskFinished(os);

    // Expected state: the saved sub-alignment is opened. Check the content.
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    QStringList expectedNameList = QStringList() << "seqB"
                                                 << "seqA_1"
                                                 << "seqA";
    CHECK_SET_ERR(nameList == expectedNameList, "Unexpected name list in the exported alignment: " + nameList.join(","));
}

GUI_TEST_CLASS_DEFINITION(test_7045) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa", "COI_subalign.aln");
    GTUtilsMsaEditor::checkMsaEditorWindowIsActive(os);

    // Select 's1'.
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "s1");

    // Copy (CTRL C) and Paste (CTRL V) -> new 's1_1' sequence appears.
    GTKeyboardDriver::keyClick('c', Qt::ControlModifier);
    GTKeyboardDriver::keyClick('v', Qt::ControlModifier);

    // Switch collapsing mode on -> 2 collapsed groups: 's1' and' Mecopoda_elongata_Ishigaki_J' are on the screen.
    GTUtilsMsaEditor::toggleCollapsingMode(os);

    // Select 's1'.
    GTUtilsMSAEditorSequenceArea::selectSequence(os, "s1");

    // Call Export -> Save subalignment context menu.
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Save subalignment", GTGlobals::UseMouse));
    auto saveSubalignmentDialogFiller = new ExtractSelectedAsMSADialogFiller(os, sandBoxDir + "test_7044.aln");
    saveSubalignmentDialogFiller->setUseDefaultSequenceSelection(true);
    GTUtilsDialog::waitForDialog(os, saveSubalignmentDialogFiller);
    GTMenu::showContextMenu(os, GTUtilsMsaEditor::getSequenceArea(os));
    GTUtilsTaskTreeView::waitTaskFinished(os);

    // Expected state : new alignment where s1, s1_1 and s2 are present.
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    QStringList expectedNameList = QStringList() << "s1"
                                                 << "s1_1"
                                                 << "s2";
    CHECK_SET_ERR(nameList == expectedNameList, "Unexpected name list in the exported alignment: " + nameList.join(","));
}

}    // namespace GUITest_regression_scenarios

}    // namespace U2
