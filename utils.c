#include "functions.h"


// Expressed as float so gluPerspective division returns a float and not 0 (640/480 != 640.0/480.0).
#define RENDER_WIDTH 800.0
#define RENDER_HEIGHT 600.0
#define SHADOW_MAP_RATIO 2

//Camera position
float p_camera[3] = {32,20,0};
//Camera lookAt
float l_camera[3] = {2,0,-10};
//Light position
float p_light[3] = {3,20,0};

//Light lookAt
float l_light[3] = {0,0,-5};

//Light mouvement circle radius
float light_mvnt = 30.0f;

// Hold id of the framebuffer for light POV rendering
GLuint fboId;

// Z values will be rendered to this texture when using fboId framebuffer
GLuint depthTextureId;

// Use to activate/disable shadowShader
GLhandleARB shadowShaderId;
GLuint shadowMapUniform;


// Loading shader function
GLhandleARB loadShader(char* filename, unsigned int type){
	FILE *pfile;
	GLhandleARB handle;
	const GLcharARB* files[1];
	
	// shader Compilation variable
	GLint result;				// Compilation code result
	GLint errorLoglength ;
	char* errorLogText;
	GLsizei actualErrorLogLength;
	
	char buffer[400000];
	memset(buffer,0,400000);
	
	// This will raise a warning on MS compiler
	pfile = fopen(filename, "rb");
	if(!pfile){
		printf("Sorry, can't open file: '%s'.\n", filename);
		exit(0);
	}
	
	fread(buffer,sizeof(char),400000,pfile);
	fclose(pfile);
	
	handle = glCreateShaderObjectARB(type);
	if (!handle){
		//We have failed creating the vertex shader object.
		printf("Failed creating vertex shader object from file: %s.",filename);
		exit(0);
	}
	
	files[0] = (const GLcharARB*)buffer;
	glShaderSourceARB(  handle, 1, files, NULL);
	glCompileShaderARB(handle);
	
	//Compilation checking.
	glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &result);
	
	// If an error was detected.
	if (!result){		
		printf("Shader '%s' failed compilation.\n",filename);
		glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &errorLoglength);
		errorLogText = malloc(sizeof(char) * errorLoglength);
		glGetInfoLogARB(handle, errorLoglength, &actualErrorLogLength, errorLogText);
		printf("%s\n",errorLogText);
		free(errorLogText);
	}
	
	return handle;
}

void loadShadowShader()
{
	GLhandleARB vertexShaderHandle;
	GLhandleARB fragmentShaderHandle;
	
	vertexShaderHandle   = loadShader("VertexShader.c",GL_VERTEX_SHADER);
	fragmentShaderHandle = loadShader("FragmentShader.c",GL_FRAGMENT_SHADER);
	
	shadowShaderId = glCreateProgramObjectARB();
	
	glAttachObjectARB(shadowShaderId,vertexShaderHandle);
	glAttachObjectARB(shadowShaderId,fragmentShaderHandle);
	glLinkProgramARB(shadowShaderId);
	
	shadowMapUniform = glGetUniformLocationARB(shadowShaderId,"ShadowMap");
}

void generateShadowFBO(){
	int shadowMapWidth = RENDER_WIDTH * SHADOW_MAP_RATIO;
	int shadowMapHeight = RENDER_HEIGHT * SHADOW_MAP_RATIO;
	
	//GLfloat borderColor[4] = {0,0,0,0};
	
	GLenum FBOstatus;
	
	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	//glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );

	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
	
	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);
	
	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,RENDER_WIDTH/RENDER_HEIGHT,10,40000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_x,position_y,position_z,lookAt_x,lookAt_y,lookAt_z,0,1,0);
}


// This update only change the position of the light.
//int elapsedTimeCounter = 0;
float time  = 0.0f;
void update(void)
{
	time += 0.005f;
	p_light[0] = light_mvnt * cos( time);
	p_light[2] = light_mvnt * sin( time);
	
	//p_light[0] = light_mvnt * cos(3652/1000.0);
	//p_light[2] = light_mvnt * sin(3652/1000.0);
}


