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

#ifndef _U2_DIAMOND_CLASSIFY_PROMPTER_H_
#define _U2_DIAMOND_CLASSIFY_PROMPTER_H_

#include <U2Lang/WorkflowUtils.h>

namespace U2 {
namespace LocalWorkflow {

class DiamondClassifyPrompter : public PrompterBase<DiamondClassifyPrompter> {
    Q_OBJECT
public:
    DiamondClassifyPrompter(Actor *actor);

private:
    QString composeRichDoc();
};

}  // namespace LocalWorkflow
}  // namespace U2

#endif  // _U2_DIAMOND_CLASSIFY_PROMPTER_H_
