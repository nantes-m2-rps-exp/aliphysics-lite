add_library(aliphysics-lite-oadb-base SHARED)

target_sources(aliphysics-lite-oadb-base PRIVATE
  AliAnalysisUtils.cxx
  AliPPVsMultUtils.cxx
)

target_link_libraries(aliphysics-lite-oadb-base PUBLIC 
  aliroot-lite-base
  aliroot-lite-esd
  aliroot-lite-aod
  aliroot-lite-ana-alice)


target_include_directories(aliphysics-lite-oadb-base
    PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_property(TARGET aliphysics-lite-oadb-base PROPERTY PUBLIC_HEADER 
  AliAnalysisUtils.h
  AliPPVsMultUtils.h
)

root_generate_dictionary(G__AliPhysicsLiteOADBBase
  AliAnalysisUtils.h
  AliPPVsMultUtils.h
                         aliphysics-lite-oadb-base-linkdef.h
  MODULE aliphysics-lite-oadb-base)
 
install(TARGETS aliphysics-lite-oadb-base EXPORT aliphysics-lite)

