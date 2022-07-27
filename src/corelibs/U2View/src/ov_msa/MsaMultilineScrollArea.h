#ifndef MSAMULTILINESCROLLAREA_H
#define MSAMULTILINESCROLLAREA_H

#include <U2Core/global.h>

#include <QScrollArea>

#include "MsaEditorMultilineWgt.h"
#include "MultilineScrollController.h"

namespace U2 {

class GScrollBar;

class U2VIEW_EXPORT MsaMultilineScrollArea : public QScrollArea {
    Q_OBJECT

public:
    MsaMultilineScrollArea(MaEditor *maEditor, MaEditorMultilineWgt *ui);
    void scrollVert(const MultilineScrollController::Directions &directions, bool byStep, bool selectionChange = false);
    bool eventFilter(QObject *obj, QEvent *event) override;

protected:
    void wheelEvent(QWheelEvent *we) override;

private:
    MaEditor *maEditor;
    MaEditorMultilineWgt *maEditorUi;
};

}  // namespace U2

#endif // MSAMULTILINESCROLLAREA_H
