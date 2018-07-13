/******************************Module*Header**********************************\
*
* Module Name: d3dkmthk.h
*
* Content: longhorn display driver model kernel mode thunk interfaces
*
* Copyright (c) 2003 Microsoft Corporation.  All rights reserved.
\*****************************************************************************/
#ifndef _D3DKMTHK_H_
#define _D3DKMTHK_H_
#include <d3dukmdt.h>

typedef struct _D3DKMT_CREATEDEVICEFLAGS
{
    UINT    LegacyMode   :  1;   // 0x00000001
    UINT    RequestVSync :  1;   // 0x00000002
    UINT    Reserved     : 30;   // 0xFFFFFFFC
} D3DKMT_CREATEDEVICEFLAGS;

typedef struct _D3DKMT_CREATEDEVICE
{
    union
    {
        D3DKMT_HANDLE           hAdapter;           // in: identifies the adapter for user-mode creation
        VOID*                   pAdapter;           // in: identifies the adapter for kernel-mode creation
    };

    D3DKMT_CREATEDEVICEFLAGS    Flags;

    D3DKMT_HANDLE               hDevice;                // out: Indentifies the device
    VOID*                       pCommandBuffer;         // out: D3D10 compatibility.
    UINT                        CommandBufferSize;      // out: D3D10 compatibility.
    D3DDDI_ALLOCATIONLIST*      pAllocationList;        // out: D3D10 compatibility.
    UINT                        AllocationListSize;     // out: D3D10 compatibility.
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationList;     // out: D3D10 compatibility.
    UINT                        PatchLocationListSize;  // out: D3D10 compatibility.
} D3DKMT_CREATEDEVICE;

typedef struct _D3DKMT_DESTROYDEVICE
{
    D3DKMT_HANDLE     hDevice;              // in: Indentifies the device
}D3DKMT_DESTROYDEVICE;

typedef enum _D3DKMT_CLIENTHINT
{
    D3DKMT_CLIENTHINT_UNKNOWN     = 0,
    D3DKMT_CLIENTHINT_OPENGL      = 1,
    D3DKMT_CLIENTHINT_CDD         = 2,       // Internal   ;internal
    D3DKMT_CLIENTHINT_DX7         = 7,
    D3DKMT_CLIENTHINT_DX8         = 8,
    D3DKMT_CLIENTHINT_DX9         = 9,
    D3DKMT_CLIENTHINT_DX10        = 10,
} D3DKMT_CLIENTHINT;

typedef struct _D3DKMT_CREATECONTEXT
{
    D3DKMT_HANDLE               hDevice;                    // in:  Handle to the device owning this context.
    UINT                        NodeOrdinal;                // in:  Identifier for the node targetted by this context.
    UINT                        EngineAffinity;             // in:  Engine affinity within the specified node.
    D3DDDI_CREATECONTEXTFLAGS   Flags;                      // in:  Context creation flags.
    VOID*                       pPrivateDriverData;         // in:  Private driver data
    UINT                        PrivateDriverDataSize;      // in:  Size of private driver data
    D3DKMT_CLIENTHINT           ClientHint;                 // in:  Hints which client is creating this
    D3DKMT_HANDLE               hContext;                   // out: Handle of the created context.
    VOID*                       pCommandBuffer;             // out: Pointer to the first command buffer.
    UINT                        CommandBufferSize;          // out: Command buffer size (bytes).
    D3DDDI_ALLOCATIONLIST*      pAllocationList;            // out: Pointer to the first allocation list.
    UINT                        AllocationListSize;         // out: Allocation list size (elements).
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationList;         // out: Pointer to the first patch location list.
    UINT                        PatchLocationListSize;      // out: Patch location list size (elements).
} D3DKMT_CREATECONTEXT;

typedef struct _D3DKMT_DESTROYCONTEXT
{
    D3DKMT_HANDLE               hContext;                   // in:  Identifies the context being destroyed.
} D3DKMT_DESTROYCONTEXT;

typedef struct _D3DKMT_CREATESYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE                           hDevice;                    // in:  Handle to the device.
    D3DDDI_SYNCHRONIZATIONOBJECTINFO        Info;                       // in:  Attributes of the synchronization object.
    D3DKMT_HANDLE                           hSyncObject;                // out: Handle to the synchronization object created.
} D3DKMT_CREATESYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_DESTROYSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE               hSyncObject;                // in:  Identifies the synchronization objects being destroyed.
} D3DKMT_DESTROYSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_WAITFORSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE               hContext;                   // in: Identifies the context that needs to wait.
    UINT                        ObjectCount;                // in: Specifies the number of object to wait on.
    D3DKMT_HANDLE               ObjectHandleArray[D3DDDI_MAX_OBJECT_WAITED_ON]; // in: Specifies the object to wait on.
} D3DKMT_WAITFORSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_SIGNALSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE               hContext;                                       // in: Identifies the context that needs to signal.
    UINT                        ObjectCount;                                    // in: Specifies the number of object to signal.
    D3DKMT_HANDLE               ObjectHandleArray[D3DDDI_MAX_OBJECT_SIGNALED];  // in: Specifies the object to be signaled.
    D3DDDICB_SIGNALFLAGS        Flags;                                          // in: Specifies signal behavior.
} D3DKMT_SIGNALSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_LOCK
{
    D3DKMT_HANDLE       hDevice;            // in: identifies the device
    D3DKMT_HANDLE       hAllocation;        // in: allocation to lock
                                            // out: New handle representing the allocation after the lock.
    UINT                PrivateDriverData;  // in: Used by UMD for AcquireAperture
    UINT                NumPages;
    CONST UINT*         pPages;
    VOID*               pData;              // out: pointer to memory
    D3DDDICB_LOCKFLAGS  Flags;              // in: Bit field defined by D3DDDI_LOCKFLAGS
} D3DKMT_LOCK;

typedef struct _D3DKMT_UNLOCK
{
    D3DKMT_HANDLE           hDevice;        // in: Identifies the device
    UINT                    NumAllocations; // in: Number of allocations in the array
    CONST D3DKMT_HANDLE*    phAllocations;  // in: array of allocations to unlock
} D3DKMT_UNLOCK;


typedef enum _D3DKMDT_MODE_PRUNING_REASON
{
    D3DKMDT_MPR_UNINITIALIZED                               = 0, // mode was pruned or is supported because of:
    D3DKMDT_MPR_ALLCAPS                                     = 1, //   all of the monitor caps (only used to imply lack of support - for support, specific reason is always indicated)
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_SOURCE_MODE              = 2, //   monitor source mode in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_FREQUENCY_RANGE          = 3, //   monitor frequency range in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_SOURCE_MODE     = 4, //   monitor source mode in the monitor descriptor override
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_FREQUENCY_RANGE = 5, //   monitor frequency range in the monitor descriptor override
    D3DKMDT_MPR_DEFAULT_PROFILE_MONITOR_SOURCE_MODE         = 6, //   monitor source mode in the default monitor profile
    D3DKMDT_MPR_DRIVER_RECOMMENDED_MONITOR_SOURCE_MODE      = 7, //   monitor source mode recommended by the driver
    D3DKMDT_MPR_MONITOR_FREQUENCY_RANGE_OVERRIDE            = 8, //   monitor frequency range override
    D3DKMDT_MPR_MAXVALID                                    = 9
}
D3DKMDT_MODE_PRUNING_REASON;

typedef struct _D3DKMDT_DISPLAYMODE_FLAGS
{
    BOOLEAN                      ValidatedAgainstMonitorCaps : 1;
    BOOLEAN                      RoundedFakeMode             : 1;
    D3DKMDT_MODE_PRUNING_REASON  ModePruningReason           : 4;
    UINT                         Reserved                    : 26;
}
D3DKMDT_DISPLAYMODE_FLAGS;

