cmake_minimum_required(VERSION 3.29)
project(Players)

set(CMAKE_CXX_STANDARD 17)

add_executable(Players main.cpp
        Archer.h
        CharacterRole.h
        CharacterType.h
        Magician.h
        Player.h
        Responsible.h
        RiskTaking.h
        Warrior.h
        Archer.cpp
        CharacterRole.cpp
        Magician.cpp
        Player.cpp
        Responsible.cpp
        RiskTaking.cpp
        Warrior.cpp)
