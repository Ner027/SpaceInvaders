cmake_minimum_required(VERSION 3.21)
project(SpaceInvaders)

link_directories("/home/nero/Desktop/ncurses-6.3/lib")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 23)

add_executable(SpaceInvaders main.cpp CursesWrapper/Vector2.cpp CursesWrapper/Vector2.h Managers/RenderManager.cpp Managers/RenderManager.h CursesWrapper/IScreenObject.h CursesWrapper/Sprite.cpp CursesWrapper/Sprite.h Util/Util.h Util/Util.cpp Managers/SpriteManager.cpp Managers/SpriteManager.h Util/Constants.h CursesWrapper/SpriteContainer.cpp CursesWrapper/SpriteContainer.h Managers/GameClock.cpp Managers/GameClock.h Game/ITick.h Game/ITick.cpp Game/GameObject.cpp Game/GameObject.h Components/IComponent.h Components/SpriteRenderer.cpp Components/SpriteRenderer.h Components/AnimatedSprite.cpp Components/AnimatedSprite.h Components/Physics.cpp Components/Physics.h)

target_link_libraries(SpaceInvaders libncurses.a Threads::Threads)