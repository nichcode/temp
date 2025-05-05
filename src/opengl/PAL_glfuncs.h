
#pragma once

#include "PAL/PAL_defines.h"
#include "glcorearb.h"

struct GLVersion
{
    i32 major = 0;
    i32 minor = 0;
};

static GLVersion glVersion;

static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
static PFNGLGENTEXTURESPROC glGenTextures = nullptr;
static PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
static PFNGLDRAWBUFFERPROC glDrawBuffer = nullptr;
static PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
static PFNGLUNIFORM1FPROC glUniform1f = nullptr;
static PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
static PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
static PFNGLUNIFORM1IPROC glUniform1i = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = nullptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
static PFNGLDRAWBUFFERSPROC glDrawBuffers = nullptr;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;
static PFNGLBLENDFUNCIPROC glBlendFunci = nullptr;
static PFNGLBLENDEQUATIONPROC glBlendEquation = nullptr;
static PFNGLCLEARBUFFERFVPROC glClearBufferfv = nullptr;
static PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
static PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
static PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
static PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
static PFNGLBUFFERDATAPROC glBufferData = nullptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
static PFNGLDETACHSHADERPROC glDetachShader = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = nullptr;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
static PFNGLGETSTRINGPROC glGetstring = nullptr;

static PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
static PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;
static PFNGLTEXPARAMETERFVPROC glTexParameterfv = nullptr;
static PFNGLCLEARPROC glClear = nullptr;
static PFNGLCLEARCOLORPROC glClearColor = nullptr;
static PFNGLREADBUFFERPROC glReadBuffer = nullptr;
static PFNGLDEPTHMASKPROC glDepthMask = nullptr;
static PFNGLDISABLEPROC glDisable = nullptr;
static PFNGLENABLEPROC glEnable = nullptr;
static PFNGLSCISSORPROC glScissor = nullptr;
static PFNGLVIEWPORTPROC glViewport = nullptr;
static PFNGLDEPTHFUNCPROC glDepthFunc = nullptr;
static PFNGLCULLFACEPROC glCullFace = nullptr;
static PFNGLBLENDFUNCPROC glBlendFunc = nullptr;
static PFNGLFRONTFACEPROC glFrontFace = nullptr;
static PFNGLUNIFORM2FPROC glUniform2f = nullptr;
static PFNGLUNIFORM3FPROC glUniform3f = nullptr;
static PFNGLUNIFORM4FPROC glUniform4f = nullptr;
static PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
static PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;
static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
static PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = nullptr;
static PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
static PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
static PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
static PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
static PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
static PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
static PFNGLPIXELSTOREIPROC glPixelStorei;
static PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;

void PAL_LoadGL();