typedef struct _D3DKMT_DISPLAYMODE
{
    UINT                                   Width;
    UINT                                   Height;
    D3DDDIFORMAT                           Format;
    UINT                                   IntegerRefreshRate;
    D3DDDI_RATIONAL                        RefreshRate;
    D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING  ScanLineOrdering;
    D3DDDI_ROTATION                        DisplayOrientation;
    UINT                                   DisplayFixedOutput;
    D3DKMDT_DISPLAYMODE_FLAGS              Flags;
} D3DKMT_DISPLAYMODE;

typedef struct _D3DKMT_GETDISPLAYMODELIST
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    D3DKMT_DISPLAYMODE*             pModeList;      // out:
    UINT                            ModeCount;      // in/out:
} D3DKMT_GETDISPLAYMODELIST;

typedef struct _D3DKMT_SETDISPLAYMODE
{
    D3DKMT_HANDLE                          hDevice;                         // in: Identifies the device
    D3DKMT_HANDLE                          hPrimaryAllocation;              // in:
    D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING  ScanLineOrdering;                // in:
    D3DDDI_ROTATION                        DisplayOrientation;              // in:
    UINT                                   PrivateDriverFormatAttribute;    // out: Private Format Attribute of the current primary surface if DxgkSetDisplayMode failed with STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT
} D3DKMT_SETDISPLAYMODE;

typedef struct _D3DKMT_MULTISAMPLEMETHOD
{
    UINT    NumSamples;
    UINT    NumQualityLevels;
    UINT    Reserved;   //workaround for NTRAID#Longhorn-1124385-2005/03/14-kanqiu
} D3DKMT_MULTISAMPLEMETHOD;

typedef struct _D3DKMT_GETMULTISAMPLEMETHODLIST
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    UINT                            Width;          // in:
    UINT                            Height;         // in:
    D3DDDIFORMAT                    Format;         // in:
    D3DKMT_MULTISAMPLEMETHOD*       pMethodList;    // out:
    UINT                            MethodCount;    // in/out:
} D3DKMT_GETMULTISAMPLEMETHODLIST;

typedef struct _D3DKMT_PRESENTFLAGS
{
    union
    {
        struct
        {
            UINT    Blt                 : 1;        // 0x00000001
            UINT    ColorFill           : 1;        // 0x00000002
            UINT    Flip                : 1;        // 0x00000004
            UINT    FlipDoNotFlip       : 1;        // 0x00000008
            UINT    FlipDoNotWait       : 1;        // 0x00000010
            UINT    FlipRestart         : 1;        // 0x00000020
            UINT    DstRectValid        : 1;        // 0x00000040
            UINT    SrcRectValid        : 1;        // 0x00000080
            UINT    RestrictVidPnSource : 1;        // 0x00000100
            UINT    SrcColorKey         : 1;        // 0x00000200
            UINT    DstColorKey         : 1;        // 0x00000400
            UINT    LinearToSrgb        : 1;        // 0x00000800
            UINT    PresentCountValid   : 1;        // 0x00001000
            UINT    Rotate              : 1;        // 0x00002000
            UINT    Reserved            :18;        // 0xFFFFC000
        };
        UINT    Value;
    };
} D3DKMT_PRESENTFLAGS;

typedef struct _D3DKMT_PRESENT
{
    union
    {
        D3DKMT_HANDLE               hDevice;            // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;           // in: Indentifies the context
    };
    HWND                            hWindow;            // in: window to present to
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: VidPn source ID if RestrictVidPnSource is flagged
    D3DKMT_HANDLE                   hSource;            // in: Source allocation to present from
    D3DKMT_HANDLE                   hDestination;       // in: Destination allocation whenever non-zero
    UINT                            Color;              // in: color value in ARGB 32 bit format
    RECT                            DstRect;            // in: unclipped dest rect
    RECT                            SrcRect;            // in: unclipped src rect
    UINT                            SubRectCnt;         // in: count of sub rects
    CONST RECT*                     pSrcSubRects;       // in: sub rects in source space
    UINT                            PresentCount;       // in: present counter
    D3DDDI_FLIPINTERVAL_TYPE        FlipInterval;       // in: flip interval
    D3DKMT_PRESENTFLAGS             Flags;              // in:
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.
} D3DKMT_PRESENT;

typedef struct _D3DKMT_RENDERFLAGS
{
    UINT    ResizeCommandBuffer     :  1;  // 0x00000001
    UINT    ResizeAllocationList    :  1;  // 0x00000002
    UINT    ResizePatchLocationList :  1;  // 0x00000004
    UINT    NullRendering           :  1;  // 0x00000008
    UINT    PresentRedirected       :  1;  // 0x00000010
    UINT    Reserved                : 27;  // 0xFFFFFFE0
} D3DKMT_RENDERFLAGS;

typedef struct _D3DKMT_RENDER
{
    union
    {
        D3DKMT_HANDLE               hDevice;                    // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;                   // in: Indentifies the context
    };
    UINT                            CommandOffset;              // in: offset in bytes from start
    UINT                            CommandLength;              // in: number of bytes
    UINT                            AllocationCount;            // in: Number of allocations in allocation list.
    UINT                            PatchLocationCount;         // in: Number of patch locations in patch allocation list.
    VOID*                           pNewCommandBuffer;          // out: Pointer to the next command buffer to use.
    UINT                            NewCommandBufferSize;       // in: Size requested for the next command buffer.
                                                                // out: Size of the next command buffer to use.
    D3DDDI_ALLOCATIONLIST*          pNewAllocationList;         // out: Pointer to the next allocation list to use.
    UINT                            NewAllocationListSize;      // in: Size requested for the next allocation list.
                                                                // out: Size of the new allocation list.
    D3DDDI_PATCHLOCATIONLIST*       pNewPatchLocationList;      // out: Pointer to the next patch location list.
    UINT                            NewPatchLocationListSize;   // in: Size requested for the next patch location list.
                                                                // out: Size of the new patch location list.
    D3DKMT_RENDERFLAGS              Flags;                      // in:
    ULONGLONG                       PresentHistoryToken;        // in: Present history token for redirected present calls
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.
    ULONG                           QueuedBufferCount;          // out: Number of DMA buffer queued to this context after this submission.
} D3DKMT_RENDER;

typedef struct _D3DKMT_CREATEALLOCATIONFLAGS
{
    UINT    CreateResource              :  1;    // 0x00000001
    UINT    CreateShared                :  1;    // 0x00000002
    UINT    NonSecure                   :  1;    // 0x00000004
    UINT    Reserved                    : 29;    // 0xFFFFFFF8
} D3DKMT_CREATEALLOCATIONFLAGS;

typedef struct _D3DKMT_CREATEALLOCATION
{
                                            D3DKMT_HANDLE                   hDevice;
                                            D3DKMT_HANDLE                   hResource;      //in/out:valid only within device
                                            D3DKMT_HANDLE                   hGlobalShare;   //out:Shared handle if CreateShared
    __field_bcount(PrivateRuntimeDataSize)  CONST VOID*                     pPrivateRuntimeData;
                                            UINT                            PrivateRuntimeDataSize;
    __field_bcount(PrivateDriverDataSize)   CONST VOID*                     pPrivateDriverData;
                                            UINT                            PrivateDriverDataSize;
                                            UINT                            NumAllocations;
   __field_ecount(NumAllocations)           D3DDDI_ALLOCATIONINFO*          pAllocationInfo;
                                            D3DKMT_CREATEALLOCATIONFLAGS    Flags;
                                            HANDLE                          hPrivateRuntimeResourceHandle; // opaque handle used for event tracing
} D3DKMT_CREATEALLOCATION;

