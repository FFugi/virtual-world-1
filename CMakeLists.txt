cmake_minimum_required(VERSION 3.0)
project(virtual_world_1)

set(CMAKE_CXX_COMPILER g++-7)
set(CMAKE_CXX_FLAGS "-Wall -Werror -lncurses -std=c++17")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(virtual_world_1 main.cpp Organism.cpp Organism.hpp World.cpp World.hpp animals/Sheep.cpp animals/Sheep.hpp animals/Wolf.cpp animals/Wolf.hpp animals/Animal.cpp animals/Animal.hpp Position.hpp plants/Grass.cpp plants/Grass.hpp plants/Plant.cpp plants/Plant.hpp Logger.cpp Logger.hpp plants/Sonchus.cpp plants/Sonchus.hpp animals/Fox.cpp animals/Fox.hpp animals/Tortoise.cpp animals/Tortoise.hpp plants/Guarana.cpp plants/Guarana.hpp plants/WolfBerry.cpp plants/WolfBerry.hpp plants/Hogweed.cpp plants/Hogweed.hpp animals/Antelope.cpp animals/Antelope.hpp serialization/Serializer.cpp serialization/Serializer.hpp serialization/Serializable.hpp OrganismManager.cpp OrganismManager.hpp Color.hpp animals/Human.cpp animals/Human.hpp serialization/Parser.cpp serialization/Parser.hpp Menu.cpp Menu.hpp OrganismFactory.cpp OrganismFactory.hpp serialization/IncorrectDataDeserializationException.cpp serialization/IncorrectDataDeserializationException.hpp)

target_link_libraries(virtual_world_1 ${CURSES_LIBRARIES})
