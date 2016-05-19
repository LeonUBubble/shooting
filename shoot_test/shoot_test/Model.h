/*Model.h
    Abstract base class for a model. The specific extended calss will render the given model.
*/
#ifndef MODEL_H
#define MODEL_H


#include "matrix.h"
#include "CTimer.h"
#include "Defines.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <gl/GL.h>
#include <GL/GLU.h>

#include<assert.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Vector.h"
#include "SOIL.h"

#pragma comment(lib,"opengl32.lib");
#pragma  comment(lib,"glu32.lib");
#pragma  comment(lib,"glaux.lib");

#define  MAX_STATES 20

class Model
{
public :
    //Mesh ����
    struct Mesh
    {
        int m_materialIndex;//����������-1Ϊû�в���
        int m_numTriangles;//�����е���������Ŀ  
        int *m_pTriangleIndices;//����������
    };

    //��������ͼ
    struct Material
    {
        //�ֱ�Ϊ�����⣬����⣬����⣬�Է���
        float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
        float m_shininess;//����ֵ����ģ���е�Nֵ
        GLuint m_texture;
        char *m_pTextureFilename;//��ͼ�ļ���
    };

    //������
    struct Triangle
    {
        float m_vertexNormals[3][3];//��������ķ���
        float m_s[3], m_t[3];//�洢���������������
        int m_vertexIndices[3];//��������
    };

    //��
    struct Vertex
    {
        char m_boneID;//�ö������󶨵Ĺ�����ID�ţ������ֵΪ-1�������û�а��κι���
        float m_location[3];//���������
    };

    //�ؼ�֡����ʾĳһ֡ʱĳ����������ת֡���ݻ�ƽ��֡����
    struct Keyframe
    {
        int m_jointIndex;
        float m_time;   //���뼶����ʾ��һ֡������ʱ��
        float m_parameter[3];//��һ����ά��������ʾ��ת��ƽ�ơ������ʾƽ�ƣ���ô����ֵ�ֱ���X,Y,Z���ϵ�ƽ��ֵ�������ʾ��ת����ô����ֵ��ʾ��ת��ŷ����
    };

    //�ؽ�
    struct Joint
    {
        float m_localRotation[3];//��ʼ��ת
        float m_localTranslation[3];//��ʼƽ��
        Matrix m_absolute, m_relative;//���Ծ�������Ծ���

        //����������ת֡������ƽ��֡����
        int m_numRotationKeyframes,m_numTranslationKeyframes;
        Keyframe *m_pTranslationKeyframes;//��������������ת֡����
        Keyframe *m_pRotationKeyframes;//������������ƽ��֡����
        
        //���Կ�����ʱ����
        int m_currentTranslationKeyframe, m_currentRotationKeyframe;
        Matrix m_final;

        int m_parent;//�������ĸ�����
    };

public :
    Model();

    virtual ~Model();

    virtual bool loadModelData(const char *filename) = 0;

    void draw();

    /*Called if OpenGL context was lost and we need to reload textures, display lists
    ����·�����ڴ�*/
    void reloadTextures();

    void setState(int newState);

    void addState(int start, int length, int loop)
    {
        states[num_states][0] = start;
        states[num_states][1] = length;
        states[num_states][2] = loop;
        num_states++;
    };
    void setSuite(int newSuit)
    {
        suit = newSuit;
    };

    int getSuite()
    {
        return suit;
    };
    
    bool noAnimation()
    {
        return state == NO_ANIMATION;
    };
    void setVisible(bool visibility)
    {
        visible = visibility;
    };
    bool getVisible()
    {
        return visible;
    }

protected:
    /*
    Set the values of a particular keyframe for a particular joint.
    jointIndex		The joint to setup the keyframe for
    keyframeIndex	The maximum number of keyframes
    time			The time in milliseconds of the keyframe
    parameter		The rotation/translation values for the keyframe
    isRotation		Whether it is a rotation or a translation keyframe
    */
    void setJointKeyframe(int jointIndex, int keyframeIndex, float time, float *parameter, bool isRotation);

    /*Setup joint matrices. ��ʼ��������󶨽ڵ�*/
    void setupJoints();

    /*Setup looping factor for animation*/
    void setLooping(bool looping){
        m_looping = looping;
    }

    /*Advance animation by a frame.���ݶ����Ĺؼ�֡������ȷ��˳��������нڵ㣬���Ҹ���ǰһ���ڵ�任��ľ�����Դ˽ڵ��ǰһ���ڵ����Ա仯����ô����ˢ�����й�����λ��*/
    void advanceAnimation();

    void restart();

protected:
    //Meshes used
    int m_numMeshes;
    Mesh *m_pMeshes;
    
    //Materials used
    int m_numMaterials;
    Material *m_pMaterials;

    //Triangles used
    int m_numTriangles;
    Triangle *m_pTriangles;

    //Vertices used
    int m_numVertices;
    Vertex *m_pVertices;

    //Joints used
    int m_numJoints;
    Joint *m_pJoints;

    Timer *m_pTimer;

    double m_totalTime;

    bool m_looping;

    //current state of model
    int state;

    //number of states
    int num_states;

    //state description
    int states[MAX_STATES][3];//start of animation and length of animation

    //suit :)
    int suit;

    float FPS;

    bool visible;
       
};

#endif // ndef MODEL_H