typedef struct _D3DKMT_OPENRESOURCE
{
                                                        D3DKMT_HANDLE               hDevice;                            // in : Indentifies the device
                                                        D3DKMT_HANDLE               hGlobalShare;                       // in : Shared resource handle
                                                        UINT                        NumAllocations;                     // in : Number of allocations associated with the resource
    __field_ecount(NumAllocations)                      D3DDDI_OPENALLOCATIONINFO*  pOpenAllocationInfo;                // in : Array of open allocation structs
    __field_bcount(PrivateRuntimeDataSize)              VOID*                       pPrivateRuntimeData;                // in : Caller supplied buffer where the runtime private data associated with this resource will be copied
                                                        UINT                        PrivateRuntimeDataSize;             // in : Size in bytes of the pPrivateRuntimeData buffer
    __field_bcount(ResourcePrivateDriverDataSize)       VOID*                       pResourcePrivateDriverData;         // in : Caller supplied buffer where the driver private data associated with the resource will be copied
                                                        UINT                        ResourcePrivateDriverDataSize;      // in : Size in bytes of the pResourcePrivateDriverData buffer
    __field_bcount(TotalPrivateDriverDataBufferSize)    VOID*                       pTotalPrivateDriverDataBuffer;      // in : Caller supplied buffer where the Driver private data will be stored
                                                        UINT                        TotalPrivateDriverDataBufferSize;   // in/out : Size in bytes of pTotalPrivateDriverDataBuffer / Size in bytes of data written to pTotalPrivateDriverDataBuffer
                                                        D3DKMT_HANDLE               hResource;                          // out : Handle for this resource in this process
}D3DKMT_OPENRESOURCE;

typedef struct _D3DKMT_QUERYRESOURCEINFO
{
    D3DKMT_HANDLE   hDevice;                        // in : Indentifies the device
    D3DKMT_HANDLE   hGlobalShare;                   // in : Global resource handle to open
    VOID*           pPrivateRuntimeData;            // in : Ptr to buffer that will receive runtime private data for the resource
    UINT            PrivateRuntimeDataSize;         // in/out : Size in bytes of buffer passed in for runtime private data / If pPrivateRuntimeData was NULL then size in bytes of buffer required for the runtime private data otherwise size in bytes of runtime private data copied into the buffer
    UINT            TotalPrivateDriverDataSize;     // out : Size in bytes of buffer required to hold all the DriverPrivate data for all of the allocations associated withe the resource
    UINT            ResourcePrivateDriverDataSize;  // out : Size in bytes of the driver's resource private data
    UINT            NumAllocations;                 // out : Number of allocations associated with this resource
}D3DKMT_QUERYRESOURCEINFO;

typedef struct _D3DKMT_DESTROYALLOCATION
{
    D3DKMT_HANDLE           hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE           hResource;
    CONST D3DKMT_HANDLE*    phAllocationList;   // in: pointer to an array allocation handles to destroy
    UINT                    AllocationCount;    // in: Number of allocations in phAllocationList
} D3DKMT_DESTROYALLOCATION;

typedef struct _D3DKMT_SETALLOCATIONPRIORITY
{
    D3DKMT_HANDLE           hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE           hResource;          // in: Specify the resource to set priority to.
    CONST D3DKMT_HANDLE*    phAllocationList;   // in: pointer to an array allocation to set priority to.
    UINT                    AllocationCount;    // in: Number of allocations in phAllocationList
    CONST UINT*             pPriorities;        // in: New priority for each of the allocation in the array.
} D3DKMT_SETALLOCATIONPRIORITY;

typedef enum _D3DKMT_ALLOCATIONRESIDENCYSTATUS
{
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_RESIDENTINGPUMEMORY=1,
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_RESIDENTINSHAREDMEMORY=2,
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_NOTRESIDENT=3,
} D3DKMT_ALLOCATIONRESIDENCYSTATUS;

typedef struct _D3DKMT_QUERYALLOCATIONRESIDENCY
{
    D3DKMT_HANDLE                       hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE                       hResource;          // in: pointer to resource owning the list of allocation.
    CONST D3DKMT_HANDLE*                phAllocationList;   // in: pointer to an array allocation to get residency status.
    UINT                                AllocationCount;    // in: Number of allocations in phAllocationList
    D3DKMT_ALLOCATIONRESIDENCYSTATUS*   pResidencyStatus;   // out: Residency status of each allocation in the array.
} D3DKMT_QUERYALLOCATIONRESIDENCY;

typedef struct _D3DKMT_GETRUNTIMEDATA
{
    D3DKMT_HANDLE       hAdapter;
    D3DKMT_HANDLE       hGlobalShare;       // in: shared handle
    VOID*               pRuntimeData;       // out: in: for a version?
    UINT                RuntimeDataSize;    // in:
} D3DKMT_GETRUNTIMEDATA;

typedef enum _KMTUMDVERSION
{
    KMTUMDVERSION_DX9 = 0,
    KMTUMDVERSION_DX10,
    KMTUMDVERSION_DX11,
} KMTUMDVERSION;

typedef struct _D3DKMT_UMDFILENAMEINFO
{
    KMTUMDVERSION       Version;                // In: UMD version
    WCHAR               UmdFileName[MAX_PATH];  // Out: UMD file name
} D3DKMT_UMDFILENAMEINFO;

typedef struct _D3DKMT_OPENGLINFO
{
    WCHAR               UmdOpenGlIcdFileName[MAX_PATH];
    ULONG               Version;
    ULONG               Flags;
} D3DKMT_OPENGLINFO;

typedef struct _D3DKMT_SEGMENTSIZEINFO
{
    ULONGLONG           DedicatedVideoMemorySize;
    ULONGLONG           DedicatedSystemMemorySize;
    ULONGLONG           SharedSystemMemorySize;
} D3DKMT_SEGMENTSIZEINFO;

typedef struct _D3DKMT_WORKINGSETFLAGS
{
    UINT    UseDefault   :  1;   // 0x00000001
    UINT    Reserved     : 31;   // 0xFFFFFFFE
} D3DKMT_WORKINGSETFLAGS;

typedef struct _D3DKMT_WORKINGSETINFO
{
    D3DKMT_WORKINGSETFLAGS Flags;
    ULONG MinimumWorkingSetPercentile;
    ULONG MaximumWorkingSetPercentile;
} D3DKMT_WORKINGSETINFO;

typedef struct _D3DKMT_FLIPINFOFLAGS
{
    UINT                FlipInterval :  1; // 0x00000001 // Set when kmd driver support FlipInterval natively
    UINT                Reserved     : 31; // 0xFFFFFFFE
} D3DKMT_FLIPINFOFLAGS;

typedef struct _D3DKMT_FLIPQUEUEINFO
{
    UINT                 MaxHardwareFlipQueueLength; // Max flip can be queued for hardware flip queue.
    UINT                 MaxSoftwareFlipQueueLength; // Max flip can be queued for software flip queue for non-legacy device.
    D3DKMT_FLIPINFOFLAGS FlipFlags;
} D3DKMT_FLIPQUEUEINFO;

typedef struct _D3DKMT_ADAPTERADDRESS
{
    UINT   BusNumber;              // Bus number on which the physical device is located.
    UINT   DeviceNumber;           // Index of the physical device on the bus.
    UINT   FunctionNumber;         // Function number of the adapter on the physical device.
} D3DKMT_ADAPTERADDRESS;

typedef struct _D3DKMT_ADAPTERREGISTRYINFO
{
    WCHAR   AdapterString[MAX_PATH];
    WCHAR   BiosString[MAX_PATH];
    WCHAR   DacType[MAX_PATH];
    WCHAR   ChipType[MAX_PATH];
} D3DKMT_ADAPTERREGISTRYINFO;

