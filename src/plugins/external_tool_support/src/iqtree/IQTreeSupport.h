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

#ifndef _U2_IQTREE_SUPPORT_H_
#define _U2_IQTREE_SUPPORT_H_

#include <U2Algorithm/PhyTreeGenerator.h>

#include <U2Core/ExternalToolRegistry.h>

namespace U2 {

class IQTreeSupport : public ExternalTool {
    Q_OBJECT
public:
    IQTreeSupport();

    static const QString IQTREE_ID;
    static const QString ET_IQTREE_ALGORITHM_NAME_AND_KEY;
};

class IQTreeAdapter : public PhyTreeGenerator {
public:
    Task *createCalculatePhyTreeTask(const MultipleSequenceAlignment &msa, const CreatePhyTreeSettings &settings) override;

    CreatePhyTreeWidget *createPhyTreeSettingsWidget(const MultipleSequenceAlignment &msa, QWidget *parent = nullptr) override;
};

}  // namespace U2
#endif  // _U2_IQTREE_SUPPORT_H_