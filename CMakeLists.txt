# CMakeList.txt: проект CMake для AiSD-lab3-2024; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("AiSD-lab3-2024")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (AiSD-lab3-2024 "AiSD-lab3-2024.cpp" "AiSD-lab3-2024.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AiSD-lab3-2024 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
