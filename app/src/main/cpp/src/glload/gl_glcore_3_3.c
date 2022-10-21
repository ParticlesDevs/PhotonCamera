#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "gl_glcore_3_3.h"

#if defined(__APPLE__)
#include <dlfcn.h>

static void* AppleGLGetProcAddress (const char *name)
{
	static void* image = NULL;

	if (NULL == image)
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

	return (image ? dlsym(image, name) : NULL);
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32) && 0

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#pragma warning(disable: 4996)
#endif

static int TestPointer(const PROC pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;

	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;

	return 1;
}

static PROC WinGetProcAddress(const char *name)
{
	HMODULE glMod = NULL;
	PROC pFunc = wglGetProcAddress((LPCSTR)name);
	if(TestPointer(pFunc))
	{
		return pFunc;
	}
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}

#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
	#if defined(__APPLE__)
		#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define IntGetProcAddress(name) SunGetProcAddress(name)
		#else /* SDL */
      #include <SDL2/SDL_video.h>
      #define IntGetProcAddress(name) SDL_GL_GetProcAddress(name)
		#endif
	#endif
#endif


/* Extension: 1.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFunc(GLenum sfactor, GLenum dfactor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_Clear(GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARDEPTHPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_ClearDepth(GLdouble depth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARSTENCILPROC)(GLint);
static void CODEGEN_FUNCPTR Switch_ClearStencil(GLint s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORMASKPROC)(GLboolean, GLboolean, GLboolean, GLboolean);
static void CODEGEN_FUNCPTR Switch_ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCULLFACEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_CullFace(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHFUNCPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_DepthFunc(GLenum func);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHMASKPROC)(GLboolean);
static void CODEGEN_FUNCPTR Switch_DepthMask(GLboolean flag);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHRANGEPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_DepthRange(GLdouble ren_near, GLdouble ren_far);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_Disable(GLenum cap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWBUFFERPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_DrawBuffer(GLenum buf);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_Enable(GLenum cap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFINISHPROC)(void);
static void CODEGEN_FUNCPTR Switch_Finish(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFLUSHPROC)(void);
static void CODEGEN_FUNCPTR Switch_Flush(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRONTFACEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_FrontFace(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBOOLEANVPROC)(GLenum, GLboolean *);
static void CODEGEN_FUNCPTR Switch_GetBooleanv(GLenum pname, GLboolean * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETDOUBLEVPROC)(GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetDoublev(GLenum pname, GLdouble * data);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLGETERRORPROC)(void);
static GLenum CODEGEN_FUNCPTR Switch_GetError(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFLOATVPROC)(GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetFloatv(GLenum pname, GLfloat * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGERVPROC)(GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetIntegerv(GLenum pname, GLint * data);
typedef const GLubyte * (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSTRINGPROC)(GLenum);
static const GLubyte * CODEGEN_FUNCPTR Switch_GetString(GLenum name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXIMAGEPROC)(GLenum, GLint, GLenum, GLenum, void *);
static void CODEGEN_FUNCPTR Switch_GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC)(GLenum, GLint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC)(GLenum, GLint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameteriv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLHINTPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_Hint(GLenum target, GLenum mode);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISENABLEDPROC)(GLenum);
static GLboolean CODEGEN_FUNCPTR Switch_IsEnabled(GLenum cap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLINEWIDTHPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_LineWidth(GLfloat width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOGICOPPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_LogicOp(GLenum opcode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELSTOREFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_PixelStoref(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELSTOREIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PixelStorei(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTSIZEPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_PointSize(GLfloat size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOLYGONMODEPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_PolygonMode(GLenum face, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLREADBUFFERPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ReadBuffer(GLenum src);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLREADPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
static void CODEGEN_FUNCPTR Switch_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCISSORPROC)(GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILFUNCPROC)(GLenum, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilFunc(GLenum func, GLint ref, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILMASKPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_StencilMask(GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILOPPROC)(GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexParameterf(GLenum target, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexParameterfv(GLenum target, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_TexParameteri(GLenum target, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexParameteriv(GLenum target, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_Viewport(GLint x, GLint y, GLsizei width, GLsizei height);

/* Extension: 1.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDTEXTUREPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindTexture(GLenum target, GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETETEXTURESPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteTextures(GLsizei n, const GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawArrays(GLenum mode, GLint first, GLsizei count);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENTEXTURESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenTextures(GLsizei n, GLuint * textures);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISTEXTUREPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsTexture(GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOLYGONOFFSETPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_PolygonOffset(GLfloat factor, GLfloat units);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);

/* Extension: 1.2*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWRANGEELEMENTSPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE3DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);

/* Extension: 1.3*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLACTIVETEXTUREPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ActiveTexture(GLenum texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, void *);
static void CODEGEN_FUNCPTR Switch_GetCompressedTexImage(GLenum target, GLint level, void * img);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLECOVERAGEPROC)(GLfloat, GLboolean);
static void CODEGEN_FUNCPTR Switch_SampleCoverage(GLfloat value, GLboolean invert);

/* Extension: 1.4*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquation(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWARRAYSPROC)(GLenum, const GLint *, const GLsizei *, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWELEMENTSPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_PointParameterf(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERFVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_PointParameterfv(GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PointParameteri(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERIVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_PointParameteriv(GLenum pname, const GLint * params);

/* Extension: 1.5*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINQUERYPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BeginQuery(GLenum target, GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindBuffer(GLenum target, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void *, GLenum);
static void CODEGEN_FUNCPTR Switch_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, const void *);
static void CODEGEN_FUNCPTR Switch_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteBuffers(GLsizei n, const GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEQUERIESPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteQueries(GLsizei n, const GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDQUERYPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_EndQuery(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenBuffers(GLsizei n, GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENQUERIESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenQueries(GLsizei n, GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPOINTERVPROC)(GLenum, GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetBufferPointerv(GLenum target, GLenum pname, void ** params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, void *);
static void CODEGEN_FUNCPTR Switch_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetQueryiv(GLenum target, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsBuffer(GLuint buffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISQUERYPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsQuery(GLuint id);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPBUFFERPROC)(GLenum, GLenum);
static void * CODEGEN_FUNCPTR Switch_MapBuffer(GLenum target, GLenum access);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLUNMAPBUFFERPROC)(GLenum);
static GLboolean CODEGEN_FUNCPTR Switch_UnmapBuffer(GLenum target);

/* Extension: 2.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLATTACHSHADERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_AttachShader(GLuint program, GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDATTRIBLOCATIONPROC)(GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindAttribLocation(GLuint program, GLuint index, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPILESHADERPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_CompileShader(GLuint shader);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEPROGRAMPROC)(void);
static GLuint CODEGEN_FUNCPTR Switch_CreateProgram(void);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATESHADERPROC)(GLenum);
static GLuint CODEGEN_FUNCPTR Switch_CreateShader(GLenum type);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DeleteProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESHADERPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DeleteShader(GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDETACHSHADERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_DetachShader(GLuint program, GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DisableVertexAttribArray(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWBUFFERSPROC)(GLsizei, const GLenum *);
static void CODEGEN_FUNCPTR Switch_DrawBuffers(GLsizei n, const GLenum * bufs);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_EnableVertexAttribArray(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEATTRIBPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETATTACHEDSHADERSPROC)(GLuint, GLsizei, GLsizei *, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETATTRIBLOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetAttribLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramiv(GLuint program, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERSOURCEPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetShaderiv(GLuint shader, GLenum pname, GLint * params);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetUniformLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMFVPROC)(GLuint, GLint, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetUniformfv(GLuint program, GLint location, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMIVPROC)(GLuint, GLint, GLint *);
static void CODEGEN_FUNCPTR Switch_GetUniformiv(GLuint program, GLint location, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC)(GLuint, GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBDVPROC)(GLuint, GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBFVPROC)(GLuint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribiv(GLuint index, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISPROGRAMPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsProgram(GLuint program);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSHADERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsShader(GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLINKPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_LinkProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar *const*, const GLint *);
static void CODEGEN_FUNCPTR Switch_ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILFUNCSEPARATEPROC)(GLenum, GLenum, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILMASKSEPARATEPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilMaskSeparate(GLenum face, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILOPSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1FPROC)(GLint, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform1f(GLint location, GLfloat v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform1fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform1i(GLint location, GLint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform1iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2FPROC)(GLint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform2f(GLint location, GLfloat v0, GLfloat v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform2fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform2i(GLint location, GLint v0, GLint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform2iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform3fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform3iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform4fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4IPROC)(GLint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform4iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUSEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_UseProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVALIDATEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_ValidateProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1DPROC)(GLuint, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1d(GLuint index, GLdouble x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1FPROC)(GLuint, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1f(GLuint index, GLfloat x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1SPROC)(GLuint, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1s(GLuint index, GLshort x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2DPROC)(GLuint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2FPROC)(GLuint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2SPROC)(GLuint, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2s(GLuint index, GLshort x, GLshort y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3FPROC)(GLuint, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3SPROC)(GLuint, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NBVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nbv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NIVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Niv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NSVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nsv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUBPROC)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nuiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUSVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nusv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4BVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4bv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4FPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4SPROC)(GLuint, GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4UBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4ubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4USVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4usv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

/* Extension: 2.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);

/* Extension: 3.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINCONDITIONALRENDERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_BeginConditionalRender(GLuint id, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_BeginTransformFeedback(GLenum primitiveMode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERBASEPROC)(GLenum, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BindBufferBase(GLenum target, GLuint index, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERRANGEPROC)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAGDATALOCATIONPROC)(GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindFragDataLocation(GLuint program, GLuint color, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAMEBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindFramebuffer(GLenum target, GLuint framebuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDRENDERBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindRenderbuffer(GLenum target, GLuint renderbuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDVERTEXARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_BindVertexArray(GLuint ren_array);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLITFRAMEBUFFERPROC)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
static void CODEGEN_FUNCPTR Switch_BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
static GLenum CODEGEN_FUNCPTR Switch_CheckFramebufferStatus(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLAMPCOLORPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_ClampColor(GLenum target, GLenum clamp);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERFIPROC)(GLenum, GLint, GLfloat, GLint);
static void CODEGEN_FUNCPTR Switch_ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERFVPROC)(GLenum, GLint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERIVPROC)(GLenum, GLint, const GLint *);
static void CODEGEN_FUNCPTR Switch_ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERUIVPROC)(GLenum, GLint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORMASKIPROC)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
static void CODEGEN_FUNCPTR Switch_ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEFRAMEBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETERENDERBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteVertexArrays(GLsizei n, const GLuint * arrays);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEIPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_Disablei(GLenum target, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEIPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_Enablei(GLenum target, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDCONDITIONALRENDERPROC)(void);
static void CODEGEN_FUNCPTR Switch_EndConditionalRender(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC)(void);
static void CODEGEN_FUNCPTR Switch_EndTransformFeedback(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC)(GLenum, GLenum, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC)(GLenum, GLenum, GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENFRAMEBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenFramebuffers(GLsizei n, GLuint * framebuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENRENDERBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenRenderbuffers(GLsizei n, GLuint * renderbuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENVERTEXARRAYSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenVertexArrays(GLsizei n, GLuint * arrays);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENERATEMIPMAPPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_GenerateMipmap(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBOOLEANI_VPROC)(GLenum, GLuint, GLboolean *);
static void CODEGEN_FUNCPTR Switch_GetBooleani_v(GLenum target, GLuint index, GLboolean * data);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAGDATALOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetFragDataLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum, GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGERI_VPROC)(GLenum, GLuint, GLint *);
static void CODEGEN_FUNCPTR Switch_GetIntegeri_v(GLenum target, GLuint index, GLint * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
typedef const GLubyte * (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSTRINGIPROC)(GLenum, GLuint);
static const GLubyte * CODEGEN_FUNCPTR Switch_GetStringi(GLenum name, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterIiv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIUIVPROC)(GLenum, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMUIVPROC)(GLuint, GLint, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetUniformuiv(GLuint program, GLint location, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISENABLEDIPROC)(GLenum, GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsEnabledi(GLenum target, GLuint index);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISFRAMEBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsFramebuffer(GLuint framebuffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISRENDERBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsRenderbuffer(GLuint renderbuffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISVERTEXARRAYPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsVertexArray(GLuint ren_array);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
static void * CODEGEN_FUNCPTR Switch_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRENDERBUFFERSTORAGEPROC)(GLenum, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexParameterIiv(GLenum target, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIUIVPROC)(GLenum, GLenum, const GLuint *);
static void CODEGEN_FUNCPTR Switch_TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint, GLsizei, const GLchar *const*, GLenum);
static void CODEGEN_FUNCPTR Switch_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1UIPROC)(GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform1ui(GLint location, GLuint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform1uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2UIPROC)(GLint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform2ui(GLint location, GLuint v0, GLuint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform2uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3UIPROC)(GLint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform3uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4UIPROC)(GLint, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform4uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1IPROC)(GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1i(GLuint index, GLint x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1UIPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1ui(GLuint index, GLuint x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2IPROC)(GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2i(GLuint index, GLint x, GLint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2UIPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2ui(GLuint index, GLuint x, GLuint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3IPROC)(GLuint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3UIPROC)(GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4BVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4bv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4IPROC)(GLuint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4ubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UIPROC)(GLuint, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4USVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4usv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);

/* Extension: 3.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYBUFFERSUBDATAPROC)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC)(GLenum, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC)(GLuint, const GLchar *);
static GLuint CODEGEN_FUNCPTR Switch_GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMINDICESPROC)(GLuint, GLsizei, const GLchar *const*, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_PrimitiveRestartIndex(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXBUFFERPROC)(GLenum, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_TexBuffer(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

/* Extension: 3.2*/
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLCLIENTWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
static GLenum CODEGEN_FUNCPTR Switch_ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESYNCPROC)(GLsync);
static void CODEGEN_FUNCPTR Switch_DeleteSync(GLsync sync);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLint);
static void CODEGEN_FUNCPTR Switch_DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
static void CODEGEN_FUNCPTR Switch_DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef GLsync (CODEGEN_FUNCPTR *PFN_PTRC_GLFENCESYNCPROC)(GLenum, GLbitfield);
static GLsync CODEGEN_FUNCPTR Switch_FenceSync(GLenum condition, GLbitfield flags);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC)(GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC)(GLenum, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGER64I_VPROC)(GLenum, GLuint, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetInteger64i_v(GLenum target, GLuint index, GLint64 * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGER64VPROC)(GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetInteger64v(GLenum pname, GLint64 * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMULTISAMPLEFVPROC)(GLenum, GLuint, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSYNCIVPROC)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSYNCPROC)(GLsync);
static GLboolean CODEGEN_FUNCPTR Switch_IsSync(GLsync sync);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROVOKINGVERTEXPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ProvokingVertex(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLEMASKIPROC)(GLuint, GLbitfield);
static void CODEGEN_FUNCPTR Switch_SampleMaski(GLuint maskNumber, GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
static void CODEGEN_FUNCPTR Switch_WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);

/* Extension: 3.3*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint, GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDSAMPLERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BindSampler(GLuint unit, GLuint sampler);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESAMPLERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteSamplers(GLsizei count, const GLuint * samplers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENSAMPLERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenSamplers(GLsizei count, GLuint * samplers);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAGDATAINDEXPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetFragDataIndex(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTI64VPROC)(GLuint, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTUI64VPROC)(GLuint, GLenum, GLuint64 *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC)(GLuint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSAMPLERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsSampler(GLuint sampler);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLQUERYCOUNTERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_QueryCounter(GLuint id, GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, const GLuint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERFPROC)(GLuint, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERFVPROC)(GLuint, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIPROC)(GLuint, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_SamplerParameteri(GLuint sampler, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBDIVISORPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribDivisor(GLuint index, GLuint divisor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP1UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP1UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP2UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP2UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP3UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP3UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP4UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP4UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);


/* Extension: 1.0*/
PFN_PTRC_GLBLENDFUNCPROC _ptrc_glBlendFunc = Switch_BlendFunc;
PFN_PTRC_GLCLEARPROC _ptrc_glClear = Switch_Clear;
PFN_PTRC_GLCLEARCOLORPROC _ptrc_glClearColor = Switch_ClearColor;
PFN_PTRC_GLCLEARDEPTHPROC _ptrc_glClearDepth = Switch_ClearDepth;
PFN_PTRC_GLCLEARSTENCILPROC _ptrc_glClearStencil = Switch_ClearStencil;
PFN_PTRC_GLCOLORMASKPROC _ptrc_glColorMask = Switch_ColorMask;
PFN_PTRC_GLCULLFACEPROC _ptrc_glCullFace = Switch_CullFace;
PFN_PTRC_GLDEPTHFUNCPROC _ptrc_glDepthFunc = Switch_DepthFunc;
PFN_PTRC_GLDEPTHMASKPROC _ptrc_glDepthMask = Switch_DepthMask;
PFN_PTRC_GLDEPTHRANGEPROC _ptrc_glDepthRange = Switch_DepthRange;
PFN_PTRC_GLDISABLEPROC _ptrc_glDisable = Switch_Disable;
PFN_PTRC_GLDRAWBUFFERPROC _ptrc_glDrawBuffer = Switch_DrawBuffer;
PFN_PTRC_GLENABLEPROC _ptrc_glEnable = Switch_Enable;
PFN_PTRC_GLFINISHPROC _ptrc_glFinish = Switch_Finish;
PFN_PTRC_GLFLUSHPROC _ptrc_glFlush = Switch_Flush;
PFN_PTRC_GLFRONTFACEPROC _ptrc_glFrontFace = Switch_FrontFace;
PFN_PTRC_GLGETBOOLEANVPROC _ptrc_glGetBooleanv = Switch_GetBooleanv;
PFN_PTRC_GLGETDOUBLEVPROC _ptrc_glGetDoublev = Switch_GetDoublev;
PFN_PTRC_GLGETERRORPROC _ptrc_glGetError = Switch_GetError;
PFN_PTRC_GLGETFLOATVPROC _ptrc_glGetFloatv = Switch_GetFloatv;
PFN_PTRC_GLGETINTEGERVPROC _ptrc_glGetIntegerv = Switch_GetIntegerv;
PFN_PTRC_GLGETSTRINGPROC _ptrc_glGetString = Switch_GetString;
PFN_PTRC_GLGETTEXIMAGEPROC _ptrc_glGetTexImage = Switch_GetTexImage;
PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC _ptrc_glGetTexLevelParameterfv = Switch_GetTexLevelParameterfv;
PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC _ptrc_glGetTexLevelParameteriv = Switch_GetTexLevelParameteriv;
PFN_PTRC_GLGETTEXPARAMETERFVPROC _ptrc_glGetTexParameterfv = Switch_GetTexParameterfv;
PFN_PTRC_GLGETTEXPARAMETERIVPROC _ptrc_glGetTexParameteriv = Switch_GetTexParameteriv;
PFN_PTRC_GLHINTPROC _ptrc_glHint = Switch_Hint;
PFN_PTRC_GLISENABLEDPROC _ptrc_glIsEnabled = Switch_IsEnabled;
PFN_PTRC_GLLINEWIDTHPROC _ptrc_glLineWidth = Switch_LineWidth;
PFN_PTRC_GLLOGICOPPROC _ptrc_glLogicOp = Switch_LogicOp;
PFN_PTRC_GLPIXELSTOREFPROC _ptrc_glPixelStoref = Switch_PixelStoref;
PFN_PTRC_GLPIXELSTOREIPROC _ptrc_glPixelStorei = Switch_PixelStorei;
PFN_PTRC_GLPOINTSIZEPROC _ptrc_glPointSize = Switch_PointSize;
PFN_PTRC_GLPOLYGONMODEPROC _ptrc_glPolygonMode = Switch_PolygonMode;
PFN_PTRC_GLREADBUFFERPROC _ptrc_glReadBuffer = Switch_ReadBuffer;
PFN_PTRC_GLREADPIXELSPROC _ptrc_glReadPixels = Switch_ReadPixels;
PFN_PTRC_GLSCISSORPROC _ptrc_glScissor = Switch_Scissor;
PFN_PTRC_GLSTENCILFUNCPROC _ptrc_glStencilFunc = Switch_StencilFunc;
PFN_PTRC_GLSTENCILMASKPROC _ptrc_glStencilMask = Switch_StencilMask;
PFN_PTRC_GLSTENCILOPPROC _ptrc_glStencilOp = Switch_StencilOp;
PFN_PTRC_GLTEXIMAGE1DPROC _ptrc_glTexImage1D = Switch_TexImage1D;
PFN_PTRC_GLTEXIMAGE2DPROC _ptrc_glTexImage2D = Switch_TexImage2D;
PFN_PTRC_GLTEXPARAMETERFPROC _ptrc_glTexParameterf = Switch_TexParameterf;
PFN_PTRC_GLTEXPARAMETERFVPROC _ptrc_glTexParameterfv = Switch_TexParameterfv;
PFN_PTRC_GLTEXPARAMETERIPROC _ptrc_glTexParameteri = Switch_TexParameteri;
PFN_PTRC_GLTEXPARAMETERIVPROC _ptrc_glTexParameteriv = Switch_TexParameteriv;
PFN_PTRC_GLVIEWPORTPROC _ptrc_glViewport = Switch_Viewport;

/* Extension: 1.1*/
PFN_PTRC_GLBINDTEXTUREPROC _ptrc_glBindTexture = Switch_BindTexture;
PFN_PTRC_GLCOPYTEXIMAGE1DPROC _ptrc_glCopyTexImage1D = Switch_CopyTexImage1D;
PFN_PTRC_GLCOPYTEXIMAGE2DPROC _ptrc_glCopyTexImage2D = Switch_CopyTexImage2D;
PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC _ptrc_glCopyTexSubImage1D = Switch_CopyTexSubImage1D;
PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC _ptrc_glCopyTexSubImage2D = Switch_CopyTexSubImage2D;
PFN_PTRC_GLDELETETEXTURESPROC _ptrc_glDeleteTextures = Switch_DeleteTextures;
PFN_PTRC_GLDRAWARRAYSPROC _ptrc_glDrawArrays = Switch_DrawArrays;
PFN_PTRC_GLDRAWELEMENTSPROC _ptrc_glDrawElements = Switch_DrawElements;
PFN_PTRC_GLGENTEXTURESPROC _ptrc_glGenTextures = Switch_GenTextures;
PFN_PTRC_GLISTEXTUREPROC _ptrc_glIsTexture = Switch_IsTexture;
PFN_PTRC_GLPOLYGONOFFSETPROC _ptrc_glPolygonOffset = Switch_PolygonOffset;
PFN_PTRC_GLTEXSUBIMAGE1DPROC _ptrc_glTexSubImage1D = Switch_TexSubImage1D;
PFN_PTRC_GLTEXSUBIMAGE2DPROC _ptrc_glTexSubImage2D = Switch_TexSubImage2D;

/* Extension: 1.2*/
PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC _ptrc_glCopyTexSubImage3D = Switch_CopyTexSubImage3D;
PFN_PTRC_GLDRAWRANGEELEMENTSPROC _ptrc_glDrawRangeElements = Switch_DrawRangeElements;
PFN_PTRC_GLTEXIMAGE3DPROC _ptrc_glTexImage3D = Switch_TexImage3D;
PFN_PTRC_GLTEXSUBIMAGE3DPROC _ptrc_glTexSubImage3D = Switch_TexSubImage3D;

/* Extension: 1.3*/
PFN_PTRC_GLACTIVETEXTUREPROC _ptrc_glActiveTexture = Switch_ActiveTexture;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC _ptrc_glCompressedTexImage1D = Switch_CompressedTexImage1D;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC _ptrc_glCompressedTexImage2D = Switch_CompressedTexImage2D;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC _ptrc_glCompressedTexImage3D = Switch_CompressedTexImage3D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC _ptrc_glCompressedTexSubImage1D = Switch_CompressedTexSubImage1D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC _ptrc_glCompressedTexSubImage2D = Switch_CompressedTexSubImage2D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC _ptrc_glCompressedTexSubImage3D = Switch_CompressedTexSubImage3D;
PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC _ptrc_glGetCompressedTexImage = Switch_GetCompressedTexImage;
PFN_PTRC_GLSAMPLECOVERAGEPROC _ptrc_glSampleCoverage = Switch_SampleCoverage;

/* Extension: 1.4*/
PFN_PTRC_GLBLENDCOLORPROC _ptrc_glBlendColor = Switch_BlendColor;
PFN_PTRC_GLBLENDEQUATIONPROC _ptrc_glBlendEquation = Switch_BlendEquation;
PFN_PTRC_GLBLENDFUNCSEPARATEPROC _ptrc_glBlendFuncSeparate = Switch_BlendFuncSeparate;
PFN_PTRC_GLMULTIDRAWARRAYSPROC _ptrc_glMultiDrawArrays = Switch_MultiDrawArrays;
PFN_PTRC_GLMULTIDRAWELEMENTSPROC _ptrc_glMultiDrawElements = Switch_MultiDrawElements;
PFN_PTRC_GLPOINTPARAMETERFPROC _ptrc_glPointParameterf = Switch_PointParameterf;
PFN_PTRC_GLPOINTPARAMETERFVPROC _ptrc_glPointParameterfv = Switch_PointParameterfv;
PFN_PTRC_GLPOINTPARAMETERIPROC _ptrc_glPointParameteri = Switch_PointParameteri;
PFN_PTRC_GLPOINTPARAMETERIVPROC _ptrc_glPointParameteriv = Switch_PointParameteriv;

/* Extension: 1.5*/
PFN_PTRC_GLBEGINQUERYPROC _ptrc_glBeginQuery = Switch_BeginQuery;
PFN_PTRC_GLBINDBUFFERPROC _ptrc_glBindBuffer = Switch_BindBuffer;
PFN_PTRC_GLBUFFERDATAPROC _ptrc_glBufferData = Switch_BufferData;
PFN_PTRC_GLBUFFERSUBDATAPROC _ptrc_glBufferSubData = Switch_BufferSubData;
PFN_PTRC_GLDELETEBUFFERSPROC _ptrc_glDeleteBuffers = Switch_DeleteBuffers;
PFN_PTRC_GLDELETEQUERIESPROC _ptrc_glDeleteQueries = Switch_DeleteQueries;
PFN_PTRC_GLENDQUERYPROC _ptrc_glEndQuery = Switch_EndQuery;
PFN_PTRC_GLGENBUFFERSPROC _ptrc_glGenBuffers = Switch_GenBuffers;
PFN_PTRC_GLGENQUERIESPROC _ptrc_glGenQueries = Switch_GenQueries;
PFN_PTRC_GLGETBUFFERPARAMETERIVPROC _ptrc_glGetBufferParameteriv = Switch_GetBufferParameteriv;
PFN_PTRC_GLGETBUFFERPOINTERVPROC _ptrc_glGetBufferPointerv = Switch_GetBufferPointerv;
PFN_PTRC_GLGETBUFFERSUBDATAPROC _ptrc_glGetBufferSubData = Switch_GetBufferSubData;
PFN_PTRC_GLGETQUERYOBJECTIVPROC _ptrc_glGetQueryObjectiv = Switch_GetQueryObjectiv;
PFN_PTRC_GLGETQUERYOBJECTUIVPROC _ptrc_glGetQueryObjectuiv = Switch_GetQueryObjectuiv;
PFN_PTRC_GLGETQUERYIVPROC _ptrc_glGetQueryiv = Switch_GetQueryiv;
PFN_PTRC_GLISBUFFERPROC _ptrc_glIsBuffer = Switch_IsBuffer;
PFN_PTRC_GLISQUERYPROC _ptrc_glIsQuery = Switch_IsQuery;
PFN_PTRC_GLMAPBUFFERPROC _ptrc_glMapBuffer = Switch_MapBuffer;
PFN_PTRC_GLUNMAPBUFFERPROC _ptrc_glUnmapBuffer = Switch_UnmapBuffer;

/* Extension: 2.0*/
PFN_PTRC_GLATTACHSHADERPROC _ptrc_glAttachShader = Switch_AttachShader;
PFN_PTRC_GLBINDATTRIBLOCATIONPROC _ptrc_glBindAttribLocation = Switch_BindAttribLocation;
PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC _ptrc_glBlendEquationSeparate = Switch_BlendEquationSeparate;
PFN_PTRC_GLCOMPILESHADERPROC _ptrc_glCompileShader = Switch_CompileShader;
PFN_PTRC_GLCREATEPROGRAMPROC _ptrc_glCreateProgram = Switch_CreateProgram;
PFN_PTRC_GLCREATESHADERPROC _ptrc_glCreateShader = Switch_CreateShader;
PFN_PTRC_GLDELETEPROGRAMPROC _ptrc_glDeleteProgram = Switch_DeleteProgram;
PFN_PTRC_GLDELETESHADERPROC _ptrc_glDeleteShader = Switch_DeleteShader;
PFN_PTRC_GLDETACHSHADERPROC _ptrc_glDetachShader = Switch_DetachShader;
PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC _ptrc_glDisableVertexAttribArray = Switch_DisableVertexAttribArray;
PFN_PTRC_GLDRAWBUFFERSPROC _ptrc_glDrawBuffers = Switch_DrawBuffers;
PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC _ptrc_glEnableVertexAttribArray = Switch_EnableVertexAttribArray;
PFN_PTRC_GLGETACTIVEATTRIBPROC _ptrc_glGetActiveAttrib = Switch_GetActiveAttrib;
PFN_PTRC_GLGETACTIVEUNIFORMPROC _ptrc_glGetActiveUniform = Switch_GetActiveUniform;
PFN_PTRC_GLGETATTACHEDSHADERSPROC _ptrc_glGetAttachedShaders = Switch_GetAttachedShaders;
PFN_PTRC_GLGETATTRIBLOCATIONPROC _ptrc_glGetAttribLocation = Switch_GetAttribLocation;
PFN_PTRC_GLGETPROGRAMINFOLOGPROC _ptrc_glGetProgramInfoLog = Switch_GetProgramInfoLog;
PFN_PTRC_GLGETPROGRAMIVPROC _ptrc_glGetProgramiv = Switch_GetProgramiv;
PFN_PTRC_GLGETSHADERINFOLOGPROC _ptrc_glGetShaderInfoLog = Switch_GetShaderInfoLog;
PFN_PTRC_GLGETSHADERSOURCEPROC _ptrc_glGetShaderSource = Switch_GetShaderSource;
PFN_PTRC_GLGETSHADERIVPROC _ptrc_glGetShaderiv = Switch_GetShaderiv;
PFN_PTRC_GLGETUNIFORMLOCATIONPROC _ptrc_glGetUniformLocation = Switch_GetUniformLocation;
PFN_PTRC_GLGETUNIFORMFVPROC _ptrc_glGetUniformfv = Switch_GetUniformfv;
PFN_PTRC_GLGETUNIFORMIVPROC _ptrc_glGetUniformiv = Switch_GetUniformiv;
PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC _ptrc_glGetVertexAttribPointerv = Switch_GetVertexAttribPointerv;
PFN_PTRC_GLGETVERTEXATTRIBDVPROC _ptrc_glGetVertexAttribdv = Switch_GetVertexAttribdv;
PFN_PTRC_GLGETVERTEXATTRIBFVPROC _ptrc_glGetVertexAttribfv = Switch_GetVertexAttribfv;
PFN_PTRC_GLGETVERTEXATTRIBIVPROC _ptrc_glGetVertexAttribiv = Switch_GetVertexAttribiv;
PFN_PTRC_GLISPROGRAMPROC _ptrc_glIsProgram = Switch_IsProgram;
PFN_PTRC_GLISSHADERPROC _ptrc_glIsShader = Switch_IsShader;
PFN_PTRC_GLLINKPROGRAMPROC _ptrc_glLinkProgram = Switch_LinkProgram;
PFN_PTRC_GLSHADERSOURCEPROC _ptrc_glShaderSource = Switch_ShaderSource;
PFN_PTRC_GLSTENCILFUNCSEPARATEPROC _ptrc_glStencilFuncSeparate = Switch_StencilFuncSeparate;
PFN_PTRC_GLSTENCILMASKSEPARATEPROC _ptrc_glStencilMaskSeparate = Switch_StencilMaskSeparate;
PFN_PTRC_GLSTENCILOPSEPARATEPROC _ptrc_glStencilOpSeparate = Switch_StencilOpSeparate;
PFN_PTRC_GLUNIFORM1FPROC _ptrc_glUniform1f = Switch_Uniform1f;
PFN_PTRC_GLUNIFORM1FVPROC _ptrc_glUniform1fv = Switch_Uniform1fv;
PFN_PTRC_GLUNIFORM1IPROC _ptrc_glUniform1i = Switch_Uniform1i;
PFN_PTRC_GLUNIFORM1IVPROC _ptrc_glUniform1iv = Switch_Uniform1iv;
PFN_PTRC_GLUNIFORM2FPROC _ptrc_glUniform2f = Switch_Uniform2f;
PFN_PTRC_GLUNIFORM2FVPROC _ptrc_glUniform2fv = Switch_Uniform2fv;
PFN_PTRC_GLUNIFORM2IPROC _ptrc_glUniform2i = Switch_Uniform2i;
PFN_PTRC_GLUNIFORM2IVPROC _ptrc_glUniform2iv = Switch_Uniform2iv;
PFN_PTRC_GLUNIFORM3FPROC _ptrc_glUniform3f = Switch_Uniform3f;
PFN_PTRC_GLUNIFORM3FVPROC _ptrc_glUniform3fv = Switch_Uniform3fv;
PFN_PTRC_GLUNIFORM3IPROC _ptrc_glUniform3i = Switch_Uniform3i;
PFN_PTRC_GLUNIFORM3IVPROC _ptrc_glUniform3iv = Switch_Uniform3iv;
PFN_PTRC_GLUNIFORM4FPROC _ptrc_glUniform4f = Switch_Uniform4f;
PFN_PTRC_GLUNIFORM4FVPROC _ptrc_glUniform4fv = Switch_Uniform4fv;
PFN_PTRC_GLUNIFORM4IPROC _ptrc_glUniform4i = Switch_Uniform4i;
PFN_PTRC_GLUNIFORM4IVPROC _ptrc_glUniform4iv = Switch_Uniform4iv;
PFN_PTRC_GLUNIFORMMATRIX2FVPROC _ptrc_glUniformMatrix2fv = Switch_UniformMatrix2fv;
PFN_PTRC_GLUNIFORMMATRIX3FVPROC _ptrc_glUniformMatrix3fv = Switch_UniformMatrix3fv;
PFN_PTRC_GLUNIFORMMATRIX4FVPROC _ptrc_glUniformMatrix4fv = Switch_UniformMatrix4fv;
PFN_PTRC_GLUSEPROGRAMPROC _ptrc_glUseProgram = Switch_UseProgram;
PFN_PTRC_GLVALIDATEPROGRAMPROC _ptrc_glValidateProgram = Switch_ValidateProgram;
PFN_PTRC_GLVERTEXATTRIB1DPROC _ptrc_glVertexAttrib1d = Switch_VertexAttrib1d;
PFN_PTRC_GLVERTEXATTRIB1DVPROC _ptrc_glVertexAttrib1dv = Switch_VertexAttrib1dv;
PFN_PTRC_GLVERTEXATTRIB1FPROC _ptrc_glVertexAttrib1f = Switch_VertexAttrib1f;
PFN_PTRC_GLVERTEXATTRIB1FVPROC _ptrc_glVertexAttrib1fv = Switch_VertexAttrib1fv;
PFN_PTRC_GLVERTEXATTRIB1SPROC _ptrc_glVertexAttrib1s = Switch_VertexAttrib1s;
PFN_PTRC_GLVERTEXATTRIB1SVPROC _ptrc_glVertexAttrib1sv = Switch_VertexAttrib1sv;
PFN_PTRC_GLVERTEXATTRIB2DPROC _ptrc_glVertexAttrib2d = Switch_VertexAttrib2d;
PFN_PTRC_GLVERTEXATTRIB2DVPROC _ptrc_glVertexAttrib2dv = Switch_VertexAttrib2dv;
PFN_PTRC_GLVERTEXATTRIB2FPROC _ptrc_glVertexAttrib2f = Switch_VertexAttrib2f;
PFN_PTRC_GLVERTEXATTRIB2FVPROC _ptrc_glVertexAttrib2fv = Switch_VertexAttrib2fv;
PFN_PTRC_GLVERTEXATTRIB2SPROC _ptrc_glVertexAttrib2s = Switch_VertexAttrib2s;
PFN_PTRC_GLVERTEXATTRIB2SVPROC _ptrc_glVertexAttrib2sv = Switch_VertexAttrib2sv;
PFN_PTRC_GLVERTEXATTRIB3DPROC _ptrc_glVertexAttrib3d = Switch_VertexAttrib3d;
PFN_PTRC_GLVERTEXATTRIB3DVPROC _ptrc_glVertexAttrib3dv = Switch_VertexAttrib3dv;
PFN_PTRC_GLVERTEXATTRIB3FPROC _ptrc_glVertexAttrib3f = Switch_VertexAttrib3f;
PFN_PTRC_GLVERTEXATTRIB3FVPROC _ptrc_glVertexAttrib3fv = Switch_VertexAttrib3fv;
PFN_PTRC_GLVERTEXATTRIB3SPROC _ptrc_glVertexAttrib3s = Switch_VertexAttrib3s;
PFN_PTRC_GLVERTEXATTRIB3SVPROC _ptrc_glVertexAttrib3sv = Switch_VertexAttrib3sv;
PFN_PTRC_GLVERTEXATTRIB4NBVPROC _ptrc_glVertexAttrib4Nbv = Switch_VertexAttrib4Nbv;
PFN_PTRC_GLVERTEXATTRIB4NIVPROC _ptrc_glVertexAttrib4Niv = Switch_VertexAttrib4Niv;
PFN_PTRC_GLVERTEXATTRIB4NSVPROC _ptrc_glVertexAttrib4Nsv = Switch_VertexAttrib4Nsv;
PFN_PTRC_GLVERTEXATTRIB4NUBPROC _ptrc_glVertexAttrib4Nub = Switch_VertexAttrib4Nub;
PFN_PTRC_GLVERTEXATTRIB4NUBVPROC _ptrc_glVertexAttrib4Nubv = Switch_VertexAttrib4Nubv;
PFN_PTRC_GLVERTEXATTRIB4NUIVPROC _ptrc_glVertexAttrib4Nuiv = Switch_VertexAttrib4Nuiv;
PFN_PTRC_GLVERTEXATTRIB4NUSVPROC _ptrc_glVertexAttrib4Nusv = Switch_VertexAttrib4Nusv;
PFN_PTRC_GLVERTEXATTRIB4BVPROC _ptrc_glVertexAttrib4bv = Switch_VertexAttrib4bv;
PFN_PTRC_GLVERTEXATTRIB4DPROC _ptrc_glVertexAttrib4d = Switch_VertexAttrib4d;
PFN_PTRC_GLVERTEXATTRIB4DVPROC _ptrc_glVertexAttrib4dv = Switch_VertexAttrib4dv;
PFN_PTRC_GLVERTEXATTRIB4FPROC _ptrc_glVertexAttrib4f = Switch_VertexAttrib4f;
PFN_PTRC_GLVERTEXATTRIB4FVPROC _ptrc_glVertexAttrib4fv = Switch_VertexAttrib4fv;
PFN_PTRC_GLVERTEXATTRIB4IVPROC _ptrc_glVertexAttrib4iv = Switch_VertexAttrib4iv;
PFN_PTRC_GLVERTEXATTRIB4SPROC _ptrc_glVertexAttrib4s = Switch_VertexAttrib4s;
PFN_PTRC_GLVERTEXATTRIB4SVPROC _ptrc_glVertexAttrib4sv = Switch_VertexAttrib4sv;
PFN_PTRC_GLVERTEXATTRIB4UBVPROC _ptrc_glVertexAttrib4ubv = Switch_VertexAttrib4ubv;
PFN_PTRC_GLVERTEXATTRIB4UIVPROC _ptrc_glVertexAttrib4uiv = Switch_VertexAttrib4uiv;
PFN_PTRC_GLVERTEXATTRIB4USVPROC _ptrc_glVertexAttrib4usv = Switch_VertexAttrib4usv;
PFN_PTRC_GLVERTEXATTRIBPOINTERPROC _ptrc_glVertexAttribPointer = Switch_VertexAttribPointer;

/* Extension: 2.1*/
PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC _ptrc_glUniformMatrix2x3fv = Switch_UniformMatrix2x3fv;
PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC _ptrc_glUniformMatrix2x4fv = Switch_UniformMatrix2x4fv;
PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC _ptrc_glUniformMatrix3x2fv = Switch_UniformMatrix3x2fv;
PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC _ptrc_glUniformMatrix3x4fv = Switch_UniformMatrix3x4fv;
PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC _ptrc_glUniformMatrix4x2fv = Switch_UniformMatrix4x2fv;
PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC _ptrc_glUniformMatrix4x3fv = Switch_UniformMatrix4x3fv;

/* Extension: 3.0*/
PFN_PTRC_GLBEGINCONDITIONALRENDERPROC _ptrc_glBeginConditionalRender = Switch_BeginConditionalRender;
PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC _ptrc_glBeginTransformFeedback = Switch_BeginTransformFeedback;
PFN_PTRC_GLBINDBUFFERBASEPROC _ptrc_glBindBufferBase = Switch_BindBufferBase;
PFN_PTRC_GLBINDBUFFERRANGEPROC _ptrc_glBindBufferRange = Switch_BindBufferRange;
PFN_PTRC_GLBINDFRAGDATALOCATIONPROC _ptrc_glBindFragDataLocation = Switch_BindFragDataLocation;
PFN_PTRC_GLBINDFRAMEBUFFERPROC _ptrc_glBindFramebuffer = Switch_BindFramebuffer;
PFN_PTRC_GLBINDRENDERBUFFERPROC _ptrc_glBindRenderbuffer = Switch_BindRenderbuffer;
PFN_PTRC_GLBINDVERTEXARRAYPROC _ptrc_glBindVertexArray = Switch_BindVertexArray;
PFN_PTRC_GLBLITFRAMEBUFFERPROC _ptrc_glBlitFramebuffer = Switch_BlitFramebuffer;
PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC _ptrc_glCheckFramebufferStatus = Switch_CheckFramebufferStatus;
PFN_PTRC_GLCLAMPCOLORPROC _ptrc_glClampColor = Switch_ClampColor;
PFN_PTRC_GLCLEARBUFFERFIPROC _ptrc_glClearBufferfi = Switch_ClearBufferfi;
PFN_PTRC_GLCLEARBUFFERFVPROC _ptrc_glClearBufferfv = Switch_ClearBufferfv;
PFN_PTRC_GLCLEARBUFFERIVPROC _ptrc_glClearBufferiv = Switch_ClearBufferiv;
PFN_PTRC_GLCLEARBUFFERUIVPROC _ptrc_glClearBufferuiv = Switch_ClearBufferuiv;
PFN_PTRC_GLCOLORMASKIPROC _ptrc_glColorMaski = Switch_ColorMaski;
PFN_PTRC_GLDELETEFRAMEBUFFERSPROC _ptrc_glDeleteFramebuffers = Switch_DeleteFramebuffers;
PFN_PTRC_GLDELETERENDERBUFFERSPROC _ptrc_glDeleteRenderbuffers = Switch_DeleteRenderbuffers;
PFN_PTRC_GLDELETEVERTEXARRAYSPROC _ptrc_glDeleteVertexArrays = Switch_DeleteVertexArrays;
PFN_PTRC_GLDISABLEIPROC _ptrc_glDisablei = Switch_Disablei;
PFN_PTRC_GLENABLEIPROC _ptrc_glEnablei = Switch_Enablei;
PFN_PTRC_GLENDCONDITIONALRENDERPROC _ptrc_glEndConditionalRender = Switch_EndConditionalRender;
PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC _ptrc_glEndTransformFeedback = Switch_EndTransformFeedback;
PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC _ptrc_glFlushMappedBufferRange = Switch_FlushMappedBufferRange;
PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC _ptrc_glFramebufferRenderbuffer = Switch_FramebufferRenderbuffer;
PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC _ptrc_glFramebufferTexture1D = Switch_FramebufferTexture1D;
PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC _ptrc_glFramebufferTexture2D = Switch_FramebufferTexture2D;
PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC _ptrc_glFramebufferTexture3D = Switch_FramebufferTexture3D;
PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC _ptrc_glFramebufferTextureLayer = Switch_FramebufferTextureLayer;
PFN_PTRC_GLGENFRAMEBUFFERSPROC _ptrc_glGenFramebuffers = Switch_GenFramebuffers;
PFN_PTRC_GLGENRENDERBUFFERSPROC _ptrc_glGenRenderbuffers = Switch_GenRenderbuffers;
PFN_PTRC_GLGENVERTEXARRAYSPROC _ptrc_glGenVertexArrays = Switch_GenVertexArrays;
PFN_PTRC_GLGENERATEMIPMAPPROC _ptrc_glGenerateMipmap = Switch_GenerateMipmap;
PFN_PTRC_GLGETBOOLEANI_VPROC _ptrc_glGetBooleani_v = Switch_GetBooleani_v;
PFN_PTRC_GLGETFRAGDATALOCATIONPROC _ptrc_glGetFragDataLocation = Switch_GetFragDataLocation;
PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _ptrc_glGetFramebufferAttachmentParameteriv = Switch_GetFramebufferAttachmentParameteriv;
PFN_PTRC_GLGETINTEGERI_VPROC _ptrc_glGetIntegeri_v = Switch_GetIntegeri_v;
PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC _ptrc_glGetRenderbufferParameteriv = Switch_GetRenderbufferParameteriv;
PFN_PTRC_GLGETSTRINGIPROC _ptrc_glGetStringi = Switch_GetStringi;
PFN_PTRC_GLGETTEXPARAMETERIIVPROC _ptrc_glGetTexParameterIiv = Switch_GetTexParameterIiv;
PFN_PTRC_GLGETTEXPARAMETERIUIVPROC _ptrc_glGetTexParameterIuiv = Switch_GetTexParameterIuiv;
PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC _ptrc_glGetTransformFeedbackVarying = Switch_GetTransformFeedbackVarying;
PFN_PTRC_GLGETUNIFORMUIVPROC _ptrc_glGetUniformuiv = Switch_GetUniformuiv;
PFN_PTRC_GLGETVERTEXATTRIBIIVPROC _ptrc_glGetVertexAttribIiv = Switch_GetVertexAttribIiv;
PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC _ptrc_glGetVertexAttribIuiv = Switch_GetVertexAttribIuiv;
PFN_PTRC_GLISENABLEDIPROC _ptrc_glIsEnabledi = Switch_IsEnabledi;
PFN_PTRC_GLISFRAMEBUFFERPROC _ptrc_glIsFramebuffer = Switch_IsFramebuffer;
PFN_PTRC_GLISRENDERBUFFERPROC _ptrc_glIsRenderbuffer = Switch_IsRenderbuffer;
PFN_PTRC_GLISVERTEXARRAYPROC _ptrc_glIsVertexArray = Switch_IsVertexArray;
PFN_PTRC_GLMAPBUFFERRANGEPROC _ptrc_glMapBufferRange = Switch_MapBufferRange;
PFN_PTRC_GLRENDERBUFFERSTORAGEPROC _ptrc_glRenderbufferStorage = Switch_RenderbufferStorage;
PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC _ptrc_glRenderbufferStorageMultisample = Switch_RenderbufferStorageMultisample;
PFN_PTRC_GLTEXPARAMETERIIVPROC _ptrc_glTexParameterIiv = Switch_TexParameterIiv;
PFN_PTRC_GLTEXPARAMETERIUIVPROC _ptrc_glTexParameterIuiv = Switch_TexParameterIuiv;
PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC _ptrc_glTransformFeedbackVaryings = Switch_TransformFeedbackVaryings;
PFN_PTRC_GLUNIFORM1UIPROC _ptrc_glUniform1ui = Switch_Uniform1ui;
PFN_PTRC_GLUNIFORM1UIVPROC _ptrc_glUniform1uiv = Switch_Uniform1uiv;
PFN_PTRC_GLUNIFORM2UIPROC _ptrc_glUniform2ui = Switch_Uniform2ui;
PFN_PTRC_GLUNIFORM2UIVPROC _ptrc_glUniform2uiv = Switch_Uniform2uiv;
PFN_PTRC_GLUNIFORM3UIPROC _ptrc_glUniform3ui = Switch_Uniform3ui;
PFN_PTRC_GLUNIFORM3UIVPROC _ptrc_glUniform3uiv = Switch_Uniform3uiv;
PFN_PTRC_GLUNIFORM4UIPROC _ptrc_glUniform4ui = Switch_Uniform4ui;
PFN_PTRC_GLUNIFORM4UIVPROC _ptrc_glUniform4uiv = Switch_Uniform4uiv;
PFN_PTRC_GLVERTEXATTRIBI1IPROC _ptrc_glVertexAttribI1i = Switch_VertexAttribI1i;
PFN_PTRC_GLVERTEXATTRIBI1IVPROC _ptrc_glVertexAttribI1iv = Switch_VertexAttribI1iv;
PFN_PTRC_GLVERTEXATTRIBI1UIPROC _ptrc_glVertexAttribI1ui = Switch_VertexAttribI1ui;
PFN_PTRC_GLVERTEXATTRIBI1UIVPROC _ptrc_glVertexAttribI1uiv = Switch_VertexAttribI1uiv;
PFN_PTRC_GLVERTEXATTRIBI2IPROC _ptrc_glVertexAttribI2i = Switch_VertexAttribI2i;
PFN_PTRC_GLVERTEXATTRIBI2IVPROC _ptrc_glVertexAttribI2iv = Switch_VertexAttribI2iv;
PFN_PTRC_GLVERTEXATTRIBI2UIPROC _ptrc_glVertexAttribI2ui = Switch_VertexAttribI2ui;
PFN_PTRC_GLVERTEXATTRIBI2UIVPROC _ptrc_glVertexAttribI2uiv = Switch_VertexAttribI2uiv;
PFN_PTRC_GLVERTEXATTRIBI3IPROC _ptrc_glVertexAttribI3i = Switch_VertexAttribI3i;
PFN_PTRC_GLVERTEXATTRIBI3IVPROC _ptrc_glVertexAttribI3iv = Switch_VertexAttribI3iv;
PFN_PTRC_GLVERTEXATTRIBI3UIPROC _ptrc_glVertexAttribI3ui = Switch_VertexAttribI3ui;
PFN_PTRC_GLVERTEXATTRIBI3UIVPROC _ptrc_glVertexAttribI3uiv = Switch_VertexAttribI3uiv;
PFN_PTRC_GLVERTEXATTRIBI4BVPROC _ptrc_glVertexAttribI4bv = Switch_VertexAttribI4bv;
PFN_PTRC_GLVERTEXATTRIBI4IPROC _ptrc_glVertexAttribI4i = Switch_VertexAttribI4i;
PFN_PTRC_GLVERTEXATTRIBI4IVPROC _ptrc_glVertexAttribI4iv = Switch_VertexAttribI4iv;
PFN_PTRC_GLVERTEXATTRIBI4SVPROC _ptrc_glVertexAttribI4sv = Switch_VertexAttribI4sv;
PFN_PTRC_GLVERTEXATTRIBI4UBVPROC _ptrc_glVertexAttribI4ubv = Switch_VertexAttribI4ubv;
PFN_PTRC_GLVERTEXATTRIBI4UIPROC _ptrc_glVertexAttribI4ui = Switch_VertexAttribI4ui;
PFN_PTRC_GLVERTEXATTRIBI4UIVPROC _ptrc_glVertexAttribI4uiv = Switch_VertexAttribI4uiv;
PFN_PTRC_GLVERTEXATTRIBI4USVPROC _ptrc_glVertexAttribI4usv = Switch_VertexAttribI4usv;
PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC _ptrc_glVertexAttribIPointer = Switch_VertexAttribIPointer;

/* Extension: 3.1*/
PFN_PTRC_GLCOPYBUFFERSUBDATAPROC _ptrc_glCopyBufferSubData = Switch_CopyBufferSubData;
PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC _ptrc_glDrawArraysInstanced = Switch_DrawArraysInstanced;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC _ptrc_glDrawElementsInstanced = Switch_DrawElementsInstanced;
PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC _ptrc_glGetActiveUniformBlockName = Switch_GetActiveUniformBlockName;
PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC _ptrc_glGetActiveUniformBlockiv = Switch_GetActiveUniformBlockiv;
PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC _ptrc_glGetActiveUniformName = Switch_GetActiveUniformName;
PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC _ptrc_glGetActiveUniformsiv = Switch_GetActiveUniformsiv;
PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC _ptrc_glGetUniformBlockIndex = Switch_GetUniformBlockIndex;
PFN_PTRC_GLGETUNIFORMINDICESPROC _ptrc_glGetUniformIndices = Switch_GetUniformIndices;
PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC _ptrc_glPrimitiveRestartIndex = Switch_PrimitiveRestartIndex;
PFN_PTRC_GLTEXBUFFERPROC _ptrc_glTexBuffer = Switch_TexBuffer;
PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC _ptrc_glUniformBlockBinding = Switch_UniformBlockBinding;

/* Extension: 3.2*/
PFN_PTRC_GLCLIENTWAITSYNCPROC _ptrc_glClientWaitSync = Switch_ClientWaitSync;
PFN_PTRC_GLDELETESYNCPROC _ptrc_glDeleteSync = Switch_DeleteSync;
PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC _ptrc_glDrawElementsBaseVertex = Switch_DrawElementsBaseVertex;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC _ptrc_glDrawElementsInstancedBaseVertex = Switch_DrawElementsInstancedBaseVertex;
PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC _ptrc_glDrawRangeElementsBaseVertex = Switch_DrawRangeElementsBaseVertex;
PFN_PTRC_GLFENCESYNCPROC _ptrc_glFenceSync = Switch_FenceSync;
PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC _ptrc_glFramebufferTexture = Switch_FramebufferTexture;
PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC _ptrc_glGetBufferParameteri64v = Switch_GetBufferParameteri64v;
PFN_PTRC_GLGETINTEGER64I_VPROC _ptrc_glGetInteger64i_v = Switch_GetInteger64i_v;
PFN_PTRC_GLGETINTEGER64VPROC _ptrc_glGetInteger64v = Switch_GetInteger64v;
PFN_PTRC_GLGETMULTISAMPLEFVPROC _ptrc_glGetMultisamplefv = Switch_GetMultisamplefv;
PFN_PTRC_GLGETSYNCIVPROC _ptrc_glGetSynciv = Switch_GetSynciv;
PFN_PTRC_GLISSYNCPROC _ptrc_glIsSync = Switch_IsSync;
PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC _ptrc_glMultiDrawElementsBaseVertex = Switch_MultiDrawElementsBaseVertex;
PFN_PTRC_GLPROVOKINGVERTEXPROC _ptrc_glProvokingVertex = Switch_ProvokingVertex;
PFN_PTRC_GLSAMPLEMASKIPROC _ptrc_glSampleMaski = Switch_SampleMaski;
PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC _ptrc_glTexImage2DMultisample = Switch_TexImage2DMultisample;
PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC _ptrc_glTexImage3DMultisample = Switch_TexImage3DMultisample;
PFN_PTRC_GLWAITSYNCPROC _ptrc_glWaitSync = Switch_WaitSync;

/* Extension: 3.3*/
PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC _ptrc_glBindFragDataLocationIndexed = Switch_BindFragDataLocationIndexed;
PFN_PTRC_GLBINDSAMPLERPROC _ptrc_glBindSampler = Switch_BindSampler;
PFN_PTRC_GLDELETESAMPLERSPROC _ptrc_glDeleteSamplers = Switch_DeleteSamplers;
PFN_PTRC_GLGENSAMPLERSPROC _ptrc_glGenSamplers = Switch_GenSamplers;
PFN_PTRC_GLGETFRAGDATAINDEXPROC _ptrc_glGetFragDataIndex = Switch_GetFragDataIndex;
PFN_PTRC_GLGETQUERYOBJECTI64VPROC _ptrc_glGetQueryObjecti64v = Switch_GetQueryObjecti64v;
PFN_PTRC_GLGETQUERYOBJECTUI64VPROC _ptrc_glGetQueryObjectui64v = Switch_GetQueryObjectui64v;
PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC _ptrc_glGetSamplerParameterIiv = Switch_GetSamplerParameterIiv;
PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC _ptrc_glGetSamplerParameterIuiv = Switch_GetSamplerParameterIuiv;
PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC _ptrc_glGetSamplerParameterfv = Switch_GetSamplerParameterfv;
PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC _ptrc_glGetSamplerParameteriv = Switch_GetSamplerParameteriv;
PFN_PTRC_GLISSAMPLERPROC _ptrc_glIsSampler = Switch_IsSampler;
PFN_PTRC_GLQUERYCOUNTERPROC _ptrc_glQueryCounter = Switch_QueryCounter;
PFN_PTRC_GLSAMPLERPARAMETERIIVPROC _ptrc_glSamplerParameterIiv = Switch_SamplerParameterIiv;
PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC _ptrc_glSamplerParameterIuiv = Switch_SamplerParameterIuiv;
PFN_PTRC_GLSAMPLERPARAMETERFPROC _ptrc_glSamplerParameterf = Switch_SamplerParameterf;
PFN_PTRC_GLSAMPLERPARAMETERFVPROC _ptrc_glSamplerParameterfv = Switch_SamplerParameterfv;
PFN_PTRC_GLSAMPLERPARAMETERIPROC _ptrc_glSamplerParameteri = Switch_SamplerParameteri;
PFN_PTRC_GLSAMPLERPARAMETERIVPROC _ptrc_glSamplerParameteriv = Switch_SamplerParameteriv;
PFN_PTRC_GLVERTEXATTRIBDIVISORPROC _ptrc_glVertexAttribDivisor = Switch_VertexAttribDivisor;
PFN_PTRC_GLVERTEXATTRIBP1UIPROC _ptrc_glVertexAttribP1ui = Switch_VertexAttribP1ui;
PFN_PTRC_GLVERTEXATTRIBP1UIVPROC _ptrc_glVertexAttribP1uiv = Switch_VertexAttribP1uiv;
PFN_PTRC_GLVERTEXATTRIBP2UIPROC _ptrc_glVertexAttribP2ui = Switch_VertexAttribP2ui;
PFN_PTRC_GLVERTEXATTRIBP2UIVPROC _ptrc_glVertexAttribP2uiv = Switch_VertexAttribP2uiv;
PFN_PTRC_GLVERTEXATTRIBP3UIPROC _ptrc_glVertexAttribP3ui = Switch_VertexAttribP3ui;
PFN_PTRC_GLVERTEXATTRIBP3UIVPROC _ptrc_glVertexAttribP3uiv = Switch_VertexAttribP3uiv;
PFN_PTRC_GLVERTEXATTRIBP4UIPROC _ptrc_glVertexAttribP4ui = Switch_VertexAttribP4ui;
PFN_PTRC_GLVERTEXATTRIBP4UIVPROC _ptrc_glVertexAttribP4uiv = Switch_VertexAttribP4uiv;


/* Extension: 1.0*/
static void CODEGEN_FUNCPTR Switch_BlendFunc(GLenum sfactor, GLenum dfactor)
{
  _ptrc_glBlendFunc = (PFN_PTRC_GLBLENDFUNCPROC)IntGetProcAddress("glBlendFunc");
  _ptrc_glBlendFunc(sfactor, dfactor);
}

static void CODEGEN_FUNCPTR Switch_Clear(GLbitfield mask)
{
  _ptrc_glClear = (PFN_PTRC_GLCLEARPROC)IntGetProcAddress("glClear");
  _ptrc_glClear(mask);
}

static void CODEGEN_FUNCPTR Switch_ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  _ptrc_glClearColor = (PFN_PTRC_GLCLEARCOLORPROC)IntGetProcAddress("glClearColor");
  _ptrc_glClearColor(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_ClearDepth(GLdouble depth)
{
  _ptrc_glClearDepth = (PFN_PTRC_GLCLEARDEPTHPROC)IntGetProcAddress("glClearDepth");
  _ptrc_glClearDepth(depth);
}

static void CODEGEN_FUNCPTR Switch_ClearStencil(GLint s)
{
  _ptrc_glClearStencil = (PFN_PTRC_GLCLEARSTENCILPROC)IntGetProcAddress("glClearStencil");
  _ptrc_glClearStencil(s);
}

static void CODEGEN_FUNCPTR Switch_ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
  _ptrc_glColorMask = (PFN_PTRC_GLCOLORMASKPROC)IntGetProcAddress("glColorMask");
  _ptrc_glColorMask(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_CullFace(GLenum mode)
{
  _ptrc_glCullFace = (PFN_PTRC_GLCULLFACEPROC)IntGetProcAddress("glCullFace");
  _ptrc_glCullFace(mode);
}

static void CODEGEN_FUNCPTR Switch_DepthFunc(GLenum func)
{
  _ptrc_glDepthFunc = (PFN_PTRC_GLDEPTHFUNCPROC)IntGetProcAddress("glDepthFunc");
  _ptrc_glDepthFunc(func);
}

static void CODEGEN_FUNCPTR Switch_DepthMask(GLboolean flag)
{
  _ptrc_glDepthMask = (PFN_PTRC_GLDEPTHMASKPROC)IntGetProcAddress("glDepthMask");
  _ptrc_glDepthMask(flag);
}

static void CODEGEN_FUNCPTR Switch_DepthRange(GLdouble ren_near, GLdouble ren_far)
{
  _ptrc_glDepthRange = (PFN_PTRC_GLDEPTHRANGEPROC)IntGetProcAddress("glDepthRange");
  _ptrc_glDepthRange(ren_near, ren_far);
}

static void CODEGEN_FUNCPTR Switch_Disable(GLenum cap)
{
  _ptrc_glDisable = (PFN_PTRC_GLDISABLEPROC)IntGetProcAddress("glDisable");
  _ptrc_glDisable(cap);
}

static void CODEGEN_FUNCPTR Switch_DrawBuffer(GLenum buf)
{
  _ptrc_glDrawBuffer = (PFN_PTRC_GLDRAWBUFFERPROC)IntGetProcAddress("glDrawBuffer");
  _ptrc_glDrawBuffer(buf);
}

static void CODEGEN_FUNCPTR Switch_Enable(GLenum cap)
{
  _ptrc_glEnable = (PFN_PTRC_GLENABLEPROC)IntGetProcAddress("glEnable");
  _ptrc_glEnable(cap);
}

static void CODEGEN_FUNCPTR Switch_Finish(void)
{
  _ptrc_glFinish = (PFN_PTRC_GLFINISHPROC)IntGetProcAddress("glFinish");
  _ptrc_glFinish();
}

static void CODEGEN_FUNCPTR Switch_Flush(void)
{
  _ptrc_glFlush = (PFN_PTRC_GLFLUSHPROC)IntGetProcAddress("glFlush");
  _ptrc_glFlush();
}

static void CODEGEN_FUNCPTR Switch_FrontFace(GLenum mode)
{
  _ptrc_glFrontFace = (PFN_PTRC_GLFRONTFACEPROC)IntGetProcAddress("glFrontFace");
  _ptrc_glFrontFace(mode);
}

static void CODEGEN_FUNCPTR Switch_GetBooleanv(GLenum pname, GLboolean * data)
{
  _ptrc_glGetBooleanv = (PFN_PTRC_GLGETBOOLEANVPROC)IntGetProcAddress("glGetBooleanv");
  _ptrc_glGetBooleanv(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetDoublev(GLenum pname, GLdouble * data)
{
  _ptrc_glGetDoublev = (PFN_PTRC_GLGETDOUBLEVPROC)IntGetProcAddress("glGetDoublev");
  _ptrc_glGetDoublev(pname, data);
}

static GLenum CODEGEN_FUNCPTR Switch_GetError(void)
{
  _ptrc_glGetError = (PFN_PTRC_GLGETERRORPROC)IntGetProcAddress("glGetError");
  return _ptrc_glGetError();
}

static void CODEGEN_FUNCPTR Switch_GetFloatv(GLenum pname, GLfloat * data)
{
  _ptrc_glGetFloatv = (PFN_PTRC_GLGETFLOATVPROC)IntGetProcAddress("glGetFloatv");
  _ptrc_glGetFloatv(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetIntegerv(GLenum pname, GLint * data)
{
  _ptrc_glGetIntegerv = (PFN_PTRC_GLGETINTEGERVPROC)IntGetProcAddress("glGetIntegerv");
  _ptrc_glGetIntegerv(pname, data);
}

static const GLubyte * CODEGEN_FUNCPTR Switch_GetString(GLenum name)
{
  _ptrc_glGetString = (PFN_PTRC_GLGETSTRINGPROC)IntGetProcAddress("glGetString");
  return _ptrc_glGetString(name);
}

static void CODEGEN_FUNCPTR Switch_GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
  _ptrc_glGetTexImage = (PFN_PTRC_GLGETTEXIMAGEPROC)IntGetProcAddress("glGetTexImage");
  _ptrc_glGetTexImage(target, level, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
  _ptrc_glGetTexLevelParameterfv = (PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC)IntGetProcAddress("glGetTexLevelParameterfv");
  _ptrc_glGetTexLevelParameterfv(target, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
{
  _ptrc_glGetTexLevelParameteriv = (PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC)IntGetProcAddress("glGetTexLevelParameteriv");
  _ptrc_glGetTexLevelParameteriv(target, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
  _ptrc_glGetTexParameterfv = (PFN_PTRC_GLGETTEXPARAMETERFVPROC)IntGetProcAddress("glGetTexParameterfv");
  _ptrc_glGetTexParameterfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameteriv(GLenum target, GLenum pname, GLint * params)
{
  _ptrc_glGetTexParameteriv = (PFN_PTRC_GLGETTEXPARAMETERIVPROC)IntGetProcAddress("glGetTexParameteriv");
  _ptrc_glGetTexParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Hint(GLenum target, GLenum mode)
{
  _ptrc_glHint = (PFN_PTRC_GLHINTPROC)IntGetProcAddress("glHint");
  _ptrc_glHint(target, mode);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsEnabled(GLenum cap)
{
  _ptrc_glIsEnabled = (PFN_PTRC_GLISENABLEDPROC)IntGetProcAddress("glIsEnabled");
  return _ptrc_glIsEnabled(cap);
}

static void CODEGEN_FUNCPTR Switch_LineWidth(GLfloat width)
{
  _ptrc_glLineWidth = (PFN_PTRC_GLLINEWIDTHPROC)IntGetProcAddress("glLineWidth");
  _ptrc_glLineWidth(width);
}

static void CODEGEN_FUNCPTR Switch_LogicOp(GLenum opcode)
{
  _ptrc_glLogicOp = (PFN_PTRC_GLLOGICOPPROC)IntGetProcAddress("glLogicOp");
  _ptrc_glLogicOp(opcode);
}

static void CODEGEN_FUNCPTR Switch_PixelStoref(GLenum pname, GLfloat param)
{
  _ptrc_glPixelStoref = (PFN_PTRC_GLPIXELSTOREFPROC)IntGetProcAddress("glPixelStoref");
  _ptrc_glPixelStoref(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PixelStorei(GLenum pname, GLint param)
{
  _ptrc_glPixelStorei = (PFN_PTRC_GLPIXELSTOREIPROC)IntGetProcAddress("glPixelStorei");
  _ptrc_glPixelStorei(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PointSize(GLfloat size)
{
  _ptrc_glPointSize = (PFN_PTRC_GLPOINTSIZEPROC)IntGetProcAddress("glPointSize");
  _ptrc_glPointSize(size);
}

static void CODEGEN_FUNCPTR Switch_PolygonMode(GLenum face, GLenum mode)
{
  _ptrc_glPolygonMode = (PFN_PTRC_GLPOLYGONMODEPROC)IntGetProcAddress("glPolygonMode");
  _ptrc_glPolygonMode(face, mode);
}

static void CODEGEN_FUNCPTR Switch_ReadBuffer(GLenum src)
{
  _ptrc_glReadBuffer = (PFN_PTRC_GLREADBUFFERPROC)IntGetProcAddress("glReadBuffer");
  _ptrc_glReadBuffer(src);
}

static void CODEGEN_FUNCPTR Switch_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
{
  _ptrc_glReadPixels = (PFN_PTRC_GLREADPIXELSPROC)IntGetProcAddress("glReadPixels");
  _ptrc_glReadPixels(x, y, width, height, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
  _ptrc_glScissor = (PFN_PTRC_GLSCISSORPROC)IntGetProcAddress("glScissor");
  _ptrc_glScissor(x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_StencilFunc(GLenum func, GLint ref, GLuint mask)
{
  _ptrc_glStencilFunc = (PFN_PTRC_GLSTENCILFUNCPROC)IntGetProcAddress("glStencilFunc");
  _ptrc_glStencilFunc(func, ref, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilMask(GLuint mask)
{
  _ptrc_glStencilMask = (PFN_PTRC_GLSTENCILMASKPROC)IntGetProcAddress("glStencilMask");
  _ptrc_glStencilMask(mask);
}

static void CODEGEN_FUNCPTR Switch_StencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
  _ptrc_glStencilOp = (PFN_PTRC_GLSTENCILOPPROC)IntGetProcAddress("glStencilOp");
  _ptrc_glStencilOp(fail, zfail, zpass);
}

static void CODEGEN_FUNCPTR Switch_TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexImage1D = (PFN_PTRC_GLTEXIMAGE1DPROC)IntGetProcAddress("glTexImage1D");
  _ptrc_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexImage2D = (PFN_PTRC_GLTEXIMAGE2DPROC)IntGetProcAddress("glTexImage2D");
  _ptrc_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexParameterf(GLenum target, GLenum pname, GLfloat param)
{
  _ptrc_glTexParameterf = (PFN_PTRC_GLTEXPARAMETERFPROC)IntGetProcAddress("glTexParameterf");
  _ptrc_glTexParameterf(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexParameterfv(GLenum target, GLenum pname, const GLfloat * params)
{
  _ptrc_glTexParameterfv = (PFN_PTRC_GLTEXPARAMETERFVPROC)IntGetProcAddress("glTexParameterfv");
  _ptrc_glTexParameterfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexParameteri(GLenum target, GLenum pname, GLint param)
{
  _ptrc_glTexParameteri = (PFN_PTRC_GLTEXPARAMETERIPROC)IntGetProcAddress("glTexParameteri");
  _ptrc_glTexParameteri(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexParameteriv(GLenum target, GLenum pname, const GLint * params)
{
  _ptrc_glTexParameteriv = (PFN_PTRC_GLTEXPARAMETERIVPROC)IntGetProcAddress("glTexParameteriv");
  _ptrc_glTexParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  _ptrc_glViewport = (PFN_PTRC_GLVIEWPORTPROC)IntGetProcAddress("glViewport");
  _ptrc_glViewport(x, y, width, height);
}


/* Extension: 1.1*/
static void CODEGEN_FUNCPTR Switch_BindTexture(GLenum target, GLuint texture)
{
  _ptrc_glBindTexture = (PFN_PTRC_GLBINDTEXTUREPROC)IntGetProcAddress("glBindTexture");
  _ptrc_glBindTexture(target, texture);
}

static void CODEGEN_FUNCPTR Switch_CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
  _ptrc_glCopyTexImage1D = (PFN_PTRC_GLCOPYTEXIMAGE1DPROC)IntGetProcAddress("glCopyTexImage1D");
  _ptrc_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

static void CODEGEN_FUNCPTR Switch_CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
  _ptrc_glCopyTexImage2D = (PFN_PTRC_GLCOPYTEXIMAGE2DPROC)IntGetProcAddress("glCopyTexImage2D");
  _ptrc_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

static void CODEGEN_FUNCPTR Switch_CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
  _ptrc_glCopyTexSubImage1D = (PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC)IntGetProcAddress("glCopyTexSubImage1D");
  _ptrc_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

static void CODEGEN_FUNCPTR Switch_CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  _ptrc_glCopyTexSubImage2D = (PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC)IntGetProcAddress("glCopyTexSubImage2D");
  _ptrc_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_DeleteTextures(GLsizei n, const GLuint * textures)
{
  _ptrc_glDeleteTextures = (PFN_PTRC_GLDELETETEXTURESPROC)IntGetProcAddress("glDeleteTextures");
  _ptrc_glDeleteTextures(n, textures);
}

static void CODEGEN_FUNCPTR Switch_DrawArrays(GLenum mode, GLint first, GLsizei count)
{
  _ptrc_glDrawArrays = (PFN_PTRC_GLDRAWARRAYSPROC)IntGetProcAddress("glDrawArrays");
  _ptrc_glDrawArrays(mode, first, count);
}

static void CODEGEN_FUNCPTR Switch_DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
  _ptrc_glDrawElements = (PFN_PTRC_GLDRAWELEMENTSPROC)IntGetProcAddress("glDrawElements");
  _ptrc_glDrawElements(mode, count, type, indices);
}

static void CODEGEN_FUNCPTR Switch_GenTextures(GLsizei n, GLuint * textures)
{
  _ptrc_glGenTextures = (PFN_PTRC_GLGENTEXTURESPROC)IntGetProcAddress("glGenTextures");
  _ptrc_glGenTextures(n, textures);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsTexture(GLuint texture)
{
  _ptrc_glIsTexture = (PFN_PTRC_GLISTEXTUREPROC)IntGetProcAddress("glIsTexture");
  return _ptrc_glIsTexture(texture);
}

static void CODEGEN_FUNCPTR Switch_PolygonOffset(GLfloat factor, GLfloat units)
{
  _ptrc_glPolygonOffset = (PFN_PTRC_GLPOLYGONOFFSETPROC)IntGetProcAddress("glPolygonOffset");
  _ptrc_glPolygonOffset(factor, units);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexSubImage1D = (PFN_PTRC_GLTEXSUBIMAGE1DPROC)IntGetProcAddress("glTexSubImage1D");
  _ptrc_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexSubImage2D = (PFN_PTRC_GLTEXSUBIMAGE2DPROC)IntGetProcAddress("glTexSubImage2D");
  _ptrc_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}


/* Extension: 1.2*/
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  _ptrc_glCopyTexSubImage3D = (PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC)IntGetProcAddress("glCopyTexSubImage3D");
  _ptrc_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
  _ptrc_glDrawRangeElements = (PFN_PTRC_GLDRAWRANGEELEMENTSPROC)IntGetProcAddress("glDrawRangeElements");
  _ptrc_glDrawRangeElements(mode, start, end, count, type, indices);
}

static void CODEGEN_FUNCPTR Switch_TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexImage3D = (PFN_PTRC_GLTEXIMAGE3DPROC)IntGetProcAddress("glTexImage3D");
  _ptrc_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
  _ptrc_glTexSubImage3D = (PFN_PTRC_GLTEXSUBIMAGE3DPROC)IntGetProcAddress("glTexSubImage3D");
  _ptrc_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}


/* Extension: 1.3*/
static void CODEGEN_FUNCPTR Switch_ActiveTexture(GLenum texture)
{
  _ptrc_glActiveTexture = (PFN_PTRC_GLACTIVETEXTUREPROC)IntGetProcAddress("glActiveTexture");
  _ptrc_glActiveTexture(texture);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexImage1D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC)IntGetProcAddress("glCompressedTexImage1D");
  _ptrc_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexImage2D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC)IntGetProcAddress("glCompressedTexImage2D");
  _ptrc_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexImage3D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC)IntGetProcAddress("glCompressedTexImage3D");
  _ptrc_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexSubImage1D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC)IntGetProcAddress("glCompressedTexSubImage1D");
  _ptrc_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexSubImage2D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC)IntGetProcAddress("glCompressedTexSubImage2D");
  _ptrc_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
  _ptrc_glCompressedTexSubImage3D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC)IntGetProcAddress("glCompressedTexSubImage3D");
  _ptrc_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_GetCompressedTexImage(GLenum target, GLint level, void * img)
{
  _ptrc_glGetCompressedTexImage = (PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC)IntGetProcAddress("glGetCompressedTexImage");
  _ptrc_glGetCompressedTexImage(target, level, img);
}

static void CODEGEN_FUNCPTR Switch_SampleCoverage(GLfloat value, GLboolean invert)
{
  _ptrc_glSampleCoverage = (PFN_PTRC_GLSAMPLECOVERAGEPROC)IntGetProcAddress("glSampleCoverage");
  _ptrc_glSampleCoverage(value, invert);
}


/* Extension: 1.4*/
static void CODEGEN_FUNCPTR Switch_BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  _ptrc_glBlendColor = (PFN_PTRC_GLBLENDCOLORPROC)IntGetProcAddress("glBlendColor");
  _ptrc_glBlendColor(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_BlendEquation(GLenum mode)
{
  _ptrc_glBlendEquation = (PFN_PTRC_GLBLENDEQUATIONPROC)IntGetProcAddress("glBlendEquation");
  _ptrc_glBlendEquation(mode);
}

static void CODEGEN_FUNCPTR Switch_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
  _ptrc_glBlendFuncSeparate = (PFN_PTRC_GLBLENDFUNCSEPARATEPROC)IntGetProcAddress("glBlendFuncSeparate");
  _ptrc_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{
  _ptrc_glMultiDrawArrays = (PFN_PTRC_GLMULTIDRAWARRAYSPROC)IntGetProcAddress("glMultiDrawArrays");
  _ptrc_glMultiDrawArrays(mode, first, count, drawcount);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount)
{
  _ptrc_glMultiDrawElements = (PFN_PTRC_GLMULTIDRAWELEMENTSPROC)IntGetProcAddress("glMultiDrawElements");
  _ptrc_glMultiDrawElements(mode, count, type, indices, drawcount);
}

static void CODEGEN_FUNCPTR Switch_PointParameterf(GLenum pname, GLfloat param)
{
  _ptrc_glPointParameterf = (PFN_PTRC_GLPOINTPARAMETERFPROC)IntGetProcAddress("glPointParameterf");
  _ptrc_glPointParameterf(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PointParameterfv(GLenum pname, const GLfloat * params)
{
  _ptrc_glPointParameterfv = (PFN_PTRC_GLPOINTPARAMETERFVPROC)IntGetProcAddress("glPointParameterfv");
  _ptrc_glPointParameterfv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_PointParameteri(GLenum pname, GLint param)
{
  _ptrc_glPointParameteri = (PFN_PTRC_GLPOINTPARAMETERIPROC)IntGetProcAddress("glPointParameteri");
  _ptrc_glPointParameteri(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PointParameteriv(GLenum pname, const GLint * params)
{
  _ptrc_glPointParameteriv = (PFN_PTRC_GLPOINTPARAMETERIVPROC)IntGetProcAddress("glPointParameteriv");
  _ptrc_glPointParameteriv(pname, params);
}


/* Extension: 1.5*/
static void CODEGEN_FUNCPTR Switch_BeginQuery(GLenum target, GLuint id)
{
  _ptrc_glBeginQuery = (PFN_PTRC_GLBEGINQUERYPROC)IntGetProcAddress("glBeginQuery");
  _ptrc_glBeginQuery(target, id);
}

static void CODEGEN_FUNCPTR Switch_BindBuffer(GLenum target, GLuint buffer)
{
  _ptrc_glBindBuffer = (PFN_PTRC_GLBINDBUFFERPROC)IntGetProcAddress("glBindBuffer");
  _ptrc_glBindBuffer(target, buffer);
}

static void CODEGEN_FUNCPTR Switch_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
  _ptrc_glBufferData = (PFN_PTRC_GLBUFFERDATAPROC)IntGetProcAddress("glBufferData");
  _ptrc_glBufferData(target, size, data, usage);
}

static void CODEGEN_FUNCPTR Switch_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
  _ptrc_glBufferSubData = (PFN_PTRC_GLBUFFERSUBDATAPROC)IntGetProcAddress("glBufferSubData");
  _ptrc_glBufferSubData(target, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_DeleteBuffers(GLsizei n, const GLuint * buffers)
{
  _ptrc_glDeleteBuffers = (PFN_PTRC_GLDELETEBUFFERSPROC)IntGetProcAddress("glDeleteBuffers");
  _ptrc_glDeleteBuffers(n, buffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteQueries(GLsizei n, const GLuint * ids)
{
  _ptrc_glDeleteQueries = (PFN_PTRC_GLDELETEQUERIESPROC)IntGetProcAddress("glDeleteQueries");
  _ptrc_glDeleteQueries(n, ids);
}

static void CODEGEN_FUNCPTR Switch_EndQuery(GLenum target)
{
  _ptrc_glEndQuery = (PFN_PTRC_GLENDQUERYPROC)IntGetProcAddress("glEndQuery");
  _ptrc_glEndQuery(target);
}

static void CODEGEN_FUNCPTR Switch_GenBuffers(GLsizei n, GLuint * buffers)
{
  _ptrc_glGenBuffers = (PFN_PTRC_GLGENBUFFERSPROC)IntGetProcAddress("glGenBuffers");
  _ptrc_glGenBuffers(n, buffers);
}

static void CODEGEN_FUNCPTR Switch_GenQueries(GLsizei n, GLuint * ids)
{
  _ptrc_glGenQueries = (PFN_PTRC_GLGENQUERIESPROC)IntGetProcAddress("glGenQueries");
  _ptrc_glGenQueries(n, ids);
}

static void CODEGEN_FUNCPTR Switch_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
  _ptrc_glGetBufferParameteriv = (PFN_PTRC_GLGETBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetBufferParameteriv");
  _ptrc_glGetBufferParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetBufferPointerv(GLenum target, GLenum pname, void ** params)
{
  _ptrc_glGetBufferPointerv = (PFN_PTRC_GLGETBUFFERPOINTERVPROC)IntGetProcAddress("glGetBufferPointerv");
  _ptrc_glGetBufferPointerv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{
  _ptrc_glGetBufferSubData = (PFN_PTRC_GLGETBUFFERSUBDATAPROC)IntGetProcAddress("glGetBufferSubData");
  _ptrc_glGetBufferSubData(target, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
  _ptrc_glGetQueryObjectiv = (PFN_PTRC_GLGETQUERYOBJECTIVPROC)IntGetProcAddress("glGetQueryObjectiv");
  _ptrc_glGetQueryObjectiv(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
  _ptrc_glGetQueryObjectuiv = (PFN_PTRC_GLGETQUERYOBJECTUIVPROC)IntGetProcAddress("glGetQueryObjectuiv");
  _ptrc_glGetQueryObjectuiv(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryiv(GLenum target, GLenum pname, GLint * params)
{
  _ptrc_glGetQueryiv = (PFN_PTRC_GLGETQUERYIVPROC)IntGetProcAddress("glGetQueryiv");
  _ptrc_glGetQueryiv(target, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsBuffer(GLuint buffer)
{
  _ptrc_glIsBuffer = (PFN_PTRC_GLISBUFFERPROC)IntGetProcAddress("glIsBuffer");
  return _ptrc_glIsBuffer(buffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsQuery(GLuint id)
{
  _ptrc_glIsQuery = (PFN_PTRC_GLISQUERYPROC)IntGetProcAddress("glIsQuery");
  return _ptrc_glIsQuery(id);
}

static void * CODEGEN_FUNCPTR Switch_MapBuffer(GLenum target, GLenum access)
{
  _ptrc_glMapBuffer = (PFN_PTRC_GLMAPBUFFERPROC)IntGetProcAddress("glMapBuffer");
  return _ptrc_glMapBuffer(target, access);
}

static GLboolean CODEGEN_FUNCPTR Switch_UnmapBuffer(GLenum target)
{
  _ptrc_glUnmapBuffer = (PFN_PTRC_GLUNMAPBUFFERPROC)IntGetProcAddress("glUnmapBuffer");
  return _ptrc_glUnmapBuffer(target);
}


/* Extension: 2.0*/
static void CODEGEN_FUNCPTR Switch_AttachShader(GLuint program, GLuint shader)
{
  _ptrc_glAttachShader = (PFN_PTRC_GLATTACHSHADERPROC)IntGetProcAddress("glAttachShader");
  _ptrc_glAttachShader(program, shader);
}

static void CODEGEN_FUNCPTR Switch_BindAttribLocation(GLuint program, GLuint index, const GLchar * name)
{
  _ptrc_glBindAttribLocation = (PFN_PTRC_GLBINDATTRIBLOCATIONPROC)IntGetProcAddress("glBindAttribLocation");
  _ptrc_glBindAttribLocation(program, index, name);
}

static void CODEGEN_FUNCPTR Switch_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
  _ptrc_glBlendEquationSeparate = (PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC)IntGetProcAddress("glBlendEquationSeparate");
  _ptrc_glBlendEquationSeparate(modeRGB, modeAlpha);
}

static void CODEGEN_FUNCPTR Switch_CompileShader(GLuint shader)
{
  _ptrc_glCompileShader = (PFN_PTRC_GLCOMPILESHADERPROC)IntGetProcAddress("glCompileShader");
  _ptrc_glCompileShader(shader);
}

static GLuint CODEGEN_FUNCPTR Switch_CreateProgram(void)
{
  _ptrc_glCreateProgram = (PFN_PTRC_GLCREATEPROGRAMPROC)IntGetProcAddress("glCreateProgram");
  return _ptrc_glCreateProgram();
}

static GLuint CODEGEN_FUNCPTR Switch_CreateShader(GLenum type)
{
  _ptrc_glCreateShader = (PFN_PTRC_GLCREATESHADERPROC)IntGetProcAddress("glCreateShader");
  return _ptrc_glCreateShader(type);
}

static void CODEGEN_FUNCPTR Switch_DeleteProgram(GLuint program)
{
  _ptrc_glDeleteProgram = (PFN_PTRC_GLDELETEPROGRAMPROC)IntGetProcAddress("glDeleteProgram");
  _ptrc_glDeleteProgram(program);
}

static void CODEGEN_FUNCPTR Switch_DeleteShader(GLuint shader)
{
  _ptrc_glDeleteShader = (PFN_PTRC_GLDELETESHADERPROC)IntGetProcAddress("glDeleteShader");
  _ptrc_glDeleteShader(shader);
}

static void CODEGEN_FUNCPTR Switch_DetachShader(GLuint program, GLuint shader)
{
  _ptrc_glDetachShader = (PFN_PTRC_GLDETACHSHADERPROC)IntGetProcAddress("glDetachShader");
  _ptrc_glDetachShader(program, shader);
}

static void CODEGEN_FUNCPTR Switch_DisableVertexAttribArray(GLuint index)
{
  _ptrc_glDisableVertexAttribArray = (PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glDisableVertexAttribArray");
  _ptrc_glDisableVertexAttribArray(index);
}

static void CODEGEN_FUNCPTR Switch_DrawBuffers(GLsizei n, const GLenum * bufs)
{
  _ptrc_glDrawBuffers = (PFN_PTRC_GLDRAWBUFFERSPROC)IntGetProcAddress("glDrawBuffers");
  _ptrc_glDrawBuffers(n, bufs);
}

static void CODEGEN_FUNCPTR Switch_EnableVertexAttribArray(GLuint index)
{
  _ptrc_glEnableVertexAttribArray = (PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glEnableVertexAttribArray");
  _ptrc_glEnableVertexAttribArray(index);
}

static void CODEGEN_FUNCPTR Switch_GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
  _ptrc_glGetActiveAttrib = (PFN_PTRC_GLGETACTIVEATTRIBPROC)IntGetProcAddress("glGetActiveAttrib");
  _ptrc_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
  _ptrc_glGetActiveUniform = (PFN_PTRC_GLGETACTIVEUNIFORMPROC)IntGetProcAddress("glGetActiveUniform");
  _ptrc_glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{
  _ptrc_glGetAttachedShaders = (PFN_PTRC_GLGETATTACHEDSHADERSPROC)IntGetProcAddress("glGetAttachedShaders");
  _ptrc_glGetAttachedShaders(program, maxCount, count, shaders);
}

static GLint CODEGEN_FUNCPTR Switch_GetAttribLocation(GLuint program, const GLchar * name)
{
  _ptrc_glGetAttribLocation = (PFN_PTRC_GLGETATTRIBLOCATIONPROC)IntGetProcAddress("glGetAttribLocation");
  return _ptrc_glGetAttribLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
  _ptrc_glGetProgramInfoLog = (PFN_PTRC_GLGETPROGRAMINFOLOGPROC)IntGetProcAddress("glGetProgramInfoLog");
  _ptrc_glGetProgramInfoLog(program, bufSize, length, infoLog);
}

static void CODEGEN_FUNCPTR Switch_GetProgramiv(GLuint program, GLenum pname, GLint * params)
{
  _ptrc_glGetProgramiv = (PFN_PTRC_GLGETPROGRAMIVPROC)IntGetProcAddress("glGetProgramiv");
  _ptrc_glGetProgramiv(program, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
  _ptrc_glGetShaderInfoLog = (PFN_PTRC_GLGETSHADERINFOLOGPROC)IntGetProcAddress("glGetShaderInfoLog");
  _ptrc_glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

static void CODEGEN_FUNCPTR Switch_GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
  _ptrc_glGetShaderSource = (PFN_PTRC_GLGETSHADERSOURCEPROC)IntGetProcAddress("glGetShaderSource");
  _ptrc_glGetShaderSource(shader, bufSize, length, source);
}

static void CODEGEN_FUNCPTR Switch_GetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
  _ptrc_glGetShaderiv = (PFN_PTRC_GLGETSHADERIVPROC)IntGetProcAddress("glGetShaderiv");
  _ptrc_glGetShaderiv(shader, pname, params);
}

static GLint CODEGEN_FUNCPTR Switch_GetUniformLocation(GLuint program, const GLchar * name)
{
  _ptrc_glGetUniformLocation = (PFN_PTRC_GLGETUNIFORMLOCATIONPROC)IntGetProcAddress("glGetUniformLocation");
  return _ptrc_glGetUniformLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetUniformfv(GLuint program, GLint location, GLfloat * params)
{
  _ptrc_glGetUniformfv = (PFN_PTRC_GLGETUNIFORMFVPROC)IntGetProcAddress("glGetUniformfv");
  _ptrc_glGetUniformfv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetUniformiv(GLuint program, GLint location, GLint * params)
{
  _ptrc_glGetUniformiv = (PFN_PTRC_GLGETUNIFORMIVPROC)IntGetProcAddress("glGetUniformiv");
  _ptrc_glGetUniformiv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer)
{
  _ptrc_glGetVertexAttribPointerv = (PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC)IntGetProcAddress("glGetVertexAttribPointerv");
  _ptrc_glGetVertexAttribPointerv(index, pname, pointer);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
  _ptrc_glGetVertexAttribdv = (PFN_PTRC_GLGETVERTEXATTRIBDVPROC)IntGetProcAddress("glGetVertexAttribdv");
  _ptrc_glGetVertexAttribdv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
  _ptrc_glGetVertexAttribfv = (PFN_PTRC_GLGETVERTEXATTRIBFVPROC)IntGetProcAddress("glGetVertexAttribfv");
  _ptrc_glGetVertexAttribfv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
  _ptrc_glGetVertexAttribiv = (PFN_PTRC_GLGETVERTEXATTRIBIVPROC)IntGetProcAddress("glGetVertexAttribiv");
  _ptrc_glGetVertexAttribiv(index, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsProgram(GLuint program)
{
  _ptrc_glIsProgram = (PFN_PTRC_GLISPROGRAMPROC)IntGetProcAddress("glIsProgram");
  return _ptrc_glIsProgram(program);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsShader(GLuint shader)
{
  _ptrc_glIsShader = (PFN_PTRC_GLISSHADERPROC)IntGetProcAddress("glIsShader");
  return _ptrc_glIsShader(shader);
}

static void CODEGEN_FUNCPTR Switch_LinkProgram(GLuint program)
{
  _ptrc_glLinkProgram = (PFN_PTRC_GLLINKPROGRAMPROC)IntGetProcAddress("glLinkProgram");
  _ptrc_glLinkProgram(program);
}

static void CODEGEN_FUNCPTR Switch_ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length)
{
  _ptrc_glShaderSource = (PFN_PTRC_GLSHADERSOURCEPROC)IntGetProcAddress("glShaderSource");
  _ptrc_glShaderSource(shader, count, string, length);
}

static void CODEGEN_FUNCPTR Switch_StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
  _ptrc_glStencilFuncSeparate = (PFN_PTRC_GLSTENCILFUNCSEPARATEPROC)IntGetProcAddress("glStencilFuncSeparate");
  _ptrc_glStencilFuncSeparate(face, func, ref, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilMaskSeparate(GLenum face, GLuint mask)
{
  _ptrc_glStencilMaskSeparate = (PFN_PTRC_GLSTENCILMASKSEPARATEPROC)IntGetProcAddress("glStencilMaskSeparate");
  _ptrc_glStencilMaskSeparate(face, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
  _ptrc_glStencilOpSeparate = (PFN_PTRC_GLSTENCILOPSEPARATEPROC)IntGetProcAddress("glStencilOpSeparate");
  _ptrc_glStencilOpSeparate(face, sfail, dpfail, dppass);
}

static void CODEGEN_FUNCPTR Switch_Uniform1f(GLint location, GLfloat v0)
{
  _ptrc_glUniform1f = (PFN_PTRC_GLUNIFORM1FPROC)IntGetProcAddress("glUniform1f");
  _ptrc_glUniform1f(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1fv(GLint location, GLsizei count, const GLfloat * value)
{
  _ptrc_glUniform1fv = (PFN_PTRC_GLUNIFORM1FVPROC)IntGetProcAddress("glUniform1fv");
  _ptrc_glUniform1fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform1i(GLint location, GLint v0)
{
  _ptrc_glUniform1i = (PFN_PTRC_GLUNIFORM1IPROC)IntGetProcAddress("glUniform1i");
  _ptrc_glUniform1i(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1iv(GLint location, GLsizei count, const GLint * value)
{
  _ptrc_glUniform1iv = (PFN_PTRC_GLUNIFORM1IVPROC)IntGetProcAddress("glUniform1iv");
  _ptrc_glUniform1iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2f(GLint location, GLfloat v0, GLfloat v1)
{
  _ptrc_glUniform2f = (PFN_PTRC_GLUNIFORM2FPROC)IntGetProcAddress("glUniform2f");
  _ptrc_glUniform2f(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2fv(GLint location, GLsizei count, const GLfloat * value)
{
  _ptrc_glUniform2fv = (PFN_PTRC_GLUNIFORM2FVPROC)IntGetProcAddress("glUniform2fv");
  _ptrc_glUniform2fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2i(GLint location, GLint v0, GLint v1)
{
  _ptrc_glUniform2i = (PFN_PTRC_GLUNIFORM2IPROC)IntGetProcAddress("glUniform2i");
  _ptrc_glUniform2i(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2iv(GLint location, GLsizei count, const GLint * value)
{
  _ptrc_glUniform2iv = (PFN_PTRC_GLUNIFORM2IVPROC)IntGetProcAddress("glUniform2iv");
  _ptrc_glUniform2iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  _ptrc_glUniform3f = (PFN_PTRC_GLUNIFORM3FPROC)IntGetProcAddress("glUniform3f");
  _ptrc_glUniform3f(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3fv(GLint location, GLsizei count, const GLfloat * value)
{
  _ptrc_glUniform3fv = (PFN_PTRC_GLUNIFORM3FVPROC)IntGetProcAddress("glUniform3fv");
  _ptrc_glUniform3fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
  _ptrc_glUniform3i = (PFN_PTRC_GLUNIFORM3IPROC)IntGetProcAddress("glUniform3i");
  _ptrc_glUniform3i(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3iv(GLint location, GLsizei count, const GLint * value)
{
  _ptrc_glUniform3iv = (PFN_PTRC_GLUNIFORM3IVPROC)IntGetProcAddress("glUniform3iv");
  _ptrc_glUniform3iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  _ptrc_glUniform4f = (PFN_PTRC_GLUNIFORM4FPROC)IntGetProcAddress("glUniform4f");
  _ptrc_glUniform4f(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4fv(GLint location, GLsizei count, const GLfloat * value)
{
  _ptrc_glUniform4fv = (PFN_PTRC_GLUNIFORM4FVPROC)IntGetProcAddress("glUniform4fv");
  _ptrc_glUniform4fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  _ptrc_glUniform4i = (PFN_PTRC_GLUNIFORM4IPROC)IntGetProcAddress("glUniform4i");
  _ptrc_glUniform4i(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4iv(GLint location, GLsizei count, const GLint * value)
{
  _ptrc_glUniform4iv = (PFN_PTRC_GLUNIFORM4IVPROC)IntGetProcAddress("glUniform4iv");
  _ptrc_glUniform4iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix2fv = (PFN_PTRC_GLUNIFORMMATRIX2FVPROC)IntGetProcAddress("glUniformMatrix2fv");
  _ptrc_glUniformMatrix2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix3fv = (PFN_PTRC_GLUNIFORMMATRIX3FVPROC)IntGetProcAddress("glUniformMatrix3fv");
  _ptrc_glUniformMatrix3fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix4fv = (PFN_PTRC_GLUNIFORMMATRIX4FVPROC)IntGetProcAddress("glUniformMatrix4fv");
  _ptrc_glUniformMatrix4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UseProgram(GLuint program)
{
  _ptrc_glUseProgram = (PFN_PTRC_GLUSEPROGRAMPROC)IntGetProcAddress("glUseProgram");
  _ptrc_glUseProgram(program);
}

static void CODEGEN_FUNCPTR Switch_ValidateProgram(GLuint program)
{
  _ptrc_glValidateProgram = (PFN_PTRC_GLVALIDATEPROGRAMPROC)IntGetProcAddress("glValidateProgram");
  _ptrc_glValidateProgram(program);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1d(GLuint index, GLdouble x)
{
  _ptrc_glVertexAttrib1d = (PFN_PTRC_GLVERTEXATTRIB1DPROC)IntGetProcAddress("glVertexAttrib1d");
  _ptrc_glVertexAttrib1d(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1dv(GLuint index, const GLdouble * v)
{
  _ptrc_glVertexAttrib1dv = (PFN_PTRC_GLVERTEXATTRIB1DVPROC)IntGetProcAddress("glVertexAttrib1dv");
  _ptrc_glVertexAttrib1dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1f(GLuint index, GLfloat x)
{
  _ptrc_glVertexAttrib1f = (PFN_PTRC_GLVERTEXATTRIB1FPROC)IntGetProcAddress("glVertexAttrib1f");
  _ptrc_glVertexAttrib1f(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1fv(GLuint index, const GLfloat * v)
{
  _ptrc_glVertexAttrib1fv = (PFN_PTRC_GLVERTEXATTRIB1FVPROC)IntGetProcAddress("glVertexAttrib1fv");
  _ptrc_glVertexAttrib1fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1s(GLuint index, GLshort x)
{
  _ptrc_glVertexAttrib1s = (PFN_PTRC_GLVERTEXATTRIB1SPROC)IntGetProcAddress("glVertexAttrib1s");
  _ptrc_glVertexAttrib1s(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1sv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttrib1sv = (PFN_PTRC_GLVERTEXATTRIB1SVPROC)IntGetProcAddress("glVertexAttrib1sv");
  _ptrc_glVertexAttrib1sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
  _ptrc_glVertexAttrib2d = (PFN_PTRC_GLVERTEXATTRIB2DPROC)IntGetProcAddress("glVertexAttrib2d");
  _ptrc_glVertexAttrib2d(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2dv(GLuint index, const GLdouble * v)
{
  _ptrc_glVertexAttrib2dv = (PFN_PTRC_GLVERTEXATTRIB2DVPROC)IntGetProcAddress("glVertexAttrib2dv");
  _ptrc_glVertexAttrib2dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
  _ptrc_glVertexAttrib2f = (PFN_PTRC_GLVERTEXATTRIB2FPROC)IntGetProcAddress("glVertexAttrib2f");
  _ptrc_glVertexAttrib2f(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2fv(GLuint index, const GLfloat * v)
{
  _ptrc_glVertexAttrib2fv = (PFN_PTRC_GLVERTEXATTRIB2FVPROC)IntGetProcAddress("glVertexAttrib2fv");
  _ptrc_glVertexAttrib2fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
  _ptrc_glVertexAttrib2s = (PFN_PTRC_GLVERTEXATTRIB2SPROC)IntGetProcAddress("glVertexAttrib2s");
  _ptrc_glVertexAttrib2s(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2sv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttrib2sv = (PFN_PTRC_GLVERTEXATTRIB2SVPROC)IntGetProcAddress("glVertexAttrib2sv");
  _ptrc_glVertexAttrib2sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
  _ptrc_glVertexAttrib3d = (PFN_PTRC_GLVERTEXATTRIB3DPROC)IntGetProcAddress("glVertexAttrib3d");
  _ptrc_glVertexAttrib3d(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3dv(GLuint index, const GLdouble * v)
{
  _ptrc_glVertexAttrib3dv = (PFN_PTRC_GLVERTEXATTRIB3DVPROC)IntGetProcAddress("glVertexAttrib3dv");
  _ptrc_glVertexAttrib3dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
  _ptrc_glVertexAttrib3f = (PFN_PTRC_GLVERTEXATTRIB3FPROC)IntGetProcAddress("glVertexAttrib3f");
  _ptrc_glVertexAttrib3f(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3fv(GLuint index, const GLfloat * v)
{
  _ptrc_glVertexAttrib3fv = (PFN_PTRC_GLVERTEXATTRIB3FVPROC)IntGetProcAddress("glVertexAttrib3fv");
  _ptrc_glVertexAttrib3fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
  _ptrc_glVertexAttrib3s = (PFN_PTRC_GLVERTEXATTRIB3SPROC)IntGetProcAddress("glVertexAttrib3s");
  _ptrc_glVertexAttrib3s(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3sv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttrib3sv = (PFN_PTRC_GLVERTEXATTRIB3SVPROC)IntGetProcAddress("glVertexAttrib3sv");
  _ptrc_glVertexAttrib3sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nbv(GLuint index, const GLbyte * v)
{
  _ptrc_glVertexAttrib4Nbv = (PFN_PTRC_GLVERTEXATTRIB4NBVPROC)IntGetProcAddress("glVertexAttrib4Nbv");
  _ptrc_glVertexAttrib4Nbv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Niv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttrib4Niv = (PFN_PTRC_GLVERTEXATTRIB4NIVPROC)IntGetProcAddress("glVertexAttrib4Niv");
  _ptrc_glVertexAttrib4Niv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nsv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttrib4Nsv = (PFN_PTRC_GLVERTEXATTRIB4NSVPROC)IntGetProcAddress("glVertexAttrib4Nsv");
  _ptrc_glVertexAttrib4Nsv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
  _ptrc_glVertexAttrib4Nub = (PFN_PTRC_GLVERTEXATTRIB4NUBPROC)IntGetProcAddress("glVertexAttrib4Nub");
  _ptrc_glVertexAttrib4Nub(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nubv(GLuint index, const GLubyte * v)
{
  _ptrc_glVertexAttrib4Nubv = (PFN_PTRC_GLVERTEXATTRIB4NUBVPROC)IntGetProcAddress("glVertexAttrib4Nubv");
  _ptrc_glVertexAttrib4Nubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nuiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttrib4Nuiv = (PFN_PTRC_GLVERTEXATTRIB4NUIVPROC)IntGetProcAddress("glVertexAttrib4Nuiv");
  _ptrc_glVertexAttrib4Nuiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nusv(GLuint index, const GLushort * v)
{
  _ptrc_glVertexAttrib4Nusv = (PFN_PTRC_GLVERTEXATTRIB4NUSVPROC)IntGetProcAddress("glVertexAttrib4Nusv");
  _ptrc_glVertexAttrib4Nusv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4bv(GLuint index, const GLbyte * v)
{
  _ptrc_glVertexAttrib4bv = (PFN_PTRC_GLVERTEXATTRIB4BVPROC)IntGetProcAddress("glVertexAttrib4bv");
  _ptrc_glVertexAttrib4bv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  _ptrc_glVertexAttrib4d = (PFN_PTRC_GLVERTEXATTRIB4DPROC)IntGetProcAddress("glVertexAttrib4d");
  _ptrc_glVertexAttrib4d(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4dv(GLuint index, const GLdouble * v)
{
  _ptrc_glVertexAttrib4dv = (PFN_PTRC_GLVERTEXATTRIB4DVPROC)IntGetProcAddress("glVertexAttrib4dv");
  _ptrc_glVertexAttrib4dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  _ptrc_glVertexAttrib4f = (PFN_PTRC_GLVERTEXATTRIB4FPROC)IntGetProcAddress("glVertexAttrib4f");
  _ptrc_glVertexAttrib4f(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4fv(GLuint index, const GLfloat * v)
{
  _ptrc_glVertexAttrib4fv = (PFN_PTRC_GLVERTEXATTRIB4FVPROC)IntGetProcAddress("glVertexAttrib4fv");
  _ptrc_glVertexAttrib4fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4iv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttrib4iv = (PFN_PTRC_GLVERTEXATTRIB4IVPROC)IntGetProcAddress("glVertexAttrib4iv");
  _ptrc_glVertexAttrib4iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
  _ptrc_glVertexAttrib4s = (PFN_PTRC_GLVERTEXATTRIB4SPROC)IntGetProcAddress("glVertexAttrib4s");
  _ptrc_glVertexAttrib4s(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4sv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttrib4sv = (PFN_PTRC_GLVERTEXATTRIB4SVPROC)IntGetProcAddress("glVertexAttrib4sv");
  _ptrc_glVertexAttrib4sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4ubv(GLuint index, const GLubyte * v)
{
  _ptrc_glVertexAttrib4ubv = (PFN_PTRC_GLVERTEXATTRIB4UBVPROC)IntGetProcAddress("glVertexAttrib4ubv");
  _ptrc_glVertexAttrib4ubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4uiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttrib4uiv = (PFN_PTRC_GLVERTEXATTRIB4UIVPROC)IntGetProcAddress("glVertexAttrib4uiv");
  _ptrc_glVertexAttrib4uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4usv(GLuint index, const GLushort * v)
{
  _ptrc_glVertexAttrib4usv = (PFN_PTRC_GLVERTEXATTRIB4USVPROC)IntGetProcAddress("glVertexAttrib4usv");
  _ptrc_glVertexAttrib4usv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
  _ptrc_glVertexAttribPointer = (PFN_PTRC_GLVERTEXATTRIBPOINTERPROC)IntGetProcAddress("glVertexAttribPointer");
  _ptrc_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}


/* Extension: 2.1*/
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix2x3fv = (PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glUniformMatrix2x3fv");
  _ptrc_glUniformMatrix2x3fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix2x4fv = (PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glUniformMatrix2x4fv");
  _ptrc_glUniformMatrix2x4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix3x2fv = (PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glUniformMatrix3x2fv");
  _ptrc_glUniformMatrix3x2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix3x4fv = (PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glUniformMatrix3x4fv");
  _ptrc_glUniformMatrix3x4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix4x2fv = (PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glUniformMatrix4x2fv");
  _ptrc_glUniformMatrix4x2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
  _ptrc_glUniformMatrix4x3fv = (PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glUniformMatrix4x3fv");
  _ptrc_glUniformMatrix4x3fv(location, count, transpose, value);
}


/* Extension: 3.0*/
static void CODEGEN_FUNCPTR Switch_BeginConditionalRender(GLuint id, GLenum mode)
{
  _ptrc_glBeginConditionalRender = (PFN_PTRC_GLBEGINCONDITIONALRENDERPROC)IntGetProcAddress("glBeginConditionalRender");
  _ptrc_glBeginConditionalRender(id, mode);
}

static void CODEGEN_FUNCPTR Switch_BeginTransformFeedback(GLenum primitiveMode)
{
  _ptrc_glBeginTransformFeedback = (PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBeginTransformFeedback");
  _ptrc_glBeginTransformFeedback(primitiveMode);
}

static void CODEGEN_FUNCPTR Switch_BindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
  _ptrc_glBindBufferBase = (PFN_PTRC_GLBINDBUFFERBASEPROC)IntGetProcAddress("glBindBufferBase");
  _ptrc_glBindBufferBase(target, index, buffer);
}

static void CODEGEN_FUNCPTR Switch_BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  _ptrc_glBindBufferRange = (PFN_PTRC_GLBINDBUFFERRANGEPROC)IntGetProcAddress("glBindBufferRange");
  _ptrc_glBindBufferRange(target, index, buffer, offset, size);
}

static void CODEGEN_FUNCPTR Switch_BindFragDataLocation(GLuint program, GLuint color, const GLchar * name)
{
  _ptrc_glBindFragDataLocation = (PFN_PTRC_GLBINDFRAGDATALOCATIONPROC)IntGetProcAddress("glBindFragDataLocation");
  _ptrc_glBindFragDataLocation(program, color, name);
}

static void CODEGEN_FUNCPTR Switch_BindFramebuffer(GLenum target, GLuint framebuffer)
{
  _ptrc_glBindFramebuffer = (PFN_PTRC_GLBINDFRAMEBUFFERPROC)IntGetProcAddress("glBindFramebuffer");
  _ptrc_glBindFramebuffer(target, framebuffer);
}

static void CODEGEN_FUNCPTR Switch_BindRenderbuffer(GLenum target, GLuint renderbuffer)
{
  _ptrc_glBindRenderbuffer = (PFN_PTRC_GLBINDRENDERBUFFERPROC)IntGetProcAddress("glBindRenderbuffer");
  _ptrc_glBindRenderbuffer(target, renderbuffer);
}

static void CODEGEN_FUNCPTR Switch_BindVertexArray(GLuint ren_array)
{
  _ptrc_glBindVertexArray = (PFN_PTRC_GLBINDVERTEXARRAYPROC)IntGetProcAddress("glBindVertexArray");
  _ptrc_glBindVertexArray(ren_array);
}

static void CODEGEN_FUNCPTR Switch_BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  _ptrc_glBlitFramebuffer = (PFN_PTRC_GLBLITFRAMEBUFFERPROC)IntGetProcAddress("glBlitFramebuffer");
  _ptrc_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

static GLenum CODEGEN_FUNCPTR Switch_CheckFramebufferStatus(GLenum target)
{
  _ptrc_glCheckFramebufferStatus = (PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC)IntGetProcAddress("glCheckFramebufferStatus");
  return _ptrc_glCheckFramebufferStatus(target);
}

static void CODEGEN_FUNCPTR Switch_ClampColor(GLenum target, GLenum clamp)
{
  _ptrc_glClampColor = (PFN_PTRC_GLCLAMPCOLORPROC)IntGetProcAddress("glClampColor");
  _ptrc_glClampColor(target, clamp);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
  _ptrc_glClearBufferfi = (PFN_PTRC_GLCLEARBUFFERFIPROC)IntGetProcAddress("glClearBufferfi");
  _ptrc_glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value)
{
  _ptrc_glClearBufferfv = (PFN_PTRC_GLCLEARBUFFERFVPROC)IntGetProcAddress("glClearBufferfv");
  _ptrc_glClearBufferfv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value)
{
  _ptrc_glClearBufferiv = (PFN_PTRC_GLCLEARBUFFERIVPROC)IntGetProcAddress("glClearBufferiv");
  _ptrc_glClearBufferiv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value)
{
  _ptrc_glClearBufferuiv = (PFN_PTRC_GLCLEARBUFFERUIVPROC)IntGetProcAddress("glClearBufferuiv");
  _ptrc_glClearBufferuiv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
  _ptrc_glColorMaski = (PFN_PTRC_GLCOLORMASKIPROC)IntGetProcAddress("glColorMaski");
  _ptrc_glColorMaski(index, r, g, b, a);
}

static void CODEGEN_FUNCPTR Switch_DeleteFramebuffers(GLsizei n, const GLuint * framebuffers)
{
  _ptrc_glDeleteFramebuffers = (PFN_PTRC_GLDELETEFRAMEBUFFERSPROC)IntGetProcAddress("glDeleteFramebuffers");
  _ptrc_glDeleteFramebuffers(n, framebuffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers)
{
  _ptrc_glDeleteRenderbuffers = (PFN_PTRC_GLDELETERENDERBUFFERSPROC)IntGetProcAddress("glDeleteRenderbuffers");
  _ptrc_glDeleteRenderbuffers(n, renderbuffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteVertexArrays(GLsizei n, const GLuint * arrays)
{
  _ptrc_glDeleteVertexArrays = (PFN_PTRC_GLDELETEVERTEXARRAYSPROC)IntGetProcAddress("glDeleteVertexArrays");
  _ptrc_glDeleteVertexArrays(n, arrays);
}

static void CODEGEN_FUNCPTR Switch_Disablei(GLenum target, GLuint index)
{
  _ptrc_glDisablei = (PFN_PTRC_GLDISABLEIPROC)IntGetProcAddress("glDisablei");
  _ptrc_glDisablei(target, index);
}

static void CODEGEN_FUNCPTR Switch_Enablei(GLenum target, GLuint index)
{
  _ptrc_glEnablei = (PFN_PTRC_GLENABLEIPROC)IntGetProcAddress("glEnablei");
  _ptrc_glEnablei(target, index);
}

static void CODEGEN_FUNCPTR Switch_EndConditionalRender(void)
{
  _ptrc_glEndConditionalRender = (PFN_PTRC_GLENDCONDITIONALRENDERPROC)IntGetProcAddress("glEndConditionalRender");
  _ptrc_glEndConditionalRender();
}

static void CODEGEN_FUNCPTR Switch_EndTransformFeedback(void)
{
  _ptrc_glEndTransformFeedback = (PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glEndTransformFeedback");
  _ptrc_glEndTransformFeedback();
}

static void CODEGEN_FUNCPTR Switch_FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
  _ptrc_glFlushMappedBufferRange = (PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedBufferRange");
  _ptrc_glFlushMappedBufferRange(target, offset, length);
}

static void CODEGEN_FUNCPTR Switch_FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  _ptrc_glFramebufferRenderbuffer = (PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC)IntGetProcAddress("glFramebufferRenderbuffer");
  _ptrc_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  _ptrc_glFramebufferTexture1D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC)IntGetProcAddress("glFramebufferTexture1D");
  _ptrc_glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  _ptrc_glFramebufferTexture2D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC)IntGetProcAddress("glFramebufferTexture2D");
  _ptrc_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
  _ptrc_glFramebufferTexture3D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC)IntGetProcAddress("glFramebufferTexture3D");
  _ptrc_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
  _ptrc_glFramebufferTextureLayer = (PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC)IntGetProcAddress("glFramebufferTextureLayer");
  _ptrc_glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

static void CODEGEN_FUNCPTR Switch_GenFramebuffers(GLsizei n, GLuint * framebuffers)
{
  _ptrc_glGenFramebuffers = (PFN_PTRC_GLGENFRAMEBUFFERSPROC)IntGetProcAddress("glGenFramebuffers");
  _ptrc_glGenFramebuffers(n, framebuffers);
}

static void CODEGEN_FUNCPTR Switch_GenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
  _ptrc_glGenRenderbuffers = (PFN_PTRC_GLGENRENDERBUFFERSPROC)IntGetProcAddress("glGenRenderbuffers");
  _ptrc_glGenRenderbuffers(n, renderbuffers);
}

static void CODEGEN_FUNCPTR Switch_GenVertexArrays(GLsizei n, GLuint * arrays)
{
  _ptrc_glGenVertexArrays = (PFN_PTRC_GLGENVERTEXARRAYSPROC)IntGetProcAddress("glGenVertexArrays");
  _ptrc_glGenVertexArrays(n, arrays);
}

static void CODEGEN_FUNCPTR Switch_GenerateMipmap(GLenum target)
{
  _ptrc_glGenerateMipmap = (PFN_PTRC_GLGENERATEMIPMAPPROC)IntGetProcAddress("glGenerateMipmap");
  _ptrc_glGenerateMipmap(target);
}

static void CODEGEN_FUNCPTR Switch_GetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
  _ptrc_glGetBooleani_v = (PFN_PTRC_GLGETBOOLEANI_VPROC)IntGetProcAddress("glGetBooleani_v");
  _ptrc_glGetBooleani_v(target, index, data);
}

static GLint CODEGEN_FUNCPTR Switch_GetFragDataLocation(GLuint program, const GLchar * name)
{
  _ptrc_glGetFragDataLocation = (PFN_PTRC_GLGETFRAGDATALOCATIONPROC)IntGetProcAddress("glGetFragDataLocation");
  return _ptrc_glGetFragDataLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
  _ptrc_glGetFramebufferAttachmentParameteriv = (PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)IntGetProcAddress("glGetFramebufferAttachmentParameteriv");
  _ptrc_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
  _ptrc_glGetIntegeri_v = (PFN_PTRC_GLGETINTEGERI_VPROC)IntGetProcAddress("glGetIntegeri_v");
  _ptrc_glGetIntegeri_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
  _ptrc_glGetRenderbufferParameteriv = (PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetRenderbufferParameteriv");
  _ptrc_glGetRenderbufferParameteriv(target, pname, params);
}

static const GLubyte * CODEGEN_FUNCPTR Switch_GetStringi(GLenum name, GLuint index)
{
  _ptrc_glGetStringi = (PFN_PTRC_GLGETSTRINGIPROC)IntGetProcAddress("glGetStringi");
  return _ptrc_glGetStringi(name, index);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
  _ptrc_glGetTexParameterIiv = (PFN_PTRC_GLGETTEXPARAMETERIIVPROC)IntGetProcAddress("glGetTexParameterIiv");
  _ptrc_glGetTexParameterIiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
  _ptrc_glGetTexParameterIuiv = (PFN_PTRC_GLGETTEXPARAMETERIUIVPROC)IntGetProcAddress("glGetTexParameterIuiv");
  _ptrc_glGetTexParameterIuiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
  _ptrc_glGetTransformFeedbackVarying = (PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC)IntGetProcAddress("glGetTransformFeedbackVarying");
  _ptrc_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetUniformuiv(GLuint program, GLint location, GLuint * params)
{
  _ptrc_glGetUniformuiv = (PFN_PTRC_GLGETUNIFORMUIVPROC)IntGetProcAddress("glGetUniformuiv");
  _ptrc_glGetUniformuiv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
  _ptrc_glGetVertexAttribIiv = (PFN_PTRC_GLGETVERTEXATTRIBIIVPROC)IntGetProcAddress("glGetVertexAttribIiv");
  _ptrc_glGetVertexAttribIiv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
  _ptrc_glGetVertexAttribIuiv = (PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC)IntGetProcAddress("glGetVertexAttribIuiv");
  _ptrc_glGetVertexAttribIuiv(index, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsEnabledi(GLenum target, GLuint index)
{
  _ptrc_glIsEnabledi = (PFN_PTRC_GLISENABLEDIPROC)IntGetProcAddress("glIsEnabledi");
  return _ptrc_glIsEnabledi(target, index);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsFramebuffer(GLuint framebuffer)
{
  _ptrc_glIsFramebuffer = (PFN_PTRC_GLISFRAMEBUFFERPROC)IntGetProcAddress("glIsFramebuffer");
  return _ptrc_glIsFramebuffer(framebuffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsRenderbuffer(GLuint renderbuffer)
{
  _ptrc_glIsRenderbuffer = (PFN_PTRC_GLISRENDERBUFFERPROC)IntGetProcAddress("glIsRenderbuffer");
  return _ptrc_glIsRenderbuffer(renderbuffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsVertexArray(GLuint ren_array)
{
  _ptrc_glIsVertexArray = (PFN_PTRC_GLISVERTEXARRAYPROC)IntGetProcAddress("glIsVertexArray");
  return _ptrc_glIsVertexArray(ren_array);
}

static void * CODEGEN_FUNCPTR Switch_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  _ptrc_glMapBufferRange = (PFN_PTRC_GLMAPBUFFERRANGEPROC)IntGetProcAddress("glMapBufferRange");
  return _ptrc_glMapBufferRange(target, offset, length, access);
}

static void CODEGEN_FUNCPTR Switch_RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
  _ptrc_glRenderbufferStorage = (PFN_PTRC_GLRENDERBUFFERSTORAGEPROC)IntGetProcAddress("glRenderbufferStorage");
  _ptrc_glRenderbufferStorage(target, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
  _ptrc_glRenderbufferStorageMultisample = (PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC)IntGetProcAddress("glRenderbufferStorageMultisample");
  _ptrc_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_TexParameterIiv(GLenum target, GLenum pname, const GLint * params)
{
  _ptrc_glTexParameterIiv = (PFN_PTRC_GLTEXPARAMETERIIVPROC)IntGetProcAddress("glTexParameterIiv");
  _ptrc_glTexParameterIiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params)
{
  _ptrc_glTexParameterIuiv = (PFN_PTRC_GLTEXPARAMETERIUIVPROC)IntGetProcAddress("glTexParameterIuiv");
  _ptrc_glTexParameterIuiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode)
{
  _ptrc_glTransformFeedbackVaryings = (PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC)IntGetProcAddress("glTransformFeedbackVaryings");
  _ptrc_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

static void CODEGEN_FUNCPTR Switch_Uniform1ui(GLint location, GLuint v0)
{
  _ptrc_glUniform1ui = (PFN_PTRC_GLUNIFORM1UIPROC)IntGetProcAddress("glUniform1ui");
  _ptrc_glUniform1ui(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1uiv(GLint location, GLsizei count, const GLuint * value)
{
  _ptrc_glUniform1uiv = (PFN_PTRC_GLUNIFORM1UIVPROC)IntGetProcAddress("glUniform1uiv");
  _ptrc_glUniform1uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2ui(GLint location, GLuint v0, GLuint v1)
{
  _ptrc_glUniform2ui = (PFN_PTRC_GLUNIFORM2UIPROC)IntGetProcAddress("glUniform2ui");
  _ptrc_glUniform2ui(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2uiv(GLint location, GLsizei count, const GLuint * value)
{
  _ptrc_glUniform2uiv = (PFN_PTRC_GLUNIFORM2UIVPROC)IntGetProcAddress("glUniform2uiv");
  _ptrc_glUniform2uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
  _ptrc_glUniform3ui = (PFN_PTRC_GLUNIFORM3UIPROC)IntGetProcAddress("glUniform3ui");
  _ptrc_glUniform3ui(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3uiv(GLint location, GLsizei count, const GLuint * value)
{
  _ptrc_glUniform3uiv = (PFN_PTRC_GLUNIFORM3UIVPROC)IntGetProcAddress("glUniform3uiv");
  _ptrc_glUniform3uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  _ptrc_glUniform4ui = (PFN_PTRC_GLUNIFORM4UIPROC)IntGetProcAddress("glUniform4ui");
  _ptrc_glUniform4ui(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4uiv(GLint location, GLsizei count, const GLuint * value)
{
  _ptrc_glUniform4uiv = (PFN_PTRC_GLUNIFORM4UIVPROC)IntGetProcAddress("glUniform4uiv");
  _ptrc_glUniform4uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1i(GLuint index, GLint x)
{
  _ptrc_glVertexAttribI1i = (PFN_PTRC_GLVERTEXATTRIBI1IPROC)IntGetProcAddress("glVertexAttribI1i");
  _ptrc_glVertexAttribI1i(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1iv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttribI1iv = (PFN_PTRC_GLVERTEXATTRIBI1IVPROC)IntGetProcAddress("glVertexAttribI1iv");
  _ptrc_glVertexAttribI1iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1ui(GLuint index, GLuint x)
{
  _ptrc_glVertexAttribI1ui = (PFN_PTRC_GLVERTEXATTRIBI1UIPROC)IntGetProcAddress("glVertexAttribI1ui");
  _ptrc_glVertexAttribI1ui(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1uiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttribI1uiv = (PFN_PTRC_GLVERTEXATTRIBI1UIVPROC)IntGetProcAddress("glVertexAttribI1uiv");
  _ptrc_glVertexAttribI1uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2i(GLuint index, GLint x, GLint y)
{
  _ptrc_glVertexAttribI2i = (PFN_PTRC_GLVERTEXATTRIBI2IPROC)IntGetProcAddress("glVertexAttribI2i");
  _ptrc_glVertexAttribI2i(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2iv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttribI2iv = (PFN_PTRC_GLVERTEXATTRIBI2IVPROC)IntGetProcAddress("glVertexAttribI2iv");
  _ptrc_glVertexAttribI2iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
  _ptrc_glVertexAttribI2ui = (PFN_PTRC_GLVERTEXATTRIBI2UIPROC)IntGetProcAddress("glVertexAttribI2ui");
  _ptrc_glVertexAttribI2ui(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2uiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttribI2uiv = (PFN_PTRC_GLVERTEXATTRIBI2UIVPROC)IntGetProcAddress("glVertexAttribI2uiv");
  _ptrc_glVertexAttribI2uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
  _ptrc_glVertexAttribI3i = (PFN_PTRC_GLVERTEXATTRIBI3IPROC)IntGetProcAddress("glVertexAttribI3i");
  _ptrc_glVertexAttribI3i(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3iv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttribI3iv = (PFN_PTRC_GLVERTEXATTRIBI3IVPROC)IntGetProcAddress("glVertexAttribI3iv");
  _ptrc_glVertexAttribI3iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
  _ptrc_glVertexAttribI3ui = (PFN_PTRC_GLVERTEXATTRIBI3UIPROC)IntGetProcAddress("glVertexAttribI3ui");
  _ptrc_glVertexAttribI3ui(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3uiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttribI3uiv = (PFN_PTRC_GLVERTEXATTRIBI3UIVPROC)IntGetProcAddress("glVertexAttribI3uiv");
  _ptrc_glVertexAttribI3uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4bv(GLuint index, const GLbyte * v)
{
  _ptrc_glVertexAttribI4bv = (PFN_PTRC_GLVERTEXATTRIBI4BVPROC)IntGetProcAddress("glVertexAttribI4bv");
  _ptrc_glVertexAttribI4bv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
  _ptrc_glVertexAttribI4i = (PFN_PTRC_GLVERTEXATTRIBI4IPROC)IntGetProcAddress("glVertexAttribI4i");
  _ptrc_glVertexAttribI4i(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4iv(GLuint index, const GLint * v)
{
  _ptrc_glVertexAttribI4iv = (PFN_PTRC_GLVERTEXATTRIBI4IVPROC)IntGetProcAddress("glVertexAttribI4iv");
  _ptrc_glVertexAttribI4iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4sv(GLuint index, const GLshort * v)
{
  _ptrc_glVertexAttribI4sv = (PFN_PTRC_GLVERTEXATTRIBI4SVPROC)IntGetProcAddress("glVertexAttribI4sv");
  _ptrc_glVertexAttribI4sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4ubv(GLuint index, const GLubyte * v)
{
  _ptrc_glVertexAttribI4ubv = (PFN_PTRC_GLVERTEXATTRIBI4UBVPROC)IntGetProcAddress("glVertexAttribI4ubv");
  _ptrc_glVertexAttribI4ubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
  _ptrc_glVertexAttribI4ui = (PFN_PTRC_GLVERTEXATTRIBI4UIPROC)IntGetProcAddress("glVertexAttribI4ui");
  _ptrc_glVertexAttribI4ui(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4uiv(GLuint index, const GLuint * v)
{
  _ptrc_glVertexAttribI4uiv = (PFN_PTRC_GLVERTEXATTRIBI4UIVPROC)IntGetProcAddress("glVertexAttribI4uiv");
  _ptrc_glVertexAttribI4uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4usv(GLuint index, const GLushort * v)
{
  _ptrc_glVertexAttribI4usv = (PFN_PTRC_GLVERTEXATTRIBI4USVPROC)IntGetProcAddress("glVertexAttribI4usv");
  _ptrc_glVertexAttribI4usv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  _ptrc_glVertexAttribIPointer = (PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC)IntGetProcAddress("glVertexAttribIPointer");
  _ptrc_glVertexAttribIPointer(index, size, type, stride, pointer);
}


/* Extension: 3.1*/
static void CODEGEN_FUNCPTR Switch_CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  _ptrc_glCopyBufferSubData = (PFN_PTRC_GLCOPYBUFFERSUBDATAPROC)IntGetProcAddress("glCopyBufferSubData");
  _ptrc_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

static void CODEGEN_FUNCPTR Switch_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
  _ptrc_glDrawArraysInstanced = (PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC)IntGetProcAddress("glDrawArraysInstanced");
  _ptrc_glDrawArraysInstanced(mode, first, count, instancecount);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
{
  _ptrc_glDrawElementsInstanced = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC)IntGetProcAddress("glDrawElementsInstanced");
  _ptrc_glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
  _ptrc_glGetActiveUniformBlockName = (PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC)IntGetProcAddress("glGetActiveUniformBlockName");
  _ptrc_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
  _ptrc_glGetActiveUniformBlockiv = (PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC)IntGetProcAddress("glGetActiveUniformBlockiv");
  _ptrc_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
  _ptrc_glGetActiveUniformName = (PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveUniformName");
  _ptrc_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params)
{
  _ptrc_glGetActiveUniformsiv = (PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC)IntGetProcAddress("glGetActiveUniformsiv");
  _ptrc_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

static GLuint CODEGEN_FUNCPTR Switch_GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName)
{
  _ptrc_glGetUniformBlockIndex = (PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC)IntGetProcAddress("glGetUniformBlockIndex");
  return _ptrc_glGetUniformBlockIndex(program, uniformBlockName);
}

static void CODEGEN_FUNCPTR Switch_GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
{
  _ptrc_glGetUniformIndices = (PFN_PTRC_GLGETUNIFORMINDICESPROC)IntGetProcAddress("glGetUniformIndices");
  _ptrc_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

static void CODEGEN_FUNCPTR Switch_PrimitiveRestartIndex(GLuint index)
{
  _ptrc_glPrimitiveRestartIndex = (PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC)IntGetProcAddress("glPrimitiveRestartIndex");
  _ptrc_glPrimitiveRestartIndex(index);
}

static void CODEGEN_FUNCPTR Switch_TexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
  _ptrc_glTexBuffer = (PFN_PTRC_GLTEXBUFFERPROC)IntGetProcAddress("glTexBuffer");
  _ptrc_glTexBuffer(target, internalformat, buffer);
}

static void CODEGEN_FUNCPTR Switch_UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
  _ptrc_glUniformBlockBinding = (PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC)IntGetProcAddress("glUniformBlockBinding");
  _ptrc_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}


/* Extension: 3.2*/
static GLenum CODEGEN_FUNCPTR Switch_ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  _ptrc_glClientWaitSync = (PFN_PTRC_GLCLIENTWAITSYNCPROC)IntGetProcAddress("glClientWaitSync");
  return _ptrc_glClientWaitSync(sync, flags, timeout);
}

static void CODEGEN_FUNCPTR Switch_DeleteSync(GLsync sync)
{
  _ptrc_glDeleteSync = (PFN_PTRC_GLDELETESYNCPROC)IntGetProcAddress("glDeleteSync");
  _ptrc_glDeleteSync(sync);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
  _ptrc_glDrawElementsBaseVertex = (PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawElementsBaseVertex");
  _ptrc_glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
{
  _ptrc_glDrawElementsInstancedBaseVertex = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertex");
  _ptrc_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

static void CODEGEN_FUNCPTR Switch_DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
  _ptrc_glDrawRangeElementsBaseVertex = (PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawRangeElementsBaseVertex");
  _ptrc_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

static GLsync CODEGEN_FUNCPTR Switch_FenceSync(GLenum condition, GLbitfield flags)
{
  _ptrc_glFenceSync = (PFN_PTRC_GLFENCESYNCPROC)IntGetProcAddress("glFenceSync");
  return _ptrc_glFenceSync(condition, flags);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
  _ptrc_glFramebufferTexture = (PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glFramebufferTexture");
  _ptrc_glFramebufferTexture(target, attachment, texture, level);
}

static void CODEGEN_FUNCPTR Switch_GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params)
{
  _ptrc_glGetBufferParameteri64v = (PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetBufferParameteri64v");
  _ptrc_glGetBufferParameteri64v(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetInteger64i_v(GLenum target, GLuint index, GLint64 * data)
{
  _ptrc_glGetInteger64i_v = (PFN_PTRC_GLGETINTEGER64I_VPROC)IntGetProcAddress("glGetInteger64i_v");
  _ptrc_glGetInteger64i_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetInteger64v(GLenum pname, GLint64 * data)
{
  _ptrc_glGetInteger64v = (PFN_PTRC_GLGETINTEGER64VPROC)IntGetProcAddress("glGetInteger64v");
  _ptrc_glGetInteger64v(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
  _ptrc_glGetMultisamplefv = (PFN_PTRC_GLGETMULTISAMPLEFVPROC)IntGetProcAddress("glGetMultisamplefv");
  _ptrc_glGetMultisamplefv(pname, index, val);
}

static void CODEGEN_FUNCPTR Switch_GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
  _ptrc_glGetSynciv = (PFN_PTRC_GLGETSYNCIVPROC)IntGetProcAddress("glGetSynciv");
  _ptrc_glGetSynciv(sync, pname, bufSize, length, values);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsSync(GLsync sync)
{
  _ptrc_glIsSync = (PFN_PTRC_GLISSYNCPROC)IntGetProcAddress("glIsSync");
  return _ptrc_glIsSync(sync);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex)
{
  _ptrc_glMultiDrawElementsBaseVertex = (PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glMultiDrawElementsBaseVertex");
  _ptrc_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
}

static void CODEGEN_FUNCPTR Switch_ProvokingVertex(GLenum mode)
{
  _ptrc_glProvokingVertex = (PFN_PTRC_GLPROVOKINGVERTEXPROC)IntGetProcAddress("glProvokingVertex");
  _ptrc_glProvokingVertex(mode);
}

static void CODEGEN_FUNCPTR Switch_SampleMaski(GLuint maskNumber, GLbitfield mask)
{
  _ptrc_glSampleMaski = (PFN_PTRC_GLSAMPLEMASKIPROC)IntGetProcAddress("glSampleMaski");
  _ptrc_glSampleMaski(maskNumber, mask);
}

static void CODEGEN_FUNCPTR Switch_TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  _ptrc_glTexImage2DMultisample = (PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexImage2DMultisample");
  _ptrc_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  _ptrc_glTexImage3DMultisample = (PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexImage3DMultisample");
  _ptrc_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  _ptrc_glWaitSync = (PFN_PTRC_GLWAITSYNCPROC)IntGetProcAddress("glWaitSync");
  _ptrc_glWaitSync(sync, flags, timeout);
}


/* Extension: 3.3*/
static void CODEGEN_FUNCPTR Switch_BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name)
{
  _ptrc_glBindFragDataLocationIndexed = (PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC)IntGetProcAddress("glBindFragDataLocationIndexed");
  _ptrc_glBindFragDataLocationIndexed(program, colorNumber, index, name);
}

static void CODEGEN_FUNCPTR Switch_BindSampler(GLuint unit, GLuint sampler)
{
  _ptrc_glBindSampler = (PFN_PTRC_GLBINDSAMPLERPROC)IntGetProcAddress("glBindSampler");
  _ptrc_glBindSampler(unit, sampler);
}

static void CODEGEN_FUNCPTR Switch_DeleteSamplers(GLsizei count, const GLuint * samplers)
{
  _ptrc_glDeleteSamplers = (PFN_PTRC_GLDELETESAMPLERSPROC)IntGetProcAddress("glDeleteSamplers");
  _ptrc_glDeleteSamplers(count, samplers);
}

static void CODEGEN_FUNCPTR Switch_GenSamplers(GLsizei count, GLuint * samplers)
{
  _ptrc_glGenSamplers = (PFN_PTRC_GLGENSAMPLERSPROC)IntGetProcAddress("glGenSamplers");
  _ptrc_glGenSamplers(count, samplers);
}

static GLint CODEGEN_FUNCPTR Switch_GetFragDataIndex(GLuint program, const GLchar * name)
{
  _ptrc_glGetFragDataIndex = (PFN_PTRC_GLGETFRAGDATAINDEXPROC)IntGetProcAddress("glGetFragDataIndex");
  return _ptrc_glGetFragDataIndex(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params)
{
  _ptrc_glGetQueryObjecti64v = (PFN_PTRC_GLGETQUERYOBJECTI64VPROC)IntGetProcAddress("glGetQueryObjecti64v");
  _ptrc_glGetQueryObjecti64v(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params)
{
  _ptrc_glGetQueryObjectui64v = (PFN_PTRC_GLGETQUERYOBJECTUI64VPROC)IntGetProcAddress("glGetQueryObjectui64v");
  _ptrc_glGetQueryObjectui64v(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
  _ptrc_glGetSamplerParameterIiv = (PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glGetSamplerParameterIiv");
  _ptrc_glGetSamplerParameterIiv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
  _ptrc_glGetSamplerParameterIuiv = (PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glGetSamplerParameterIuiv");
  _ptrc_glGetSamplerParameterIuiv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
  _ptrc_glGetSamplerParameterfv = (PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC)IntGetProcAddress("glGetSamplerParameterfv");
  _ptrc_glGetSamplerParameterfv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
  _ptrc_glGetSamplerParameteriv = (PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC)IntGetProcAddress("glGetSamplerParameteriv");
  _ptrc_glGetSamplerParameteriv(sampler, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsSampler(GLuint sampler)
{
  _ptrc_glIsSampler = (PFN_PTRC_GLISSAMPLERPROC)IntGetProcAddress("glIsSampler");
  return _ptrc_glIsSampler(sampler);
}

static void CODEGEN_FUNCPTR Switch_QueryCounter(GLuint id, GLenum target)
{
  _ptrc_glQueryCounter = (PFN_PTRC_GLQUERYCOUNTERPROC)IntGetProcAddress("glQueryCounter");
  _ptrc_glQueryCounter(id, target);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param)
{
  _ptrc_glSamplerParameterIiv = (PFN_PTRC_GLSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glSamplerParameterIiv");
  _ptrc_glSamplerParameterIiv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param)
{
  _ptrc_glSamplerParameterIuiv = (PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glSamplerParameterIuiv");
  _ptrc_glSamplerParameterIuiv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
  _ptrc_glSamplerParameterf = (PFN_PTRC_GLSAMPLERPARAMETERFPROC)IntGetProcAddress("glSamplerParameterf");
  _ptrc_glSamplerParameterf(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param)
{
  _ptrc_glSamplerParameterfv = (PFN_PTRC_GLSAMPLERPARAMETERFVPROC)IntGetProcAddress("glSamplerParameterfv");
  _ptrc_glSamplerParameterfv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
  _ptrc_glSamplerParameteri = (PFN_PTRC_GLSAMPLERPARAMETERIPROC)IntGetProcAddress("glSamplerParameteri");
  _ptrc_glSamplerParameteri(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param)
{
  _ptrc_glSamplerParameteriv = (PFN_PTRC_GLSAMPLERPARAMETERIVPROC)IntGetProcAddress("glSamplerParameteriv");
  _ptrc_glSamplerParameteriv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribDivisor(GLuint index, GLuint divisor)
{
  _ptrc_glVertexAttribDivisor = (PFN_PTRC_GLVERTEXATTRIBDIVISORPROC)IntGetProcAddress("glVertexAttribDivisor");
  _ptrc_glVertexAttribDivisor(index, divisor);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  _ptrc_glVertexAttribP1ui = (PFN_PTRC_GLVERTEXATTRIBP1UIPROC)IntGetProcAddress("glVertexAttribP1ui");
  _ptrc_glVertexAttribP1ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
  _ptrc_glVertexAttribP1uiv = (PFN_PTRC_GLVERTEXATTRIBP1UIVPROC)IntGetProcAddress("glVertexAttribP1uiv");
  _ptrc_glVertexAttribP1uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  _ptrc_glVertexAttribP2ui = (PFN_PTRC_GLVERTEXATTRIBP2UIPROC)IntGetProcAddress("glVertexAttribP2ui");
  _ptrc_glVertexAttribP2ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
  _ptrc_glVertexAttribP2uiv = (PFN_PTRC_GLVERTEXATTRIBP2UIVPROC)IntGetProcAddress("glVertexAttribP2uiv");
  _ptrc_glVertexAttribP2uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  _ptrc_glVertexAttribP3ui = (PFN_PTRC_GLVERTEXATTRIBP3UIPROC)IntGetProcAddress("glVertexAttribP3ui");
  _ptrc_glVertexAttribP3ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
  _ptrc_glVertexAttribP3uiv = (PFN_PTRC_GLVERTEXATTRIBP3UIVPROC)IntGetProcAddress("glVertexAttribP3uiv");
  _ptrc_glVertexAttribP3uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  _ptrc_glVertexAttribP4ui = (PFN_PTRC_GLVERTEXATTRIBP4UIPROC)IntGetProcAddress("glVertexAttribP4ui");
  _ptrc_glVertexAttribP4ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
  _ptrc_glVertexAttribP4uiv = (PFN_PTRC_GLVERTEXATTRIBP4UIVPROC)IntGetProcAddress("glVertexAttribP4uiv");
  _ptrc_glVertexAttribP4uiv(index, type, normalized, value);
}



static void ClearExtensionVariables(void)
{
}

typedef struct ogl_MapTable_s
{
	char *extName;
	int *extVariable;
}ogl_MapTable;

static ogl_MapTable g_mappingTable[1]; /*This is intensionally left uninitialized.*/

static void LoadExtByName(const char *extensionName)
{
	ogl_MapTable *tableEnd = &g_mappingTable[0];
	ogl_MapTable *entry = &g_mappingTable[0];
	for(; entry != tableEnd; ++entry)
	{
		if(strcmp(entry->extName, extensionName) == 0)
			break;
	}

	if(entry != tableEnd)
		*(entry->extVariable) = 1;
}

void ProcExtsFromExtList(void)
{
	GLint iLoop;
	GLint iNumExtensions = 0;
	_ptrc_glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = (const char *)_ptrc_glGetStringi(GL_EXTENSIONS, iLoop);
		LoadExtByName(strExtensionName);
	}
}

void ogl_CheckExtensions()
{
  ClearExtensionVariables();

  ProcExtsFromExtList();
}

