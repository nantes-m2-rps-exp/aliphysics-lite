add_library(aliphysics-lite-oadb-multiplicity SHARED)

target_sources(aliphysics-lite-oadb-multiplicity PRIVATE
  AliMultSelection.cxx
  AliOADBMultSelection.cxx
  AliMultEstimator.cxx
  AliMultInput.cxx
  AliMultSelectionCuts.cxx
)


target_link_libraries(aliphysics-lite-oadb-multiplicity PUBLIC aliroot-lite-esd
 aliroot-lite-aod aliroot-lite-ana-alice)

target_include_directories(aliphysics-lite-oadb-multiplicity
    PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_property(TARGET aliphysics-lite-oadb-multiplicity PROPERTY PUBLIC_HEADER 
  AliMultSelection.h
)

root_generate_dictionary(G__AliPhysicsLiteOADBMultiplicity
  AliMultSelection.h
  AliOADBMultSelection.h
  AliMultEstimator.h
  AliMultInput.h
  AliMultSelectionCuts.h
                         aliphysics-lite-oadb-multiplicity-linkdef.h
  MODULE aliphysics-lite-oadb-multiplicity)
 
install(TARGETS aliphysics-lite-oadb-multiplicity)

