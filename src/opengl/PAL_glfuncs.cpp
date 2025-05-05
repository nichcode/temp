
#include "PAL_pch.h"
#include "PAL/PAL.h"
#include "PAL_glfuncs.h"

typedef void* (*PAL_LoadFun)(void* dll_name, const char* func_name);
typedef PROC (WINAPI * PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);

static PAL_LoadFun s_Load = nullptr;
static PFNWGLGETPROCADDRESSPROC s_WGLProcAddress = nullptr;

void* PAL_LoadWin32GLProcs(void* opengl32, const char* func_name)
{
    PROC proc = s_WGLProcAddress(func_name);
    if (!proc) {
        proc = GetProcAddress((HMODULE)opengl32, func_name);
        if (!proc) { PAL_SetError("failed to load gl function %s", func_name); }
    }
    return (void*)proc;
}

void PAL_LoadGL()
{
    void* opengl32 = PAL_LoadLibrary("opengl32.dll");

#ifdef PAL_PLATFORM_WINDOWS
    s_Load = PAL_LoadWin32GLProcs;
    s_WGLProcAddress = (PFNWGLGETPROCADDRESSPROC)GetProcAddress((HMODULE)opengl32, "wglGetProcAddress");
#endif // PAL_PLATFORM_WINDOWS

    glGetstring = (PFNGLGETSTRINGPROC)s_Load(opengl32, "glGetString");
    const char* version = (const char*) glGetstring(GL_VERSION);
    PAL_CHECK(version, "failed to get opengl version",);

    sscanf(version, "%d.%d", &glVersion.major, &glVersion.minor);

    glCreateProgram = (PFNGLCREATEPROGRAMPROC)s_Load(opengl32, "glCreateProgram");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)s_Load(opengl32, "glDeleteTextures");
    glGenTextures = (PFNGLGENTEXTURESPROC)s_Load(opengl32, "glGenTextures");
    glBindTexture = (PFNGLBINDTEXTUREPROC)s_Load(opengl32, "glBindTexture");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)s_Load(opengl32, "glDrawArrays");
    glCreateShader = (PFNGLCREATESHADERPROC)s_Load(opengl32, "glCreateShader");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) s_Load(opengl32, "glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC)s_Load(opengl32, "glUniform1f");
    glUniform2fv = (PFNGLUNIFORM2FVPROC)s_Load(opengl32, "glUniform2fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC)s_Load(opengl32, "glUniform3fv");
    glUniform1i = (PFNGLUNIFORM1IPROC)s_Load(opengl32, "glUniform1i");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)s_Load(opengl32, "glUniformMatrix4fv");
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)s_Load(opengl32, "glVertexAttribDivisor");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC)s_Load(opengl32, "glActiveTexture");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC)s_Load(opengl32, "glBufferSubData");
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)s_Load(opengl32, "glDrawArraysInstanced");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)s_Load(opengl32, "glBindFramebuffer");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)s_Load(opengl32, "glCheckFramebufferStatus");
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)s_Load(opengl32, "glGenFramebuffers");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)s_Load(opengl32, "glFramebufferTexture2D");
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC)s_Load(opengl32, "glDrawBuffers");
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)s_Load(opengl32, "glDeleteFramebuffers");
    glBlendFunci = (PFNGLBLENDFUNCIPROC)s_Load(opengl32, "glBlendFunci");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC)s_Load(opengl32, "glBlendEquation");
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)s_Load(opengl32, "glClearBufferfv");
    glShaderSource = (PFNGLSHADERSOURCEPROC)s_Load(opengl32, "glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)s_Load(opengl32, "glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)s_Load(opengl32, "glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)s_Load(opengl32, "glGetShaderInfoLog");
    glAttachShader = (PFNGLATTACHSHADERPROC)s_Load(opengl32, "glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)s_Load(opengl32, "glLinkProgram");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)s_Load(opengl32, "glValidateProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)s_Load(opengl32, "glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)s_Load(opengl32, "glGetProgramInfoLog");
    glGenBuffers = (PFNGLGENBUFFERSPROC)s_Load(opengl32, "glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)s_Load(opengl32, "glGenVertexArrays");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)s_Load(opengl32, "glGetAttribLocation");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)s_Load(opengl32, "glBindVertexArray");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)s_Load(opengl32, "glEnableVertexAttribArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)s_Load(opengl32, "glVertexAttribPointer");
    glBindBuffer = (PFNGLBINDBUFFERPROC)s_Load(opengl32, "glBindBuffer");
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)s_Load(opengl32, "glBindBufferBase");
    glBufferData = (PFNGLBUFFERDATAPROC)s_Load(opengl32, "glBufferData");
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)s_Load(opengl32, "glGetVertexAttribPointerv");
    glUseProgram = (PFNGLUSEPROGRAMPROC)s_Load(opengl32, "glUseProgram");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)s_Load(opengl32, "glDeleteVertexArrays");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)s_Load(opengl32, "glDeleteBuffers");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)s_Load(opengl32, "glDeleteProgram");
    glDetachShader = (PFNGLDETACHSHADERPROC)s_Load(opengl32, "glDetachShader");
    glDeleteShader = (PFNGLDELETESHADERPROC)s_Load(opengl32, "glDeleteShader");
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)s_Load(opengl32, "glDrawElementsInstanced");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)s_Load(opengl32, "glGenerateMipmap");
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)s_Load(opengl32, "glDebugMessageCallback");

    glTexImage2D = (PFNGLTEXIMAGE2DPROC)s_Load(opengl32, "glTexImage2D");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)s_Load(opengl32, "glTexParameteri");
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)s_Load(opengl32, "glTexParameterfv");
    glClear = (PFNGLCLEARPROC)s_Load(opengl32, "glClear");
    glClearColor = (PFNGLCLEARCOLORPROC)s_Load(opengl32, "glClearColor");
    glReadBuffer = (PFNGLREADBUFFERPROC)s_Load(opengl32, "glReadBuffer");
    glDepthMask = (PFNGLDEPTHMASKPROC)s_Load(opengl32, "glDepthMask");
    glDisable = (PFNGLDISABLEPROC)s_Load(opengl32, "glDisable");
    glEnable = (PFNGLENABLEPROC)s_Load(opengl32, "glEnable");
    glScissor = (PFNGLSCISSORPROC)s_Load(opengl32, "glScissor");
    glViewport = (PFNGLVIEWPORTPROC)s_Load(opengl32, "glViewport");
    glDepthFunc = (PFNGLDEPTHFUNCPROC)s_Load(opengl32, "glDepthFunc");
    glCullFace = (PFNGLCULLFACEPROC)s_Load(opengl32, "glCullFace");
    glBlendFunc = (PFNGLBLENDFUNCPROC)s_Load(opengl32, "glBlendFunc");
    glFrontFace = (PFNGLFRONTFACEPROC)s_Load(opengl32, "glFrontFace");

    glUniform2f = (PFNGLUNIFORM2FPROC)s_Load(opengl32, "glUniform2f");
    glUniform3f = (PFNGLUNIFORM3FPROC)s_Load(opengl32, "glUniform3f");
    glUniform4f = (PFNGLUNIFORM4FPROC)s_Load(opengl32, "glUniform4f");
    glUniform1iv = (PFNGLUNIFORM1IVPROC)s_Load(opengl32, "glUniform1iv");
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)s_Load(opengl32, "glUniformMatrix2fv");
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)s_Load(opengl32, "glUniformMatrix3fv");
    glVertexAttribIPointer =  (PFNGLVERTEXATTRIBIPOINTERPROC)s_Load(opengl32, "glVertexAttribIPointer");
    glDrawElements = (PFNGLDRAWELEMENTSPROC)s_Load(opengl32, "glDrawElements");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)s_Load(opengl32, "glDisableVertexAttribArray");

    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)s_Load(opengl32, "glGenRenderbuffers");
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)s_Load(opengl32, "glBindRenderbuffer");
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)s_Load(opengl32, "glRenderbufferStorage");
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)s_Load(opengl32, "glFramebufferRenderbuffer");
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)s_Load(opengl32, "glDeleteRenderbuffers");
    glPixelStorei = (PFNGLPIXELSTOREIPROC)s_Load(opengl32, "glPixelStorei");
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)s_Load(opengl32, "glTexSubImage2D");

    s_Load = nullptr;
    PAL_FreeLibrary(opengl32);
}