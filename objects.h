#ifndef _OBJECT_H
#define _OBJECT_H


#define             RIGHT       0
#define             LEFT        1
#define             BOTTOM      2
#define             TOP         3
#define             BACK        4
#define             FRONT       5


#define             MAX_SHADER  5

typedef struct{
    GLuint          GLSL_Prog[3];
    float           TransRotMatrix[16]; 
    int             Counter;
    GLuint          gTexture;

    void          (*Init)( void *, const char *, const char *);
    void          (*EnableProgram)( void *);
    void          (*DisableProgram)( void *);
    void          (*Release)(void *);

    GLuint        (*GetProgram)( void *);  
    void          (*SetUniform3f)( void *, const char *, float, float, float);
    void          (*SetUniform1f)( void *, const char *, float);
    void          (*SetUniform1i)( void *, const char *, int);

    void          (*gMatrixRotation)( void *, float, float, float, float);
    void          (*gMatrixTranslation)( void *, float, float, float);
    void          (*gPopMatrix)( void *, const char *);

    void          (*LoadTexture)( void *, const char *, const char *, unsigned int *, int);
    void          (*EnableTexture)(void *, GLenum);
    void          (*DisableTexture)(void *);

    GLuint          bufferID[MAX_SHADER];
    GLuint          UBOcount;                       // set for Uniform Buffer Object count
    void          (*uBufferObject)(void *, int, void *, const char *, GLenum);
    void          (*ObjectUpdate)(void *, int , void *, int, int);

}GLSL_PROGRAM;


typedef struct{
    float           Cam[3][3];                      // Camera Pose/View/Upvx
    float           MouseCoord[2];                  // Mouse Coords
    GLfloat         Proj_Matrix[16];                // frustum matrix
    GLfloat         View_Matrix[16];                // Camera matrix
    GLfloat         static_Matrix[16];              // static camera fix to the screen
    GLfloat         Orth_Matrix[16];                // Ortho 2D view
    GLfloat         Proj_View[16];                  // Projection * Camera VIew
    GLfloat         Orth_View[16];                  // Ortho * Camera VIew
    float           gFrustum[6][4];                 // Frustum plane

    void          (*SetProjection)( void *, float, float, float, float, float, float);
    void          (*SetOrthoGraphic)( void *, float, float, float, float, float, float);
    void          (*SetCamera)( void *, float *, float *, float *); 
    void          (*Lookup)( void *);
    void          (*uProjView)( void *, GLuint, const char *);
    void          (*oProjView)( void *, GLuint, const char *);

    void          (*MouseCamera)( void *, float, float);
    void          (*MoveCamera)( void *, float);
    void          (*RotateCamera)( void *, float, float, float, float);
    void          (*StrafeCamera)( void *, float);
    int           (*PointinPlane)( void *, int, float *);
}CAMERA;


typedef struct{
    GLubyte         indices[6];
    float           width;
    float           height;
    float           vertices[12];

    void          (*Render)(void *, float, float);
    void          (*RenderInstances)(void *, float, float, int);
}RECTANGLE;


#endif