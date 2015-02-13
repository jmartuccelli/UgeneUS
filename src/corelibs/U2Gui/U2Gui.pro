include (U2Gui.pri)

# Input
HEADERS += src/AppSettingsGUI.h \
           src/MainWindow.h \
           src/Notification.h \
           src/NotificationsTypes.h \
           src/NotificationWidget.h \
           src/ObjectViewModel.h \
           src/ObjectViewTasks.h \
           src/OpenViewTask.h \
           src/PluginViewer.h \
           src/ProjectParsing.h \
           src/ProjectView.h \
           src/ToolsMenu.h \
           src/U2SavableWidget.h \
           src/U2WidgetStateStorage.h \
           src/UnloadDocumentTask.h \
           src/WelcomePageAction.h \
           src/options_panel/GroupHeaderImageWidget.h \
           src/options_panel/GroupOptionsWidget.h \
           src/options_panel/OptionsPanel.h \
           src/options_panel/OptionsPanelGroup.h \
           src/options_panel/OptionsPanelWidget.h \
           src/options_panel/OPWidgetFactory.h \
           src/options_panel/OPWidgetFactoryRegistry.h \
           src/options_panel/ShowHideSubgroupWidget.h \
           src/util/AddNewDocumentDialogController.h \
           src/util/AddNewDocumentDialogImpl.h \
           src/util/AuthenticationDialog.h \
           src/util/AuthenticationWidget.h \
           src/util/BreakpointConditionEditDialog.h \
           src/util/CreateAnnotationDialog.h \
           src/util/CreateAnnotationWidget.h \
           src/util/CreateAnnotationWidgetController.h \
           src/util/CreateDocumentFromTextDialogController.h \
           src/util/CreateObjectRelationDialogController.h \
           src/util/CredentialsAskerGui.h \
           src/util/DialogUtils.h \
           src/util/DocumentFormatComboboxController.h \
           src/util/DownloadRemoteFileDialog.h \
           src/util/EditQualifierDialog.h \
           src/util/EditSequenceDialogController.h \
           src/util/ExportAnnotations2CSVTask.h \
           src/util/ExportAnnotationsDialog.h \
           src/util/ExportDocumentDialogController.h \
           src/util/ExportImageDialog.h \
           src/util/ExportObjectUtils.h \
           src/util/GlassView.h \
           src/util/GObjectComboBoxController.h \
           src/util/GraphUtils.h \
           src/util/GScrollBar.h \
           src/util/GUIUtils.h \
           src/util/HBar.h \
           src/util/HelpButton.h \
           src/util/ImportDialogsFactories.h \
           src/util/InputWidgetsControllers.h \
           src/util/LastUsedDirHelper.h \
           src/util/ObjectViewTreeController.h \
           src/util/PositionSelector.h \
           src/util/ProjectDocumentComboBoxController.h \
           src/util/ProjectTreeItemSelectorDialog.h \
           src/util/ProjectTreeItemSelectorDialogImpl.h \
           src/util/RangeSelector.h \
           src/util/RegionSelector.h \
           src/util/RemovePartFromSequenceDialogController.h \
           src/util/SaveDocumentGroupController.h \
           src/util/ScaleBar.h \
           src/util/ScriptEditorDelegate.h \
           src/util/ScriptEditorDialog.h \
           src/util/ScriptEditorWidget.h \
           src/util/ScriptHighlighter.h \
           src/util/SearchGenbankSequenceDialogController.h \
           src/util/SeqPasterWidgetController.h \
           src/util/SuggestCompleter.h \
           src/util/TreeWidgetUtils.h \
           src/util/U2FileDialog.h \
           src/util/U2LongLongValidator.h \
           src/util/imageExport/ImageExportTask.h \
           src/util/imageExport/WidgetScreenshotExportTask.h \
           src/util/ImportDialogs/AceImportDialog.h \
           src/util/GenbankLocationValidator.h \
           src/util/logview/LogView.h \
           src/util/project/filter_tasks/FeatureKeyFilterTask.h \
           src/util/project/filter_tasks/MsaContentFilterTask.h \
           src/util/project/filter_tasks/MsaSeqNameFilterTask.h \
           src/util/project/filter_tasks/ObjectNameFilterTask.h \
           src/util/project/filter_tasks/SequenceAccFilterTask.h \
           src/util/project/filter_tasks/TextContentFilterTask.h \
           src/util/project/ConnectionHelper.h \
           src/util/project/DocumentFolders.h \
           src/util/project/FilteredProjectItemDelegate.h \
           src/util/project/FilteredProjectGroup.h \
           src/util/project/FolderNameDialog.h \
           src/util/project/LoadDocumentTaskProvider.h \
           src/util/project/ProjectFilteringController.h \
           src/util/project/ProjectFilterNames.h \
           src/util/project/ProjectFilterProxyModel.h \
           src/util/project/ProjectTreeController.h \
           src/util/project/ProjectUpdater.h \
           src/util/project/ProjectUtils.h \
           src/util/project/ProjectViewFilterModel.h \
           src/util/project/ProjectViewModel.h \
           src/util/shared_db/CommonImportOptionsDialog.h \
           src/util/shared_db/EditConnectionDialog.h \
           src/util/shared_db/ImportOptionsWidget.h \
           src/util/shared_db/ImportToDatabaseDialog.h \
           src/util/shared_db/ItemToImportEditDialog.h \
           src/util/shared_db/SharedConnectionsDialog.h
