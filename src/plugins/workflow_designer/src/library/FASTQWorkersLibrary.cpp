/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
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

#include <U2Core/AppContext.h>
#include <U2Core/IOAdapter.h>
#include <U2Core/IOAdapterUtils.h>
#include <U2Core/GUrlUtils.h>
#include <U2Core/FileAndDirectoryUtils.h>
#include <U2Formats/BAMUtils.h>
#include <U2Formats/FastqFormat.h>
#include <U2Designer/DelegateEditors.h>
#include <U2Lang/ActorPrototypeRegistry.h>
#include <U2Lang/BaseActorCategories.h>
#include <U2Lang/IntegralBusModel.h>
#include <U2Lang/WorkflowEnv.h>
#include <U2Lang/WorkflowMonitor.h>
#include <U2Lang/BaseAttributes.h>
#include <U2Lang/BaseTypes.h>
#include <U2Lang/BaseSlots.h>

#include "FASTQWorkersLibrary.h"

namespace U2 {
namespace LocalWorkflow {

///////////////////////////////////////////////////////////////
//CASAVAFilter
const QString CASAVAFilterWorkerFactory::ACTOR_ID("CASAVAFilter");

/************************************************************************/
/* CASAVAFilterPrompter */
/************************************************************************/
QString CASAVAFilterPrompter::composeRichDoc() {
    IntegralBusPort* input = qobject_cast<IntegralBusPort*>(target->getPort(BaseNGSWorker::INPUT_PORT));
    const Actor* producer = input->getProducer(BaseSlots::URL_SLOT().getId());
    QString unsetStr = "<font color='red'>"+tr("unset")+"</font>";
    QString producerName = tr(" from <u>%1</u>").arg(producer ? producer->getLabel() : unsetStr);

    QString doc = tr("Filters FASTQ reads from %1 generated by CASAVA 1.8.").arg(producerName);
    return doc;
}

/************************************************************************/
/* CASAVAFilterWorkerFactory */
/************************************************************************/
void CASAVAFilterWorkerFactory::init() {
    Descriptor desc( ACTOR_ID, CASAVAFilterWorker::tr("CASAVA FASTQ Filter"),
        CASAVAFilterWorker::tr("Reads in FASTQ file produced by CASAVA 1.8 contain 'N' or 'Y' as a part of an idetifier. 'Y' if a read if filtered, 'N' if the read if the read is not filtered. The workflow cleans up the filtered reads.\n"
                           "For example:\n"
                           "@HWI-ST880:181:D1WRUACXX:8:1102:4905:2125 1:N:0:TAAGGG\n"
                           "CTTACATAACTACTGACCATGCTCTCTCTTGTCTGTCTCTTATACACATCT\n"
                           "+\n"
                           "111442222322324232AAFFHIJJJJJJIHIIF111CGGFHIG???FGB\n"
                           "@HWI-ST880:181:D1WRUACXX:8:1102:7303:2101 1:Y:0:TAAGGG\n"
                           "TCCTTACTGTCTGAGCAATGGGATTCCATCTTTTACGATCTAGACATGGCT\n"
                           "+\n"
                           "11++4222322<CEE2<:3<3333333<A<CAFE:1?C??::C?00?BD90.\n") );

    QList<PortDescriptor*> p;
    {
        Descriptor inD(BaseNGSWorker::INPUT_PORT, CASAVAFilterWorker::tr("Input File"),
            CASAVAFilterWorker::tr("Set of FASTQ reads files"));
        Descriptor outD(BaseNGSWorker::OUTPUT_PORT, CASAVAFilterWorker::tr("Output File"),
            CASAVAFilterWorker::tr("Output FASTQ files"));

        QMap<Descriptor, DataTypePtr> inM;
        inM[BaseSlots::URL_SLOT()] = BaseTypes::STRING_TYPE();
        p << new PortDescriptor(inD, DataTypePtr(new MapDataType("cf.input-url", inM)), true);

        QMap<Descriptor, DataTypePtr> outM;
        outM[BaseSlots::URL_SLOT()] = BaseTypes::STRING_TYPE();
        p << new PortDescriptor(outD, DataTypePtr(new MapDataType("cf.output-url", outM)), false, true);
    }

    QList<Attribute*> a;
    {
        Descriptor outDir(BaseNGSWorker::OUT_MODE_ID, CASAVAFilterWorker::tr("Output directory"),
            CASAVAFilterWorker::tr("Select an output directory. <b>Custom</b> - specify the output directory in the 'Custom directory' parameter. "
            "<b>Workflow</b> - internal workflow directory. "
            "<b>Input file</b> - the directory of the input file."));

        Descriptor customDir(BaseNGSWorker::CUSTOM_DIR_ID, CASAVAFilterWorker::tr("Custom directory"),
            CASAVAFilterWorker::tr("Select the custom output directory."));

        Descriptor outName(BaseNGSWorker::OUT_NAME_ID, CASAVAFilterWorker::tr("Output file name"),
            CASAVAFilterWorker::tr("A name of an output file. If default of empty value is provided the output name is the name of the first file with additional extention."));

        a << new Attribute( outDir, BaseTypes::NUM_TYPE(), false, QVariant(FileAndDirectoryUtils::FILE_DIRECTORY));
        Attribute* customDirAttr = new Attribute(customDir, BaseTypes::STRING_TYPE(), false, QVariant(""));
        customDirAttr->addRelation(new VisibilityRelation(BaseNGSWorker::OUT_MODE_ID, CASAVAFilterWorker::tr("Custom")));
        a << customDirAttr;
        a << new Attribute( outName, BaseTypes::STRING_TYPE(), false, QVariant(BaseNGSWorker::DEFAULT_NAME));
    }

    QMap<QString, PropertyDelegate*> delegates;
    {
        QVariantMap directoryMap;
        QString fileDir = CASAVAFilterWorker::tr("Input file");
        QString workflowDir = CASAVAFilterWorker::tr("Workflow");
        QString customD = CASAVAFilterWorker::tr("Custom");
        directoryMap[fileDir] = FileAndDirectoryUtils::FILE_DIRECTORY;
        directoryMap[workflowDir] = FileAndDirectoryUtils::WORKFLOW_INTERNAL;
        directoryMap[customD] = FileAndDirectoryUtils::CUSTOM;
        delegates[BaseNGSWorker::OUT_MODE_ID] = new ComboBoxDelegate(directoryMap);

        delegates[BaseNGSWorker::CUSTOM_DIR_ID] = new URLDelegate("", "", false, true);
    }

    ActorPrototype* proto = new IntegralBusActorPrototype(desc, p, a);
    proto->setEditor(new DelegateEditor(delegates));
    proto->setPrompter(new CASAVAFilterPrompter());

    WorkflowEnv::getProtoRegistry()->registerProto(BaseActorCategories::CATEGORY_NGS_BASIC(), proto);
    DomainFactory *localDomain = WorkflowEnv::getDomainRegistry()->getById(LocalDomainFactory::ID);
    localDomain->registerEntry(new CASAVAFilterWorkerFactory());
}

/************************************************************************/
/* CASAVAFilterWorker */
/************************************************************************/
CASAVAFilterWorker::CASAVAFilterWorker(Actor *a)
:BaseNGSWorker(a)
{

}

QVariantMap CASAVAFilterWorker::getCustomParameters() const{
    QVariantMap res;
    return res;
}

QString CASAVAFilterWorker::getDefaultFileName() const{
    return ".filtered.fastq";
}

Task *CASAVAFilterWorker::getTask(const BaseNGSSetting &settings) const{
    return new CASAVAFilterTask(settings);
}

//////////////////////////////////////////////////////
//CASAVAFilterTask
CASAVAFilterTask::CASAVAFilterTask(const BaseNGSSetting &settings)
    :BaseNGSTask(settings){

}

void CASAVAFilterTask::runStep(){
    int ncount = 0;
    int ycount = 0;

    QScopedPointer<IOAdapter> io  (IOAdapterUtils::open(settings.outDir + settings.outName, stateInfo, IOAdapterMode_Append));

    //1:N:0:TAAGGG
    QRegExp pattern (":Y:[^:]:");
    FASTQIterator iter(settings.inputUrl);
    while(iter.hasNext()){
        if(stateInfo.isCoR()){
            return;
        }
        DNASequence seq = iter.next();
        QString comment = DNAInfo::getFastqComment(seq.info);
        if(pattern.indexIn(comment) != -1){
            ycount++;
        }else{
            FastqFormat::writeEntry(seq.getName() + " " + comment, seq, io.data(), "Writing error", stateInfo);
            ncount++;
        }
    }

    algoLog.info(QString("Discarded by CASAVA filter %1").arg(ycount));
    algoLog.info(QString("Accepted by CASAVA filter %1").arg(ncount));
    algoLog.info(QString("Total by CASAVA FILTER: %1").arg(ncount + ycount));
}

QStringList CASAVAFilterTask::getParameters(U2OpStatus &os){
    QStringList res;
    return res;
}


///////////////////////////////////////////////////////////////
//QualityTrim
const QString QualityTrimWorkerFactory::ACTOR_ID("QualityTrim");

static const QString QUALITY_ID("qual-id");
static const QString LEN_ID("len-id");

/************************************************************************/
/* QualityTrimPrompter */
/************************************************************************/
QString QualityTrimPrompter::composeRichDoc() {
    IntegralBusPort* input = qobject_cast<IntegralBusPort*>(target->getPort(BaseNGSWorker::INPUT_PORT));
    const Actor* producer = input->getProducer(BaseSlots::URL_SLOT().getId());
    QString unsetStr = "<font color='red'>"+tr("unset")+"</font>";
    QString producerName = tr(" from <u>%1</u>").arg(producer ? producer->getLabel() : unsetStr);

    QString doc = tr("Trim input sequence %1 from the end, using the quality threshold.").arg(producerName);
    return doc;
}

/************************************************************************/
/* QualityTrimWorkerFactory */
/************************************************************************/
void QualityTrimWorkerFactory::init() {
    Descriptor desc( ACTOR_ID, QualityTrimWorker::tr("FASTQ Quality Trimmer"),
        QualityTrimWorker::tr("The workflow scans each input sequence from the end to find the first position where the quality is greater or equal to the minimum quality threshold. "
                              "Then it trims the sequence to that position. If a the whole sequence has quality less than the threshold or the length of the output sequence less than "
                              "the minimum length threshold then the sequence is skipped.") );

    QList<PortDescriptor*> p;
    {
        Descriptor inD(BaseNGSWorker::INPUT_PORT, QualityTrimWorker::tr("Input File"),
            QualityTrimWorker::tr("Set of FASTQ reads files"));
        Descriptor outD(BaseNGSWorker::OUTPUT_PORT, QualityTrimWorker::tr("Output File"),
            QualityTrimWorker::tr("Output FASTQ files"));

        QMap<Descriptor, DataTypePtr> inM;
        inM[BaseSlots::URL_SLOT()] = BaseTypes::STRING_TYPE();
        p << new PortDescriptor(inD, DataTypePtr(new MapDataType("cf.input-url", inM)), true);

        QMap<Descriptor, DataTypePtr> outM;
        outM[BaseSlots::URL_SLOT()] = BaseTypes::STRING_TYPE();
        p << new PortDescriptor(outD, DataTypePtr(new MapDataType("cf.output-url", outM)), false, true);
    }

    QList<Attribute*> a;
    {
        Descriptor outDir(BaseNGSWorker::OUT_MODE_ID, QualityTrimWorker::tr("Output directory"),
            QualityTrimWorker::tr("Select an output directory. <b>Custom</b> - specify the output directory in the 'Custom directory' parameter. "
            "<b>Workflow</b> - internal workflow directory. "
            "<b>Input file</b> - the directory of the input file."));

        Descriptor customDir(BaseNGSWorker::CUSTOM_DIR_ID, QualityTrimWorker::tr("Custom directory"),
            QualityTrimWorker::tr("Select the custom output directory."));

        Descriptor outName(BaseNGSWorker::OUT_NAME_ID, QualityTrimWorker::tr("Output file name"),
            QualityTrimWorker::tr("A name of an output file. If default of empty value is provided the output name is the name of the first file with additional extention."));

        Descriptor qualT(QUALITY_ID, QualityTrimWorker::tr("Quality threshold"),
            QualityTrimWorker::tr("Quality threshold for trimming."));

        Descriptor lenT(LEN_ID, QualityTrimWorker::tr("Min Length"),
            QualityTrimWorker::tr("Too short reads are discarded by the filter."));

        a << new Attribute( outDir, BaseTypes::NUM_TYPE(), false, QVariant(FileAndDirectoryUtils::FILE_DIRECTORY));
        Attribute* customDirAttr = new Attribute(customDir, BaseTypes::STRING_TYPE(), false, QVariant(""));
        customDirAttr->addRelation(new VisibilityRelation(BaseNGSWorker::OUT_MODE_ID, QualityTrimWorker::tr("Custom")));
        a << customDirAttr;
        a << new Attribute( outName, BaseTypes::STRING_TYPE(), false, QVariant(BaseNGSWorker::DEFAULT_NAME));
        a << new Attribute( qualT, BaseTypes:: NUM_TYPE(), false, QVariant(30));
        a << new Attribute( lenT, BaseTypes::NUM_TYPE(), false, QVariant(0));
    }

    QMap<QString, PropertyDelegate*> delegates;
    {
        QVariantMap directoryMap;
        QString fileDir = QualityTrimWorker::tr("Input file");
        QString workflowDir = QualityTrimWorker::tr("Workflow");
        QString customD = QualityTrimWorker::tr("Custom");
        directoryMap[fileDir] = FileAndDirectoryUtils::FILE_DIRECTORY;
        directoryMap[workflowDir] = FileAndDirectoryUtils::WORKFLOW_INTERNAL;
        directoryMap[customD] = FileAndDirectoryUtils::CUSTOM;
        delegates[BaseNGSWorker::OUT_MODE_ID] = new ComboBoxDelegate(directoryMap);

        delegates[BaseNGSWorker::CUSTOM_DIR_ID] = new URLDelegate("", "", false, true);

        QVariantMap len; len["minimum"] = 0; len["maximum"] = INT_MAX;
        delegates[QUALITY_ID] = new SpinBoxDelegate(len);
        delegates[LEN_ID] = new SpinBoxDelegate(len);
    }

    ActorPrototype* proto = new IntegralBusActorPrototype(desc, p, a);
    proto->setEditor(new DelegateEditor(delegates));
    proto->setPrompter(new QualityTrimPrompter());

    WorkflowEnv::getProtoRegistry()->registerProto(BaseActorCategories::CATEGORY_NGS_BASIC(), proto);
    DomainFactory *localDomain = WorkflowEnv::getDomainRegistry()->getById(LocalDomainFactory::ID);
    localDomain->registerEntry(new QualityTrimWorkerFactory());
}

/************************************************************************/
/* QualityTrimWorker */
/************************************************************************/
QualityTrimWorker::QualityTrimWorker(Actor *a)
:BaseNGSWorker(a)
{

}

QVariantMap QualityTrimWorker::getCustomParameters() const{
    QVariantMap res;
    res.insert(QUALITY_ID, getValue<int>(QUALITY_ID));
    res.insert(LEN_ID, getValue<int>(LEN_ID));
    return res;
}

QString QualityTrimWorker::getDefaultFileName() const{
    return ".trimmed.fastq";
}

Task *QualityTrimWorker::getTask(const BaseNGSSetting &settings) const{
    return new QualityTrimTask(settings);
}

//////////////////////////////////////////////////////
//QualityTrimTask
QualityTrimTask::QualityTrimTask(const BaseNGSSetting &settings)
    :BaseNGSTask(settings){

}

void QualityTrimTask::runStep(){
    int ncount = 0;
    int ycount = 0;

    QScopedPointer<IOAdapter> io  (IOAdapterUtils::open(settings.outDir + settings.outName, stateInfo, IOAdapterMode_Append));

    int quality = settings.customParameters.value(QUALITY_ID, 20).toInt();
    int minLen = settings.customParameters.value(LEN_ID, 0).toInt();

    FASTQIterator iter(settings.inputUrl);
    while(iter.hasNext()){
        if(stateInfo.isCoR()){
            return;
        }
        DNASequence dna = iter.next();
        QString comment = DNAInfo::getFastqComment(dna.info);
        int seqLen = dna.length();
        if(seqLen > dna.quality.qualCodes.length()){
            ncount++;
            continue;
        }else{
            int endPosition = seqLen-1;
            for (; endPosition>=0; endPosition--){
                if(dna.quality.getValue(endPosition) >= quality){
                    break;
                }
            }
            if(endPosition>=0 && endPosition+1 >= minLen){
                DNASequence trimmed(dna.getName(), dna.seq.left(endPosition+1), dna.alphabet);
                trimmed.quality = dna.quality;
                trimmed.quality.qualCodes = trimmed.quality.qualCodes.left(endPosition+1);
                FastqFormat::writeEntry(trimmed.getName(), trimmed, io.data(), "Writing error", stateInfo);
                ycount++;
            }else{
                ncount++;
                continue;
            }
        }
    }

    algoLog.info(QString("Discarded by trimmer %1").arg(ncount));
    algoLog.info(QString("Accepted by trimmer %1").arg(ycount));
    algoLog.info(QString("Total by trimmer %1").arg(ncount + ycount));
}

QStringList QualityTrimTask::getParameters(U2OpStatus &os){
    QStringList res;
    return res;
}

} //LocalWorkflow
} //U2
