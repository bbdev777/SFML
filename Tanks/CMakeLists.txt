#############################################################################################
# General settings
#############################################################################################
cmake_minimum_required(VERSION 3.5)

set(ProjectName "ConsoleGraphics")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pipe -Wall -fPIC -Werror=return-type")

find_package(glm CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
#target_link_libraries(main PRIVATE glm::glm-header-only) #example


##############################################################################################
# Stars
##############################################################################################
add_executable(Stars 
    Tanks.cpp
    Sources/Common/SfmlApp.cpp
)

target_include_directories(Stars PUBLIC
    Sources/
    Sources/Common/
)

target_link_libraries(Stars
    sfml-graphics
    sfml-window
    sfml-system
)
##############################################################################################