typedef struct _D3DKMT_CURRENTDISPLAYMODE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;
    D3DKMT_DISPLAYMODE DisplayMode;
} D3DKMT_CURRENTDISPLAYMODE;

typedef enum _KMTQUERYADAPTERINFOTYPE
{
     KMTQAITYPE_UMDRIVERPRIVATE         =  0,
     KMTQAITYPE_UMDRIVERNAME            =  1,
     KMTQAITYPE_UMOPENGLINFO            =  2,
     KMTQAITYPE_GETSEGMENTSIZE          =  3,
     KMTQAITYPE_ADAPTERGUID             =  4,
     KMTQAITYPE_FLIPQUEUEINFO           =  5,
     KMTQAITYPE_ADAPTERADDRESS          =  6,
     KMTQAITYPE_SETWORKINGSETINFO       =  7,
     KMTQAITYPE_ADAPTERREGISTRYINFO     =  8,
     KMTQAITYPE_CURRENTDISPLAYMODE      =  9,
     KMTQAITYPE_MODELIST                = 10,
     KMTQAITYPE_CHECKDRIVERUPDATESTATUS = 11,
} KMTQUERYADAPTERINFOTYPE;

typedef struct _D3DKMT_QUERYADAPTERINFO
{
    D3DKMT_HANDLE           hAdapter;
    KMTQUERYADAPTERINFOTYPE Type;
    VOID*                   pPrivateDriverData;
    UINT                    PrivateDriverDataSize;
} D3DKMT_QUERYADAPTERINFO;

typedef struct _D3DKMT_OPENADAPTERFROMHDC
{
    HDC                             hDc;            // in:  DC that maps to a single display
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // out: VidPN source ID for that particular display
} D3DKMT_OPENADAPTERFROMHDC;

typedef struct _D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME
{
    WCHAR                           DeviceName[32]; // in:  Name of GDI device from which to open an adapter instance
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // out: VidPN source ID for that particular display
} D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME;

typedef struct _D3DKMT_OPENADAPTERFROMDEVICENAME
{
    PCWSTR                          pDeviceName;    // in:  NULL terminated string containing the device name to open
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
} D3DKMT_OPENADAPTERFROMDEVICENAME;

typedef struct _D3DKMT_CLOSEADAPTER
{
    D3DKMT_HANDLE   hAdapter;   // in: adapter handle
} D3DKMT_CLOSEADAPTER;

typedef struct _D3DKMT_GETSHAREDPRIMARYHANDLE
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    D3DKMT_HANDLE                   hSharedPrimary; // out: global shared primary handle (if one exists currently)
} D3DKMT_GETSHAREDPRIMARYHANDLE;

typedef struct _D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION
{
    LUID                            AdapterLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    RECTL                           LockRect;               // in: If zero rect then we are locking the whole primary else the lock sub-rect
} D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION;

typedef struct _D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION
{
    LUID                            AdapterLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
} D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION;

typedef enum _D3DKMT_ESCAPETYPE
{
    D3DKMT_ESCAPE_DRIVERPRIVATE           = 0,
    D3DKMT_ESCAPE_VIDMM                   = 1,
    D3DKMT_ESCAPE_TDRDBGCTRL              = 2,
    D3DKMT_ESCAPE_VIDSCH                  = 3,
    D3DKMT_ESCAPE_DEVICE                  = 4,
    D3DKMT_ESCAPE_DMM                     = 5,
    D3DKMT_ESCAPE_DEBUG_SNAPSHOT          = 6,
    D3DKMT_ESCAPE_SETDRIVERUPDATESTATUS   = 7
} D3DKMT_ESCAPETYPE;

typedef enum _D3DKMT_TDRDBGCTRLTYPE
{
    D3DKMT_TDRDBGCTRLTYPE_FORCETDR      = 0, //Simulate a TDR
    D3DKMT_TDRDBGCTRLTYPE_DISABLEBREAK  = 1, //Disable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_ENABLEBREAK   = 2, //Enable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_UNCONDITIONAL = 3, //Disables all safety conditions (e.g. check for consecutive recoveries)
    D3DKMT_TDRDBGCTRLTYPE_VSYNCTDR      = 4, //Simulate a Vsync TDR
    D3DKMT_TDRDBGCTRLTYPE_GPUTDR        = 5, //Simulate a GPU TDR
} D3DKMT_TDRDBGCTRLTYPE;

typedef enum _D3DKMT_VIDMMESCAPETYPE
{
    D3DKMT_VIDMMESCAPETYPE_SETFAULT                     = 0,
    D3DKMT_VIDMMESCAPETYPE_RUN_COHERENCY_TEST           = 1,
    D3DKMT_VIDMMESCAPETYPE_RUN_UNMAP_TO_DUMMY_PAGE_TEST = 2,
    D3DKMT_VIDMMESCAPETYPE_APERTURE_CORRUPTION_CHECK    = 3,
    D3DKMT_VIDMMESCAPETYPE_SUSPEND_CPU_ACCESS_TEST      = 4
} D3DKMT_VIDMMESCAPETYPE;

typedef enum _D3DKMT_VIDSCHESCAPETYPE
{
    D3DKMT_VIDSCHESCAPETYPE_PREEMPTIONCONTROL = 0, //Enable/Disable preemption
    D3DKMT_VIDSCHESCAPETYPE_SUSPENDSCHEDULER  = 1, //Suspend/Resume scheduler
    D3DKMT_VIDSCHESCAPETYPE_TDRCONTROL        = 2, //Tdr control
} D3DKMT_VIDSCHESCAPETYPE;

typedef enum _D3DKMT_DMMESCAPETYPE
{
    D3DKMT_DMMESCAPETYPE_UNINITIALIZED                       =  0,
    D3DKMT_DMMESCAPETYPE_GET_SUMMARY_INFO                    =  1,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_SOURCES_INFO      =  2,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_TARGETS_INFO      =  3,
    D3DKMT_DMMESCAPETYPE_GET_ACTIVEVIDPN_INFO                =  4,
    D3DKMT_DMMESCAPETYPE_GET_MONITORS_INFO                   =  5,
    D3DKMT_DMMESCAPETYPE_RECENTLY_COMMITTED_VIDPNS_INFO      =  6,
    D3DKMT_DMMESCAPETYPE_RECENT_MODECHANGE_REQUESTS_INFO     =  7,
    D3DKMT_DMMESCAPETYPE_RECENTLY_RECOMMENDED_VIDPNS_INFO    =  8,
    D3DKMT_DMMESCAPETYPE_RECENT_MONITOR_PRESENCE_EVENTS_INFO =  9,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_SOURCEMODESET_INFO      = 10,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO = 11,
    D3DKMT_DMMESCAPETYPE_GET_LASTCLIENTCOMMITTEDVIDPN_INFO   = 12
} D3DKMT_DMMESCAPETYPE;

typedef struct _D3DKMT_VIDMM_ESCAPE
{
    D3DKMT_VIDMMESCAPETYPE Type;
    union
    {
        struct
        {
            union
            {
                struct
                {
                    ULONG ProbeAndLock : 1;
                    ULONG SplitPoint : 1;
                    ULONG HotAddMemory : 1;
                    ULONG SwizzlingAperture : 1;
                    ULONG PagingPathLockSubRange : 1;
                    ULONG PagingPathLockMinRange : 1;
                    ULONG ComplexLock : 1;
                    ULONG FailVARotation : 1;
                    ULONG NoWriteCombined : 1;
                    ULONG NoPrePatching : 1;
                    ULONG AlwaysRepatch : 1;
                    ULONG ExpectPreparationFailure : 1;
                    ULONG FailUserModeVAMapping : 1;
                    ULONG Reserved : 19;
                };
                ULONG Value;
            };
        } SetFault;
    };
} D3DKMT_VIDMM_ESCAPE;

