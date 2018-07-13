/******************************Module*Header**********************************\
*
* Module Name: d3dkmddi.h
*
* Content: longhorn display driver kernel mode interfaces
*
* Copyright (c) 2003 Microsoft Corporation.  All rights reserved.
\*****************************************************************************/
#ifndef _D3DKMDDI_H_
#define _D3DKMDDI_H_

#include <d3dkmdt.h>

typedef struct _DXGK_SEGMENTPREFERENCE
{
    union
    {
        struct
        {
            UINT SegmentId0 : 5;                // 0x0000001F
            UINT Direction0 : 1;                // 0x00000020
            UINT SegmentId1 : 5;                // 0x000007C0
            UINT Direction1 : 1;                // 0x00000800
            UINT SegmentId2 : 5;                // 0x0001F000
            UINT Direction2 : 1;                // 0x00020000
            UINT SegmentId3 : 5;                // 0x007C0000
            UINT Direction3 : 1;                // 0x00800000
            UINT SegmentId4 : 5;                // 0x1F000000
            UINT Direction4 : 1;                // 0x20000000
            UINT Reserved   : 2;                // 0xC0000000
        };
        UINT Value;
    };
} DXGK_SEGMENTPREFERENCE;

typedef struct _DXGK_SEGMENTBANKPREFERENCE
{
    union
    {
        struct
        {
            UINT Bank0          : 7;    // 0x0000007F
            UINT Direction0     : 1;    // 0x00000080
            UINT Bank1          : 7;    // 0x00007F00
            UINT Direction1     : 1;    // 0x00008000
            UINT Bank2          : 7;    // 0x007F0000
            UINT Direction2     : 1;    // 0x00800000
            UINT Bank3          : 7;    // 0x7F000000
            UINT Direction3     : 1;    // 0x80000000
        };
        UINT Value;
    };
} DXGK_SEGMENTBANKPREFERENCE;

typedef struct _DXGK_ALLOCATIONLIST
{
    HANDLE              hDeviceSpecificAllocation;
    struct
    {
        UINT            WriteOperation  : 1;    // 0x00000001
        UINT            SegmentId       : 5;    // 0x0000002E
        UINT            Reserved        : 26;   // 0xFFFFFFC0
    };
    PHYSICAL_ADDRESS    PhysicalAddress;
} DXGK_ALLOCATIONLIST;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Define parameter types for SAL-annotated DDI parameters.  These are used by DDI function
//          name typedefs in dispmprt.h and d3dkmddi.h.  They are not needed in a driver's DDI function
//          definitions, and should not be used in driver code.
//
//  Naming convention: Concatenate all SAL annotations, an underscore, other modifiers
//                     such as CONST, and the type of the parameter, and use uppercase
//                     only.
//
typedef __in          BOOLEAN               IN_BOOLEAN;
typedef __in          UCHAR                 IN_UCHAR;
typedef __in          DEVICE_POWER_STATE    IN_DEVICE_POWER_STATE;
typedef __in    CONST HANDLE                IN_CONST_HANDLE;
typedef __inout       UINT*                 INOUT_PUINT;
typedef __in          ULONG                 IN_ULONG;
typedef __out         PULONG                OUT_PULONG;
typedef __in          POWER_ACTION          IN_POWER_ACTION;
typedef __in          PVOID                 IN_PVOID;
typedef __in    CONST PVOID                 IN_CONST_PVOID;
typedef __out         PVOID*                OUT_PPVOID;


typedef struct _DXGKARG_RENDER
{
    CONST VOID* CONST           pCommand;
    CONST UINT                  CommandLength;
    VOID*                       pDmaBuffer;
    UINT                        DmaSize;
    VOID*                       pDmaBufferPrivateData;
    UINT                        DmaBufferPrivateDataSize;
    DXGK_ALLOCATIONLIST*        pAllocationList;
    UINT                        AllocationListSize;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListIn;
    UINT                        PatchLocationListInSize;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;
    UINT                        PatchLocationListOutSize;
    UINT                        MultipassOffset;
    UINT                        DmaBufferSegmentId;
    PHYSICAL_ADDRESS            DmaBufferPhysicalAddress;
} DXGKARG_RENDER;

typedef __inout DXGKARG_RENDER*     INOUT_PDXGKARG_RENDER;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_RENDER(
    IN_CONST_HANDLE         hContext,
    INOUT_PDXGKARG_RENDER   pRender
    );

#define DXGK_PRESENT_SOURCE_INDEX       1
#define DXGK_PRESENT_DESTINATION_INDEX  2
#define DXGK_PRESENT_MAX_INDEX          DXGK_PRESENT_DESTINATION_INDEX

typedef struct _DXGK_PRESENTFLAGS
{
    union
    {
        struct
        {
            UINT    Blt             : 1;    // 0x00000001
            UINT    ColorFill       : 1;    // 0x00000002
            UINT    Flip            : 1;    // 0x00000004
            UINT    FlipWithNoWait  : 1;    // 0x00000008
            UINT    SrcColorKey     : 1;    // 0x00000010
            UINT    DstColorKey     : 1;    // 0x00000020
            UINT    LinearToSrgb    : 1;    // 0x00000040
            UINT    Rotate          : 1;    // 0x00000080
            UINT    Reserved        :24;    // 0xFFFFFF00
        };
        UINT Value;
    };
} DXGK_PRESENTFLAGS;

typedef struct _DXGKARG_PRESENT
{
    VOID*                       pDmaBuffer;
    UINT                        DmaSize;
    VOID*                       pDmaBufferPrivateData;
    UINT                        DmaBufferPrivateDataSize;
    DXGK_ALLOCATIONLIST*        pAllocationList;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;
    UINT                        PatchLocationListOutSize;
    UINT                        MultipassOffset;
    UINT                        Color;
    RECT                        DstRect;
    RECT                        SrcRect;
    UINT                        SubRectCnt;
    CONST RECT*                 pDstSubRects;
    D3DDDI_FLIPINTERVAL_TYPE    FlipInterval;
    DXGK_PRESENTFLAGS           Flags;
    UINT                        DmaBufferSegmentId;
    PHYSICAL_ADDRESS            DmaBufferPhysicalAddress;    
} DXGKARG_PRESENT;

typedef __inout DXGKARG_PRESENT*    INOUT_PDXGKARG_PRESENT;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_PRESENT(
    IN_CONST_HANDLE         hContext,
    INOUT_PDXGKARG_PRESENT  pPresent
    );

typedef struct _DXGKARG_STOPCAPTURE
{
    HANDLE                      hAllocation;
} DXGKARG_STOPCAPTURE;

typedef __in CONST DXGKARG_STOPCAPTURE*     IN_CONST_PDXGKARG_STOPCAPTURE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_STOPCAPTURE(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_STOPCAPTURE   pStopCapture
    );

// Definition for Scheduler Interrupt Event Type.
//
typedef enum _DXGK_INTERRUPT_TYPE
{
    DXGK_INTERRUPT_DMA_COMPLETED  = 1,
    DXGK_INTERRUPT_DMA_PREEMPTED  = 2,
    DXGK_INTERRUPT_CRTC_VSYNC     = 3,
    DXGK_INTERRUPT_DMA_FAULTED    = 4,
} DXGK_INTERRUPT_TYPE;

typedef struct _DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS
{
    union
    {
        struct
        {
            UINT            ValidPhysicalAdapterMask : 1; // 0x00000001
            UINT            Reserved                 :31; // 0xFFFFFFFE
        };
        UINT                Value;
    };
} DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS;

typedef struct _DXGKARGCB_NOTIFY_INTERRUPT_DATA
{
    DXGK_INTERRUPT_TYPE  InterruptType;        // in: interrupt type
    union
    {
        struct
        {
            UINT             SubmissionFenceId;         // in: submission id of completed command.
            UINT             NodeOrdinal;               // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;             // in: Engine ordinal of engine generating the notification.
        } DmaCompleted;
        struct
        {
            UINT             PreemptionFenceId;    // in: submission id of preemption request.
            UINT             LastCompletedFenceId; // in: submission id of last completed command before preemption.
            UINT             NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;        // in: Engine ordinal of engine generating the notification.
        } DmaPreempted;
        struct
        {
            UINT             FaultedFenceId;       // in: submission id of faulted command.
            NTSTATUS         Status;               // in: status of fault
            UINT             NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;        // in: Engine ordinal of engine generating the notification.
        } DmaFaulted;
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID VidPnTargetId;       // in: VidPnTarget id (where vsync occurs).
            PHYSICAL_ADDRESS               PhysicalAddress;     // in: Physical Address of displaying buffer.
            UINT                           PhysicalAdapterMask; // in: Physical adapter mask (where vsync occurs).
                                                                //     (Must set Flags.ValidPhysicalAdapterMask as well)
        } CrtcVsync;
        struct
        {
            UINT            Reserved[16];
        } Reserved;
    };
    DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS Flags;      // in: event flags
} DXGKARGCB_NOTIFY_INTERRUPT_DATA;

// Device Driver Interface fence update at ISR.
//
typedef VOID (APIENTRY CALLBACK *DXGKCB_NOTIFY_INTERRUPT)(HANDLE hAdapter, CONST DXGKARGCB_NOTIFY_INTERRUPT_DATA*);

// Device Driver Interface fence update at DPC.
//
typedef VOID (APIENTRY CALLBACK *DXGKCB_NOTIFY_DPC)(HANDLE hAdapter);

typedef struct _DXGK_OPENALLOCATIONINFO
{
    D3DKMT_HANDLE   hAllocation;                        // in: dxg assigned per Device handle
    VOID*           pPrivateDriverData;                 // in/out: Private data for each allocation allocated by the user mode driver
    UINT            PrivateDriverDataSize;              // in: Size of the private data
    HANDLE          hDeviceSpecificAllocation;          // out: driver set it
} DXGK_OPENALLOCATIONINFO;

typedef struct _DXGK_OPENALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT    Create          : 1;    // 0x00000001       // Indicates that this allocation is being created, if not set then allocation is being opened
            UINT    Reserved        :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_OPENALLOCATIONFLAGS;

typedef struct _DXGKARG_OPENALLOCATION
{
    UINT                            NumAllocations;
    DXGK_OPENALLOCATIONINFO*        pOpenAllocation;
    VOID*                           pPrivateDriverData;
    UINT                            PrivateDriverSize;
    DXGK_OPENALLOCATIONFLAGS        Flags;
} DXGKARG_OPENALLOCATION;

typedef __inout CONST DXGKARG_OPENALLOCATION*   INOUT_CONST_PDXGKARG_OPENALLOCATION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_OPENALLOCATIONINFO(
    IN_CONST_HANDLE                         hDevice,
    INOUT_CONST_PDXGKARG_OPENALLOCATION     pOpenAllocation
    );

typedef struct _DXGKARG_CLOSEALLOCATION
{
    UINT            NumAllocations;
    CONST HANDLE*   pOpenHandleList;    //in: hDeviceSpecificAllocation list
} DXGKARG_CLOSEALLOCATION;

typedef __in    CONST DXGKARG_CLOSEALLOCATION*  IN_CONST_PDXGKARG_CLOSEALLOCATION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CLOSEALLOCATION(
    IN_CONST_HANDLE                     hDevice,
    IN_CONST_PDXGKARG_CLOSEALLOCATION   pCloseAllocation
    );

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_DESTROYDEVICE(
    IN_CONST_HANDLE     hDevice
    );

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_DESTROYCONTEXT(
    IN_CONST_HANDLE     hContext
    );

typedef D3DKMT_HANDLE (APIENTRY CALLBACK *DXGKCB_GETHANDLEPARENT)(D3DKMT_HANDLE hAllocation);

typedef enum _DXGK_HANDLE_TYPE
{
    DXGK_HANDLE_ALLOCATION  = 1,
    DXGK_HANDLE_RESOURCE    = 2,
} DXGK_HANDLE_TYPE;

