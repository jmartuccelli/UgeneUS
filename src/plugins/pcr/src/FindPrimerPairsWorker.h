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

#pragma once

#include <U2Core/DNASequence.h>
#include <U2Core/MultipleSequenceAlignment.h>
#include <U2Core/PrimerStatistics.h>

#include <U2Lang/LocalDomain.h>
#include <U2Lang/WorkflowUtils.h>

namespace U2 {

class BaseTempCalc;

namespace LocalWorkflow {

class FindPrimerPairsPromter : public PrompterBase<FindPrimerPairsPromter> {
    Q_OBJECT
public:
    FindPrimerPairsPromter(Actor* p = 0)
        : PrompterBase<FindPrimerPairsPromter>(p) {};

protected:
    QString composeRichDoc();
};

class FindPrimerPairsWorker : public BaseWorker {
    Q_OBJECT
public:
    FindPrimerPairsWorker(Actor* p)
        : BaseWorker(p), inPort(nullptr), outPort(nullptr) {};

    virtual void init();
    virtual Task* tick();
    virtual void cleanup();

private:
    IntegralBus* inPort;
    IntegralBus* outPort;
private slots:
    void sl_onTaskFinished(Task* t);

private:
    QList<DNASequence> data;
};

class FindPrimerPairsWorkerFactory : public DomainFactory {
public:
    const static QString ACTOR_ID;
    const static QString OUT_FILE;
    const static QString TEMPERATURE_SETTINGS_ID;

    FindPrimerPairsWorkerFactory()
        : DomainFactory(ACTOR_ID) {};
    static void init();
    virtual Worker* createWorker(Actor* a) {
        return new FindPrimerPairsWorker(a);
    }
};

}  // namespace LocalWorkflow

class FindPrimersTask : public Task {
    Q_OBJECT
public:
    FindPrimersTask(const QString& outputFileUrl, const QList<DNASequence>& sequences, BaseTempCalc* temperatureCalculator);
    ~FindPrimersTask();

    void run();
    QString getReport() const {
        return report;
    }

private:
    void createReport();
    void writeReportToFile();

    QString createRow(const QString& forwardName, const QString& reverseName, double forwardTm, double reverseTm);
    QString createCell(const QString& value);
    QString createColumn(const QString& name);

private:
    QList<DNASequence> sequences;
    BaseTempCalc* temperatureCalculator = nullptr;
    QString report;
    QString outputUrl;
    QStringList rows;
};

}  // namespace U2