typedef struct _D3DKMT_VIDSCH_ESCAPE
{
    D3DKMT_VIDSCHESCAPETYPE Type;
    union
    {
        BOOL PreemptionControl; // enable/disable preemption
        BOOL SuspendScheduler;  // suspend/resume scheduler
        ULONG TdrControl;       // control tdr
    };
} D3DKMT_VIDSCH_ESCAPE;

// Upper boundary on the DMM escape data size (in bytes).
enum
{
    D3DKMT_MAX_DMM_ESCAPE_DATASIZE = 10*1024
};

// Can't be included at top of this header because it depends on D3DKMT_DISPLAYMODE.
#include <dmmdiag.h>

typedef struct _D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_SOURCEMODESET_INFO
{
    __in  D3DDDI_VIDEO_PRESENT_SOURCE_ID        VidPnSourceId;
    __out DMM_VIDPNSOURCEMODESET_SERIALIZATION  VidPnSourceModeSet;

} D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_SOURCEMODESET_INFO;

typedef struct _D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO
{
    __in  D3DDDI_VIDEO_PRESENT_SOURCE_ID         VidPnSourceId;
    __in  D3DKMDT_VIDPN_SOURCE_MODE              VidPnSourceMode;
    __out DMM_COFUNCPATHSMODALITY_SERIALIZATION  CofuncPathModality;

} D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO;


// NOTE: If (ProvidedBufferSize >= MinRequiredBufferSize), then MinRequiredBufferSize = size of the actual complete data set in the Data[] array.
//
// See dmmdiag.h for definitions of corresponding serialization formats.
typedef struct _D3DKMT_DMM_ESCAPE
{
    __in  D3DKMT_DMMESCAPETYPE  Type;
    __in  SIZE_T                ProvidedBufferSize;     // actual size of Data[] array, in bytes.
    __out SIZE_T                MinRequiredBufferSize;  // minimum required size of Data[] array to contain requested data.

    union
    {
        // NOTE: These types are not defined in the public header, since they are for test consumption only.
        //       They are listed here only for reference.
        //
        DMM_DIAG_INFO_INDEX                                        DmmSummaryInfo;                        // (Type == D3DKMT_DMMESCAPETYPE_GET_SUMMARY_INFO)
        DMM_VIDEOPRESENTSOURCESET_SERIALIZATION                    VideoPresentSourceSetInfo;             // (Type == D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_SOURCES_INFO)
        DMM_VIDEOPRESENTTARGETSET_SERIALIZATION                    VideoPresentTargetSetInfo;             // (Type == D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_TARGETS_INFO)
        DMM_VIDPN_SERIALIZATION                                    ActiveVidPnInfo;                       // (Type == D3DKMT_DMMESCAPETYPE_GET_ACTIVEVIDPN_INFO)
        DMM_MONITORSET_SERIALIZATION                               ConnectedMonitorsInfo;                 // (Type == D3DKMT_DMMESCAPETYPE_GET_MONITORS_INFO)
        DMM_VIDPNSET_SERIALIZATION                                 RecentlyCommittedVidPnsInfo;           // (Type == D3DKMT_DMMESCAPETYPE_RECENTLY_COMMITTED_VIDPNS_INFO)
        DMM_VIDPNSET_SERIALIZATION                                 RecentlyRecommendedVidPnsInfo;         // (Type == D3DKMT_DMMESCAPETYPE_RECENTLY_RECOMMENDED_VIDPNS_INFO)
        DMM_DISPMODECHANGEREQUESTSET_SERIALIZATION                 RecentlyRequestedDispModeChangesInfo;  // (Type == D3DKMT_DMMESCAPETYPE_RECENT_MODECHANGE_REQUESTS_INFO)
        D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_SOURCEMODESET_INFO       ActiveVidPnSourceModeSetInfo;          // (Type == D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_SOURCEMODESET_INFO)
        D3DKMDT_DMMESCARG_GET_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO  ActiveVidPnCofuncPathModalityInfo;     // (Type == D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO)

        __out_bcount(ProvidedBufferSize) UCHAR  Data[1];
    };

} D3DKMT_DMM_ESCAPE;

typedef enum _D3DKMT_DEVICEESCAPE_TYPE
{
    D3DKMT_DEVICEESCAPE_VIDPNFROMALLOCATION = 0,
} D3DKMT_DEVICEESCAPE_TYPE;

typedef struct _D3DKMT_DEVICE_ESCAPE
{
    D3DKMT_DEVICEESCAPE_TYPE Type;
    union
    {
        struct
        {
            D3DKMT_HANDLE                   hPrimaryAllocation; // in: Primary allocation handle
            D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // out: VidPnSoureId of primary allocation
        } VidPnFromAllocation;
    };
} D3DKMT_DEVICE_ESCAPE;

typedef struct _D3DKMT_DEBUG_SNAPSHOT_ESCAPE
{
    ULONG Length;   // out: Actual length of the snapshot written in Buffer
    BYTE Buffer[1]; // out: Buffer to place snapshot
} D3DKMT_DEBUG_SNAPSHOT_ESCAPE;

typedef struct _D3DKMT_ESCAPE
{
    D3DKMT_HANDLE       hAdapter;               // in: adapter handle
    D3DKMT_HANDLE       hDevice;                // in: device handle [Optional]
    D3DKMT_ESCAPETYPE   Type;                   // in: escape type.
    D3DDDI_ESCAPEFLAGS  Flags;                  // in: flags
    VOID*               pPrivateDriverData;     // in/out: escape data
    UINT                PrivateDriverDataSize;  // in: size of escape data
    D3DKMT_HANDLE       hContext;               // in: context handle [Optional]
} D3DKMT_ESCAPE;

typedef enum _D3DKMT_QUERYSTATISTICS_TYPE
{
    D3DKMT_QUERYSTATISTICS_ADAPTER  =  0,
    D3DKMT_QUERYSTATISTICS_PROCESS  =  1
} D3DKMT_QUERYSTATISTICS_TYPE;

typedef struct _D3DKMT_QUERYSTATISTICS
{
    D3DKMT_QUERYSTATISTICS_TYPE Type;
    VOID*                       pBuffer;        // in/out: statistics data
    UINT                        BufferSize;     // in: size of statistics data buffer
    union
    {
        struct
        {
            D3DKMT_HANDLE   hAdapter;
        } QueryAdapter;
        struct
        {
            LUID            AdapterLuid;
            HANDLE          hProcess;
        } QueryProcess;
    } u;
} D3DKMT_QUERYSTATISTICS;

typedef enum _D3DKMT_VIDPNSOURCEOWNER_TYPE
{
     D3DKMT_VIDPNSOURCEOWNER_UNOWNED        = 0,    //Has no owner or GDI is the owner   ;internal
     D3DKMT_VIDPNSOURCEOWNER_SHARED         = 1,    //Has shared owner, that is owner can yield to any exclusive owner, not available to legacy devices
     D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVE      = 2,    //Has exclusive owner without shared gdi primary,
     D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVEGDI   = 3,    //Has exclusive owner with shared gdi primary and must be exclusive owner of all VidPn sources, only available to legacy devices
} D3DKMT_VIDPNSOURCEOWNER_TYPE;

typedef struct _D3DKMT_SETVIDPNSOURCEOWNER
{
    D3DKMT_HANDLE                           hDevice;            // in: Device handle
    CONST D3DKMT_VIDPNSOURCEOWNER_TYPE*     pType;              // in: OwnerType array
    CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID*   pVidPnSourceId;     // in: VidPn source ID array
    UINT                                    VidPnSourceCount;   // in: Number of valid entries in above array
} D3DKMT_SETVIDPNSOURCEOWNER;

