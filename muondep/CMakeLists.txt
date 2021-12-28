find_package(ROOT REQUIRED)

add_library(aliphysics-lite-muondep SHARED)

target_sources(aliphysics-lite-muondep PRIVATE
  AliAnalysisMuMuConfig.cxx
  AliAnalysisMuMuFnorm.cxx
  AliAnalysisMuMuGraphUtil.cxx
  AliAnalysisMuMuResult.cxx
  AliAnalysisRunList.cxx
  AliAnalysisTriggerScalers.cxx
)

target_include_directories(aliphysics-lite-muondep
    PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_property(TARGET aliphysics-lite-muondep PROPERTY PUBLIC_HEADER 
AliAnalysisMuMuFnorm.h 
AliAnalysisRunList.h 
AliAnalysisMuMuConfig.h)

target_link_libraries(aliphysics-lite-muondep PUBLIC aliroot-lite-cdb aliroot-lite-steer aliroot-lite-ana-base aliphysics-lite-muon ROOT::Gpad)

root_generate_dictionary(G__AliPhysicsLiteMuonDep
  AliAnalysisMuMuConfig.h
  AliAnalysisMuMuFnorm.h
  AliAnalysisMuMuGraphUtil.h
  AliAnalysisMuMuResult.h
  AliAnalysisRunList.h
  AliAnalysisTriggerScalers.h
                         aliphysics-lite-muondep-linkdef.h
  MODULE aliphysics-lite-muondep)

install(TARGETS aliphysics-lite-muondep)
