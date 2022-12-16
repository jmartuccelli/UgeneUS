include (U2Algorithm.pri)

# Input
HEADERS += src/misc/BitsTable.h \
           src/misc/CDSearchTaskFactory.h \
           src/misc/DnaAssemblyMultiTask.h \
           src/misc/DynTable.h \
           src/misc/EnzymeModel.h \
           src/misc/FindAlgorithm.h \
           src/misc/FindAlgorithmTask.h \
           src/misc/GenomeAssemblyMultiTask.h \
           src/misc/RepeatFinderSettings.h \
           src/misc/RepeatFinderTaskFactory.h \
           src/misc/RollingArray.h \
           src/misc/RollingMatrix.h \
           src/misc/SequenceContentFilterTask.h \
           src/misc/SyncSort.h \
           src/molecular_geometry/GeomUtils.h \
           src/molecular_geometry/MolecularSurface.h \
           src/molecular_geometry/MolecularSurfaceFactoryRegistry.h \
           src/molecular_geometry/VanDerWaalsSurface.h \
           src/msa_alignment/AbstractAlignmentTask.h \ 
           src/msa_alignment/AlignSequencesToAlignmentTaskSettings.h \   
           src/msa_alignment/BaseAlignmentAlgorithmIds.h \       
           src/msa_alignment/SimpleAddingToAlignment.h \
           src/pairwise_alignment/NWAligner.h \
           src/pairwise_alignment/PairwiseAligner.h \
           src/pairwise_alignment/PairwiseAlignmentTask.h \
           src/phyltree/CreatePhyTreeSettings.h \
           src/phyltree/PhyTreeGenerator.h \
           src/phyltree/PhyTreeGeneratorRegistry.h \
           src/phyltree/PhyTreeGeneratorTask.h \
           src/registry/AlignmentAlgorithmsRegistry.h \
           src/registry/CDSearchTaskFactoryRegistry.h \
           src/registry/DnaAssemblyAlgRegistry.h \
           src/registry/DnaAssemblyTask.h \
           src/registry/GenomeAssemblyRegistry.h \
           src/registry/RepeatFinderTaskFactoryRegistry.h \
           src/registry/SecStructPredictAlgRegistry.h \
           src/registry/SecStructPredictTask.h \
           src/registry/SplicedAlignmentTask.h \
           src/registry/SplicedAlignmentTaskRegistry.h \
           src/registry/SubstMatrixRegistry.h \
           src/registry/TempCalcRegistry.h \
           src/smith_waterman/SmithWatermanReportCallback.h \
           src/smith_waterman/SmithWatermanResult.h \
           src/smith_waterman/SmithWatermanResultFilters.h \
           src/smith_waterman/SmithWatermanSettings.h \
           src/smith_waterman/SmithWatermanTaskFactory.h \
           src/smith_waterman/SmithWatermanTaskFactoryRegistry.h \
           src/smith_waterman/SmithWatermanUtil.h \
           src/smith_waterman/SWResultFilterRegistry.h \
           src/smith_waterman/SWMulAlignExternalPropTag.h \
           src/smith_waterman/SWMulAlignResultNamesTag.h \
           src/smith_waterman/SWMulAlignResultNamesTagsRegistry.h \
           src/smith_waterman/SWMulAlignSeqPrefixTag.h \
           src/smith_waterman/SWMulAlignSubseqPropTag.h \
           src/structural_alignment/StructuralAlignmentAlgorithm.h \
           src/structural_alignment/StructuralAlignmentAlgorithmFactory.h \
           src/structural_alignment/StructuralAlignmentAlgorithmRegistry.h \
           src/temperature/BaseTempCalc.h \
           src/temperature/TempCalcFactory.h \
           src/util_assembly_consensus/AssemblyConsensusAlgorithm.h \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmDefault.h \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmRegistry.h \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmSamtools.h \
           src/util_assembly_consensus/AssemblyConsensusUtils.h \
           src/util_assembly_consensus/BuiltInAssemblyConsensusAlgorithms.h \
           src/util_msa_consensus/BuiltInConsensusAlgorithms.h \
           src/util_msa_consensus/MaConsensusAlgorithmSimpleExtended.h \
           src/util_msa_consensus/MSAConsensusAlgorithm.h \
           src/util_msa_consensus/MSAConsensusAlgorithmClustal.h \
           src/util_msa_consensus/MSAConsensusAlgorithmDefault.h \
           src/util_msa_consensus/MSAConsensusAlgorithmLevitsky.h \
           src/util_msa_consensus/MSAConsensusAlgorithmRegistry.h \
           src/util_msa_consensus/MSAConsensusAlgorithmStrict.h \
           src/util_msa_consensus/MSAConsensusUtils.h \
           src/util_msa_distance/BuiltInDistanceAlgorithms.h \
           src/util_msa_distance/MSADistanceAlgorithm.h \
           src/util_msa_distance/MSADistanceAlgorithmHamming.h \
           src/util_msa_distance/MSADistanceAlgorithmSimilarity.h \
           src/util_msa_distance/MSADistanceAlgorithmHammingRevCompl.h \
           src/util_msa_distance/MSADistanceAlgorithmRegistry.h \
           src/util_msaedit/CreateSubalignmentTask.h \
           src/util_msaedit/MsaUtilTasks.h \
           src/util_msaedit/color_schemes/percentage_idententity/colored/ColumnCharsCounter.h \
           src/util_msaedit/color_schemes/percentage_idententity/colored/MsaColorSchemePercentageIdententityColored.h \
           src/util_msaedit/color_schemes/percentage_idententity/colored/MsaColorSchemePercentageIdententityColoredFactory.h \
           src/util_msaedit/color_schemes/ColorSchemeUtils.h \
           src/util_msaedit/color_schemes/MsaColorScheme.h \
           src/util_msaedit/color_schemes/MsaColorSchemeClustalX.h \
           src/util_msaedit/color_schemes/MsaColorSchemeCustom.h \
           src/util_msaedit/color_schemes/MsaColorSchemePercentageIdententityGrayscale.h \
           src/util_msaedit/color_schemes/MsaColorSchemePercentageIdentity.h \
           src/util_msaedit/color_schemes/MsaColorSchemeStatic.h \
           src/util_msaedit/color_schemes/MsaColorSchemeWeakSimilarities.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingScheme.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeAgreements.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeConservation.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeDisagreements.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeGaps.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeNoColors.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeTransitions.h \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeTransversions.h \
           src/util_orf/ORFAlgorithmTask.h \
           src/util_orf/ORFFinder.h \
           src/util_sarray/SArrayBasedFindTask.h \
           src/util_sarray/SArrayIndex.h \
           src/util_sarray/SArrayIndexSerializer.h \
           src/util_weight_matrix/BuiltInPWMConversionAlgorithms.h \
           src/util_weight_matrix/PWMConversionAlgorithm.h \
           src/util_weight_matrix/PWMConversionAlgorithmBVH.h \
           src/util_weight_matrix/PWMConversionAlgorithmLOD.h \
           src/util_weight_matrix/PWMConversionAlgorithmMCH.h \
           src/util_weight_matrix/PWMConversionAlgorithmNLG.h \
           src/util_weight_matrix/PWMConversionAlgorithmRegistry.h

