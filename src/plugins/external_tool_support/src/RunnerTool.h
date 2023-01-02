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

#ifndef _U2_RUNNER_TOOL_H_
#define _U2_RUNNER_TOOL_H_

#include <U2Core/ExternalToolRegistry.h>

namespace U2 {

class RunnerTool : public ExternalTool {
    Q_OBJECT
public:
    RunnerTool(const QStringList& runParameters, const QString& id, const QString& dirName, const QString& name, const QString& path = "");

    QStringList getRunParameters() const override;

protected slots:
    void sl_toolValidationStatusChanged(bool isValid);

private:
    QStringList runParameters;
};

}  // namespace U2
#endif