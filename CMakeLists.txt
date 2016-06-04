cmake_minimum_required(VERSION 3.4)
project(TowerDefense)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp Opponent.cpp Opponent.h Defense.cpp Defense.h Game.cpp Game.h Button.cpp Button.h Constants.h MenuButton.cpp MenuButton.h CreatorButton.cpp CreatorButton.h GameField.cpp GameField.h MainObject.cpp MainObject.h GameObject.cpp GameObject.h Obstacle.cpp Obstacle.h HPButton.cpp HPButton.h Legend.cpp Legend.h Play.cpp Play.h Bullet.cpp Bullet.h Statistics.cpp Statistics.h NumberChangeButton.cpp NumberChangeButton.h Text.cpp Text.h NumberField.cpp NumberField.h ProgressField.cpp ProgressField.h GameObjectSelector.cpp GameObjectSelector.h DefenseIce.cpp DefenseIce.h BulletIce.cpp BulletIce.h)
add_executable(TowerDefense ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(TowerDefense allegro allegro_primitives allegro_font allegro_ttf allegro_image)

