cmake_minimum_required(VERSION 3.21)
project(SpaceInvaders)

link_directories("/home/nero/Desktop/ncurses-6.3/lib")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 23)

add_executable(SpaceInvaders main.cpp CursesWrapper/Vector2.cpp CursesWrapper/Vector2.h Managers/RenderManager.cpp Managers/RenderManager.h CursesWrapper/ScreenObject.h CursesWrapper/Sprite.cpp CursesWrapper/Sprite.h Util/Util.h Util/Util.cpp Managers/AssetManager.cpp Managers/AssetManager.h Util/Constants.h CursesWrapper/SpriteContainer.cpp CursesWrapper/SpriteContainer.h Managers/GameClock.cpp Managers/GameClock.h Game/GameObject.cpp Game/GameObject.h Components/IComponent.h Components/SpriteRenderer.cpp Components/SpriteRenderer.h Components/AnimatedSprite.cpp Components/AnimatedSprite.h Components/Physics.cpp Components/Physics.h Components/MovableComponent.h CursesWrapper/ScreenObject.cpp Components/EnemyRow.cpp Components/EnemyRow.h Components/Bullet.cpp Components/Bullet.h Components/ICollider.h CursesWrapper/TextBox.cpp CursesWrapper/TextBox.h CursesWrapper/Rect.cpp CursesWrapper/Rect.h)

target_link_libraries(SpaceInvaders libncurses.a Threads::Threads)