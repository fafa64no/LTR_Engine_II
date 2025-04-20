cmake_minimum_required(VERSION 3.28.3)
project(LTR_Engine_II)

set(CMAKE_CXX_STANDARD 20)

add_executable(LTR_Engine_II
    src/main.cpp
)

if (WIN32)
    target_link_libraries(LTR_Engine_II
        opengl32
    )
elseif (UNIX)
    target_link_libraries(LTR_Engine_II
        X11
        GL
    )
else ()
    message(FATAL_ERROR
        "Unrecognized operating system"
    )
endif ()

target_sources(LTR_Engine_II PRIVATE
        src/third_party/glcorearb.h
)

target_sources(LTR_Engine_II PRIVATE
        src/game/GameEngine.cpp

        src/game/inputs/mouseInputs.cpp
        src/game/inputs/Key.cpp
        src/game/inputs/keys.cpp
        src/game/inputs/clickables/ClickableArea.cpp
        src/game/inputs/clickables/CheckBox.cpp
        src/game/inputs/clickables/Button.cpp
        src/game/inputs/clickables/RadioButton.cpp
        src/game/inputs/clickables/clickables.cpp

        src/physics/PhysicsEngine.cpp

        src/rendering/RenderEngine.cpp

        src/rendering/opengl/glFunctions.cpp
        src/rendering/opengl/OpenGLRenderer.cpp
        src/rendering/opengl/shading/Shader.cpp
        src/rendering/opengl/shading/shaders.cpp
        src/rendering/opengl/textures/Texture.cpp
        src/rendering/opengl/textures/textures.cpp
        src/rendering/opengl/vao/VAO.cpp
        src/rendering/opengl/vao/vaos.cpp
        src/rendering/opengl/displayables/Sprite.cpp
        src/rendering/opengl/displayables/SpriteWithFilter.cpp
        src/rendering/opengl/displayables/SpriteGroup.cpp
        src/rendering/opengl/ui/uiElements.cpp

        src/utils/logging/log.cpp
        src/utils/file_io/fileIO.cpp
)

if (WIN32)
    target_sources(LTR_Engine_II PRIVATE
        src/platform/windows.cpp
    )
elseif (UNIX)
    target_sources(LTR_Engine_II PRIVATE
        src/platform/unix.cpp
    )
endif ()

target_include_directories(LTR_Engine_II PRIVATE
        src/game/
        src/game/inputs/
        src/game/inputs/clickables/

        src/physics/

        src/rendering/
        src/rendering/opengl/
        src/rendering/opengl/shading/
        src/rendering/opengl/textures/
        src/rendering/opengl/vao/
        src/rendering/opengl/displayables/
        src/rendering/opengl/ui/

        src/utils/
        src/utils/config/
        src/utils/logging/
        src/utils/file_io/

        src/platform/

        src/third_party/
        src/third_party/glm/
        src/third_party/glm/gtc/
)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(LTR_Engine_II copy_assets)

execute_process(
        COMMAND ${CMAKE_COMMAND} -E environment
)