#define D3DKMT_GETPRESENTHISTORY_MAXTOKENS  2048

typedef struct _D3DKMT_GETPRESENTHISTORY
{
    D3DKMT_HANDLE                   hAdapter;                   // in:  Adapter handle
    ULONGLONG*                      pPresentHistory;            // out: buffer for completed present tokens
    UINT                            PresentHistoryTokenCount;   // in/out: max/returned number of present tokens
} D3DKMT_GETPRESENTHISTORY;

typedef struct _D3DKMT_CREATEOVERLAY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in
    D3DKMT_HANDLE                   hDevice;            // in: Indentifies the device
    D3DDDI_KERNELOVERLAYINFO        OverlayInfo;        // in
    D3DKMT_HANDLE                   hOverlay;           // out: Kernel overlay handle
} D3DKMT_CREATEOVERLAY;

typedef struct _D3DKMT_UPDATEOVERLAY
{
    D3DKMT_HANDLE            hDevice;           // in: Indentifies the device
    D3DKMT_HANDLE            hOverlay;          // in: Kernel overlay handle
    D3DDDI_KERNELOVERLAYINFO OverlayInfo;       // in
} D3DKMT_UPDATEOVERLAY;

typedef struct _D3DKMT_FLIPOVERLAY
{
    D3DKMT_HANDLE        hDevice;               // in: Indentifies the device
    D3DKMT_HANDLE        hOverlay;              // in: Kernel overlay handle
    D3DKMT_HANDLE        hSource;               // in: Allocation currently displayed
    VOID*                pPrivateDriverData;    // in: Private driver data
    UINT                 PrivateDriverDataSize; // in: Size of private driver data
} D3DKMT_FLIPOVERLAY;

typedef struct _D3DKMT_DESTROYOVERLAY
{
    D3DKMT_HANDLE        hDevice;               // in: Indentifies the device
    D3DKMT_HANDLE        hOverlay;              // in: Kernel overlay handle
} D3DKMT_DESTROYOVERLAY;

typedef struct _D3DKMT_WAITFORVERTICALBLANKEVENT
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DKMT_HANDLE                   hDevice;       // in: device handle [Optional]
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
} D3DKMT_WAITFORVERTICALBLANKEVENT;

typedef struct _D3DKMT_SETGAMMARAMP
{
    D3DKMT_HANDLE                   hDevice;       // in: device handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    D3DDDI_GAMMARAMP_TYPE           Type;          // in: Gamma ramp type
    union
    {
        D3DDDI_GAMMA_RAMP_RGB256x3x16* pGammaRampRgb256x3x16;
        D3DDDI_GAMMA_RAMP_DXGI_1*      pGammaRampDXGI1;
    };
    UINT                            Size;
} D3DKMT_SETGAMMARAMP;

typedef enum _D3DKMT_DEVICEEXECUTION_STATE
{
    D3DKMT_DEVICEEXECUTION_ACTIVE               = 1,
    D3DKMT_DEVICEEXECUTION_RESET                = 2,
    D3DKMT_DEVICEEXECUTION_HUNG                 = 3,
    D3DKMT_DEVICEEXECUTION_STOPPED              = 4,
    D3DKMT_DEVICEEXECUTION_ERROR_OUTOFMEMORY    = 5,
    D3DKMT_DEVICEEXECUTION_ERROR_DMAFAULT       = 6,
} D3DKMT_DEVICEEXECUTION_STATE;

typedef struct _D3DKMT_DEVICERESET_STATE
{
    union
    {
        struct
        {
            UINT    DesktopSwitched : 1;        // 0x00000001
            UINT    Reserved        :31;        // 0xFFFFFFFE
        };
        UINT    Value;
    };
} D3DKMT_DEVICERESET_STATE;

typedef struct _D3DKMT_PRESENT_STATS
{
    UINT PresentCount;
    UINT PresentRefreshCount;
    UINT SyncRefreshCount;
    LARGE_INTEGER SyncQPCTime;
    LARGE_INTEGER SyncGPUTime;
} D3DKMT_PRESENT_STATS;

typedef struct _D3DKMT_DEVICEPRESENT_STATE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in: present source id
    D3DKMT_PRESENT_STATS           PresentStats;  // out: present stats
} D3DKMT_DEVICEPRESENT_STATE;

typedef enum _D3DKMT_DEVICESTATE_TYPE
{
    D3DKMT_DEVICESTATE_EXECUTION = 1,
    D3DKMT_DEVICESTATE_PRESENT   = 2,
    D3DKMT_DEVICESTATE_RESET     = 3,
} D3DKMT_DEVICESTATE_TYPE;

typedef struct _D3DKMT_GETDEVICESTATE
{
    D3DKMT_HANDLE                   hDevice;       // in: device handle
    D3DKMT_DEVICESTATE_TYPE         StateType;     // in: device state type
    union
    {
        D3DKMT_DEVICEEXECUTION_STATE ExecutionState; // out: device state
        D3DKMT_DEVICEPRESENT_STATE   PresentState;   // in/out: present state
        D3DKMT_DEVICERESET_STATE     ResetState;     // out: reset state
    };
} D3DKMT_GETDEVICESTATE;

typedef struct _D3DKMT_CREATEDCFROMMEMORY
{
    VOID*                           pMemory;       // in: memory for DC
    D3DDDIFORMAT                    Format;        // in: Memory pixel format
    UINT                            Width;         // in: Memory Width
    UINT                            Height;        // in: Memory Height
    UINT                            Pitch;         // in: Memory pitch
    HDC                             hDeviceDc;     // in: DC describing the device
    PALETTEENTRY*                   pColorTable;   // in: Palette
    HDC                             hDc;           // out: HDC
    HANDLE                          hBitmap;       // out: Handle to bitmap
} D3DKMT_CREATEDCFROMMEMORY;

typedef struct _D3DKMT_DESTROYDCFROMMEMORY
{
    HDC                             hDc;           // in:
    HANDLE                          hBitmap;       // in:
} D3DKMT_DESTROYDCFROMMEMORY;

typedef struct _D3DKMT_SETCONTEXTSCHEDULINGPRIORITY
{
    D3DKMT_HANDLE                   hContext;      // in: context handle
    INT                             Priority;      // in: context priority
} D3DKMT_SETCONTEXTSCHEDULINGPRIORITY;

typedef struct _D3DKMT_CHANGESURFACEPOINTER
{
    HDC                             hDC;             // in: dc handle
    HANDLE                          hBitmap;         // in: bitmap handle
    LPVOID                          pSurfacePointer; // in: new surface pointer
    UINT                            Width;           // in: Memory Width
    UINT                            Height;          // in: Memory Height
    UINT                            Pitch;           // in: Memory pitch
} D3DKMT_CHANGESURFACEPOINTER;

typedef struct _D3DKMT_GETCONTEXTSCHEDULINGPRIORITY
{
    D3DKMT_HANDLE                   hContext;      // in: context handle
    INT                             Priority;      // out: context priority
} D3DKMT_GETCONTEXTSCHEDULINGPRIORITY;

typedef enum _D3DKMT_SCHEDULINGPRIORITYCLASS
{
    D3DKMT_SCHEDULINGPRIORITYCLASS_IDLE         = 0,
    D3DKMT_SCHEDULINGPRIORITYCLASS_BELOW_NORMAL = 1,
    D3DKMT_SCHEDULINGPRIORITYCLASS_NORMAL       = 2,
    D3DKMT_SCHEDULINGPRIORITYCLASS_ABOVE_NORMAL = 3,
    D3DKMT_SCHEDULINGPRIORITYCLASS_HIGH         = 4,
    D3DKMT_SCHEDULINGPRIORITYCLASS_REALTIME     = 5,
} D3DKMT_SCHEDULINGPRIORITYCLASS;

