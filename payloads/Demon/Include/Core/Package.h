#ifndef CALLBACK_PACKAGE_H
#define CALLBACK_PACKAGE_H

#include <Core/Command.h>

typedef struct {
    UINT32  RequestID;
    UINT32  CommandID;
    PVOID   Buffer;
    SIZE_T  Length;
    BOOL    Encrypt;
    BOOL    Destroy; /* destroy this package after Transmit */
} PACKAGE, *PPACKAGE;

/* Package generator */
PPACKAGE PackageCreate( UINT32 CommandID );
PPACKAGE PackageCreateWithRequestID( UINT32 RequestID, UINT32 CommandID );

/* PackageAddInt32
 * package => pointer to package response struct
 * dataInt => unsigned 32-bit integer data to add to the response
 * Description: Add unsigned 32-bit integer to the response buffer
 */
VOID PackageAddInt32(
    PPACKAGE package,
    UINT32 iData
);

VOID PackageAddInt64(
    PPACKAGE Package,
    UINT64 dataInt
);

VOID PackageAddPtr(
    PPACKAGE Package,
    PVOID pointer
);

// PackageAddBytes
VOID PackageAddBytes(
    PPACKAGE package,
    PBYTE data,
    SIZE_T dataSize
);

VOID PackageAddString(
    PPACKAGE package,
    PCHAR data
);

VOID PackageAddWString(
    PPACKAGE package,
    PWCHAR data
);

// PackageAddBytes
VOID PackageAddPad(
    PPACKAGE package,
    PCHAR data,
    SIZE_T dataSize
);

// PackageDestroy
VOID PackageDestroy(
    PPACKAGE package
);

// PackageTransmit
BOOL PackageTransmit(
    PPACKAGE Package,
    PVOID*   Response,
    PSIZE_T  Size
);

VOID PackageTransmitError(
    UINT32 CommandID,
    UINT32 ErrorCode
);

#define PACKAGE_ERROR_WIN32         PackageTransmitError( CALLBACK_ERROR_WIN32, NtGetLastError() );
#define PACKAGE_ERROR_NTSTATUS( s ) PackageTransmitError( CALLBACK_ERROR_WIN32, Instance.Win32.RtlNtStatusToDosError( s ) );

#endif