FORMS += src/util/ui/AddNewDocumentDialog.ui \
         src/util/ui/AuthenticationDialog.ui \
         src/util/ui/AuthenticationWidget.ui \
         src/util/ui/BreakpointConditionEditDialog.ui \
         src/util/ui/CreateAnnotationDialog.ui \
         src/util/ui/CreateAnnotationNormalWidget.ui \
         src/util/ui/CreateAnnotationOptionsPanelWidget.ui \
         src/util/ui/CreateDocumentFromTextDialog.ui \
         src/util/ui/CreateObjectRelationDialog.ui \
         src/util/ui/DownloadRemoteFileDialog.ui \
         src/util/ui/EditQualifierDialog.ui \
         src/util/ui/EditSequenceDialog.ui \
         src/util/ui/ExportAnnotationsDialog.ui \
         src/util/ui/ExportDocumentDialog.ui \
         src/util/ui/ExportImageDialog.ui \
         src/util/ui/FolderNameDialog.ui \
         src/util/ui/MultipartDocFormatConfiguratorWidget.ui \
         src/util/ui/ProjectTreeItemSelectorDialogBase.ui \
         src/util/ui/RangeSelectionDialog.ui \
         src/util/ui/RemovePartFromSequenceDialog.ui \
         src/util/ui/ScriptEditorDialog.ui \
         src/util/ui/SearchGenbankSequenceDialog.ui \
         src/util/ui/SeqPasterWidget.ui \
         src/util/ImportDialogs/ui/AceImportDialog.ui \
         src/util/shared_db/ui/CommonImportOptionsDialog.ui \
         src/util/shared_db/ui/EditConnectionDialog.ui \
         src/util/shared_db/ui/ImportOptionsWidget.ui \
         src/util/shared_db/ui/ImportToDatabaseDialog.ui \
         src/util/shared_db/ui/ItemToImportEditDialog.ui \
         src/util/shared_db/ui/SharedConnectionsDialog.ui
