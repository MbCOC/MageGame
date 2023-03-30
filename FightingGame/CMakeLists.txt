# CMakeList.txt: проект CMake для FightingGame; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (FightingGame "Main.cpp" "Main.h" "Player.h"  "Attack.h"  "Attack.cpp" "CoreFunctions.h" "CoreFunctions.cpp"  "Player.cpp" "Enemy.h" "Enemy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FightingGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
