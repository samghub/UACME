/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2014 - 2016
*
*  TITLE:       GLOBAL.H
*
*  VERSION:     2.30
*
*  DATE:        18 June 2016
*
*  Common header file for the program support routines.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#pragma once

#if !defined UNICODE
#error ANSI build is not supported
#endif

#if (_MSC_VER >= 1900) 
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif

//disable nonmeaningful warnings.
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4055) // %s : from data pointer %s to function pointer %s
#pragma warning(disable: 4152) // nonstandard extension, function/data pointer conversion in expression
#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable: 6102) // Using %s from failed function call at line %u
#pragma warning(disable: 6320) // exception-filter expression is the constant EXCEPTION_EXECUTE_HANDLER

#define GENERATE_COMPRESSED_PAYLOAD
#ifndef _DEBUG
#undef GENERATE_COMPRESSED_PAYLOAD
#endif

#ifdef _WIN64
#include "bin64res.h"
#define FUBUKI_ID IDR_FUBUKI64
#define HIBIKI_ID IDR_HIBIKI64
#define KONGOU_ID IDR_KONGOU64
#else
#include "bin32res.h"
#define FUBUKI_ID IDR_FUBUKI32
#define HIBIKI_ID IDR_HIBIKI32
#define KONGOU_ID IDR_KONGOU32
#endif

typedef enum _UACBYPASSMETHOD {
    UacMethodSysprep1 = 1,
    UacMethodSysprep2,
    UacMethodOobe,
    UacMethodRedirectExe,
    UacMethodSimda,
    UacMethodCarberp1,
    UacMethodCarberp2,
    UacMethodTilon,
    UacMethodAVrf,
    UacMethodWinsat,
    UacMethodShimPatch,
    UacMethodSysprep3,
    UacMethodMMC,
    UacMethodSirefef,
    UacMethodGeneric,
    UacMethodGWX,
    UacMethodSysprep4,
    UacMethodManifest,
    UacMethodInetMgr,
    UacMethodMax
} UACBYPASSMETHOD;

#include <Windows.h>
#include <ntstatus.h>
#include "..\shared\ntos.h"
#include "..\shared\minirtl.h"
#include "..\Shared\cmdline.h"
#include "..\Shared\_filename.h"
#include "consts.h"
#include "compress.h"
#include "sup.h"
#include "pitou.h"
#include "gootkit.h"
#include "simda.h"
#include "carberp.h"
#include "hybrids.h"

typedef struct _UACME_CONTEXT {
    BOOL                IsWow64;
    UACBYPASSMETHOD     Method;
    PPEB                Peb;
    HINSTANCE           hKernel32;
    HINSTANCE           hOle32;
    HINSTANCE           hShell32;
    PVOID               PayloadDll;
    ULONG               PayloadDllSize;
    ULONG               dwBuildNumber;
    WCHAR               szSystemDirectory[MAX_PATH + 1];//with end slash
    WCHAR               szTempDirectory[MAX_PATH + 1]; //with end slash
} UACMECONTEXT, *PUACMECONTEXT;

extern UACMECONTEXT g_ctx;