SOURCES += src/MainWindow.cpp \
           src/Notification.cpp \
           src/NotificationWidget.cpp \
           src/ObjectViewModel.cpp \
           src/ObjectViewTasks.cpp \
           src/OpenViewTask.cpp \
           src/ProjectParsing.cpp \
           src/ToolsMenu.cpp \
           src/UnloadDocumentTask.cpp \
           src/U2SavableWidget.cpp \
           src/U2WidgetStateStorage.cpp \
           src/WelcomePageAction.cpp \
           src/options_panel/GroupHeaderImageWidget.cpp \
           src/options_panel/GroupOptionsWidget.cpp \
           src/options_panel/OptionsPanel.cpp \
           src/options_panel/OptionsPanelGroup.cpp \
           src/options_panel/OptionsPanelWidget.cpp \
           src/options_panel/OPWidgetFactory.cpp \
           src/options_panel/OPWidgetFactoryRegistry.cpp \
           src/options_panel/ShowHideSubgroupWidget.cpp \
           src/util/AddNewDocumentDialogImpl.cpp \
           src/util/AuthenticationDialog.cpp \
           src/util/AuthenticationWidget.cpp \
           src/util/BreakpointConditionEditDialog.cpp \
           src/util/CreateAnnotationDialog.cpp \
           src/util/CreateAnnotationWidget.cpp \
           src/util/CreateAnnotationWidgetController.cpp \
           src/util/CreateDocumentFromTextDialogController.cpp \
           src/util/CreateObjectRelationDialogController.cpp \
           src/util/CredentialsAskerGui.cpp \
           src/util/DialogUtils.cpp \
           src/util/DocumentFormatComboboxController.cpp \
           src/util/DownloadRemoteFileDialog.cpp \
           src/util/EditQualifierDialog.cpp \
           src/util/EditSequenceDialogController.cpp \
           src/util/ExportAnnotations2CSVTask.cpp \
           src/util/ExportAnnotationsDialog.cpp \
           src/util/ExportDocumentDialogController.cpp \
           src/util/ExportImageDialog.cpp \
           src/util/ExportObjectUtils.cpp \
           src/util/GlassView.cpp \
           src/util/GObjectComboBoxController.cpp \
           src/util/GraphUtils.cpp \
           src/util/GScrollBar.cpp \
           src/util/GUIUtils.cpp \
           src/util/HBar.cpp \
           src/util/HelpButton.cpp \
           src/util/ImportDialogsFactories.cpp \
           src/util/InputWidgetsControllers.cpp \
           src/util/LastUsedDirHelper.cpp \
           src/util/ObjectViewTreeController.cpp \
           src/util/PositionSelector.cpp \
           src/util/ProjectDocumentComboBoxController.cpp \
           src/util/ProjectTreeItemSelectorDialog.cpp \
           src/util/RangeSelector.cpp \
           src/util/RegionSelector.cpp \
           src/util/RemovePartFromSequenceDialogController.cpp \
           src/util/SaveDocumentGroupController.cpp \
           src/util/ScaleBar.cpp \
           src/util/ScriptEditorDelegate.cpp \
           src/util/ScriptEditorDialog.cpp \
           src/util/ScriptEditorWidget.cpp \
           src/util/ScriptHighlighter.cpp \
           src/util/SearchGenbankSequenceDialogController.cpp \
           src/util/SeqPasterWidgetController.cpp \
           src/util/SuggestCompleter.cpp \
           src/util/TreeWidgetUtils.cpp \
           src/util/U2FileDialog.cpp \
           src/util/U2LongLongValidator.cpp \
           src/util/GenbankLocationValidator.cpp \
           src/util/imageExport/ImageExportTask.cpp \
           src/util/imageExport/WidgetScreenshotExportTask.cpp \
           src/util/ImportDialogs/AceImportDialog.cpp \
           src/util/logview/LogView.cpp \
           src/util/project/filter_tasks/FeatureKeyFilterTask.cpp \
           src/util/project/filter_tasks/MsaContentFilterTask.cpp \
           src/util/project/filter_tasks/MsaSeqNameFilterTask.cpp \
           src/util/project/filter_tasks/ObjectNameFilterTask.cpp \
           src/util/project/filter_tasks/SequenceAccFilterTask.cpp \
           src/util/project/filter_tasks/TextContentFilterTask.cpp \
           src/util/project/ConnectionHelper.cpp \
           src/util/project/DocumentFolders.cpp \
           src/util/project/FilteredProjectItemDelegate.cpp \
           src/util/project/FilteredProjectGroup.cpp \
           src/util/project/FolderNameDialog.cpp \
           src/util/project/ProjectFilteringController.cpp \
           src/util/project/ProjectFilterNames.cpp \
           src/util/project/ProjectFilterProxyModel.cpp \
           src/util/project/ProjectTreeController.cpp \
           src/util/project/ProjectUpdater.cpp \
           src/util/project/ProjectUtils.cpp \
           src/util/project/ProjectViewFilterModel.cpp \
           src/util/project/ProjectViewModel.cpp \
           src/util/shared_db/CommonImportOptionsDialog.cpp \
           src/util/shared_db/EditConnectionDialog.cpp \
           src/util/shared_db/ImportOptionsWidget.cpp \
           src/util/shared_db/ImportToDatabaseDialog.cpp \
           src/util/shared_db/ItemToImportEditDialog.cpp \
           src/util/shared_db/SharedConnectionsDialog.cpp
RESOURCES += U2Gui.qrc
TRANSLATIONS += transl/chinese.ts \
                transl/czech.ts \
                transl/english.ts \
                transl/russian.ts
