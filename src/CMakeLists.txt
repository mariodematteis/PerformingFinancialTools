add_library(PFTLibrary
            Derivative/Derivative.cpp
            FixedIncome/Bond.cpp
            FixedIncome/USBond.cpp
            FixedIncome/Option.cpp
            Method/Optimization.cpp)
target_include_directories(PFTLibrary PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(PFTExecutable main.cpp)
target_link_libraries(PFTExecutable PRIVATE PFTLibrary)