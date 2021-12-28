find_package(ROOT REQUIRED)

add_library(aliphysics-lite-muon SHARED)

target_sources(aliphysics-lite-muon PRIVATE
  AliAnalysisMuMuBase.cxx
  AliAnalysisMuMuBinning.cxx
  AliAnalysisMuMuCutCombination.cxx
  AliAnalysisMuMuCutElement.cxx
  AliAnalysisMuMuCutRegistry.cxx
  AliAnalysisMuMuEventCutter.cxx
  AliAnalysisMuMuGlobal.cxx
  AliAnalysisMuMuMinv.cxx
  AliAnalysisMuMuSingle.cxx
  AliAnalysisMuonUtility.cxx
  AliAnalysisTaskMuMu.cxx
  AliMuonEventCuts.cxx
  AliMuonTrackCuts.cxx
  AliOADBMuonTrackCutsParam.cxx
  AliMuonTriggerCombo.cxx
)

target_include_directories(aliphysics-lite-muon
    PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_property(TARGET aliphysics-lite-muon PROPERTY PUBLIC_HEADER 
  AliAnalysisMuMuBase.h
  AliAnalysisMuMuCutCombination.h
  AliAnalysisMuMuCutElement.h
  AliAnalysisMuMuCutRegistry.h
  AliAnalysisMuMuEventCutter.h
  AliAnalysisMuMuGlobal.h
  AliAnalysisMuMuMinv.h
  AliAnalysisMuMuSingle.h
  AliAnalysisMuonUtility.h
  AliAnalysisTaskMuMu.h
  AliMuonEventCuts.h
  AliMuonTrackCuts.h
  AliOADBMuonTrackCutsParam.h
  AliMuonTriggerCombo.h
)

target_link_libraries(aliphysics-lite-muon PUBLIC 
  aliroot-lite-ana-alice
  aliroot-lite-aod
  aliphysics-lite-corrfw
  aliphysics-lite-oadb-base
  aliphysics-lite-oadb-multiplicity)

root_generate_dictionary(G__aliphysicsLiteMuon
  AliAnalysisMuMuBase.h
  AliAnalysisMuMuCutCombination.h
  AliAnalysisMuMuCutElement.h
  AliAnalysisMuMuCutRegistry.h
  AliAnalysisMuMuEventCutter.h
  AliAnalysisMuMuGlobal.h
  AliAnalysisMuMuMinv.h
  AliAnalysisMuMuSingle.h
  AliAnalysisMuonUtility.h
  AliAnalysisTaskMuMu.h
  AliMuonEventCuts.h
  AliMuonTrackCuts.h
  AliOADBMuonTrackCutsParam.h
  AliMuonTriggerCombo.h
                         aliphysics-lite-muon-linkdef.h
  MODULE aliphysics-lite-muon)

install(TARGETS aliphysics-lite-muon EXPORT aliphysics-lite)
