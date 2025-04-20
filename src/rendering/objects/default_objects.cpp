//
// Created by simon on 20/04/25.
//

#include "default_objects.h"

#include "default_arrays.h"

#include "glFunctions.h"
#include "Texture.h"


VAO* quad_VAO;
VAO* cube_VAO;

Texture* white_texture;
Texture* farid_texture;

Shader* skybox_shaders[SKYBOX_SHADER_COUNT];
Shader* world_shaders[WORLD_SHADER_COUNT];
Shader* postprocessing_shaders[POSTPROCESSING_SHADER_COUNT];
Shader* ui_shaders[UI_SHADER_COUNT];

void load_default_objects() {
    load_default_VAOs();
    load_default_textures();
    load_default_shaders();

    load_debug_stuff();
}



void load_default_VAOs() {
    GLuint vao_ids[VAO_COUNT];
    GLuint vbo_ids[VAO_COUNT];
    glGenVertexArrays(VAO_COUNT, vao_ids);
    glGenBuffers(VAO_COUNT, vbo_ids);

    quad_VAO = new VAO(vao_ids[VAO_QUAD], vbo_ids[VAO_QUAD], quadVertices, sizeof(quadVertices), VAO_2D_TEXTURE);
    cube_VAO = new VAO(vao_ids[VAO_CUBE], vbo_ids[VAO_QUAD], cubeVertices, sizeof(cubeVertices), VAO_3D);
}

void load_default_textures() {
    GLuint texture_ids[TEX_COUNT];
    glGenTextures(TEX_COUNT, texture_ids);

    white_texture = new Texture(texture_ids[TEX_WHITE], "whiteSquare.png", GL_RGBA);
    farid_texture = new Texture(texture_ids[TEX_FARID], "farid.png", GL_RGBA);
}

void load_default_shaders() {
    world_shaders[WORLD_SHADER_DEFAULT_MESH] = new Shader("default/default_mesh_shader");
    world_shaders[WORLD_SHADER_DEFAULT_SPRITE] = new Shader("default/default_sprite_shader");

    ui_shaders[UI_SHADER_DEFAULT_SPRITE] = new Shader("default/default_sprite_shader");
}



void load_debug_stuff() {

}



