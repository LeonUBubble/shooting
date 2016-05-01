#pragma once 

#include <windows.h>
#include <gl\freeglut.h>
#include <gl\GLAUX.H>
#include "SOIL.h"
#include "Defines.h"
#include "CGame.h"

class CGame;

class  CStaticImages
{
public:
    CStaticImages(CGame* game, int width, int height);
    ~CStaticImages(void);

    void drawStatic(GLuint mask, GLuint image);
    void loadSkyBoxTexture();
    void loadStaticTexture();
    void loadHeightMapTexture();
    void drawGLStatics();
    int drawHealthStatic();

    int w, h;//window width,height

    //static textures
    GLuint statics[10];
    GLuint splash[4];
    GLuint selectClass[4];
    GLuint about[2];
    GLuint health[5];
    GLuint gun[4];
    GLuint endGame[2];
    GLuint skybox[6];
    GLuint heightMapTexture[2];

private:
    CGame* cGame;
       
   

};