#ifndef _UTILS_H
#define _UTILS_H


char *       ReadFile(const char *);
void         StrtoArray(const char *, int *, int);
void        _BufferData0( GLenum, GLenum, int, void *);
void        _BufferData1( GLenum, GLenum, int, void *, int, void *);
void        _BufferData2( GLenum, GLenum, int, void *, int, void *, int, void *);

void         CreateTexture( GLenum, GLuint *, unsigned char *, int, int, GLenum);


#define SUBSTRACT_VECTOR(result, Vec1, Vec2) do { \
    result[0] = Vec2[0] - Vec1[0]; \
    result[1] = Vec2[1] - Vec1[1]; \
    result[2] = Vec2[2] - Vec1[2]; \
} while(0)

#define ADD_VECTOR(result, Vec1, Vec2) do { \
    result[0] = Vec2[0] + Vec1[0]; \
    result[1] = Vec2[1] + Vec1[1]; \
    result[2] = Vec2[2] + Vec1[2]; \
} while(0)

#endif