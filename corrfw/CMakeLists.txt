
add_library(aliphysics-lite-corrfw SHARED)

target_sources(aliphysics-lite-corrfw PRIVATE
  AliCFFrame.cxx
  AliCFGridSparse.cxx
  AliCFUnfolding.cxx
)

target_include_directories(aliphysics-lite-corrfw
    PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# set_property(TARGET aliphysics-lite-corrfw PROPERTY PUBLIC_HEADER 
# AliAnalysisMuMuFnormh 
# AliAnalysisRunList.h 
# AliAnalysisMuMuConfig.h)

target_link_libraries(aliphysics-lite-corrfw PUBLIC aliroot-lite-base)

root_generate_dictionary(G__aliphysicsLite
  AliCFFrame.h
  AliCFGridSparse.h
  AliCFUnfolding.h
                         aliphysics-lite-corrfw-linkdef.h
  MODULE aliphysics-lite-corrfw)

install(TARGETS aliphysics-lite-corrfw EXPORT aliphysics-lite)
