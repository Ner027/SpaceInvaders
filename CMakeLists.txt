cmake_minimum_required(VERSION 3.21)
project(SpaceInvaders)

link_directories("/home/nero/Desktop/ncurses-6.3/lib")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 23)

add_executable(SpaceInvaders main.cpp Data/Vector2.cpp Data/Vector2.h Managers/RenderManager.cpp Managers/RenderManager.h CursesWrapper/ScreenObject.h CursesWrapper/Sprite.cpp CursesWrapper/Sprite.h Util/Util.h Util/Util.cpp Managers/AssetManager.cpp Managers/AssetManager.h Util/Constants.h Data/SpriteContainer.cpp Data/SpriteContainer.h Managers/GameClock.cpp Managers/GameClock.h Game/GameObject.cpp Game/GameObject.h Components/IComponent.h Components/SpriteRenderer.cpp Components/SpriteRenderer.h Components/AnimatedSprite.cpp Components/AnimatedSprite.h Components/Physics.cpp Components/Physics.h Components/MovableComponent.h CursesWrapper/ScreenObject.cpp Components/Bullet.cpp Components/Bullet.h Components/ICollider.h CursesWrapper/TextBox.cpp CursesWrapper/TextBox.h CursesWrapper/Rect.cpp CursesWrapper/Rect.h Components/Enemy.cpp Components/Enemy.h Managers/GameManager.cpp Managers/GameManager.h Components/EnemyAI.cpp Components/EnemyAI.h Components/ICollisionTester.h Components/BetterBoxCollider.cpp Components/BetterBoxCollider.h Data/ShipContainer.h Util/IncludeResolver.h CursesWrapper/BigTextBox.cpp CursesWrapper/BigTextBox.h Data/ScoreContainer.h)

target_link_libraries(SpaceInvaders libncurses.a Threads::Threads)