typedef struct _DXGKCB_GETHANDLEDATAFLAGS
{
    union
    {
        struct
        {
            UINT                DeviceSpecific  : 1;    // 0x00000001
            UINT                Reserved        :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGKCB_GETHANDLEDATAFLAGS;

typedef struct _DXGKARGCB_GETHANDLEDATA
{
    D3DKMT_HANDLE           hObject;
    DXGK_HANDLE_TYPE        Type;
    DXGKCB_GETHANDLEDATAFLAGS Flags;
} DXGKARGCB_GETHANDLEDATA;
typedef VOID*  (APIENTRY CALLBACK *DXGKCB_GETHANDLEDATA)(CONST DXGKARGCB_GETHANDLEDATA*);

typedef struct _DXGKARGCB_ENUMHANDLECHILDREN
{
    D3DKMT_HANDLE   hObject;
    UINT            Index;
} DXGKARGCB_ENUMHANDLECHILDREN;
typedef D3DKMT_HANDLE (APIENTRY CALLBACK *DXGKCB_ENUMHANDLECHILDREN)(CONST DXGKARGCB_ENUMHANDLECHILDREN*);

typedef struct _DXGKARGCB_GETCAPTUREADDRESS
{
    D3DKMT_HANDLE      hAllocation;          // in:  Allocation handle
    UINT               SegmentId;            // out: Segment ID of capture buffer
    PHYSICAL_ADDRESS   PhysicalAddress;      // out: Physical address of capture buffer
} DXGKARGCB_GETCAPTUREADDRESS;
typedef NTSTATUS (APIENTRY CALLBACK *DXGKCB_GETCAPTUREADDRESS)(DXGKARGCB_GETCAPTUREADDRESS*);

typedef struct _DXGK_DEVICEINFOFLAGS
{
    union
    {
        struct
        {
            UINT    GuaranteedDmaBufferContract : 1;    // 0x00000001
            UINT    Reserved                    :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
 } DXGK_DEVICEINFOFLAGS;

typedef struct _DXGK_DEVICEINFO
{
    UINT        DmaBufferSize;
    UINT        DmaBufferSegmentSet;
    UINT        DmaBufferPrivateDataSize;
    UINT        AllocationListSize;
    UINT        PatchLocationListSize;
    DXGK_DEVICEINFOFLAGS Flags;
} DXGK_DEVICEINFO;

typedef struct _DXGK_CREATEDEVICEFLAGS
{
    union
    {
        struct
        {

            UINT    SystemDevice   :  1;  // 0x00000001
            UINT    Reserved       : 31;  // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_CREATEDEVICEFLAGS;

typedef struct _DXGKARG_CREATEDEVICE
{
    HANDLE               hDevice;            // in:  Runtime handle/out: Driver handle
    union
    {
        DXGK_CREATEDEVICEFLAGS Flags;        // in:  device creation flags
        DXGK_DEVICEINFO*       pInfo;        // out: device info from driver (obsolate: backward compatibility only)
    };
} DXGKARG_CREATEDEVICE;

typedef __inout DXGKARG_CREATEDEVICE*   INOUT_PDXGKARG_CREATEDEVICE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CREATEDEVICE(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_PDXGKARG_CREATEDEVICE     pCreateDevice
    );

typedef struct _DXGK_CREATECONTEXTFLAGS
{
    union
    {
        struct
        {
            UINT    SystemContext   : 1;
            UINT    Reserved        : 31;
        };
        UINT Value;
    };
} DXGK_CREATECONTEXTFLAGS;

typedef struct _DXGK_CONTEXTINFO
{
    UINT        DmaBufferSize;
    UINT        DmaBufferSegmentSet;
    UINT        DmaBufferPrivateDataSize;
    UINT        AllocationListSize;
    UINT        PatchLocationListSize;
} DXGK_CONTEXTINFO;

typedef struct _DXGKARG_CREATECONTEXT
{
    HANDLE                  hContext;              // in:  Runtime handle/out: Driver handle
    UINT                    NodeOrdinal;           // in:  Node targetted for this context.
    UINT                    EngineAffinity;        // in:  Engine affinity.
    DXGK_CREATECONTEXTFLAGS Flags;                 // in:  Context creation flags.
    VOID*                   pPrivateDriverData;    // in:  Private driver data
    UINT                    PrivateDriverDataSize; // in:  Size of private driver data
    DXGK_CONTEXTINFO        ContextInfo;           // out: context info from driver
} DXGKARG_CREATECONTEXT;

typedef __inout DXGKARG_CREATECONTEXT*   INOUT_PDXGKARG_CREATECONTEXT;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CREATECONTEXT(
    IN_CONST_HANDLE                 hDevice,
    INOUT_PDXGKARG_CREATECONTEXT    pCreateContext
    );

typedef __in CONST DXGKARG_SETPALETTE*      IN_CONST_PDXGKARG_SETPALETTE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETPALETTE(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_SETPALETTE    pSetPalette
    );

typedef struct _DXGK_POINTERFLAGS
{
    union
    {
        struct
        {
            UINT    Monochrome      : 1;    // 0x00000001
            UINT    Color           : 1;    // 0x00000002
            UINT    MaskedColor     : 1;    // 0x00000004
            UINT    Reserved        :29;    // 0xFFFFFFF8
        };
        UINT        Value;
    };
} DXGK_POINTERFLAGS;

typedef struct _DXGKARG_SETPOINTERSHAPE
{
    DXGK_POINTERFLAGS               Flags;
    UINT                            Width;
    UINT                            Height;
    UINT                            Pitch;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    CONST VOID*                     pPixels;
    UINT                            XHot;
    UINT                            YHot;
} DXGKARG_SETPOINTERSHAPE;

//
//Flags specifies monochrome or color pointer or color pointer with alpha.
//
//Width is Width of the pointer in pixels.
//
//Height is Height of the pointer in scans.
//
//Pitch is Width of the pointer in bytes.
//
//VidPnSourceId is VidPN source ID of this adapter on which the pointer is being set.
//
//pPixels points to the start of color bitmap size of specified Width and Height
// in 32-bpp ARGB DIB format for non-monochrome pointers, or points to the start of
// monochrome bitmap size of specified Width and Height in 1-bpp DIB format AND mask
// followed by another 1-bpp DIB format XOR mask of the same size for monochrome pointers.
//
//XHot is column on which hot pixel is located from top left of pointer bitmap in pixels.
//
//YHot is row on which hot pixel is located from top left of pointer bitmap in pixels.
//

typedef __in CONST DXGKARG_SETPOINTERSHAPE*     IN_CONST_PDXGKARG_SETPOINTERSHAPE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETPOINTERSHAPE(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_SETPOINTERSHAPE   pSetPointerShape
    );

typedef struct _DXGK_SETPOINTERPOSITIONFLAGS
{
    union
    {
        struct
        {
            UINT                        Visible : 1;    // 0x00000001
            UINT                        Reserved:31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_SETPOINTERPOSITIONFLAGS;

typedef struct _DXGKARG_SETPOINTERPOSITION
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    INT                             X;
    INT                             Y;
    DXGK_SETPOINTERPOSITIONFLAGS    Flags;
} DXGKARG_SETPOINTERPOSITION;

//
//Visible indicates if the pointer should be visible or not.
//X and Y should be ignored by driver if FALSE.
//
//Output is output index of this adapter.
//
//X is Column on which the top left pixel of cursor image is located
//from the top left pixel of the VidPN source in pixels.
//
//Y is Row on which the top left pixel of cusor image is located from
//the top left pixel of the VidPN source in pixels.
//

typedef __in CONST DXGKARG_SETPOINTERPOSITION*      IN_CONST_PDXGKARG_SETPOINTERPOSITION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETPOINTERPOSITION(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_SETPOINTERPOSITION    pSetPointerPosition
    );

typedef enum _DXGK_QUERYADAPTERINFOTYPE
{
    DXGKQAITYPE_UMDRIVERPRIVATE = 0,
    DXGKQAITYPE_DRIVERCAPS      = 1,
    DXGKQAITYPE_QUERYSEGMENT    = 2,
} DXGK_QUERYADAPTERINFOTYPE;

typedef struct _DXGK_GAMMARAMPCAPS
{
    union
    {
        struct
        {
            UINT    Gamma_Rgb256x3x16  : 1;    // 0x00000001
            UINT    Reserved           :31;    // 0xFFFFFFFC
        };
        UINT        Value;
    };
} DXGK_GAMMARAMPCAPS;

typedef struct _DXGK_PRESENTATIONCAPS
{
    union
    {
        struct
        {
            UINT    NoScreenToScreenBlt : 1;
            UINT    NoOverlapScreenBlt  : 1;
            UINT    Reserved            : 30;
        };
        UINT        Value;
    };
} DXGK_PRESENTATIONCAPS;

typedef struct _DXGK_FLIPCAPS
{
    union
    {
        struct
        {
            UINT    FlipOnVSyncWithNoWait : 1; // Support Flip on vsync via command buffer without wait.
            UINT    FlipOnVSyncMmIo       : 1; // Support Flip as mmio at vsync interrupt.
            UINT    FlipInterval          : 1; // Support FLIPINTERVAL_TWO, _THREE, _FOUR.
            UINT    FlipImmediateMmIo     : 1; // Support Flip as mmio immediate. 
            UINT    Reserved              :28;
        };
        UINT        Value;
    };
} DXGK_FLIPCAPS;

typedef struct _DXGK_VIDSCHCAPS
{
    union
    {
        struct
        {
            UINT    MultiEngineAware       :1;
            UINT    VSyncPowerSaveAware    :1;
            UINT    Reserved               :30;
        };
        UINT        Value;
    };
} DXGK_VIDSCHCAPS;

typedef struct _DXGK_VIDMMCAPS
{
    union
    {
        struct
        {
            UINT    OutOfOrderLock        : 1;
            UINT    Reserved              :31;
        };
        UINT        Value;
    };
    UINT            PagingNode;
} DXGK_VIDMMCAPS;

#define DXGK_MAX_ASYMETRICAL_PROCESSING_NODES  64
typedef struct _DXGK_GPUENGINETOPOLOGY
{
    UINT NbAsymetricProcessingNodes;
    UINT Reserved[DXGK_MAX_ASYMETRICAL_PROCESSING_NODES];
} DXGK_GPUENGINETOPOLOGY;

typedef struct _DXGK_DRIVERCAPS
{
    PHYSICAL_ADDRESS        HighestAcceptableAddress;
    UINT                    MaxAllocationListSlotId;
    SIZE_T                  ApertureSegmentCommitLimit;
    UINT                    MaxPointerWidth;
    UINT                    MaxPointerHeight;
    DXGK_POINTERFLAGS       PointerCaps;
    UINT                    InterruptMessageNumber;
    UINT                    NumberOfSwizzlingRanges;
    UINT                    MaxOverlays;
    DXGK_GAMMARAMPCAPS      GammaRampCaps;
    DXGK_PRESENTATIONCAPS   PresentationCaps;
    UINT                    MaxQueuedFlipOnVSync;
    DXGK_FLIPCAPS           FlipCaps;
    DXGK_VIDSCHCAPS         SchedulingCaps;
    DXGK_VIDMMCAPS          MemoryManagementCaps;
    DXGK_GPUENGINETOPOLOGY  GpuEngineTopology;
} DXGK_DRIVERCAPS;

// Segment Caps
typedef struct _DXGK_SEGMENTFLAGS
{
    union
    {
        struct
        {
            UINT    Aperture                    : 1;    // 0x00000001
            UINT    Agp                         : 1;    // 0x00000002
            UINT    CpuVisible                  : 1;    // 0x00000004
            UINT    UseBanking                  : 1;    // 0x00000008
            UINT    CacheCoherent               : 1;    // 0x00000010
            UINT    PitchAlignment              : 1;    // 0x00000020
            UINT    PopulatedFromSystemMemory   : 1;    // 0x00000040
            UINT    Reserved                    :25;    // 0xFFFFFF80
        };
        UINT        Value;
    };
} DXGK_SEGMENTFLAGS;

typedef struct _DXGK_SEGMENTDESCRIPTOR
{
    PHYSICAL_ADDRESS        BaseAddress;            // GPU logical base address for
                                                    // the segment.
    PHYSICAL_ADDRESS        CpuTranslatedAddress;   // CPU translated base address
                                                    // for the segment if CPU visible.
    SIZE_T                  Size;                   // Size of the segment.
    UINT                    NbOfBanks;              // Number of bank in the segment.
    SIZE_T*                 pBankRangeTable;        // Range delimiting each bank.
    SIZE_T                  CommitLimit;            // Maximum number of bytes that can be
                                                    // commited to this segment, apply to
                                                    // aperture segment only.
    DXGK_SEGMENTFLAGS   Flags;                  // Segment bit field flags
} DXGK_SEGMENTDESCRIPTOR;

typedef struct _DXGK_QUERYSEGMENTIN
{
    PHYSICAL_ADDRESS        AgpApertureBase;        // AGP aperture base address.
    LARGE_INTEGER           AgpApertureSize;        // Size of the available AGP aperture.
    DXGK_SEGMENTFLAGS   AgpFlags;               // Segment bit field flags
} DXGK_QUERYSEGMENTIN;

typedef struct _DXGK_QUERYSEGMENTOUT
{
    UINT                        NbSegment;              // Number of segment described.
    DXGK_SEGMENTDESCRIPTOR* pSegmentDescriptor;     // Buffer describing the segment.
    UINT                        PagingBufferSegmentId;  // SegmentId the paging buffer
                                                        // should be allocated from.
    UINT                        PagingBufferSize;       // Paging buffer size.
    UINT                        PagingBufferPrivateDataSize;
} DXGK_QUERYSEGMENTOUT;

typedef struct _DXGKARG_QUERYADAPTERINFO
{
    DXGK_QUERYADAPTERINFOTYPE   Type;
    VOID*                           pInputData;
    UINT                            InputDataSize;
    VOID*                           pOutputData;
    UINT                            OutputDataSize;
} DXGKARG_QUERYADAPTERINFO;

typedef __inout CONST DXGKARG_QUERYADAPTERINFO*   INOUT_CONST_PDXGKARG_QUERYADAPTERINFO;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_QUERYADAPTERINFO(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_CONST_PDXGKARG_QUERYADAPTERINFO   pQueryAdapterInfo
    );

typedef struct _DXGKARG_ACQUIRESWIZZLINGRANGE
{
    HANDLE              hAllocation;
    UINT                PrivateDriverData;  // in: Passed in when UMD calls LockCB
    UINT                RangeId;
    UINT                SegmentId;
    SIZE_T              RangeSize;
    PHYSICAL_ADDRESS    CPUTranslatedAddress;
} DXGKARG_ACQUIRESWIZZLINGRANGE;

typedef __inout DXGKARG_ACQUIRESWIZZLINGRANGE*      INOUT_PDXGKARG_ACQUIRESWIZZLINGRANGE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_ACQUIRESWIZZLINGRANGE(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_PDXGKARG_ACQUIRESWIZZLINGRANGE    pAcquireSwizzlingRange
    );

typedef struct _DXGKARG_RELEASESWIZZLINGRANGE
{
    HANDLE              hAllocation;
    UINT                PrivateDriverData;
    UINT                RangeId;
} DXGKARG_RELEASESWIZZLINGRANGE;

typedef __in CONST DXGKARG_RELEASESWIZZLINGRANGE*   IN_CONST_PDXGKARG_RELEASESWIZZLINGRANGE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_RELEASESWIZZLINGRANGE(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_RELEASESWIZZLINGRANGE     pReleaseSwizzlingRange
    );

typedef struct _DXGK_ALLOCATIONINFOFLAGS
{
    union
    {
        struct
        {
            UINT    CpuVisible              : 1;    // 0x00000001
            UINT    PermanentSysMem         : 1;    // 0x00000002
            UINT    Cached                  : 1;    // 0x00000004
            UINT    Protected               : 1;    // 0x00000008
            UINT    ExistingSysMem          : 1;    // 0x00000010
            UINT    ExistingKernelSysMem    : 1;    // 0x00000020
            UINT    FromEndOfSegment        : 1;    // 0x00000040
            UINT    Swizzled                : 1;    // 0x00000080
            UINT    Overlay                 : 1;    // 0x00000100
            UINT    Capture                 : 1;    // 0x00000200
            UINT    UseAlternateVA          : 1;    // 0x00000400
            UINT    SynchronousPaging       : 1;    // 0x00000800
            UINT    LinkMirrored            : 1;    // 0x00001000
            UINT    LinkInstanced           : 1;    // 0x00002000
            UINT    Reserved                :13;    // 0x07FFC000 Following fields are RESERVED and
        };
        UINT Value;
    };
} DXGK_ALLOCATIONINFOFLAGS;

typedef struct _DXGK_ALLOCATIONUSAGEINFO1
{
    union
    {
        struct
        {
            UINT        PrivateFormat  : 1;     // 0x00000001 - Allocation is a private IHV format. Default is standard format.
            UINT        Swizzled       : 1;     // 0x00000002 - Allocation is swizzled/tiled.
            UINT        MipMap         : 1;     // 0x00000004 - Allocation is a mip mapped texture.
            UINT        Cube           : 1;     // 0x00000008 - Allocation is a cube texture.
            UINT        Volume         : 1;     // 0x00000010 - Allocation is a volume texture.
            UINT        Vertex         : 1;     // 0x00000020 - Allocation is a vertex buffer.
            UINT        Index          : 1;     // 0x00000040 - Allocation is an index buffer.
            UINT        Reserved       : 25;    // 0xFFFFFF80 - Reserved must be set to zero.
        };
        UINT            Value;
    } Flags;

    union
    {
        D3DDDIFORMAT    Format;                 // Allocation format (Flags.PrivateFormat==0)
        UINT            PrivateFormat;          // Allocation format (Flags.PrivateFormat==1)
    };

    UINT                SwizzledFormat;         // Swizzled format for the allocation (IHV private).
    UINT                ByteOffset;             // Offset within the VidMm allocation to the start of this allocation.
    UINT                Width;                  // Width (in pixel) of the allocation.
    UINT                Height;                 // Height (in line) of the allocation.
    UINT                Pitch;                  // Pitch (in bytes) of the allocation.
    UINT                Depth;                  // Depth (in level) of the allocation (mipmap/volume only).
    UINT                SlicePitch;             // Pitch from one level to another (cube/volume only).
} DXGK_ALLOCATIONUSAGEINFO1;

typedef struct _DXGK_ALLOCATIONUSAGEHINT
{
    UINT                            Version;
    DXGK_ALLOCATIONUSAGEINFO1       v1;
} DXGK_ALLOCATIONUSAGEHINT;

typedef struct _DXGK_ALLOCATIONINFO
{
    VOID*                             pPrivateDriverData;               // in: Private data for each allocation allocated by the user mode driver
    UINT                              PrivateDriverDataSize;            // in: Size of the private data
    UINT                              Alignment;
    SIZE_T                            Size;                             // out: Allocation size
    SIZE_T                            PitchAlignedSize;                 // out: Allocation pitch aligned size (for aperture segment requiring Pitch alignment only).
    DXGK_SEGMENTBANKPREFERENCE        HintedBank;
    DXGK_SEGMENTPREFERENCE            PreferredSegment;
    UINT                              SupportedReadSegmentSet;
    UINT                              SupportedWriteSegmentSet;
    UINT                              EvictionSegmentSet;
    UINT                              MaximumRenamingListLength;
    HANDLE                            hAllocation;                      // out: Private driver data for allocation
    DXGK_ALLOCATIONINFOFLAGS          Flags;                            // out: Except the reserved fields
    DXGK_ALLOCATIONUSAGEHINT*         pAllocationUsageHint;
    UINT                              AllocationPriority;               // out: Starting allocation priority.
} DXGK_ALLOCATIONINFO;

typedef struct _DXGK_CREATEALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT                Resource    : 1;    // 0x00000001
            UINT                Reserved    :31;    // 0xFFFFFFFE
        };
        UINT                    Value;
    };
} DXGK_CREATEALLOCATIONFLAGS;

typedef struct _DXGKARG_CREATEALLOCATION
{
    CONST VOID*                 pPrivateDriverData;
    UINT                        PrivateDriverDataSize;
    UINT                        NumAllocations;
    DXGK_ALLOCATIONINFO*    pAllocationInfo;
    HANDLE                      hResource;
    DXGK_CREATEALLOCATIONFLAGS  Flags;
} DXGKARG_CREATEALLOCATION;

typedef __inout DXGKARG_CREATEALLOCATION*     INOUT_PDXGKARG_CREATEALLOCATION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CREATEALLOCATION(
    IN_CONST_HANDLE                     hAdapter,
    INOUT_PDXGKARG_CREATEALLOCATION     pCreateAllocation
    );

typedef struct _DXGKARG_DESCRIBEALLOCATION
{
    HANDLE                          hAllocation;                    //in: Driver returned handle in DXGK_ALLOCATIONINFO upon CreateAllocation
    UINT                            Width;                          //out:Width of specified allocation
    UINT                            Height;                         //out:Height of specified allocation
    D3DDDIFORMAT                    Format;                         //out:Format of specified allocation
    D3DDDI_MULTISAMPLINGMETHOD      MultisampleMethod;              //out:Multisample method used of specified allocation
    D3DDDI_RATIONAL                 RefreshRate;                    //out:RefreshRate the primary surface created with if applicable
    UINT                            PrivateDriverFormatAttribute;   //out:Private format attribute of specified allocation
} DXGKARG_DESCRIBEALLOCATION;

typedef __inout DXGKARG_DESCRIBEALLOCATION*     INOUT_PDXGKARG_DESCRIBEALLOCATION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_DESCRIBEALLOCATION(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_PDXGKARG_DESCRIBEALLOCATION       pDescribeAllocation
    );

typedef struct _DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA
{
    D3DKMDT_STANDARDALLOCATION_TYPE         StandardAllocationType;     // in : Type of standard allocation to describe
    union
    {
        D3DKMDT_SHAREDPRIMARYSURFACEDATA*   pCreateSharedPrimarySurfaceData;
        D3DKMDT_SHADOWSURFACEDATA*          pCreateShadowSurfaceData;
        D3DKMDT_STAGINGSURFACEDATA*         pCreateStagingSurfaceData;
    };
    VOID*                                   pAllocationPrivateDriverData;       // in/out : If non-NULL ptr to buffer driver should place the PrivateDriverData that describes the allocation associated with this standard allocation
    UINT                                    AllocationPrivateDriverDataSize;    // out : Size of buffer required to hold the PrivateDriverData that describes the allocation for this standard allocation
    VOID*                                   pResourcePrivateDriverData;         // in/out : If non-NULL ptr to buffer driver should place the PrivateDriverData that describes the resource associated with this standard allocation
    UINT                                    ResourcePrivateDriverDataSize;      // out : Size of buffer required to hold the PrivateDriverData that describes the resource for this standard allocation
} DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA;

typedef __inout DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA*    INOUT_PDXGKARG_GETSTANDARDALLOCATIONDRIVERDATA;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA(
    IN_CONST_HANDLE                                 hAdapter,
    INOUT_PDXGKARG_GETSTANDARDALLOCATIONDRIVERDATA  pGetStandardAllocationDriverData
    );

typedef struct _DXGK_DESTROYALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT    DestroyResource : 1;    // 0x00000001
            UINT    Reserved        :31;    // 0xFFFFFFFE
        };
        UINT        Value;
    };
} DXGK_DESTROYALLOCATIONFLAGS;

typedef struct _DXGKARG_DESTROYALLOCATION
{
    UINT            NumAllocations;
    CONST HANDLE*   pAllocationList;
    HANDLE          hResource;
    DXGK_DESTROYALLOCATIONFLAGS Flags;
} DXGKARG_DESTROYALLOCATION;

typedef __in CONST DXGKARG_DESTROYALLOCATION*   IN_CONST_PDXGKARG_DESTROYALLOCATION;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_DESTROYALLOCATION(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_DESTROYALLOCATION     pDestroyAllocation
    );

typedef struct _DXGK_PATCHFLAGS
{
    union
    {
        struct
        {
            UINT                    Paging              : 1;            // 0x00000001 command buffer is a paging buffer.
            UINT                    Present             : 1;            // 0x00000002 command buffer contain a present operation.
            UINT                    RedirectedPresent   : 1;            // 0x00000004 command buffer contains a redirected present operation.
            UINT                    NullRendering       : 1;            // 0x00000008 GPU should skip rendering of DMA buffer (perf analysis)
            UINT                    Reserved            :28;            // 0xFFFFFFF0
        };
        UINT                        Value;
    };
} DXGK_PATCHFLAGS;

typedef struct _DXGKARG_PATCH
{
    union
    {
        HANDLE                          hDevice;                                // in: driver device handle for driver not MultiEngineAware.
        HANDLE                          hContext;                               // in: driver context handle for MultiEngineAware driver.
    };
    UINT                            DmaBufferSegmentId;                         // in: segment id of DMA buffer
    PHYSICAL_ADDRESS                DmaBufferPhysicalAddress;                   // in: physical address of DMA buffer
    VOID*                           pDmaBuffer;                                 // in: Virtual address to beginning of
                                                                                //     the DMA buffer.
    UINT                            DmaBufferSize;                              // in: lenght of the DMA buffer..
    UINT                            DmaBufferSubmissionStartOffset;             // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the start
                                                                                //     of this submission.
    UINT                            DmaBufferSubmissionEndOffset;               // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the end of
                                                                                //     this submission.
    VOID*                           pDmaBufferPrivateData;                      // in: Virtual address to the private
                                                                                //     data associated with this DMA buffer.
    UINT                            DmaBufferPrivateDataSize;                   // in: Size of the private data.
    UINT                            DmaBufferPrivateDataSubmissionStartOffset;  // in: Byte offset from the beginning of the
                                                                                //     private data to the start of this
                                                                                //     submission.
    UINT                            DmaBufferPrivateDataSubmissionEndOffset;    // in: Byte offset from the beginning of the
                                                                                //     private data to the end of this
                                                                                //     submission.
    CONST DXGK_ALLOCATIONLIST*      pAllocationList;                            // in: Pointer to the allocation list
                                                                                //     associated with this DMA buffer.
    UINT                            AllocationListSize;                         // in: Size of the allocation list.
    CONST D3DDDI_PATCHLOCATIONLIST* pPatchLocationList;                         // in: Pointer to the patch location list associated
                                                                                //     with this DMA buffer.
    UINT                            PatchLocationListSize;                      // in: Size of the patch location list.
    UINT                            PatchLocationListSubmissionStart;           // in: First element for this submission.
    UINT                            PatchLocationListSubmissionLength;          // in: Number of element in this submission.
    UINT                            SubmissionFenceId;                          // in: Submission fence id.
    DXGK_PATCHFLAGS                 Flags;                                      // in: Flags
    UINT                            EngineOrdinal;                              // in: Engine Ordinal within it's node.
} DXGKARG_PATCH;

typedef __in CONST DXGKARG_PATCH*   IN_CONST_PDXGKARG_PATCH;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_PATCH(
    IN_CONST_HANDLE             hAdapter,
    IN_CONST_PDXGKARG_PATCH     pPatch
    );

typedef struct _DXGK_SUBMITCOMMANDFLAGS
{
    union
    {
        struct
        {
            UINT        Paging              : 1;    // command buffer is a paging buffer.
            UINT        Present             : 1;    // command buffer contain a present operation.
            UINT        RedirectedPresent   : 1;    // command buffer contains a redirected present operation.
            UINT        NullRendering       : 1;    // GPU should skip rendering of DMA buffer (perf analysis)
            UINT        Flip                : 1;    // command buffer is for flip.
            UINT        FlipWithNoWait      : 1;    // command buffer is for flip with no built-in-wait for next vsync.
            UINT        Reserved            :26;
        };
        UINT            Value;
    };
} DXGK_SUBMITCOMMANDFLAGS;

// Definition for DXGKARG_SUBMITCOMMAND
//
typedef struct _DXGKARG_SUBMITCOMMAND
{
    union
    {
        HANDLE          hDevice;                                    // in: driver device handle for driver not MultiEngineAware.
        HANDLE          hContext;                                   // in: driver context handle for MultiEngineAware driver.
    };
    UINT                DmaBufferSegmentId;                         // in: segment id of DMA buffer
    PHYSICAL_ADDRESS    DmaBufferPhysicalAddress;                   // in: physical address of DMA buffer
    UINT                DmaBufferSize;                              // in: lenght of the DMA buffer..
    UINT                DmaBufferSubmissionStartOffset;             // in: Byte offset from the beginning
                                                                    //     of the DMA buffer to the start
                                                                    //     of this submission.
    UINT                DmaBufferSubmissionEndOffset;               // in: Byte offset from the beginning
                                                                    //     of the DMA buffer to the end of
                                                                    //     this submission.
    VOID*               pDmaBufferPrivateData;                      // in: Virtual address to the private
                                                                    //     data associated with this DMA buffer.
    UINT                DmaBufferPrivateDataSize;                   // in: Size of the private data.
    UINT                DmaBufferPrivateDataSubmissionStartOffset;  // in: Byte offset from the beginning of the
                                                                    //     private data to the start of this
                                                                    //     submission.
    UINT                DmaBufferPrivateDataSubmissionEndOffset;    // in: Byte offset from the beginning of the
                                                                    //     private data to the end of this
                                                                    //     submission.
    UINT                SubmissionFenceId;                          // in: Submission fence id.
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;                   // in: VidPnSourceId (flip only)
    D3DDDI_FLIPINTERVAL_TYPE       FlipInterval;                    // in: Flip Interval (flip only)
    DXGK_SUBMITCOMMANDFLAGS Flags;                                  // in: Flags
    UINT                EngineOrdinal;                              // in: Engine Ordinal within it's node.
} DXGKARG_SUBMITCOMMAND;

// Device Driver Interface to submit command buffer to h/w command execution unit.
//
typedef __in CONST DXGKARG_SUBMITCOMMAND*   IN_CONST_PDXGKARG_SUBMITCOMMAND;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SUBMITCOMMAND(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_SUBMITCOMMAND     pSubmitCommand
    );

typedef struct _DXGK_PREEMPTCOMMANDFLAGS
{
    union
    {
        struct
        {
            UINT        Reserved    :32;    // 0xFFFFFFFF
        };
        UINT            Value;
    };
} DXGK_PREEMPTCOMMANDFLAGS;

// Definition for DXGKARG_PREEMPTCOMMAND
//
typedef struct _DXGKARG_PREEMPTCOMMAND
{
    UINT                PreemptionFenceId;  // in: preemption uniqueness id
    UINT                NodeOrdinal;        // in: node ordinal to preempt
    UINT                EngineOrdinal;      // in: engine ordinal to preempt
    DXGK_PREEMPTCOMMANDFLAGS Flags;         // in: flags
} DXGKARG_PREEMPTCOMMAND;

// Device Driver Interface to preempt command.
//
typedef __in CONST DXGKARG_PREEMPTCOMMAND*      IN_CONST_PDXGKARG_PREEMPTCOMMAND;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_PREEMPTCOMMAND(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_PREEMPTCOMMAND    pPreemptCommand
    );

// Definition for DXGKARG_QUERYCURRENTFENCE
//
typedef struct _DXGKARG_QUERYCURRENTFENCE
{
    UINT     CurrentFence;
    UINT     NodeOrdinal;
    UINT     EngineOrdinal;
} DXGKARG_QUERYCURRENTFENCE;

// Device Driver Interface to query completed submission fence.
//
typedef __inout DXGKARG_QUERYCURRENTFENCE* INOUT_PDXGKARG_QUERYCURRENTFENCE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_QUERYCURRENTFENCE(
    IN_CONST_HANDLE                    hAdapter,
    INOUT_PDXGKARG_QUERYCURRENTFENCE   pCurrentFence
    );

// Device Driver Interface to control vertical sync interrupt.
//
typedef __in CONST DXGK_INTERRUPT_TYPE      IN_CONST_DXGK_INTERRUPT_TYPE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CONTROLINTERRUPT(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_DXGK_INTERRUPT_TYPE    InterruptType,
    IN_BOOLEAN                      EnableInterrupt
    );

typedef enum _DXGK_BUILDPAGINGBUFFER_OPERATION
{
    DXGK_OPERATION_TRANSFER                 = 0,
    DXGK_OPERATION_FILL                     = 1,
    DXGK_OPERATION_DISCARD_CONTENT          = 2,
    DXGK_OPERATION_READ_PHYSICAL            = 3,
    DXGK_OPERATION_WRITE_PHYSICAL           = 4,
    DXGK_OPERATION_MAP_APERTURE_SEGMENT     = 5,
    DXGK_OPERATION_UNMAP_APERTURE_SEGMENT   = 6,
    DXGK_OPERATION_SPECIAL_LOCK_TRANSFER    = 7
} DXGK_BUILDPAGINGBUFFER_OPERATION;

typedef struct _DXGK_TRANSFERFLAGS
{
    union
    {
        struct
        {
            UINT    Swizzle             : 1;    // 0x00000001
            UINT    Unswizzle           : 1;    // 0x00000002
            UINT    AllocationIsIdle    : 1;    // 0x00000004
            UINT    TransferStart       : 1;    // 0x00000010
            UINT    TransferEnd         : 1;    //
            UINT    Reserved            :27;    // 0xFFFFFFF8
        };
        UINT        Value;
    };
} DXGK_TRANSFERFLAGS;

typedef struct _DXGK_DISCARDCONTENTFLAGS
{
    union
    {
        struct
        {
            UINT    AllocationIsIdle    : 1;    // 0x00000001
            UINT    Reserved            :31;    // 0xFFFFFFFE
        };
        UINT        Value;
    };
} DXGK_DISCARDCONTENTFLAGS;

typedef struct _DXGK_MAPAPERTUREFLAGS
{
    union
    {
        struct
        {
            UINT    CacheCoherent   : 1;    // 0x00000001
            UINT    Reserved        :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_MAPAPERTUREFLAGS;

typedef struct _DXGKARG_BUILDPAGINGBUFFER
{
    VOID*                                   pDmaBuffer;
    UINT                                    DmaSize;
    VOID*                                   pDmaBufferPrivateData;
    UINT                                    DmaBufferPrivateDataSize;
    DXGK_BUILDPAGINGBUFFER_OPERATION        Operation;
    UINT                                    MultipassOffset;
    union
    {
        struct
        {
            HANDLE  hAllocation;
            UINT    TransferOffset;
            SIZE_T  TransferSize;
            struct
            {
                UINT    SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Source;
            struct
            {
                UINT    SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Destination;
            DXGK_TRANSFERFLAGS  Flags;
            UINT MdlOffset;
        } Transfer;

        struct
        {
            HANDLE  hAllocation;
            SIZE_T  FillSize;
            UINT    FillPattern;
            struct
            {
                UINT SegmentId;
                LARGE_INTEGER SegmentAddress;
            } Destination;
        } Fill;

        struct
        {
            HANDLE hAllocation;
            DXGK_DISCARDCONTENTFLAGS Flags;
            UINT SegmentId;
            PHYSICAL_ADDRESS SegmentAddress;
        } DiscardContent;

        struct
        {
            UINT SegmentId;
            PHYSICAL_ADDRESS PhysicalAddress;
        } ReadPhysical;

        struct
        {
            UINT SegmentId;
            PHYSICAL_ADDRESS PhysicalAddress;
        } WritePhysical;

        struct
        {
            HANDLE  hDevice;
            HANDLE  hAllocation;
            UINT    SegmentId;
            SIZE_T  OffsetInPages;
            SIZE_T  NumberOfPages;
            PMDL    pMdl;
            DXGK_MAPAPERTUREFLAGS Flags;
            ULONG   MdlOffset;
        } MapApertureSegment;

        struct
        {
            HANDLE  hDevice;
            HANDLE  hAllocation;
            UINT    SegmentId;
            SIZE_T  OffsetInPages;
            SIZE_T  NumberOfPages;
            PHYSICAL_ADDRESS DummyPage;
        } UnmapApertureSegment;

        struct
        {
            HANDLE hAllocation;
            UINT   TransferOffset;
            SIZE_T TransferSize;
            struct
            {
                UINT SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Source;
            struct
            {
                UINT SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Destination;
            DXGK_TRANSFERFLAGS  Flags;
            UINT SwizzlingRangeId;
            UINT SwizzlingRangeData;
        } SpecialLockTransfer;

        struct
        {
            UINT    Reserved[64];
        } Reserved;
    };
    HANDLE hSystemContext;
} DXGKARG_BUILDPAGINGBUFFER;

// Device Driver Interface to build a paging buffer.
//
typedef __in DXGKARG_BUILDPAGINGBUFFER*     IN_PDXGKARG_BUILDPAGINGBUFFER;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_BUILDPAGINGBUFFER(
    IN_CONST_HANDLE                 hAdapter,
    IN_PDXGKARG_BUILDPAGINGBUFFER   pBuildPagingBuffer
    );

// DXGK_TRANSFERFLAGS.Swizzle
//
//   This indicates that the source should be swizzled to the destination.
//
// DXGK_TRANSFERFLAGS.Unswizzle
//
//   This indicates that the source should be unswizzled to the destination.
//
// DXGK_TRANSFERFLAGS.AllocationIsIdle
//
//   This indicates that the given allocation is idle, i.e. no work
//   has been queued or will be queued to the GPU referencing this
//   allocation until the call to DdiBuildPagingBuffer returns.
//
// DXGK_TRANSFERFLAGS.FillDestination
//
//   This indicates that the driver should fill the destination
//   with the provided pattern. No source is provided.
//

typedef struct _DXGKARG_ESCAPE
{
    HANDLE             hDevice;                // in: driver device handle
    D3DDDI_ESCAPEFLAGS Flags;                  // in: flags
    VOID*              pPrivateDriverData;     // in/out: escape data
    UINT               PrivateDriverDataSize;  // in: size of escape data
    HANDLE             hContext;               // in: driver context handle
} DXGKARG_ESCAPE;

typedef __inout CONST DXGKARG_ESCAPE*   INOUT_CONST_PDXGKARG_ESCAPE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_ESCAPE(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_CONST_PDXGKARG_ESCAPE     pEscape
    );

#define DXGK_SECONDARY_BUCKETING_TAG ((DWORD)'bSsM')

typedef struct _DXGKARG_COLLECTDBGINFO_EXT
{
    UINT BucketingKey;           // out: Key for IHV specific secondary OCA bucketing
    UINT CurrentDmaBufferOffset; // out: execution offset in the current DMA buffer
    UINT Reserved2;
    UINT Reserved3;
    UINT Reserved4;
    UINT Reserved5;
    UINT Reserved6;
    UINT Reserved7;
} DXGKARG_COLLECTDBGINFO_EXT;

typedef struct _DXGKARG_COLLECTDBGINFO
{
    UINT    Reason;                         // in:  bugcheck code for debug report
    VOID*   pBuffer;                        // out: pointer to the buffer to save the info
    SIZE_T  BufferSize;                     // in:  maximum size of the buffer in bytes
    DXGKARG_COLLECTDBGINFO_EXT* pExtension; // out: optional extension
} DXGKARG_COLLECTDBGINFO;

typedef __inout CONST DXGKARG_COLLECTDBGINFO*   INOUT_CONST_PDXGKARG_COLLECTDBGINFO;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_COLLECTDBGINFO(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_CONST_PDXGKARG_COLLECTDBGINFO     pCollectDbgInfo
    );

typedef struct _DXGK_OVERLAYINFO
{
    HANDLE                 hAllocation;           // in: Allocation to be displayed
    PHYSICAL_ADDRESS       PhysicalAddress;       // in: Physical address of allocation
    UINT                   SegmentId;             // in: Segment ID of allocation
    RECT                   DstRect;               // in: Source rect
    RECT                   SrcRect;               // in: Dest rect
    VOID*                  pPrivateDriverData;    // in: Private driver data
    UINT                   PrivateDriverDataSize; // in: Size of private driver data
} DXGK_OVERLAYINFO;

typedef struct _DXGKARG_CREATEOVERLAY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in:  VidPn where overlay is displayed
    DXGK_OVERLAYINFO               OverlayInfo;   // in:  Overlay info
    HANDLE                         hOverlay;      // out: Driver handle
} DXGKARG_CREATEOVERLAY;

typedef __inout DXGKARG_CREATEOVERLAY*      INOUT_PDXGKARG_CREATEOVERLAY;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_CREATEOVERLAY(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_PDXGKARG_CREATEOVERLAY    pCreateOverlay
    );

typedef struct _DXGKARG_UPDATEOVERLAY
{
    DXGK_OVERLAYINFO       OverlayInfo;            // in: Overlay info
} DXGKARG_UPDATEOVERLAY;

typedef __in CONST DXGKARG_UPDATEOVERLAY*   IN_CONST_PDXGKARG_UPDATEOVERLAY;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_UPDATEOVERLAY(
    IN_CONST_HANDLE                     hOverlay,
    IN_CONST_PDXGKARG_UPDATEOVERLAY     pUpdateOverlay
    );

typedef struct _DXGKARG_FLIPOVERLAY
{
    HANDLE                 hSource;                // in: Source allocation
    PHYSICAL_ADDRESS       SrcPhysicalAddress;     // in: Physical address of source allocation
    UINT                   SrcSegmentId;           // in: Segment ID of source allocation
    VOID*                  pPrivateDriverData;     // in: Private driver data
    UINT                   PrivateDriverDataSize;  // in: Size of private driver data
} DXGKARG_FLIPOVERLAY;

typedef __in CONST DXGKARG_FLIPOVERLAY*     IN_CONST_PDXGKARG_FLIPOVERLAY;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_FLIPOVERLAY(
    IN_CONST_HANDLE                 hOverlay,
    IN_CONST_PDXGKARG_FLIPOVERLAY   pFlipOverlay
    );

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_DESTROYOVERLAY(
    IN_CONST_HANDLE     hOverlay
    );

typedef struct _DXGKARG_GETSCANLINE
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId;      // in: adapter's VidPN Target ID
    BOOLEAN                         InVerticalBlank;    // out: Within vertical blank
    UINT                            ScanLine;           // out: Current scan line
} DXGKARG_GETSCANLINE;

typedef __inout DXGKARG_GETSCANLINE*    INOUT_PDXGKARG_GETSCANLINE;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_GETSCANLINE(
    IN_CONST_HANDLE             hAdapter,
    INOUT_PDXGKARG_GETSCANLINE  pGetScanLine
    );

///////////////////////// LDDM display miniport VidPN management DDI /////////////////////////////


/*++
Routine Description:
    IsSupportedVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                - LDDM display miniport adapter handle.

    pIsSupportedVidPnArg
       ->pDesiredVidPn      - VidPN whose support with respect to display adapter's capabilities
                              is in question.

       ->bIsVidPnSupported - Placeholder for the predicate specifying whether the specified VidPN
                             is supported by the specified display adapter.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
    Predicate specifying whether the provided VidPN configuration is supported (i.e. can be extended
    to a functional VidPN).

Assumptions:
    Specified VidPN must at a minimum specify a valid topology, but can also have some or all
    of its targets/sources configured with respectively pinned modes.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_ISSUPPORTEDVIDPN
{
    IN   D3DKMDT_HVIDPN                       hDesiredVidPn;
    OUT  BOOLEAN                              IsVidPnSupported;
} DXGKARG_ISSUPPORTEDVIDPN;

typedef __inout DXGKARG_ISSUPPORTEDVIDPN*     INOUT_PDXGKARG_ISSUPPORTEDVIDPN;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_ISSUPPORTEDVIDPN(
    IN_CONST_HANDLE                     hAdapter,
    INOUT_PDXGKARG_ISSUPPORTEDVIDPN     pIsSupportedVidPn
    );


/*++
Routine Description:
    EnumVidPnCofuncModality LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                - LDDM display miniport adapter handle.

    hConstrainingVidPn      - VidPN whose cofunctional mode sets are to be (re)enumerated
                              with respect to its topology and pinned modes (if any).

    EnumPivotType           - Specifies what is the type of the mode enumeration pivot (if any).
                              No pivot is specified using D3DKMDT_EPT_NOPIVOT.

    EnumPivot.VidPnSourceId - If (EnumPivotType == D3DKMDT_EPT_VIDPNSOURCE), specifies the ID
                              of the VidPN source whose mode set must not be changed during the enumeration.
                              If EnumPivotType is D3DKMDT_EPT_SCALING or D3DKMDT_EPT_ROTATION,
                              the VidPnSourceId and VidPnTargetId specifies the path whose scaling or rotation support does
                              not need to be updated.
                              Undefined otherwise.

    EnumPivot.VidPnSourceId - If (EnumPivotType == D3DKMDT_EPT_VIDPNTARGET), specifies the ID
                              of the VidPN source whose mode set must not be changed during the enumeration.
                              If EnumPivotType is D3DKMDT_EPT_SCALING or D3DKMDT_EPT_ROTATION,
                              the VidPnSourceId and VidPnTargetId specifies the path whose scaling or rotation support does
                              not need to be updated.
                              Undefined otherwise.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
   Enumerates cofunctional video present source and target mode sets on each video present path
   in the specified VidPN's topology.

Assumptions:
    Specified VidPN's support has been confirmed via IsSupportedVidPn call by the OS.
    Miniport can assume it reported that it supports this VidPN.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGK_ENUM_PIVOT
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId;
} DXGK_ENUM_PIVOT;


typedef struct _DXGKARG_ENUMVIDPNCOFUNCMODALITY
{
    IN  D3DKMDT_HVIDPN                         hConstrainingVidPn;
    IN  D3DKMDT_ENUMCOFUNCMODALITY_PIVOT_TYPE  EnumPivotType;
    IN  DXGK_ENUM_PIVOT                        EnumPivot;
} DXGKARG_ENUMVIDPNCOFUNCMODALITY;

typedef __in CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST       IN_CONST_PDXGKARG_ENUMVIDPNCOFUNCMODALITY_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_ENUMVIDPNCOFUNCMODALITY(
    IN_CONST_HANDLE                                     hAdapter,
    IN_CONST_PDXGKARG_ENUMVIDPNCOFUNCMODALITY_CONST     pEnumCofuncModality
    );


/*++
Routine Description:
    RecommendFunctionalVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter
      - LDDM display miniport adapter handle.

    pRecommendFunctionalVidPnArg

       ->NumberOfVidPnTargets
           - Number of VidPN target IDs listed in pVidPnTargetPrioritizationVector.

       ->pVidPnTargetPrioritizationVector
           - Vector of VidPN targets IDs, ordered most important first, representing the
             importance of monitors connected to them.

       ->hRecommendedFunctionalVidPn
           - Handle of an empty VidPN object to be populated by miniport with the
             functional VidPN recommended for the current state of display adapter.

       ->RequestReason
           - Type of reason behind OS'es request of a new functional VidPN.
             Note that hotkey, power, and thermal events are mapped directly from the
             respective invalidation reasons specified via
             DXGK_INTERFACESPECIFICDATA::pfnInvalidateActiveVidPn.

       ->hContext
           - Optional context originating from the miniport on calls such as
             DXGK_INTERFACESPECIFICDATA::pfnInvalidateActiveVidPn. When miniport needs
             to invalidate an active VidPN, it should pass private context to be received
             via this parameter so it could distinguish between different concurrent requests
             of the same type leading OS to request a new functional VidPN.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN
      - Installed LDDM display adapter miniport has no VidPN recommendation
      for the current configuration of the display adapter.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR}* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
    Obtains a VidPN recommended by the LDDM display miniport, given the current state of the h/w.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef enum _DXGK_RECOMMENDFUNCTIONALVIDPN_REASON
{
    DXGK_RFVR_UNINITIALIZED  = 0,
    DXGK_RFVR_HOTKEY         = 1,
    DXGK_RFVR_USERMODE       = 2,
}
DXGK_RECOMMENDFUNCTIONALVIDPN_REASON;

typedef struct _DXGKARG_RECOMMENDFUNCTIONALVIDPN
{
    IN  UINT                                    NumberOfVidPnTargets;
    IN  CONST D3DDDI_VIDEO_PRESENT_TARGET_ID*   pVidPnTargetPrioritizationVector;
    IN  D3DKMDT_HVIDPN                          hRecommendedFunctionalVidPn;
    IN  DXGK_RECOMMENDFUNCTIONALVIDPN_REASON    RequestReason;
    IN  OPTIONAL VOID*                          pPrivateDriverData;
    IN  UINT                                    PrivateDriverDataSize;
} DXGKARG_RECOMMENDFUNCTIONALVIDPN;

typedef __in CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST      IN_CONST_PDXGKARG_RECOMMENDFUNCTIONALVIDPN_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDFUNCTIONALVIDPN(
    IN_CONST_HANDLE                                     hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDFUNCTIONALVIDPN_CONST    pRecommendFunctionalVidPn
    );

/*++
Routine Description:
    SetVidPnSourceAddress LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter              - LDDM display miniport adapter handle.

    pSetVidPnSourceVisibility
       ->VidPnSourceId    - ID of the VidPN source whose state needs to be changed.

       ->PrimarySegment   - Segment of the primary surface to scan from.

       ->PrimaryAddress   - Address of the primary surface to scan from.

       ->hAllocation      - Driver assigned allocation handle for the primary surface

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

Side-effects:
    On success, adapters starts scanning from the specified primary surface on the specified VidPN source.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGK_SETVIDPNSOURCEADDRESS_FLAGS
{
    union
    {
        struct
        {

            UINT ModeChange      : 1;    // 0x00000001
            UINT FlipImmediate   : 1;    // 0x00000002
            UINT FlipOnNextVSync : 1;    // 0x00000004
            UINT Reserved        :29;    // 0xFFFFFFF8
        };
        UINT Value;
    };
} DXGK_SETVIDPNSOURCEADDRESS_FLAGS;

typedef struct _DXGKARG_SETVIDPNSOURCEADDRESS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID   VidPnSourceId;
    UINT                             PrimarySegment;
    PHYSICAL_ADDRESS                 PrimaryAddress;
    HANDLE                           hAllocation;
    UINT                             ContextCount;
    HANDLE                           Context[1+D3DDDI_MAX_BROADCAST_CONTEXT];
    DXGK_SETVIDPNSOURCEADDRESS_FLAGS Flags;
} DXGKARG_SETVIDPNSOURCEADDRESS;

typedef __in CONST DXGKARG_SETVIDPNSOURCEADDRESS*   IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESS;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEADDRESS(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESS     pSetVidPnSourceAddress
    );

/*++
Routine Description:
    SetVidPnSourceVisibility LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter              - LDDM display miniport adapter handle.

    pSetVidPnSourceVisibility
       ->VidPnSourceId    - ID of the VidPN source whose state needs to be changed.

       ->Visible          - Visible or not for the specified VidPN source.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

Side-effects:
    When Visible == TRUE, tells the miniport to scan out data from the primary surface
    associated with the the specified VidPN source to the VidPN target(s) connected
    to that source by the active VidPN's topology.
    When Visible == FALSE, tells miniport the miniport to stop reading from the primary surface
    associated with the specified VidPN source and present black on all the VidPN targets
    connected to that source via by active VidPN's topology.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGKARG_SETVIDPNSOURCEVISIBILITY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    BOOLEAN                         Visible;
} DXGKARG_SETVIDPNSOURCEVISIBILITY;

typedef __in CONST DXGKARG_SETVIDPNSOURCEVISIBILITY*    IN_CONST_PDXGKARG_SETVIDPNSOURCEVISIBILITY;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEVISIBILITY(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEVISIBILITY  pSetVidPnSourceVisibility
    );

/*++
Routine Description:
    CommitVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                       - LDDM display miniport adapter handle.

    pCommitVidPnArg
       ->hFunctionalVidPn          - Handle of a functional VidPN to commit to h/w.

       ->AffectedVidPnSourceId     - ID of the VidPN source for which the commit should take place.

       ->MonitorConnectivityChecks - Specifies miniport whether to validate specified VidPN's topology
                                     against connected monitors or ignore its monitor connectivity checks.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    Commits the specified functional VidPN to h/w.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_COMMITVIDPN_FLAGS
{
    UINT PathPowerTransition   :  1;
    UINT PathPoweredOff        :  1;
    UINT Reserved              : 30;
} DXGKARG_COMMITVIDPN_FLAGS;

typedef struct _DXGKARG_COMMITVIDPN
{
    IN  D3DKMDT_HVIDPN                      hFunctionalVidPn;
    IN  D3DDDI_VIDEO_PRESENT_SOURCE_ID      AffectedVidPnSourceId;
    IN  D3DKMDT_MONITOR_CONNECTIVITY_CHECKS MonitorConnectivityChecks;
    IN  HANDLE                              hPrimaryAllocation; // Driver assigned primary surface allocation handle.
    IN  DXGKARG_COMMITVIDPN_FLAGS           Flags;
} DXGKARG_COMMITVIDPN;

typedef __in CONST DXGKARG_COMMITVIDPN* CONST       IN_CONST_PDXGKARG_COMMITVIDPN_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_COMMITVIDPN(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_COMMITVIDPN_CONST     pCommitVidPn
    );


/*++
Routine Description:
    UpdateActiveVidPnPresentPath LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                   - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->VidPnPresentPathInfo - VidPN present path information to update the respective
                                present path in the active VidPN with.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    Updates settings on the specified VidPN present path of the active VidPN set on the adapter.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH
{
    IN D3DKMDT_VIDPN_PRESENT_PATH  VidPnPresentPathInfo;
} DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH;

typedef __in CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST      IN_CONST_PDXGKARG_UPDATEACTIVEVIDPNPRESENTPATH_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH(
    IN_CONST_HANDLE                                         hAdapter,
    IN_CONST_PDXGKARG_UPDATEACTIVEVIDPNPRESENTPATH_CONST    pUpdateActiveVidPnPresentPath
    );


/*++
Routine Description:
    RecommendVidPnTopology LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->hVidPn - Handle of the VidPN whose topology is to be augmented with miniport's recommendation.

       ->VidPnSourceId - ID of the VidPN source for which miniport is asked to recommend path(s).

       ->RequestReason - Reason why OS asked for recommendation.

       ->hFallbackVidPn - Handle of the VidPN that OS will use if miniport provides no recommendation.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY
      - Miniport has no recommendation for augmentation of the specified VidPN's topology.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR|* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    On success, topology of the specified VidPN is augmented with miniport's recommendation with path(s)
    originating from the specified source.

Remarks:
    On success, miniport must add at least one path to the specified VidPN's source.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef enum _DXGK_RECOMMENDVIDPNTOPOLOGY_REASON
{
    DXGK_RVT_UNINITIALIZED              = 0,
    DXGK_RVT_INITIALIZATION_NOLKG       = 1,
    DXGK_RVT_AUGMENTATION_NOLKG         = 2,
    DXGK_RVT_AUGMENTATION_LKGOVERRIDE   = 3,
    DXGK_RVT_INITIALIZATION_LKGOVERRIDE = 4,

    // DEPRECATED: To be removed in RC0.
    // NOTE: These are left to avoid forcing IHVs to update their code with the new enum names this late in Beta2.
    DXGK_RVT_INITIALIZATION                       = 1,
    DXGK_RVT_FIRSTAVAILTARGETAUGMENTATIONOVERRIDE = 2,
    DXGK_RVT_LKGTARGETAUGMENTATIONOVERRIDE        = 3,
}
DXGK_RECOMMENDVIDPNTOPOLOGY_REASON;

typedef struct _DXGKARG_RECOMMENDVIDPNTOPOLOGY
{
    IN D3DKMDT_HVIDPN                      hVidPn;
    IN D3DDDI_VIDEO_PRESENT_SOURCE_ID      VidPnSourceId;
    IN DXGK_RECOMMENDVIDPNTOPOLOGY_REASON  RequestReason;
    IN D3DKMDT_HVIDPNTOPOLOGY              hFallbackTopology;
} DXGKARG_RECOMMENDVIDPNTOPOLOGY;

typedef __in CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST    IN_CONST_PDXGKARG_RECOMMENDVIDPNTOPOLOGY_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDVIDPNTOPOLOGY(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDVIDPNTOPOLOGY_CONST  pRecommendVidPnTopology
    );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNTOPOLOGY_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnGetTopology

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHS)
        (CONST D3DKMDT_HVIDPNTOPOLOGY  hVidPnTopology,
         __out SIZE_T*                 pNumPaths);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHSFROMSOURCE)
        (CONST D3DKMDT_HVIDPNTOPOLOGY          hVidPnTopology,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId,
         __out SIZE_T*                         pNumPathsFromSource);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ENUMPATHTARGETSFROMSOURCE)
        (CONST D3DKMDT_HVIDPNTOPOLOGY            hVidPnTopology,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID    VidPnSourceId,
         CONST D3DKMDT_VIDPN_PRESENT_PATH_INDEX  VidPnPresentPathIndex,
         __out D3DDDI_VIDEO_PRESENT_TARGET_ID*   pVidPnTargetId);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETPATHSOURCEFROMTARGET)
        (CONST D3DKMDT_HVIDPNTOPOLOGY           hVidTopology,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID   VidPnTargetId,
         __out D3DDDI_VIDEO_PRESENT_SOURCE_ID*  pVidPnSourceId);

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIREPATHINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID      VidPnSourceId,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID      VidPnTargetId,
         __out CONST D3DKMDT_VIDPN_PRESENT_PATH**  pVidPnPresentPathInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIREFIRSTPATHINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
         __out CONST D3DKMDT_VIDPN_PRESENT_PATH**  ppFirstVidPnPresentPathInfo);


typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIRENEXTPATHINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
         CONST D3DKMDT_VIDPN_PRESENT_PATH* CONST   pVidPnPresentPathInfo,
         __out CONST D3DKMDT_VIDPN_PRESENT_PATH**  ppNextVidPnPresentPathInfo);

// NOTE: This updates what the path supports for transformations.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_UPDATEPATHSUPPORTINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY              i_hVidPnTopology,
         CONST D3DKMDT_VIDPN_PRESENT_PATH*         i_pVidPnPresentPathInfo);

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_RELEASEPATHINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY             hVidPnTopology,
         CONST D3DKMDT_VIDPN_PRESENT_PATH* CONST  pVidPnPresentPathInfo);

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_CREATENEWPATHINFO)
        (CONST D3DKMDT_HVIDPNTOPOLOGY        hVidPnTopology,
         __out D3DKMDT_VIDPN_PRESENT_PATH**  ppNewVidPnPresentPathInfo);

// NOTE: Releases the new path info, rendering it inaccessible.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ADDPATH)
        (D3DKMDT_HVIDPNTOPOLOGY             hVidPnTopology,
         D3DKMDT_VIDPN_PRESENT_PATH* CONST  pVidPnPresentPath);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTOPOLOGY_REMOVEPATH)
        (D3DKMDT_HVIDPNTOPOLOGY                hVidPnTopology,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId);

typedef struct _DXGK_VIDPNTOPOLOGY_INTERFACE
{
    DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHS                pfnGetNumPaths;
    DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHSFROMSOURCE      pfnGetNumPathsFromSource;
    DXGKDDI_VIDPNTOPOLOGY_ENUMPATHTARGETSFROMSOURCE  pfnEnumPathTargetsFromSource;
    DXGKDDI_VIDPNTOPOLOGY_GETPATHSOURCEFROMTARGET    pfnGetPathSourceFromTarget;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIREPATHINFO            pfnAcquirePathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIREFIRSTPATHINFO       pfnAcquireFirstPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIRENEXTPATHINFO        pfnAcquireNextPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_UPDATEPATHSUPPORTINFO      pfnUpdatePathSupportInfo;
    DXGKDDI_VIDPNTOPOLOGY_RELEASEPATHINFO            pfnReleasePathInfo;
    DXGKDDI_VIDPNTOPOLOGY_CREATENEWPATHINFO          pfnCreateNewPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ADDPATH                    pfnAddPath;
    DXGKDDI_VIDPNTOPOLOGY_REMOVEPATH                 pfnRemovePath;
} DXGK_VIDPNTOPOLOGY_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNSOURCEMODESET_INTERFACE (exposed by OS to miniport)
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnAcquireSourceModeSet.

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_GETNUMMODES)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET  hVidPnSourceModeSet,
         __out SIZE_T* CONST                pNumSourceModes);

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIREFIRSTMODEINFO)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET        hVidPnSourceModeSet,
         __out CONST D3DKMDT_VIDPN_SOURCE_MODE**  ppFirstVidPnSourceModeInfo);

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIRENEXTMODEINFO)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET        hVidPnSourceModeSet,
         CONST D3DKMDT_VIDPN_SOURCE_MODE* CONST   pVidPnSourceModeInfo,
         __out CONST D3DKMDT_VIDPN_SOURCE_MODE**  ppNextVidPnSourceModeInfo);

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIREPINNEDMODEINFO)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET        hVidPnSourceModeSet,
         __out CONST D3DKMDT_VIDPN_SOURCE_MODE**  ppPinnedVidPnSourceModeInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_RELEASEMODEINFO)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET       hVidPnSourceModeSet,
         CONST D3DKMDT_VIDPN_SOURCE_MODE* CONST  pVidPnSourceModeInfo);

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_CREATENEWMODEINFO)
        (CONST D3DKMDT_HVIDPNSOURCEMODESET  hVidPnSourceModeSet,
         __out D3DKMDT_VIDPN_SOURCE_MODE**  ppNewVidPnSourceModeInfo);

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ADDMODE)
        (D3DKMDT_HVIDPNSOURCEMODESET        hVidPnSourceModeSet,
         D3DKMDT_VIDPN_SOURCE_MODE* CONST   pVidPnSourceModeInfo);

// NOTE: Mode ID is assigned to the mode by Windows Graphics Kernel at creation time
//       using DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnCreateNewModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_PINMODE)
        (D3DKMDT_HVIDPNSOURCEMODESET                 hVidPnSourceModeSet,
         CONST D3DKMDT_VIDEO_PRESENT_SOURCE_MODE_ID  VidPnSourceModeId);

typedef struct _DXGK_VIDPNSOURCEMODESET_INTERFACE
{
    DXGKDDI_VIDPNSOURCEMODESET_GETNUMMODES              pfnGetNumModes;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIREFIRSTMODEINFO     pfnAcquireFirstModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIRENEXTMODEINFO      pfnAcquireNextModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIREPINNEDMODEINFO    pfnAcquirePinnedModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_RELEASEMODEINFO          pfnReleaseModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_CREATENEWMODEINFO        pfnCreateNewModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ADDMODE                  pfnAddMode;
    DXGKDDI_VIDPNSOURCEMODESET_PINMODE                  pfnPinMode;
} DXGK_VIDPNSOURCEMODESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNTARGETMODESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnAcquireTargetModeSet.

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_GETNUMMODES)
        (CONST D3DKMDT_HVIDPNTARGETMODESET  hVidPnTargetModeSet,
         __out SIZE_T* CONST                pNumTargetModes);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIREFIRSTMODEINFO)
        (CONST D3DKMDT_HVIDPNTARGETMODESET        hVidPnTargetModeSet,
         __out CONST D3DKMDT_VIDPN_TARGET_MODE**  ppFirstVidPnTargetModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIRENEXTMODEINFO)
        (CONST D3DKMDT_HVIDPNTARGETMODESET        hVidPnTargetModeSet,
         CONST D3DKMDT_VIDPN_TARGET_MODE* CONST   pVidPnTargetModeInfo,
         __out CONST D3DKMDT_VIDPN_TARGET_MODE**  ppNextVidPnTargetModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIREPINNEDMODEINFO)
        (CONST D3DKMDT_HVIDPNTARGETMODESET        hVidPnTargetModeSet,
         __out CONST D3DKMDT_VIDPN_TARGET_MODE**  ppPinnedVidPnTargetModeInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_RELEASEMODEINFO)
        (CONST D3DKMDT_HVIDPNTARGETMODESET       hVidPnTargetModeSet,
         CONST D3DKMDT_VIDPN_TARGET_MODE* CONST  pVidPnTargetModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_CREATENEWMODEINFO)
        (CONST D3DKMDT_HVIDPNTARGETMODESET  hVidPnTargetModeSet,
         __out D3DKMDT_VIDPN_TARGET_MODE**  ppNewVidPnTargetModeInfo);

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ADDMODE)
        (D3DKMDT_HVIDPNTARGETMODESET        hVidPnTargetModeSet,
         D3DKMDT_VIDPN_TARGET_MODE* CONST   pVidPnTargetModeInfo);

// NOTE: Mode ID is assigned to the mode by Windows Graphics Kernel at creation time
//       using DXGKTARGETMODESET_INTERFACE::pfnCreateNewModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPNTARGETMODESET_PINMODE)
        (D3DKMDT_HVIDPNTARGETMODESET                 hVidPnTargetModeSet,
         CONST D3DKMDT_VIDEO_PRESENT_TARGET_MODE_ID  VidPnTargetModeId);

typedef struct _DXGK_VIDPNTARGETMODESET_INTERFACE
{
    DXGKDDI_VIDPNTARGETMODESET_GETNUMMODES              pfnGetNumModes;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIREFIRSTMODEINFO     pfnAcquireFirstModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIRENEXTMODEINFO      pfnAcquireNextModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIREPINNEDMODEINFO    pfnAcquirePinnedModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_RELEASEMODEINFO          pfnReleaseModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_CREATENEWMODEINFO        pfnCreateNewModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ADDMODE                  pfnAddMode;
    DXGKDDI_VIDPNTARGETMODESET_PINMODE                  pfnPinMode;
} DXGK_VIDPNTARGETMODESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPN_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_INTERFACESPECIFICDATA::pfnQueryVidPnInterface.

//////////////
// Topology //
//////////////

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_GETTOPOLOGY)
        (CONST D3DKMDT_HVIDPN                         hVidPn,
         __out D3DKMDT_HVIDPNTOPOLOGY*                phVidPnTopology,
         __out CONST DXGK_VIDPNTOPOLOGY_INTERFACE**   ppVidPnTopologyInterface);


/////////////////////
// Source modality //
/////////////////////

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_ACQUIRESOURCEMODESET)
        (CONST D3DKMDT_HVIDPN                              hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID              VidPnSourceId,
         __out D3DKMDT_HVIDPNSOURCEMODESET*                phVidPnSourceModeSet,
         __out CONST DXGK_VIDPNSOURCEMODESET_INTERFACE**   ppVidPnSourceModeSetInterface);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_RELEASESOURCEMODESET)
        (CONST D3DKMDT_HVIDPN               hVidPn,
         CONST D3DKMDT_HVIDPNSOURCEMODESET  hVidPnSourceModeSet);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_CREATENEWSOURCEMODESET)
        (CONST D3DKMDT_HVIDPN                             hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID             VidPnSourceId,
         __out D3DKMDT_HVIDPNSOURCEMODESET*               phNewVidPnSourceModeSet,
         __out CONST DXGK_VIDPNSOURCEMODESET_INTERFACE**  ppVidPnSourceModeSetInterface);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_ASSIGNSOURCEMODESET)
        (D3DKMDT_HVIDPN                        hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId,
         CONST D3DKMDT_HVIDPNSOURCEMODESET     hVidPnSourceModeSet);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_ASSIGNMULTISAMPLINGMETHODSET)
        (D3DKMDT_HVIDPN                        hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId,
         CONST SIZE_T                          NumMethods,
         CONST D3DDDI_MULTISAMPLINGMETHOD*     pSupportedMethodSet);


/////////////////////
// Target modality //
/////////////////////

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_ACQUIRETARGETMODESET)
        (CONST D3DKMDT_HVIDPN                              hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID              VidPnTargetId,
         __out D3DKMDT_HVIDPNTARGETMODESET*                phVidPnTargetModeSet,
         __out CONST DXGK_VIDPNTARGETMODESET_INTERFACE**   ppVidPnTargetModeSetInterface);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_RELEASETARGETMODESET)
        (CONST D3DKMDT_HVIDPN               hVidPn,
         CONST D3DKMDT_HVIDPNTARGETMODESET  hVidPnTargetModeSet);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_CREATENEWTARGETMODESET)
        (CONST D3DKMDT_HVIDPN                              hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID              VidPnTargetId,
         __out D3DKMDT_HVIDPNTARGETMODESET*                phNewVidPnTargetModeSet,
         __out CONST DXGK_VIDPNTARGETMODESET_INTERFACE**   ppVidPnTargetModeSetInterace);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_VIDPN_ASSIGNTARGETMODESET)
        (D3DKMDT_HVIDPN                        hVidPn,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId,
         CONST D3DKMDT_HVIDPNTARGETMODESET     hVidPnTargetModeSet);


// DXGK_VIDPN_INTERFACE interface versions.
typedef enum _DXGK_VIDPN_INTERFACE_VERSION
{
    DXGK_VIDPN_INTERFACE_VERSION_UNINITIALIZED = 0,
    DXGK_VIDPN_INTERFACE_VERSION_V1            = 1,
} DXGK_VIDPN_INTERFACE_VERSION;

typedef struct _DXGK_VIDPN_INTERFACE
{
    // Specifies the version of this interface as well as all the sub-interfaces, which are accessible
    // only via this interface (i.e. DXGK_VIDPNTOPOLOGY_INTERFACE, DXGK_VIDPNSOURCEMODESET_INTERFACE,
    // and DXGK_VIDPNTARGETMODESET_INTERFACE).
    DXGK_VIDPN_INTERFACE_VERSION                 Version;

    // Topology
    DXGKDDI_VIDPN_GETTOPOLOGY                    pfnGetTopology;

    // Source modality
    DXGKDDI_VIDPN_ACQUIRESOURCEMODESET           pfnAcquireSourceModeSet;
    DXGKDDI_VIDPN_RELEASESOURCEMODESET           pfnReleaseSourceModeSet;
    DXGKDDI_VIDPN_CREATENEWSOURCEMODESET         pfnCreateNewSourceModeSet;
    DXGKDDI_VIDPN_ASSIGNSOURCEMODESET            pfnAssignSourceModeSet;
    DXGKDDI_VIDPN_ASSIGNMULTISAMPLINGMETHODSET   pfnAssignMultisamplingMethodSet;

    // Target modality
    DXGKDDI_VIDPN_ACQUIRETARGETMODESET           pfnAcquireTargetModeSet;
    DXGKDDI_VIDPN_RELEASETARGETMODESET           pfnReleaseTargetModeSet;
    DXGKDDI_VIDPN_CREATENEWTARGETMODESET         pfnCreateNewTargetModeSet;
    DXGKDDI_VIDPN_ASSIGNTARGETMODESET            pfnAssignTargetModeSet;
}
DXGK_VIDPN_INTERFACE;


// Callback miniport uses to query DXGK_VIDPN_INTERFACE.
typedef NTSTATUS
        (APIENTRY CALLBACK *DXGKCB_QUERYVIDPNINTERFACE)
        (CONST D3DKMDT_HVIDPN                hVidPn,
         CONST DXGK_VIDPN_INTERFACE_VERSION  VidPnInterfaceVersion,
         __out CONST DXGK_VIDPN_INTERFACE**  ppVidPnInterface);


/////////////////////////////
// Monitor source modality //
/////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORSOURCEMODESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorSourceModeSet.

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_GETNUMMODES)
        (CONST D3DKMDT_HMONITORSOURCEMODESET  hMonitorSourceModeSet,
         __out SIZE_T* CONST                  pNumMonitorSourceModes);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIREPREFERREDMODEINFO)
        (CONST D3DKMDT_HMONITORSOURCEMODESET        hMonitorSourceModeSet,
         __out CONST D3DKMDT_MONITOR_SOURCE_MODE**  ppFirstMonitorSourceModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIREFIRSTMODEINFO)
        (CONST D3DKMDT_HMONITORSOURCEMODESET        hMonitorSourceModeSet,
         __out CONST D3DKMDT_MONITOR_SOURCE_MODE**  ppFirstMonitorSourceModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIRENEXTMODEINFO)
        (CONST D3DKMDT_HMONITORSOURCEMODESET        hMonitorSourceModeSet,
         CONST D3DKMDT_MONITOR_SOURCE_MODE* CONST   pMonitorSourceModeInfo,
         __out CONST D3DKMDT_MONITOR_SOURCE_MODE**  ppNextMonitorSourceModeInfo);

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_CREATENEWMODEINFO)
        (CONST D3DKMDT_HMONITORSOURCEMODESET  hMonitorSourceModeSet,
         __out D3DKMDT_MONITOR_SOURCE_MODE**  ppNewMonitorSourceModeInfo);

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ADDMODE)
        (D3DKMDT_HMONITORSOURCEMODESET        hMonitorSourceModeSet,
         D3DKMDT_MONITOR_SOURCE_MODE* CONST   pMonitorSourceModeInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORSOURCEMODESET_RELEASEMODEINFO)
        (CONST D3DKMDT_HMONITORSOURCEMODESET       hMonitorSourceModeSet,
         CONST D3DKMDT_MONITOR_SOURCE_MODE* CONST  pMonitorSourceModeInfo);


typedef struct _DXGK_MONITORSOURCEMODESET_INTERFACE
{
    DXGKDDI_MONITORSOURCEMODESET_GETNUMMODES               pfnGetNumModes;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIREPREFERREDMODEINFO  pfnAcquirePreferredModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIREFIRSTMODEINFO      pfnAcquireFirstModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIRENEXTMODEINFO       pfnAcquireNextModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_CREATENEWMODEINFO         pfnCreateNewModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ADDMODE                   pfnAddMode;
    DXGKDDI_MONITORSOURCEMODESET_RELEASEMODEINFO           pfnReleaseModeInfo;
} DXGK_MONITORSOURCEMODESET_INTERFACE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORFREQUENCYRANGESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorFrequencyRangeSet.

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_GETNUMFREQUENCYRANGES)
        (CONST D3DKMDT_HMONITORFREQUENCYRANGESET  hMonitorFrequencyRangeSet,
         __out SIZE_T* CONST                      pNumMonitorFrequencyRanges);

// NOTE: To dispose of use pfnReleaseFrequencyRangeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIREFIRSTFREQUENCYRANGEINFO)
        (CONST D3DKMDT_HMONITORFREQUENCYRANGESET        hMonitorFrequencyRangeSet,
         __out CONST D3DKMDT_MONITOR_FREQUENCY_RANGE**  ppFirstMonitorFrequencyRangeInfo);

// NOTE: To dispose of use pfnReleaseFrequencyRangeInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIRENEXTFREQUENCYRANGEINFO)
        (CONST D3DKMDT_HMONITORFREQUENCYRANGESET        hMonitorFrequencyRangeSet,
         CONST D3DKMDT_MONITOR_FREQUENCY_RANGE* CONST   pMonitorFrequencyRangeInfo,
         __out CONST D3DKMDT_MONITOR_FREQUENCY_RANGE**  ppNextMonitorFrequencyRangeInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_RELEASEFREQUENCYRANGEINFO)
        (CONST D3DKMDT_HMONITORFREQUENCYRANGESET       hMonitorFrequencyRangeSet,
         CONST D3DKMDT_MONITOR_FREQUENCY_RANGE* CONST  pMonitorFrequencyRangeInfo);

typedef struct _DXGK_MONITORFREQUENCYRANGESET_INTERFACE
{
    DXGKDDI_MONITORFREQUENCYRANGESET_GETNUMFREQUENCYRANGES           pfnGetNumFrequencyRanges;
    DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIREFIRSTFREQUENCYRANGEINFO  pfnAcquireFirstFrequencyRangeInfo;
    DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIRENEXTFREQUENCYRANGEINFO   pfnAcquireNextFrequencyRangeInfo;
    DXGKDDI_MONITORFREQUENCYRANGESET_RELEASEFREQUENCYRANGEINFO       pfnReleaseFrequencyRangeInfo;
} DXGK_MONITORFREQUENCYRANGESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORDESCRIPTORSET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorDescriptorSet.

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_GETNUMDESCRIPTORS)
        (CONST D3DKMDT_HMONITORDESCRIPTORSET  hMonitorDescriptorSet,
         __out SIZE_T* CONST                  pNumMonitorDescriptors);

// NOTE: To dispose of use pfnReleaseDescriptorInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_ACQUIREFIRSTDESCRIPTORINFO)
        (CONST D3DKMDT_HMONITORDESCRIPTORSET       hMonitorDescriptorSet,
         __out CONST D3DKMDT_MONITOR_DESCRIPTOR**  ppFirstMonitorDescriptorInfo);

// NOTE: To dispose of use pfnReleaseDescriptorInfo.
typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_ACQUIRENEXTDESCRIPTORINFO)
        (CONST D3DKMDT_HMONITORDESCRIPTORSET       hMonitorDescriptorSet,
         CONST D3DKMDT_MONITOR_DESCRIPTOR* CONST   pMonitorDescriptorInfo,
         __out CONST D3DKMDT_MONITOR_DESCRIPTOR**  ppNextMonitorDescriptorInfo);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_RELEASEDESCRIPTORINFO)
        (CONST D3DKMDT_HMONITORDESCRIPTORSET      hMonitorDescriptorSet,
         CONST D3DKMDT_MONITOR_DESCRIPTOR* CONST  pMonitorDescriptorInfo);

typedef struct _DXGK_MONITORDESCRIPTORSET_INTERFACE
{
    DXGKDDI_MONITORDESCRIPTORSET_GETNUMDESCRIPTORS           pfnGetNumDescriptors;
    DXGKDDI_MONITORDESCRIPTORSET_ACQUIREFIRSTDESCRIPTORINFO  pfnAcquireFirstDescriptorInfo;
    DXGKDDI_MONITORDESCRIPTORSET_ACQUIRENEXTDESCRIPTORINFO   pfnAcquireNextDescriptorInfo;
    DXGKDDI_MONITORDESCRIPTORSET_RELEASEDESCRIPTORINFO       pfnReleaseDescriptorInfo;
} DXGK_MONITORDESCRIPTORSET_INTERFACE;



typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET)
        (CONST D3DKMDT_ADAPTER                              hAdapter,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID               VideoPresentTargetId,
         __out D3DKMDT_HMONITORSOURCEMODESET*               phMonitorSourceModeSet,
         __out CONST DXGK_MONITORSOURCEMODESET_INTERFACE**  ppMonitorSourceModeSetInterface);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET)
        (CONST D3DKMDT_ADAPTER                hAdapter,
         CONST D3DKMDT_HMONITORSOURCEMODESET  hMonitorSourceModeSet);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET)
        (CONST D3DKMDT_ADAPTER                                  hAdapter,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID                   VideoPresentTargetId,
         __out D3DKMDT_HMONITORFREQUENCYRANGESET*               phMonitorFrequencyRangeSet,
         __out CONST DXGK_MONITORFREQUENCYRANGESET_INTERFACE**  ppMonitorFrequencyRangeSetInterface);

typedef NTSTATUS
        (APIENTRY *DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET)
        (CONST D3DKMDT_ADAPTER                              hAdapter,
         CONST D3DDDI_VIDEO_PRESENT_TARGET_ID               VideoPresentTargetId,
         __out D3DKMDT_HMONITORDESCRIPTORSET*               phMonitorDescriptorSet,
         __out CONST DXGK_MONITORDESCRIPTORSET_INTERFACE**  ppMonitorDescriptorSetInterface);


// DXGK_MONITOR_INTERFACE interface versions.
typedef enum _DXGK_MONITOR_INTERFACE_VERSION
{
    DXGK_MONITOR_INTERFACE_VERSION_UNINITIALIZED = 0,
    DXGK_MONITOR_INTERFACE_VERSION_V1            = 1,
} DXGK_MONITOR_INTERFACE_VERSION;

typedef struct _DXGK_MONITOR_INTERFACE
{
    // Specifies the version of this interface as well as all the sub-interfaces, which are accessible
    // only via this interface (i.e. DXGK_VIDPNTOPOLOGY_INTERFACE, DXGK_VIDPNSOURCEMODESET_INTERFACE,
    // and DXGK_VIDPNTARGETMODESET_INTERFACE).
    DXGK_MONITOR_INTERFACE_VERSION                 Version;

    DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET    pfnAcquireMonitorSourceModeSet;
    DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET    pfnReleaseMonitorSourceModeSet;
    DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET    pfnGetMonitorFrequencyRangeSet;
    DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET        pfnGetMonitorDescriptorSet;
}
DXGK_MONITOR_INTERFACE;

// Callback miniport uses to query DXGK_MONITOR_INTERFACE.
typedef NTSTATUS
        (APIENTRY CALLBACK *DXGKCB_QUERYMONITORINTERFACE)
        (CONST HANDLE                          hAdapter,
         CONST DXGK_MONITOR_INTERFACE_VERSION  MonitorInterfaceVersion,
         __out CONST DXGK_MONITOR_INTERFACE**  ppMonitorInterface);



//////////////////// Timeout Detection and Recovery /////////////////////////////////////////////////////////
typedef
    __checkReturn
NTSTATUS
APIENTRY CALLBACK
DXGKDDI_RESETFROMTIMEOUT(
    IN_CONST_HANDLE     hAdapter
    );

typedef
    __checkReturn
NTSTATUS
APIENTRY CALLBACK
DXGKDDI_RESTARTFROMTIMEOUT(
    IN_CONST_HANDLE     hAdapter
    );

typedef enum _DXGK_ACTIVE_VIDPN_INVALIDATION_REASON
{
    DXGK_AVIR_UNINITIALIZED = DXGK_RFVR_UNINITIALIZED,
    DXGK_AVIR_HOTKEY        = DXGK_RFVR_HOTKEY,
    DXGK_AVIR_USERMODE      = DXGK_RFVR_USERMODE,
}
DXGK_ACTIVE_VIDPN_INVALIDATION_REASON;

typedef struct _DXGK_INTERFACESPECIFICDATA
{
    HANDLE hAdapter;       // in: handle to dxgkrnl's adapter object

    //
    // D3DDDI interface callback functions
    //
    DXGKCB_GETHANDLEDATA          pfnGetHandleDataCb;
    DXGKCB_GETHANDLEPARENT        pfnGetHandleParentCb;
    DXGKCB_ENUMHANDLECHILDREN     pfnEnumHandleChildrenCb;
    DXGKCB_NOTIFY_INTERRUPT       pfnNotifyInterruptCb;
    DXGKCB_NOTIFY_DPC             pfnNotifyDpcCb;
    DXGKCB_QUERYVIDPNINTERFACE    pfnQueryVidPnInterfaceCb;
    DXGKCB_GETCAPTUREADDRESS      pfnGetCaptureAddressCb;
} DXGK_INTERFACESPECIFICDATA;


typedef struct _DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;                  // in: Identifies which VidPn we are changing the private driver format attribute of
    HANDLE                          PrimaryAllocation;              // in: If non zero specifies the current primary allocation for the given VidPn    
    UINT                            PrivateDriverFormatAttribute;   // in: PrivateFormatAttribute to set for the given VidPn
} DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT;

typedef __in DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT*    IN_CONST_PDXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT pSetDisplayPrivateDriverFormat
    );


/*++
Routine Description:
    RecommendMonitorModes LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter           - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->VideoPresentTargetId - ID of the video present target to which the monitor in question is connected.

       ->hMonitorSourceModeSet - Handle of the monitor mode set.

       ->pMonitorSourceModeSetInterface - Reference to the monitor mode set interface.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR|* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    On success, optionally, adds one or more monitor source modes to the mode set of the monitor connected to the specified target.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_RECOMMENDMONITORMODES
{
    IN D3DDDI_VIDEO_PRESENT_TARGET_ID              VideoPresentTargetId;
    IN D3DKMDT_HMONITORSOURCEMODESET               hMonitorSourceModeSet;
    IN CONST DXGK_MONITORSOURCEMODESET_INTERFACE*  pMonitorSourceModeSetInterface;

} DXGKARG_RECOMMENDMONITORMODES;

typedef __in CONST DXGKARG_RECOMMENDMONITORMODES* CONST     IN_CONST_PDXGKARG_RECOMMENDMONITORMODES_CONST;

typedef
    __checkReturn
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDMONITORMODES(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDMONITORMODES_CONST   pRecommendMonitorModes
    );

//
//     Function pointer typedefs
//

typedef DXGKDDI_QUERYADAPTERINFO                *PDXGKDDI_QUERYADAPTERINFO;
typedef DXGKDDI_CREATEDEVICE                    *PDXGKDDI_CREATEDEVICE;
typedef DXGKDDI_CREATEALLOCATION                *PDXGKDDI_CREATEALLOCATION;
typedef DXGKDDI_DESTROYALLOCATION               *PDXGKDDI_DESTROYALLOCATION;
typedef DXGKDDI_DESCRIBEALLOCATION              *PDXGKDDI_DESCRIBEALLOCATION;
typedef DXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA *PDXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA;
typedef DXGKDDI_ACQUIRESWIZZLINGRANGE           *PDXGKDDI_ACQUIRESWIZZLINGRANGE;
typedef DXGKDDI_RELEASESWIZZLINGRANGE           *PDXGKDDI_RELEASESWIZZLINGRANGE;
typedef DXGKDDI_PATCH                           *PDXGKDDI_PATCH;
typedef DXGKDDI_SUBMITCOMMAND                   *PDXGKDDI_SUBMITCOMMAND;
typedef DXGKDDI_PREEMPTCOMMAND                  *PDXGKDDI_PREEMPTCOMMAND;
typedef DXGKDDI_BUILDPAGINGBUFFER               *PDXGKDDI_BUILDPAGINGBUFFER;
typedef DXGKDDI_SETPALETTE                      *PDXGKDDI_SETPALETTE;
typedef DXGKDDI_SETPOINTERPOSITION              *PDXGKDDI_SETPOINTERPOSITION;
typedef DXGKDDI_SETPOINTERSHAPE                 *PDXGKDDI_SETPOINTERSHAPE;
typedef DXGKDDI_RESETFROMTIMEOUT                *PDXGKDDI_RESETFROMTIMEOUT;
typedef DXGKDDI_RESTARTFROMTIMEOUT              *PDXGKDDI_RESTARTFROMTIMEOUT;
typedef DXGKDDI_ESCAPE                          *PDXGKDDI_ESCAPE;
typedef DXGKDDI_COLLECTDBGINFO                  *PDXGKDDI_COLLECTDBGINFO;
typedef DXGKDDI_QUERYCURRENTFENCE               *PDXGKDDI_QUERYCURRENTFENCE;
typedef DXGKDDI_ISSUPPORTEDVIDPN                *PDXGKDDI_ISSUPPORTEDVIDPN;
typedef DXGKDDI_RECOMMENDFUNCTIONALVIDPN        *PDXGKDDI_RECOMMENDFUNCTIONALVIDPN;
typedef DXGKDDI_ENUMVIDPNCOFUNCMODALITY         *PDXGKDDI_ENUMVIDPNCOFUNCMODALITY;
typedef DXGKDDI_SETVIDPNSOURCEADDRESS           *PDXGKDDI_SETVIDPNSOURCEADDRESS;
typedef DXGKDDI_SETVIDPNSOURCEVISIBILITY        *PDXGKDDI_SETVIDPNSOURCEVISIBILITY;
typedef DXGKDDI_COMMITVIDPN                     *PDXGKDDI_COMMITVIDPN;
typedef DXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH    *PDXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH;
typedef DXGKDDI_RECOMMENDMONITORMODES           *PDXGKDDI_RECOMMENDMONITORMODES;
typedef DXGKDDI_RECOMMENDVIDPNTOPOLOGY          *PDXGKDDI_RECOMMENDVIDPNTOPOLOGY;
typedef DXGKDDI_GETSCANLINE                     *PDXGKDDI_GETSCANLINE;
typedef DXGKDDI_STOPCAPTURE                     *PDXGKDDI_STOPCAPTURE;
typedef DXGKDDI_CONTROLINTERRUPT                *PDXGKDDI_CONTROLINTERRUPT;
typedef DXGKDDI_CREATEOVERLAY                   *PDXGKDDI_CREATEOVERLAY;
typedef DXGKDDI_DESTROYDEVICE                   *PDXGKDDI_DESTROYDEVICE;
typedef DXGKDDI_OPENALLOCATIONINFO              *PDXGKDDI_OPENALLOCATIONINFO;
typedef DXGKDDI_CLOSEALLOCATION                 *PDXGKDDI_CLOSEALLOCATION;
typedef DXGKDDI_RENDER                          *PDXGKDDI_RENDER;
typedef DXGKDDI_PRESENT                         *PDXGKDDI_PRESENT;
typedef DXGKDDI_UPDATEOVERLAY                   *PDXGKDDI_UPDATEOVERLAY;
typedef DXGKDDI_FLIPOVERLAY                     *PDXGKDDI_FLIPOVERLAY;
typedef DXGKDDI_DESTROYOVERLAY                  *PDXGKDDI_DESTROYOVERLAY;
typedef DXGKDDI_CREATECONTEXT                   *PDXGKDDI_CREATECONTEXT;
typedef DXGKDDI_DESTROYCONTEXT                  *PDXGKDDI_DESTROYCONTEXT;
typedef DXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT   *PDXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT;

#endif /* _D3DKMDDI_H_ */


