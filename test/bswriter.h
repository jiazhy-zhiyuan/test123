#ifndef __BSWRITER_H 
#define __BSWRITER_H

/// \brief Handle for generic bitstream handler
typedef void *BITSTREAMWRITER_HANDLE;

/// \brief Callback function prototype
typedef int (*BITSTREAMWRITER_CALLBACK)(void *arg, unsigned int *msg, unsigned int *rmsg);

/// \brief Callback issued for each new block
typedef int (*BITSTREAMWRITER_NEWBLOCK)(BITSTREAMWRITER_HANDLE h, char *, int length);

/// \brief Callback issued for each new block using zero copy 
typedef int (*BITSTREAMWRITER_NEWBLOCK_UMA)(BITSTREAMWRITER_HANDLE h, char *, int length, int srcFD, void *virtualZero);

/// \brief Callback issued for closing new stream
typedef int (*BITSTREAMWRITER_CLOSE)(BITSTREAMWRITER_HANDLE h);

/// \brief Function to create an instance of a bitstream writer
typedef BITSTREAMWRITER_HANDLE (*BITSTREAMWRITER_CREATE)();

/// \brief Function to open a new stream
typedef int (*BITSTREAMWRITER_OPEN)(BITSTREAMWRITER_HANDLE h, char *name);

/// \brief ioctl for bitstream writer
typedef int (*BITSTREAMWRITER_IOCTL)(BITSTREAMWRITER_HANDLE h, unsigned int cmd, void *);

/// \brief ioctl for bitstream writer
typedef int (*BITSTREAMWRITER_SHOW)(BITSTREAMWRITER_HANDLE h);

/// \brief lseek for bitstream writer
typedef int (*BITSTREAMWRITER_PWRITE)(BITSTREAMWRITER_HANDLE h, char *buf, int count, int offset);

/// \brief Configure writer parameters
typedef int (*BITSTREAMWRITER_CONFIG)(BITSTREAMWRITER_HANDLE h, int param, int value);

/// \brief Configure writer callback function
typedef int (*BITSTREAMWRITER_SETCALLBACK)(BITSTREAMWRITER_HANDLE h, BITSTREAMWRITER_CALLBACK fn, void *arg);

/// \brief Switch output to another file
typedef int (*BITSTREAMWRITER_SWITCHFILE)(BITSTREAMWRITER_HANDLE h, char *name);

/// \brief Callback issued for each metadata block
typedef int (*BITSTREAMWRITER_NEWMETADATA)(BITSTREAMWRITER_HANDLE h, char *buf, int length, int type, int streamID);

/// \brief Struct containing various callbacks that a new bitstream handler needs to implement
typedef struct
{
    BITSTREAMWRITER_CREATE create;
    BITSTREAMWRITER_OPEN open;
    BITSTREAMWRITER_CLOSE close;
    BITSTREAMWRITER_NEWBLOCK newBlock;
    BITSTREAMWRITER_NEWBLOCK_UMA newBlockUMA;
    BITSTREAMWRITER_IOCTL ioctl;
    BITSTREAMWRITER_SHOW show;
    BITSTREAMWRITER_PWRITE pwrite;
    BITSTREAMWRITER_CONFIG config;
    BITSTREAMWRITER_SETCALLBACK setCallback;
    BITSTREAMWRITER_SWITCHFILE switchFile;
    BITSTREAMWRITER_NEWMETADATA newMetadata;
} BITSTREAMWRITER;

#endif