SOURCES += src/misc/BitsTable.cpp \
           src/misc/DnaAssemblyMultiTask.cpp \
           src/misc/EnzymeModel.cpp \
           src/misc/FindAlgorithm.cpp \
           src/misc/FindAlgorithmTask.cpp \
           src/misc/GenomeAssemblyMultiTask.cpp \
           src/misc/SequenceContentFilterTask.cpp \
           src/molecular_geometry/GeomUtils.cpp \
           src/molecular_geometry/MolecularSurface.cpp \
           src/molecular_geometry/MolecularSurfaceFactoryRegistry.cpp \
           src/molecular_geometry/VanDerWaalsSurface.cpp \
           src/msa_alignment/AbstractAlignmentTask.cpp \           
           src/msa_alignment/AlignSequencesToAlignmentTaskSettings.cpp \
           src/msa_alignment/BaseAlignmentAlgorithmIds.cpp \
           src/msa_alignment/SimpleAddingToAlignment.cpp \
           src/pairwise_alignment/NWAligner.cpp \
           src/pairwise_alignment/PairwiseAligner.cpp \
           src/pairwise_alignment/PairwiseAlignmentTask.cpp \
           src/phyltree/CreatePhyTreeSettings.cpp \
           src/phyltree/PhyTreeGeneratorRegistry.cpp \
           src/phyltree/PhyTreeGeneratorTask.cpp \
           src/registry/AlignmentAlgorithmsRegistry.cpp \
           src/registry/DnaAssemblyAlgRegistry.cpp \
           src/registry/DnaAssemblyTask.cpp \
           src/registry/GenomeAssemblyRegistry.cpp \
           src/registry/RepeatFinderTaskFactoryRegistry.cpp \
           src/registry/SecStructPredictAlgRegistry.cpp \
           src/registry/SecStructPredictTask.cpp \
           src/registry/SplicedAlignmentTask.cpp \
           src/registry/SplicedAlignmentTaskRegistry.cpp \
           src/registry/SubstMatrixRegistry.cpp \
           src/registry/TempCalcRegistry.cpp \
           src/smith_waterman/SmithWatermanReportCallback.cpp \
           src/smith_waterman/SmithWatermanResult.cpp \
           src/smith_waterman/SmithWatermanResultFilters.cpp \
           src/smith_waterman/SmithWatermanTaskFactoryRegistry.cpp \
           src/smith_waterman/SmithWatermanUtil.cpp \
           src/smith_waterman/SWResultFilterRegistry.cpp \
           src/smith_waterman/SWMulAlignExternalPropTag.cpp \
           src/smith_waterman/SWMulAlignResultNamesTagsRegistry.cpp \
           src/smith_waterman/SWMulAlignSeqPrefixTag.cpp \
           src/smith_waterman/SWMulAlignSubseqPropTag.cpp \
           src/structural_alignment/StructuralAlignmentAlgorithm.cpp \
           src/structural_alignment/StructuralAlignmentAlgorithmFactory.cpp \
           src/structural_alignment/StructuralAlignmentAlgorithmRegistry.cpp \
           src/temperature/BaseTempCalc.cpp \
           src/temperature/TempCalcFactory.cpp \
           src/util_assembly_consensus/AssemblyConsensusAlgorithm.cpp \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmDefault.cpp \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmRegistry.cpp \
           src/util_assembly_consensus/AssemblyConsensusAlgorithmSamtools.cpp \
           src/util_assembly_consensus/AssemblyConsensusUtils.cpp \
           src/util_assembly_consensus/BuiltInAssemblyConsensusAlgorithms.cpp \
           src/util_msa_consensus/BuiltInConsensusAlgorithms.cpp \
           src/util_msa_consensus/MaConsensusAlgorithmSimpleExtended.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithm.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithmClustal.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithmDefault.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithmLevitsky.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithmRegistry.cpp \
           src/util_msa_consensus/MSAConsensusAlgorithmStrict.cpp \
           src/util_msa_consensus/MSAConsensusUtils.cpp \
           src/util_msa_distance/BuiltInDistanceAlgorithms.cpp \
           src/util_msa_distance/MSADistanceAlgorithm.cpp \
           src/util_msa_distance/MSADistanceAlgorithmHamming.cpp \
           src/util_msa_distance/MSADistanceAlgorithmSimilarity.cpp \
           src/util_msa_distance/MSADistanceAlgorithmHammingRevCompl.cpp \
           src/util_msa_distance/MSADistanceAlgorithmRegistry.cpp \
           src/util_msaedit/CreateSubalignmentTask.cpp \
           src/util_msaedit/MsaUtilTasks.cpp \
           src/util_msaedit/color_schemes/percentage_idententity/colored/ColumnCharsCounter.cpp \
           src/util_msaedit/color_schemes/percentage_idententity/colored/MsaColorSchemePercentageIdententityColored.cpp \
           src/util_msaedit/color_schemes/percentage_idententity/colored/MsaColorSchemePercentageIdententityColoredFactory.cpp \
           src/util_msaedit/color_schemes/ColorSchemeUtils.cpp \
           src/util_msaedit/color_schemes/MsaColorScheme.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemeClustalX.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemeCustom.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemePercentageIdententityGrayscale.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemePercentageIdentity.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemeStatic.cpp \
           src/util_msaedit/color_schemes/MsaColorSchemeWeakSimilarities.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingScheme.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeAgreements.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeConservation.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeDisagreements.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeGaps.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeNoColors.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeTransitions.cpp \
           src/util_msaedit/highlighting_schemes/MsaHighlightingSchemeTransversions.cpp \
           src/util_orf/ORFAlgorithmTask.cpp \
           src/util_orf/ORFFinder.cpp \
           src/util_sarray/SArrayBasedFindTask.cpp \
           src/util_sarray/SArrayIndex.cpp \
           src/util_sarray/SArrayIndexSerializer.cpp \
           src/util_weight_matrix/BuiltInPWMConversionAlgorithms.cpp \
           src/util_weight_matrix/PWMConversionAlgorithm.cpp \
           src/util_weight_matrix/PWMConversionAlgorithmBVH.cpp \
           src/util_weight_matrix/PWMConversionAlgorithmLOD.cpp \
           src/util_weight_matrix/PWMConversionAlgorithmMCH.cpp \
           src/util_weight_matrix/PWMConversionAlgorithmNLG.cpp \
           src/util_weight_matrix/PWMConversionAlgorithmRegistry.cpp


TRANSLATIONS += transl/russian.ts