void setTextureMatrix(void)
{
	static double modelView[16];
	static double projection[16];
	
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5 
	// y = y* 0.5 + 0.5 
	// z = z* 0.5 + 0.5 
	// Moving from unit cube [-1,1] to [0,1]  
	const GLdouble bias[16] = {	
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0};
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();	
	glLoadMatrixd(bias);
	
	// concatating all matrice into one.
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// During translation, we also have to maintain the GL_TEXTURE8, used in the shadow shader
// to determine if a vertex is in the shadow.
void startTranslate(float x,float y,float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	glPushMatrix();
	glTranslatef(x,y,z);
}

void endTranslate(){
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void drawCube(float size) {
    // Define vertices for the cube
    GLfloat vertices[] = {
        -size, -size, -size,
        size, -size, -size,
        size, size, -size,
        -size, size, -size,
        -size, -size, size,
        size, -size, size,
        size, size, size,
        -size, size, size
    };

    // Define the indices (order in which vertices are connected)
    GLuint indices[] = {
        0, 1, 2, 3,   // Front face
        4, 5, 6, 7,   // Back face
        0, 4, 1, 5,   // Left face
        2, 6, 3, 7,   // Right face
        0, 3, 4, 7,   // Top face
        1, 5, 2, 6    // Bottom face
    };

    // Draw the cube
    glBegin(GL_QUADS);
    for (int i = 0; i < 24; i++) {
        glVertex3f(vertices[3 * indices[i]], vertices[3 * indices[i] + 1], vertices[3 * indices[i] + 2]);
    }
    glEnd();
}

void drawObjects(void)
{
	// Ground
	glColor4f(0.3f,0.3f,0.3f,1);
	glBegin(GL_QUADS);
	glVertex3f(-35,2,-35);
	glVertex3f(-35,2, 15);
	glVertex3f( 15,2, 15);
	glVertex3f( 15,2,-35);
	glEnd();
	
	glColor4f(0.9f,0.9f,0.9f,1);
	
	// Instead of calling glTranslatef, we need a custom function that also maintain the light matrix
	startTranslate(0,4,-16);
    drawCube(4); // Draw a cube with a size of 4 units
	// glutSolidCube(4);
	endTranslate();
	
	startTranslate(0,4,-5);
    drawCube(4); // Draw a cube with a size of 4 units
	// glutSolidCube(4);
	endTranslate();
	
	
}

void renderScene(GLFWwindow * window) 
{
	update();
	
	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);	//Rendering offscreen
	
	//Using the fixed pipeline to render to the depthbuffer
	glUseProgramObjectARB(0);
	
	// In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	glViewport(0,0,RENDER_WIDTH * SHADOW_MAP_RATIO,RENDER_HEIGHT* SHADOW_MAP_RATIO);
	
	// Clear previous frame values
	glClear( GL_DEPTH_BUFFER_BIT);
	
	//Disable color rendering, we only want to write to the Z-Buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	
	setupMatrices(p_light[0],p_light[1],p_light[2],l_light[0],l_light[1],l_light[2]);
	
	// Culling switching, rendering only backface, this is done to avoid self-shadowing
	glCullFace(GL_FRONT);
	drawObjects();
	
	//Save modelview/projection matrice into texture7, also add a biais
	setTextureMatrix();
	
	
	// Now rendering from the camera POV, using the FBO to generate shadows
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	
	glViewport(0,0,RENDER_WIDTH,RENDER_HEIGHT);
	
	//Enabling color write (previously disabled for light POV z-buffer rendering)
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	
	// Clear previous frame values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Using the shadow shader
	glUseProgramObjectARB(shadowShaderId);
	glUniform1iARB(shadowMapUniform,7);
	glActiveTextureARB(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,depthTextureId);
	
	
	
	setupMatrices(p_camera[0],p_camera[1],p_camera[2],l_camera[0],l_camera[1],l_camera[2]);
	
	glCullFace(GL_BACK);
	drawObjects();
	
	// glutSwapBuffers();
	glfwPollEvents();	
	glfwSwapBuffers(window);    
}

void processNormalKeys( GLFWwindow * window, unsigned char key, int x, int y) {
	
	if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose( window, 1);
	}
}


void Release() {
    glDeleteFramebuffers(1, &fboId);
    glDeleteTextures(1, &depthTextureId);
    glDeleteProgram(shadowShaderId);
}

