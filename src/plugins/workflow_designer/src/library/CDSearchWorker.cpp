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

#include "CDSearchWorker.h"

#include <U2Algorithm/CDSearchTaskFactoryRegistry.h>

#include <U2Core/AppContext.h>
#include <U2Core/DNAAlphabet.h>
#include <U2Core/DNASequence.h>
#include <U2Core/FailTask.h>
#include <U2Core/TaskSignalMapper.h>
#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/U2SafePoints.h>

#include <U2Designer/DelegateEditors.h>

#include <U2Lang/ActorPrototypeRegistry.h>
#include <U2Lang/BaseActorCategories.h>
#include <U2Lang/BasePorts.h>
#include <U2Lang/BaseSlots.h>
#include <U2Lang/BaseTypes.h>
#include <U2Lang/WorkflowEnv.h>

namespace U2 {
namespace LocalWorkflow {

const QString CDSearchWorkerFactory::ACTOR_ID("cd-search");

static const QString DATABASE_ATTR("db-name");
static const QString EVALUE_ATTR("e-val");
static const QString ANNOTATION_ATTR("result-name");
static const QString LOCAL_ATTR("local-search");
static const QString DB_PATH_ATTR("db-path");

void CDSearchWorkerFactory::init() {
    QList<PortDescriptor*> p;
    Descriptor ind(BasePorts::IN_SEQ_PORT_ID(), CDSearchWorker::tr("Input sequence"), CDSearchWorker::tr("The sequence to search the annotations for"));
    Descriptor outd(BasePorts::OUT_ANNOTATIONS_PORT_ID(), CDSearchWorker::tr("Annotations"), CDSearchWorker::tr("Found annotations"));

    QMap<Descriptor, DataTypePtr> inM;
    inM[BaseSlots::DNA_SEQUENCE_SLOT()] = BaseTypes::DNA_SEQUENCE_TYPE();
    p << new PortDescriptor(ind, DataTypePtr(new MapDataType("cds.sequence", inM)), true);
    QMap<Descriptor, DataTypePtr> outM;
    outM[BaseSlots::ANNOTATION_TABLE_SLOT()] = BaseTypes::ANNOTATION_TABLE_TYPE();
    p << new PortDescriptor(outd, DataTypePtr(new MapDataType("cds.annotations", outM)), false, true);

    QList<Attribute*> a;
    {
        Descriptor dd(DATABASE_ATTR, CDSearchWorker::tr("Database"), CDSearchWorker::tr("Currently, CD Search is offered with the following search databases:<br><ul><li><b>CDD</b> - this is a superset including <a href=\"http://www.ncbi.nlm.nih.gov/Structure/cdd/cdd_help.shtml#CDSource_NCBI_curated\">NCBI-curated domains</a> and <a href=\"http://www.ncbi.nlm.nih.gov/Structure/cdd/cdd_help.shtml#CDSource_external\">data imported</a> from Pfam, SMART, COG, PRK, and TIGRFAM.</li><li><b>Pfam</b> - a mirror of a recent Pfam-A database of curated seed alignments. Pfam version numbers do change with incremental updates. As with SMART, families describing very short motifs or peptides may be missing from the  mirror. An HMM-based search engine is offered on the <a href=\"http://pfam.sanger.ac.uk/\">Pfam</a> site.</li><li><b>SMART</b> - a mirror of a recent SMART set of domain alignments. Note that some SMART families may be missing from the mirror due to update delays or because they describe very short conserved peptides and/or motifs, which would be difficult to detect using the CD-Search service. You may want to try the HMM-based search service offered on the <a href=\"http://smart.embl-heidelberg.de\">SMART</a> site. Note also that some SMART domains are not mirrored in CD because they represent \"superfamilies\" encompassing several individual, but related, domains; the corresponding seed alignments may not be available from the source database in these cases. Note also that SMART version numbers do not change with incremental updates of the source database (and the mirrored CD-Search database).</li> <li><b>TIGRFAM</b> - a mirror of a recent TIGRFAM set of domain alignments. An HMM-based search engine is offered on the <a href=\"http://www.jcvi.org/cms/research/projects/tigrfams/overview/\"><!-- a href=\"http://blast.jcvi.org/web-hmm/\" -->TIGRFAM</a> site.</li><li><b>COG</b> - a mirror of the current COG database of orthologous protein families focusing on prokaryotes. Seed alignments have been generated by an automated process. An alternative search engine, \"Cognitor\", which runs protein-BLAST against a database of COG-assigned sequences, is offered on the <a href=\"http://www.ncbi.nlm.nih.gov/COG\">COG</a> site.</li><li><b>KOG</b> - a eukaryotic counterpart to the COG database.  KOGs are not included in the CDD superset, but are searchable as a separate data set.</li></ul><br>More information about each database is provided in the section on <a href=\"http://www.ncbi.nlm.nih.gov/Structure/cdd/cdd_help.shtml#CDSource\">Where does CDD content come from?</a>."));
        Descriptor nd(ANNOTATION_ATTR, CDSearchWorker::tr("Annotate as"), CDSearchWorker::tr("Name of the result annotations marking found conserved domains."));
        Descriptor ld(LOCAL_ATTR, CDSearchWorker::tr("Local search"), CDSearchWorker::tr("Perform the search on local machine or submit the search to NCBI for remote execution."));
        Descriptor ed(EVALUE_ATTR, CDSearchWorker::tr("Expect value"), CDSearchWorker::tr("Modifies the <a href=\"http://www.ncbi.nlm.nih.gov/BLAST/blastcgihelp.shtml#expect\">E-value</a> threshold used for filtering results. False positive results should be very rare with the default setting of 0.01 (use a more conservative, i.e. lower setting for more reliable results), results with E-values in the range of 1 and above should be considered putative false positives."));
        Descriptor pd(DB_PATH_ATTR, CDSearchWorker::tr("Database folder"), CDSearchWorker::tr("Specifies database folder for local search."));

        a << new Attribute(nd, BaseTypes::STRING_TYPE(), true, "CDD result");
        a << new Attribute(dd, BaseTypes::STRING_TYPE(), false, CDDNames::CDD_DB());
        a << new Attribute(pd, BaseTypes::STRING_TYPE(), false);
        a << new Attribute(ld, BaseTypes::BOOL_TYPE(), false, true);
        a << new Attribute(ed, BaseTypes::NUM_TYPE(), false, 0.01);
    }

    Descriptor desc(ACTOR_ID, CDSearchWorker::tr("CD Search"), CDSearchWorker::tr("Finds conserved domains in protein sequences. In case conserved domains database is downloaded the search can be executed on local machine. The search also can be submitted to the NCBI for remote execution."));
    ActorPrototype* proto = new IntegralBusActorPrototype(desc, p, a);
    QMap<QString, PropertyDelegate*> delegates;

    {
        QVariantMap m;
        m[CDDNames::CDD_DB()] = CDDNames::CDD_DB();
        m[CDDNames::PFAM_DB()] = CDDNames::PFAM_DB();
        m[CDDNames::SMART_DB()] = CDDNames::SMART_DB();
        m[CDDNames::COG_DB()] = CDDNames::COG_DB();
        m[CDDNames::KOG_DB()] = CDDNames::KOG_DB();
        m[CDDNames::PRK_DB()] = CDDNames::PRK_DB();
        m[CDDNames::TIGR_DB()] = CDDNames::TIGR_DB();
        delegates[DATABASE_ATTR] = new ComboBoxDelegate(m);
    }

    {
        QVariantMap m;
        m["1e-100"] = 1e-100;
        m["1e-10"] = 1e-10;
        m["1"] = 1;
        m["10"] = 10;
        m["100"] = 100;
        m["1000"] = 1000;
        delegates[EVALUE_ATTR] = new ComboBoxDelegate(m);
    }

    {
        delegates[DB_PATH_ATTR] = new URLDelegate("", "Database Folder", false, true, false);
    }

    proto->setPrompter(new CDSearchPrompter());
    proto->setEditor(new DelegateEditor(delegates));
    WorkflowEnv::getProtoRegistry()->registerProto(BaseActorCategories::CATEGORY_BASIC(), proto);

    DomainFactory* localDomain = WorkflowEnv::getDomainRegistry()->getById(LocalDomainFactory::ID);
    localDomain->registerEntry(new CDSearchWorkerFactory());
}

QString CDSearchPrompter::composeRichDoc() {
    IntegralBusPort* input = qobject_cast<IntegralBusPort*>(target->getPort(BasePorts::IN_SEQ_PORT_ID()));
    Actor* producer = input->getProducer(BaseSlots::DNA_SEQUENCE_SLOT().getId());
    QString unsetStr = "<font color='red'>" + tr("unset") + "</font>";
    QString producerName = tr(" from <u>%1</u>").arg(producer ? producer->getLabel() : unsetStr);

    QString dbStr = target->getParameter(DATABASE_ATTR)->getAttributeValueWithoutScript<QString>();

    QString doc = tr("For sequence %1 find conserved domains in database <u>%2</u>.")
                      .arg(producerName)
                      .arg(getHyperlink(DATABASE_ATTR, dbStr));
    return doc;
}

void CDSearchWorker::init() {
    input = ports.value(BasePorts::IN_SEQ_PORT_ID());
    output = ports.value(BasePorts::OUT_ANNOTATIONS_PORT_ID());
}

Task* CDSearchWorker::tick() {
    if (input->hasMessage()) {
        Message inputMessage = getMessageAndSetupScriptValues(input);
        if (inputMessage.isEmpty()) {
            output->transit();
            return nullptr;
        }
        SharedDbiDataHandler seqId = inputMessage.getData().toMap().value(BaseSlots::DNA_SEQUENCE_SLOT().getId()).value<SharedDbiDataHandler>();
        QScopedPointer<U2SequenceObject> seqObj(StorageUtils::getSequenceObject(context->getDataStorage(), seqId));
        if (seqObj.isNull()) {
            return nullptr;
        }
        U2OpStatusImpl os;
        DNASequence seq = seqObj->getWholeSequence(os);
        CHECK_OP(os, new FailTask(os.getError()));

        settings.query = seq.seq;
        settings.alp = seq.alphabet;
        if (!settings.alp->isAmino()) {
            QString err = "Required amino acid input sequence";
            return new FailTask(err);
        }
        settings.ev = actor->getParameter(EVALUE_ATTR)->getAttributeValue<float>(context);

        settings.dbName = actor->getParameter(DATABASE_ATTR)->getAttributeValue<QString>(context);

        bool local = actor->getParameter(LOCAL_ATTR)->getAttributePureValue().toBool();
        CDSearchFactory* factory = nullptr;
        if (local) {
            factory = AppContext::getCDSFactoryRegistry()->getFactory(CDSearchFactoryRegistry::LocalSearch);
            if (!factory) {
                QString err = tr("'External tools' plugin has to be loaded.");
                return new FailTask(err);
            }
            settings.localDbFolder = actor->getParameter(DB_PATH_ATTR)->getAttributeValue<QString>(context);
        } else {  // remote
            factory = AppContext::getCDSFactoryRegistry()->getFactory(CDSearchFactoryRegistry::RemoteSearch);
            if (!factory) {
                QString err = tr("'Remote blast' plugin has to be loaded.");
                return new FailTask(err);
            }
        }
        cds = factory->createCDSearch(settings);
        Task* t = cds->getTask();
        connect(new TaskSignalMapper(t), SIGNAL(si_taskFinished(Task*)), SLOT(sl_taskFinished(Task*)));
        return t;
    } else if (input->isEnded()) {
        setDone();
        output->setEnded();
    }
    return nullptr;
}

void CDSearchWorker::sl_taskFinished(Task* t) {
    SAFE_POINT(nullptr != t, "Invalid task is encountered", );
    if (t->isCanceled()) {
        return;
    }
    if (nullptr != output) {
        QList<SharedAnnotationData> res = cds->getCDSResults();
        QString annName = actor->getParameter(ANNOTATION_ATTR)->getAttributeValue<QString>(context);
        if (!annName.isEmpty()) {
            for (int i = 0; i < res.count(); i++) {
                res[i]->name = annName;
            }
        }
        const SharedDbiDataHandler tableId = context->getDataStorage()->putAnnotationTable(res);
        output->put(Message(BaseTypes::ANNOTATION_TABLE_TYPE(), qVariantFromValue<SharedDbiDataHandler>(tableId)));
    }
    delete cds;
    cds = nullptr;
}

}  // namespace LocalWorkflow
}  // namespace U2
