/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2019 UniPro <ugene@unipro.ru>
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

#include <QDesktopServices>
#include <QTextStream>
#include <QTreeWidget>

#include <U2Core/AppContext.h>
#include <U2Core/IOAdapter.h>
#include <U2Core/Settings.h>

#include <U2Gui/U2FileDialog.h>

#include <U2Test/GTest.h>
#include <U2Test/GTestFrameworkComponents.h>

#include "TestRunnerPlugin.h"
#include "TestViewController.h"
#include "TestViewReporter.h"

namespace U2 {


static QString generateHtmlWithNoTests() {
    return "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 //EN\" \"http://www.w3.org/TR/html401/loose.dtd\">\n<html>\n<head>\n<META http-equiv=\"Content-Type\" content=\"text/html; charset=US-ASCII\">\n<TITLE>UGENE Test Report</TITLE>\n</head>\n<body>\nNo Failed Tests</body>\n</html>";
}

static QString generateHtmlHeader() {
    QString html = "<html>\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";
    html += "<style>"
            "body {background-color: white;}"
            "table.title {border: 1px solid #c7cbcc; background-color: #e1f6f7; width:100%; margin-bottom: 10px;}"
            "table.stats {border-collapse: collapse; width: 100%;}"
            "table.stats th {text-align: center;}"
            "table.stats tr td:first-of-type {text-align:left;} "
            "table.stats tr td {text-align: center; border: 1px solid #cccccc;}"
            "table.stats tr.total {font-weight: bold}"
            "table.details {background-color: #f0f0f0; padding: 10px;} "
            "td.title {font-size: large; font-weight: bold;} "
            "td {white-space: nowrap;} "
            "table.bar {background-color: #f25913;} "
            "table.goodbar {background-color: #60de51;} "
            "td.norun {background-color: #949198;} "
            "td.bar {background-color: #60de51;} "
            "</style>\n";
    html += "<title>UGENE Test Report</title>"
            "<script>\n"
            "function toggleTestDetails(Click_Menu){if (Click_Menu.style.display === 'none'){Click_Menu.style.display = '';}else{Click_Menu.style.display = 'none';}}"
            "</script>\n";
    html += "</head>\n<body>\n";
    return html;
}

static QString generateHeaderAndLogo(int runtime) {
    QString date = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
    QString runTimeText = QString::number(runtime) + "s";
    QString html = "<table class='title'>";
    html += "<tr><td class='title'>UGENE Test Report</td></tr>";
    html += "<tr><td>&nbsp;&nbsp;&nbsp;generated by <a HREF='http://ugene.net'>UGENE</a></td></tr>";
    html += "<tr><td>&nbsp;&nbsp;&nbsp;" + date + ", total run time: " + runTimeText + "</td></tr>";
    html += "</table>";
    return html;
}

static QString generateFirstStatsRow() {
    QString html = "<tr>"
                   "<th>Test suite</th>"
                   "<th>Tests</th>"
                   "<th>Passed</th>"
                   "<th>Failed</th>"
                   "<th>Excluded</th>"
                   "<th>Success Rate</th>"
                   "</tr>";
    return html;
}

static QString generateStatusBarColumn(int data, bool noTestRun) {
    QString barClass = noTestRun ? "norun" : "bar";
    QString html = "<td>" + (noTestRun ? "—" : QString::number(data) + "%") + "</td>";
    html += "<td><table cellpadding=0 cellspacing=0 width=100 class=bar><tr><td>";
    html += "<table cellpadding=0 cellspacing=0 align=left width='" + QString::number(data) + "%' class='goodbar'>";
    html += "<tr><td height=12 class='" + barClass + "'></td></tr>";
    html += "</table></td></tr></table></td>";
    return html;
}

static QList<TVTestItem *> getFailedTests(TVTSItem *Root) {
    QList<TVTestItem *> html;
    for (int i = 0; i < Root->childCount(); i++) {
        TVItem *item = static_cast<TVItem *>(Root->child(i));
        if (item->isTest()) {
            TVTestItem *tItem = static_cast<TVTestItem *>(item);
            if (tItem->testState->isFailed()) {
                html.append(tItem);
            }
        } else {
            assert(item->isSuite());
            TVTSItem *tItem = static_cast<TVTSItem *>(item);
            html += getFailedTests(tItem);
        }
    }
    return html;
}

static bool cleanupRunResultRichTextHtml(QString *runResult) {
    if (runResult == NULL) {
        return false;
    }

    QString mainCommentColor = " <font color=\"#339966\" mainColorPoint>\\1</font mainColorPointEnd> ";
    QString commentColor = " <font color=\"#33FF66\" commentColorPoint>\\1</font commentColorPointEnd> ";
    QString normalTagColor = "<font color=\"#3366FF\">\\1</font>";
    QString valueColor = " <font color=\"#FF3333\">\\1</font>=<font color=\"#0000CC\">\\2</font> ";
    QString deleteColor = "\\1\\2";

    runResult->replace(QRegExp("(\\s[^\\s]*)=(\"[^\"]*\")"), valueColor);//first find all values

    QRegExp rx("(&lt;!--.*--&gt;)");
    rx.setMinimal(true);
    runResult->replace(rx, commentColor);//2- find all comments

    rx.setPattern("(&lt;!.*&gt;)");
    runResult->replace(rx, mainCommentColor);//2- find all main comments

    rx.setPattern("(&lt;.*\\s)");
    runResult->replace(rx, normalTagColor);//3- find all tag names
    rx.setPattern("(&lt;[^\\s]*&gt;)");
    runResult->replace(rx, normalTagColor);//3- find all tag names
    rx.setPattern("(&gt;)");
    runResult->replace(rx, normalTagColor);//3- find all tag names

    rx.setPattern("(commentColorPoint.*)</font>(.*commentColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    rx.setPattern("(commentColorPoint.*)<font color=\".*\">(.*commentColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    rx.setPattern("(commentColorPoint.*)</font mainColorPointEnd>(.*commentColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    rx.setPattern("(commentColorPoint.*)<font color=\"#339966\" mainColorPoint>(.*commentColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    rx.setPattern("(mainColorPoint.*)</font>(.*mainColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    rx.setPattern("(mainColorPoint.*)<font color=\".*\">(.*mainColorPointEnd)");
    while (rx.indexIn(*runResult) != -1) {
        runResult->replace(rx, deleteColor);//4- find information to delete
    }

    runResult->remove("commentColorPointEnd");
    runResult->remove("commentColorPoint");
    runResult->remove("mainColorPointEnd");
    runResult->remove("mainColorPoint");

    return true;
}


static QString generateSuiteErrorsBlock(const QList<TVTestItem *> &failedTests, int *idGen) {
    QString html;

    foreach(TVTestItem *curItem, failedTests) {
        html += "<div><a href='javascript:toggleTestDetails(display" + QString::number(*idGen) + ")' name='Test_" +
                QString::number(*idGen) + "'>";
        html += curItem->testState->getTestRef()->getShortName();
        html += "</a></div>\n";
        html += "<div id='display" + QString::number(*idGen) + "' style='display: none'>\n";
        *idGen = *idGen + 1;

        html += "<table width='100%' class='details'>\n";

        QString runResultHtml = curItem->getRichDesc();
        cleanupRunResultRichTextHtml(&runResultHtml);
        runResultHtml.remove("<b>" + curItem->testState->getTestRef()->getShortName() + "</b><br>");
        html += "<tr><td>" + runResultHtml + "</td></tr>";
        html += "</table>\n";
        html += "</div>\n";
    }

    return html;
}

static QString generateErrorsListBlock(QTreeWidget *tree) {
    int idGen = 1;
    QString html = "<br><br>";
    for (int i = 0, n = tree->topLevelItemCount(); i < n; i++) {
        TVItem *item = static_cast<TVItem *>(tree->topLevelItem(i));
        assert(item->isSuite());
        TVTSItem *suiteItem = static_cast<TVTSItem *>(item);
        QList<TVTestItem *> failedTests = getFailedTests(suiteItem);
        if (!failedTests.isEmpty()) {
            html += "<table>";
            html += "<tr><td><b>" + suiteItem->ts->getName() + "</b></td></tr>";
            html += "<tr><td>" + generateSuiteErrorsBlock(failedTests, &idGen) + "</td></tr>";
            html += "</table>";
        }
    }
    return html;
}

#define SETTINGS_ROOT QString("test_runner/view/")

void TestViewReporter::saveReportToFileAndOpenBrowser(QTreeWidget *tree, int runTime) {
    QString dir = AppContext::getSettings()->getValue(SETTINGS_ROOT + "lastDir", QString()).toString();
    QString fileName = U2FileDialog::getSaveFileName(NULL, "Select save location for the report",
                                                     dir + "/UGENE_test_runner_report.html", "*.html");
    if (fileName.isEmpty()) {
        return;
    }
    AppContext::getSettings()->setValue(SETTINGS_ROOT + "lastDir", QFileInfo(fileName).absoluteDir().absolutePath());

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << generateHtmlReport(tree, runTime);
    file.close();
    QDesktopServices::openUrl(QUrl(fileName));
}

QString TestViewReporter::generateHtmlReport(QTreeWidget *tree, int runTime) {
    QString html;
    if (tree == NULL) {
        html = "treeRoot is Empty";
    } else {
        int totalPassed = 0;
        int totalFailed = 0;
        int totalNotRun = 0;
        int totalExcluded = 0;
        QString perSuiteStatsHtml;
        for (int i = 0, n = tree->topLevelItemCount(); i < n; i++) {
            TVItem *item = static_cast<TVItem *>(tree->topLevelItem(i));
            assert(item->isSuite());
            TVTSItem *tItem = static_cast<TVTSItem *>(item);

            int passed = 0, failed = 0, notRun = 0;
            int excluded = 0;
            int successRatePercent = 100;

            tItem->getTestsState(&passed, &failed, &notRun, &excluded);
            totalPassed += passed;
            totalFailed += failed;
            totalNotRun += notRun;
            totalExcluded += excluded;

            if (failed != 0 && passed != 0) {
                successRatePercent = (passed * 100) / (failed + passed);
            }
            if (passed == 0 && failed != 0) {
                successRatePercent = 0;
            }
            bool noTestsRun = passed == 0 && failed == 0;
            perSuiteStatsHtml += "<tr>\n";
            perSuiteStatsHtml += "<td>" + tItem->ts->getName() + "</td>\n";
            perSuiteStatsHtml += "<td>" + QString::number(passed + failed + notRun) + "</td>\n";
            perSuiteStatsHtml += "<td>" + QString::number(passed) + "</td>\n";
            perSuiteStatsHtml += "<td>" + QString::number(failed) + "</td>\n";
            perSuiteStatsHtml += "<td>" + QString::number(excluded) + "</td>\n";
            perSuiteStatsHtml += generateStatusBarColumn(successRatePercent, noTestsRun);
            perSuiteStatsHtml += "</tr>\n";
        }
        int totalSuccessRatePercent = 100;
        if (totalFailed && totalPassed) {
            totalSuccessRatePercent = (totalPassed * 100) / (totalFailed + totalPassed);
        }
        if (!totalPassed && totalFailed) {
            totalSuccessRatePercent = 0;
        }
        if (!totalPassed && !totalFailed) {
            html = generateHtmlWithNoTests();
            return html;
        }
        html += generateHtmlHeader();
        html += generateHeaderAndLogo(runTime);
        html += "<table cellpadding=2 cellspacing=1 class='stats'>";
        html += generateFirstStatsRow();

        html += perSuiteStatsHtml;

        html += "<tr class='total'><td>Total</td>\n";
        html += "<td>" + QString::number(totalPassed + totalFailed + totalNotRun) + "</td>\n";
        html += "<td>" + QString::number(totalPassed) + "</td>\n";
        html += "<td>" + QString::number(totalFailed) + "</td>\n";
        html += "<td>" + QString::number(totalExcluded) + "</td>\n";
        html += generateStatusBarColumn(totalSuccessRatePercent, totalPassed + totalFailed == 0);
        html += "</tr></table>";

        html += generateErrorsListBlock(tree);
        html += "</body></html>";
    }

    return html;
}

/* Keeping this method for compatibility. */
void TestViewReporter::saveReport(const QString& url,const QString& data) {
    if (url.isEmpty() || data.isEmpty()) {
        return;
    }
    IOAdapterFactory *iof = AppContext::getIOAdapterRegistry()->getIOAdapterFactoryById(BaseIOAdapters::LOCAL_FILE);
    QScopedPointer<IOAdapter> io(iof->createIOAdapter());
    if (!io->open(url, IOAdapterMode_Write)) {
        return;
    }
    io->writeBlock(data.toUtf8());
}

} // namespace