typedef struct _D3DKMT_GETSCANLINE
{
    D3DKMT_HANDLE                   hAdapter;           // in: Adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: Adapter's VidPN Source ID
    BOOLEAN                         InVerticalBlank;    // out: Within vertical blank
    UINT                            ScanLine;           // out: Current scan line
} D3DKMT_GETSCANLINE;

typedef enum _D3DKMT_QUEUEDLIMIT_TYPE
{
    D3DKMT_SET_QUEUEDLIMIT_PRESENT     = 1,
    D3DKMT_GET_QUEUEDLIMIT_PRESENT     = 2,
} D3DKMT_QUEUEDLIMIT_TYPE;

typedef struct _D3DKMT_SETQUEUEDLIMIT
{
    D3DKMT_HANDLE                   hDevice;            // in: device handle
    D3DKMT_QUEUEDLIMIT_TYPE         Type;               // in: limit type
    union
    {
        UINT                        QueuedPresentLimit; // in (or out): queued present limit
        struct
        {
            D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;          // in: adapter's VidPN source ID
            UINT                           QueuedPendingFlipLimit; // in (or out): flip pending limit
        };
    };
} D3DKMT_SETQUEUEDLIMIT;

typedef struct _D3DKMT_POLLDISPLAYCHILDREN
{
    D3DKMT_HANDLE                   hAdapter;           // in: Adapter handle
    BOOLEAN                         NonDestructiveOnly; // in: Destructive or not
} D3DKMT_POLLDISPLAYCHILDREN;

typedef struct _D3DKMT_INVALIDATEACTIVEVIDPN
{
    D3DKMT_HANDLE                   hAdapter;               // in: Adapter handle
    VOID*                           pPrivateDriverData;     // in: Private driver data
    UINT                            PrivateDriverDataSize;  // in: Size of private driver data
} D3DKMT_INVALIDATEACTIVEVIDPN;

typedef struct _D3DKMT_CHECKOCCLUSION
{
    HWND            hWindow;        // in:  Destination window handle
} D3DKMT_CHECKOCCLUSION;

typedef struct _D3DKMT_WAITFORIDLE
{
    D3DKMT_HANDLE   hDevice;        // in:  Device to wait for idle
} D3DKMT_WAITFORIDLE;

typedef struct _D3DKMT_CHECKMONITORPOWERSTATE
{
    D3DKMT_HANDLE    hAdapter;    // in: Adapter to check on
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: Adapter's VidPN Source ID
} D3DKMT_CHECKMONITORPOWERSTATE;

typedef struct _D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT
{
    D3DKMT_HANDLE                   hDevice;                         // in: Identifies the device
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;                   // in: Identifies which VidPn we are changing the private driver format attribute for
    UINT                            PrivateDriverFormatAttribute;    // In: Requested private format attribute for VidPn specified
} D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT;

typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATEALLOCATION)(IN OUT D3DKMT_CREATEALLOCATION*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_QUERYRESOURCEINFO)(IN OUT D3DKMT_QUERYRESOURCEINFO*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_OPENRESOURCE)(IN OUT D3DKMT_OPENRESOURCE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYALLOCATION)(IN CONST D3DKMT_DESTROYALLOCATION*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETALLOCATIONPRIORITY)(IN CONST D3DKMT_SETALLOCATIONPRIORITY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_QUERYALLOCATIONRESIDENCY)(IN CONST D3DKMT_QUERYALLOCATIONRESIDENCY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATEDEVICE)(IN OUT D3DKMT_CREATEDEVICE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYDEVICE)(IN CONST D3DKMT_DESTROYDEVICE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATECONTEXT)(IN OUT D3DKMT_CREATECONTEXT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYCONTEXT)(IN CONST D3DKMT_DESTROYCONTEXT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATESYNCHRONIZATIONOBJECT)(IN OUT D3DKMT_CREATESYNCHRONIZATIONOBJECT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYSYNCHRONIZATIONOBJECT)(IN CONST D3DKMT_DESTROYSYNCHRONIZATIONOBJECT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_WAITFORSYNCHRONIZATIONOBJECT)(IN OUT D3DKMT_WAITFORSYNCHRONIZATIONOBJECT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SIGNALSYNCHRONIZATIONOBJECT)(IN CONST D3DKMT_SIGNALSYNCHRONIZATIONOBJECT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_LOCK)(IN OUT D3DKMT_LOCK*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_UNLOCK)(IN CONST D3DKMT_UNLOCK*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETDISPLAYMODELIST)(IN OUT D3DKMT_GETDISPLAYMODELIST*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETDISPLAYMODE)(IN CONST D3DKMT_SETDISPLAYMODE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETMULTISAMPLEMETHODLIST)(IN OUT D3DKMT_GETMULTISAMPLEMETHODLIST*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_PRESENT)(IN CONST D3DKMT_PRESENT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_RENDER)(IN OUT D3DKMT_RENDER*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETRUNTIMEDATA)(IN CONST D3DKMT_GETRUNTIMEDATA*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_QUERYADAPTERINFO)(IN CONST D3DKMT_QUERYADAPTERINFO*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_OPENADAPTERFROMHDC)(IN OUT D3DKMT_OPENADAPTERFROMHDC*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_OPENADAPTERFROMGDIDISPLAYNAME)(IN OUT D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_OPENADAPTERFROMDEVICENAME)(IN OUT D3DKMT_OPENADAPTERFROMDEVICENAME*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CLOSEADAPTER)(IN CONST D3DKMT_CLOSEADAPTER*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETSHAREDPRIMARYHANDLE)(IN OUT D3DKMT_GETSHAREDPRIMARYHANDLE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_ESCAPE)(IN CONST D3DKMT_ESCAPE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_QUERYSTATISTICS)(IN CONST D3DKMT_QUERYSTATISTICS*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETVIDPNSOURCEOWNER)(IN CONST D3DKMT_SETVIDPNSOURCEOWNER*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETPRESENTHISTORY)(IN OUT D3DKMT_GETPRESENTHISTORY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATEOVERLAY)(IN OUT D3DKMT_CREATEOVERLAY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_UPDATEOVERLAY)(IN CONST D3DKMT_UPDATEOVERLAY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_FLIPOVERLAY)(IN CONST D3DKMT_FLIPOVERLAY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYOVERLAY)(IN CONST D3DKMT_DESTROYOVERLAY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_WAITFORVERTICALBLANKEVENT)(IN CONST D3DKMT_WAITFORVERTICALBLANKEVENT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETGAMMARAMP)(IN CONST D3DKMT_SETGAMMARAMP*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETDEVICESTATE)(IN OUT D3DKMT_GETDEVICESTATE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CREATEDCFROMMEMORY)(IN OUT D3DKMT_CREATEDCFROMMEMORY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_DESTROYDCFROMMEMORY)(IN CONST D3DKMT_DESTROYDCFROMMEMORY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETCONTEXTSCHEDULINGPRIORITY)(IN CONST D3DKMT_SETCONTEXTSCHEDULINGPRIORITY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETCONTEXTSCHEDULINGPRIORITY)(IN OUT D3DKMT_GETCONTEXTSCHEDULINGPRIORITY*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETPROCESSSCHEDULINGPRIORITYCLASS)(IN HANDLE, IN D3DKMT_SCHEDULINGPRIORITYCLASS);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETPROCESSSCHEDULINGPRIORITYCLASS)(IN HANDLE, OUT D3DKMT_SCHEDULINGPRIORITYCLASS*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_RELEASEPROCESSVIDPNSOURCEOWNERS)(IN HANDLE);
typedef NTSTATUS (APIENTRY *PFND3DKMT_GETSCANLINE)(IN OUT D3DKMT_GETSCANLINE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CHANGESURFACEPOINTER)(IN CONST D3DKMT_CHANGESURFACEPOINTER*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETQUEUEDLIMIT)(IN CONST D3DKMT_SETQUEUEDLIMIT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_POLLDISPLAYCHILDREN)(IN CONST D3DKMT_POLLDISPLAYCHILDREN*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_INVALIDATEACTIVEVIDPN)(IN CONST D3DKMT_INVALIDATEACTIVEVIDPN*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CHECKOCCLUSION)(IN CONST D3DKMT_CHECKOCCLUSION*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_WAITFORIDLE)(IN CONST D3DKMT_WAITFORIDLE*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_CHECKMONITORPOWERSTATE)(IN CONST D3DKMT_CHECKMONITORPOWERSTATE*);
typedef BOOLEAN  (APIENTRY *PFND3DKMT_CHECKEXCLUSIVEOWNERSHIP)();
typedef NTSTATUS (APIENTRY *PFND3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT)(IN CONST D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SHAREDPRIMARYLOCKNOTIFICATION)(IN CONST D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION*);
typedef NTSTATUS (APIENTRY *PFND3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION)(IN CONST D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION*);

