cmake_minimum_required(VERSION 3.29)
project(mtam_HW4)

set(CMAKE_CXX_STANDARD 17)

add_executable(mtam_HW4 main.cpp
        Event.h
        Encounter.h
        SpecialEvents.h
        Encounter.cpp
        Utilities.h
        Utilities.cpp
        SpecialEvents.cpp
        SolarEclipse.h
        PotionsMerchant.h
)
