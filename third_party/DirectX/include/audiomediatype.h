

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0499 */
/* Compiler settings for audiomediatype.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __audiomediatype_h__
#define __audiomediatype_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAudioMediaType_FWD_DEFINED__
#define __IAudioMediaType_FWD_DEFINED__
typedef interface IAudioMediaType IAudioMediaType;
#endif 	/* __IAudioMediaType_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_audiomediatype_0000_0000 */
/* [local] */ 

#include <mmreg.h>
#if 0

#pragma pack(push, 1)
typedef struct tWAVEFORMATEX
    {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
    WORD wBitsPerSample;
    WORD cbSize;
    BYTE pExtraBytes[ 1 ];
    } 	WAVEFORMATEX;

typedef struct tWAVEFORMATEX *PWAVEFORMATEX;

typedef struct tWAVEFORMATEX *NPWAVEFORMATEX;

typedef struct tWAVEFORMATEX *LPWAVEFORMATEX;

typedef /* [public] */ struct __MIDL___MIDL_itf_audiomediatype_0000_0000_0001
    {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
    WORD wBitsPerSample;
    WORD cbSize;
    WORD wValidBitsPerSample;
    DWORD dwChannelMask;
    GUID SubFormat;
    } 	WAVEFORMATEXTENSIBLE;

typedef struct __MIDL___MIDL_itf_audiomediatype_0000_0000_0001 *PWAVEFORMATEXTENSIBLE;


#pragma pack(pop)
#endif /* 0 */
#if !defined( _UNCOMPRESSEDAUDIOFORMAT_ )
#define _UNCOMPRESSEDAUDIOFORMAT_
typedef struct _UNCOMPRESSEDAUDIOFORMAT
    {
    GUID guidFormatType;
    DWORD dwSamplesPerFrame;
    DWORD dwBytesPerSampleContainer;
    DWORD dwValidBitsPerSample;
    FLOAT fFramesPerSecond;
    DWORD dwChannelMask;
    } 	UNCOMPRESSEDAUDIOFORMAT;

#endif



extern RPC_IF_HANDLE __MIDL_itf_audiomediatype_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_audiomediatype_0000_0000_v0_0_s_ifspec;

#ifndef __IAudioMediaType_INTERFACE_DEFINED__
#define __IAudioMediaType_INTERFACE_DEFINED__

/* interface IAudioMediaType */
/* [local][uuid][object] */ 


EXTERN_C const IID IID_IAudioMediaType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E997F73-B71F-4798-873B-ED7DFCF15B4D")
    IAudioMediaType : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsCompressedFormat( 
            /* [out] */ BOOL *pfCompressed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsEqual( 
            /* [in] */ IAudioMediaType *pIAudioType,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual const WAVEFORMATEX *STDMETHODCALLTYPE GetAudioFormat( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUncompressedAudioFormat( 
            /* [out] */ UNCOMPRESSEDAUDIOFORMAT *pUncompressedAudioFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioMediaTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAudioMediaType * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAudioMediaType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAudioMediaType * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsCompressedFormat )( 
            IAudioMediaType * This,
            /* [out] */ BOOL *pfCompressed);
        
        HRESULT ( STDMETHODCALLTYPE *IsEqual )( 
            IAudioMediaType * This,
            /* [in] */ IAudioMediaType *pIAudioType,
            /* [out] */ DWORD *pdwFlags);
        
        const WAVEFORMATEX *( STDMETHODCALLTYPE *GetAudioFormat )( 
            IAudioMediaType * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUncompressedAudioFormat )( 
            IAudioMediaType * This,
            /* [out] */ UNCOMPRESSEDAUDIOFORMAT *pUncompressedAudioFormat);
        
        END_INTERFACE
    } IAudioMediaTypeVtbl;

    interface IAudioMediaType
    {
        CONST_VTBL struct IAudioMediaTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioMediaType_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAudioMediaType_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAudioMediaType_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAudioMediaType_IsCompressedFormat(This,pfCompressed)	\
    ( (This)->lpVtbl -> IsCompressedFormat(This,pfCompressed) ) 

#define IAudioMediaType_IsEqual(This,pIAudioType,pdwFlags)	\
    ( (This)->lpVtbl -> IsEqual(This,pIAudioType,pdwFlags) ) 

#define IAudioMediaType_GetAudioFormat(This)	\
    ( (This)->lpVtbl -> GetAudioFormat(This) ) 

#define IAudioMediaType_GetUncompressedAudioFormat(This,pUncompressedAudioFormat)	\
    ( (This)->lpVtbl -> GetUncompressedAudioFormat(This,pUncompressedAudioFormat) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAudioMediaType_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_audiomediatype_0000_0001 */
/* [local] */ 

//
// CreateAudioMediaType
//
STDAPI CreateAudioMediaType(
    const WAVEFORMATEX* pAudioFormat,
    UINT32 cbAudioFormatSize,
    IAudioMediaType** ppIAudioMediaType
    );
//
// CreateAudioMediaTypeFromUncompressedAudioFormat
//
STDAPI CreateAudioMediaTypeFromUncompressedAudioFormat(
    const UNCOMPRESSEDAUDIOFORMAT* pUncompressedAudioFormat,
    IAudioMediaType** ppIAudioMediaType
    );
#define AUDIOMEDIATYPE_EQUAL_FORMAT_TYPES 0x00000002
#define AUDIOMEDIATYPE_EQUAL_FORMAT_DATA  0x00000004
#define AUDIOMEDIATYPE_EQUAL_FORMAT_USER_DATA  0x00000008



extern RPC_IF_HANDLE __MIDL_itf_audiomediatype_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_audiomediatype_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



