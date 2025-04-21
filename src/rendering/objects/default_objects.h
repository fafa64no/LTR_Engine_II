//
// Created by simon on 20/04/25.
//

#ifndef DEFAULT_OBJECTS_H
#define DEFAULT_OBJECTS_H

#include "VAO.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"



enum vao_type{
    VAO_QUAD,
    VAO_CUBE,

    VAO_COUNT
};

extern VAO* quad_VAO;
extern VAO* cube_VAO;

enum tex_type {
    TEX_WHITE,
    TEX_FARID,

    TEX_COUNT
};

extern Texture* white_texture;
extern Texture* farid_texture;

enum skybox_shader_type {
    SKYBOX_SHADER_COUNT
};

enum world_shader_type {
    WORLD_SHADER_DEFAULT_MESH,
    WORLD_SHADER_DEFAULT_SPRITE,
    WORLD_SHADER_COUNT
};

enum postprocessing_shader_type {
    POSTPROCESSING_SHADER_COUNT
};

enum ui_shader_type {
    UI_SHADER_DEFAULT_SPRITE,
    UI_SHADER_COUNT
};

extern Shader* skybox_shaders[SKYBOX_SHADER_COUNT];
extern Shader* world_shaders[WORLD_SHADER_COUNT];
extern Shader* postprocessing_shaders[POSTPROCESSING_SHADER_COUNT];
extern Shader* ui_shaders[UI_SHADER_COUNT];

extern Camera* free_cam;

void load_default_objects();

void load_default_VAOs();
void load_default_textures();
void load_default_shaders();

void load_default_cameras();

void load_debug_stuff();

#endif //DEFAULT_OBJECTS_H
