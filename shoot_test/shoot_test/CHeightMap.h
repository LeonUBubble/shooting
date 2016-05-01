#pragma  once
#include <windows.h>
#include <gl\freeglut.h>
#include <gl\GLAUX.H>
#include "glext.h"
#include <math.h>
#include <iostream>
#include "SOIL.h"
#include "Defines.h"

using namespace std;

class CHeightMap
{
public:
    CHeightMap(void);
    ~CHeightMap(void);

    //Heightmap rendering functions
    void renderHeightmap(PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fvARB, PFNGLACTIVETEXTUREARBPROC glActiveTextureARB, GLint* heightMapTexture);
    int Height(int X, int Y);
    void SetVertexColor(int x, int y);
    void SetupTexture(bool draw_TexturedTerrain, bool splash_screen, int x, int y, int i);

private:
    //Heightmap storage
    unsigned char* g_HeightMap;

};