#ifdef __cplusplus
extern "C"
{
#endif

EXTERN_C NTSTATUS APIENTRY D3DKMTCreateAllocation(IN OUT D3DKMT_CREATEALLOCATION*);
EXTERN_C NTSTATUS APIENTRY D3DKMTQueryResourceInfo(IN OUT D3DKMT_QUERYRESOURCEINFO*);
EXTERN_C NTSTATUS APIENTRY D3DKMTOpenResource(IN OUT D3DKMT_OPENRESOURCE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroyAllocation(IN CONST D3DKMT_DESTROYALLOCATION*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetAllocationPriority(IN CONST D3DKMT_SETALLOCATIONPRIORITY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTQueryAllocationResidency(IN CONST D3DKMT_QUERYALLOCATIONRESIDENCY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCreateDevice(IN OUT D3DKMT_CREATEDEVICE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroyDevice(IN CONST D3DKMT_DESTROYDEVICE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCreateContext(IN OUT D3DKMT_CREATECONTEXT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroyContext(IN CONST D3DKMT_DESTROYCONTEXT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCreateSynchronizationObject(IN OUT D3DKMT_CREATESYNCHRONIZATIONOBJECT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroySynchronizationObject(IN CONST D3DKMT_DESTROYSYNCHRONIZATIONOBJECT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTWaitForSynchronizationObject(IN OUT D3DKMT_WAITFORSYNCHRONIZATIONOBJECT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSignalSynchronizationObject(IN CONST D3DKMT_SIGNALSYNCHRONIZATIONOBJECT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTLock(IN OUT D3DKMT_LOCK*);
EXTERN_C NTSTATUS APIENTRY D3DKMTUnlock(IN CONST D3DKMT_UNLOCK*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetDisplayModeList(IN OUT D3DKMT_GETDISPLAYMODELIST*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetDisplayMode(IN CONST D3DKMT_SETDISPLAYMODE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetMultisampleMethodList(IN OUT D3DKMT_GETMULTISAMPLEMETHODLIST*);
EXTERN_C NTSTATUS APIENTRY D3DKMTPresent(IN CONST D3DKMT_PRESENT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTRender(IN OUT D3DKMT_RENDER*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetRuntimeData(IN CONST D3DKMT_GETRUNTIMEDATA*);
EXTERN_C NTSTATUS APIENTRY D3DKMTQueryAdapterInfo(IN CONST D3DKMT_QUERYADAPTERINFO*);
EXTERN_C NTSTATUS APIENTRY D3DKMTOpenAdapterFromHdc(IN OUT D3DKMT_OPENADAPTERFROMHDC*);
EXTERN_C NTSTATUS APIENTRY D3DKMTOpenAdapterFromGdiDisplayName(IN OUT D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME*);
EXTERN_C NTSTATUS APIENTRY D3DKMTOpenAdapterFromDeviceName(IN OUT D3DKMT_OPENADAPTERFROMDEVICENAME*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCloseAdapter(IN CONST D3DKMT_CLOSEADAPTER*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetSharedPrimaryHandle(IN OUT D3DKMT_GETSHAREDPRIMARYHANDLE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTEscape(IN CONST D3DKMT_ESCAPE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetVidPnSourceOwner(IN CONST D3DKMT_SETVIDPNSOURCEOWNER*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetPresentHistory(IN OUT D3DKMT_GETPRESENTHISTORY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCreateOverlay(IN OUT D3DKMT_CREATEOVERLAY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTUpdateOverlay(IN CONST D3DKMT_UPDATEOVERLAY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTFlipOverlay(IN CONST D3DKMT_FLIPOVERLAY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroyOverlay(IN CONST D3DKMT_DESTROYOVERLAY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTWaitForVerticalBlankEvent(IN CONST D3DKMT_WAITFORVERTICALBLANKEVENT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetGammaRamp(IN CONST D3DKMT_SETGAMMARAMP*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetDeviceState(IN OUT D3DKMT_GETDEVICESTATE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCreateDCFromMemory(IN OUT D3DKMT_CREATEDCFROMMEMORY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTDestroyDCFromMemory(IN CONST D3DKMT_DESTROYDCFROMMEMORY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetContextSchedulingPriority(IN CONST D3DKMT_SETCONTEXTSCHEDULINGPRIORITY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetContextSchedulingPriority(IN OUT D3DKMT_GETCONTEXTSCHEDULINGPRIORITY*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetProcessSchedulingPriorityClass(IN HANDLE, IN D3DKMT_SCHEDULINGPRIORITYCLASS);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetProcessSchedulingPriorityClass(IN HANDLE, OUT D3DKMT_SCHEDULINGPRIORITYCLASS*);
EXTERN_C NTSTATUS APIENTRY D3DKMTReleaseProcessVidPnSourceOwners(IN HANDLE);
EXTERN_C NTSTATUS APIENTRY D3DKMTGetScanLine(IN OUT D3DKMT_GETSCANLINE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTChangeSurfacePointer(IN CONST D3DKMT_CHANGESURFACEPOINTER*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetQueuedLimit(IN CONST D3DKMT_SETQUEUEDLIMIT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTPollDisplayChildren(IN CONST D3DKMT_POLLDISPLAYCHILDREN*);
EXTERN_C NTSTATUS APIENTRY D3DKMTInvalidateActiveVidPn(IN CONST D3DKMT_INVALIDATEACTIVEVIDPN*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCheckOcclusion(IN CONST D3DKMT_CHECKOCCLUSION*);
EXTERN_C NTSTATUS APIENTRY D3DKMTWaitForIdle(IN CONST D3DKMT_WAITFORIDLE*);
EXTERN_C NTSTATUS APIENTRY D3DKMTCheckMonitorPowerState(IN CONST D3DKMT_CHECKMONITORPOWERSTATE*);
EXTERN_C BOOLEAN  APIENTRY D3DKMTCheckExclusiveOwnership(VOID);
EXTERN_C NTSTATUS APIENTRY D3DKMTSetDisplayPrivateDriverFormat(IN CONST D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSharedPrimaryLockNotification(IN CONST D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION*);
EXTERN_C NTSTATUS APIENTRY D3DKMTSharedPrimaryUnLockNotification(IN CONST D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION*);

#ifdef __cplusplus
}
#endif

#endif /* _D3DKMTHK_H_ */

