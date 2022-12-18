# CMakeList.txt : CMake project for shapes_editor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_executable (shapes_editor "main.cpp" "src/Model/Shape.cpp" "include/Model/Shape.h" "include/Model/ShapeType.h" "include/Model/Point.h" "include/Model/Defaults.h" "include/Model/Color.h" "include/Model/ShapeStore.h" "src/Model/ShapeStore.cpp" "include/Presenter/Editor.h" "src/Presenter/Editor.cpp" "src/Presenter/CommandHistory.cpp" "include/Presenter/CommandHistory.h" "include/Presenter/ShapesPresenter.h" "src/Presenter/ShapesPresenter.cpp" "include/Presenter/ResizeNode.h" "include/View/ICanvas.h" "include/Presenter/IMouseActionsHandler.h")

find_package(glad CONFIG REQUIRED)
target_link_libraries(shapes_editor PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(shapes_editor PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(shapes_editor PRIVATE imgui::imgui)
