//
// Created by sebas on 24/01/2025.
//

#include "textures.h"

#include "RenderEngine.h"
#include "glFunctions.h"

Texture* faridTexture;
Texture* ltrTexture;
Texture* frameTexture;
Texture* backgroundTexture;
Texture* boardTexture;

Texture* arcueidTexture;
Texture* artoriaTexture;
Texture* astolfoTexture;
Texture* bbdubaiTexture;
Texture* gilgameshTexture;
Texture* kiaraTexture;
Texture* kintokiTexture;
Texture* kukulcanTexture;
Texture* mashTexture;
Texture* medusaTexture;
Texture* melusineTexture;
Texture* merlinTexture;
Texture* nemoMarxTexture;
Texture* nitocrisTexture;
Texture* nobuTexture;
Texture* oberonTexture;
Texture* okitaTexture;
Texture* tanamoTexture;
Texture* ushiwakamaruTexture;
Texture* waverTexture;
Texture* xufuTexture;
Texture* zhouTexture;

Texture* emptyTexture;
Texture* whiteTexture;
Texture* screenBlockerTexture;
Texture* selectionTexture;

void loadTextures() {
    GLuint texture_ids[TEX_COUNT];
    glGenTextures(TEX_COUNT, texture_ids);

    faridTexture = new Texture(texture_ids[TEX_FARID], "farid.png", GL_RGBA);
    ltrTexture = new Texture(texture_ids[TEX_LTR], "LTR.png", GL_RGBA);
    frameTexture = new Texture(texture_ids[TEX_FRAME_TEXTURE], RenderEngine::getMaxWindowSize(), GL_RGB);
    backgroundTexture = new Texture(texture_ids[TEX_BACKGROUND], "background.jpg", GL_RGB);
    boardTexture = new Texture(texture_ids[TEX_BOARD], "board.png", GL_RGBA);

    arcueidTexture = new Texture(texture_ids[TEX_ARCUEID],"characters/arcueid.png",GL_RGBA);
    artoriaTexture = new Texture(texture_ids[TEX_ARTORIA],"characters/artoria.png",GL_RGBA);
    astolfoTexture = new Texture(texture_ids[TEX_ASTOLFO],"characters/astolfo.png",GL_RGBA);
    bbdubaiTexture = new Texture(texture_ids[TEX_BBDUBAI],"characters/bbdubai.png",GL_RGBA);
    gilgameshTexture = new Texture(texture_ids[TEX_GILGAMESH],"characters/gilgamesh.png",GL_RGBA);
    kiaraTexture = new Texture(texture_ids[TEX_KIARA],"characters/kiara.png",GL_RGBA);
    kintokiTexture = new Texture(texture_ids[TEX_KINTOKI],"characters/kintoki.png",GL_RGBA);
    kukulcanTexture = new Texture(texture_ids[TEX_KUKULCAN],"characters/kukulcan.png",GL_RGBA);
    mashTexture = new Texture(texture_ids[TEX_MASH],"characters/mash.png",GL_RGBA);
    medusaTexture = new Texture(texture_ids[TEX_MEDUSA],"characters/medusa.png",GL_RGBA);
    melusineTexture = new Texture(texture_ids[TEX_MELUSINE],"characters/melusine.png",GL_RGBA);
    merlinTexture = new Texture(texture_ids[TEX_MERLIN],"characters/merlin.png",GL_RGBA);
    nemoMarxTexture = new Texture(texture_ids[TEX_NEMO_MARX],"characters/nemo_marx.png",GL_RGBA);
    nitocrisTexture = new Texture(texture_ids[TEX_NITOCRIS],"characters/nitocris.png",GL_RGBA);
    nobuTexture = new Texture(texture_ids[TEX_NOBU],"characters/nobu.png",GL_RGBA);
    oberonTexture = new Texture(texture_ids[TEX_OBERON],"characters/oberon.png",GL_RGBA);
    okitaTexture = new Texture(texture_ids[TEX_OKITA],"characters/okita.png",GL_RGBA);
    tanamoTexture = new Texture(texture_ids[TEX_TANAMO],"characters/tanamo.png",GL_RGBA);
    ushiwakamaruTexture = new Texture(texture_ids[TEX_USHIWAKAMARU],"characters/ushiwakamaru.png",GL_RGBA);
    waverTexture = new Texture(texture_ids[TEX_WAVER],"characters/waver.png",GL_RGBA);
    xufuTexture = new Texture(texture_ids[TEX_XUFU],"characters/xufu.png",GL_RGBA);
    zhouTexture = new Texture(texture_ids[TEX_ZHOU],"characters/zhou.png",GL_RGBA);

    emptyTexture = new Texture(texture_ids[TEX_EMPTY],"emptySquare.png",GL_RGBA);
    whiteTexture = new Texture(texture_ids[TEX_WHITE],"whiteSquare.png",GL_RGBA);
    screenBlockerTexture = new Texture(texture_ids[TEX_SCREEN_BLOCKER],"screenBlocker.png",GL_RGBA);
    selectionTexture = new Texture(texture_ids[TEX_SELECTION],"selectionSquare.png",GL_RGBA);
}
