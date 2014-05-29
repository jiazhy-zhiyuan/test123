#ifndef __BSREADER_H
#define __BSREADER_H

#define BSREADER_EOF               -1
#define BSREADER_END_OF_GOP        -2
#define BSREADER_END_OF_PLAY       -3

/// \brief Handle for generic bitstream handler
typedef void *BITSTREAMREADER_HANDLE;

/// \brief Callback function prototype
typedef int (*BITSTREAMREADER_CALLBACK)(void *arg, unsigned int *msg);

/// \brief Create BSR instance
typedef BITSTREAMREADER_HANDLE (*BITSTREAMREADER_CREATE)(int *srcId, int *codecId, int nStreams);

/// \brief Callback issued for each new block
typedef int (*BITSTREAMREADER_GETBLOCK)(BITSTREAMREADER_HANDLE h, char **buf, int *length, int *au, 
                                        int *type, int *sid);

/// \brief Callback issued for closing new stream
typedef int (*BITSTREAMREADER_CLOSE)(BITSTREAMREADER_HANDLE h);

/// \brief Callback issued for opening new stream
typedef int (*BITSTREAMREADER_OPEN)(BITSTREAMREADER_HANDLE h, char *name);

/// \brief Configure reader parameters
typedef int (*BITSTREAMREADER_CONFIG)(BITSTREAMREADER_HANDLE h, int param, long long value);

/// \brief show bitstream reader info
typedef int (*BITSTREAMREADER_SHOW)(BITSTREAMREADER_HANDLE h);

/// \brief Switch to a new file, or reset and play the same file from a different location
typedef int (*BITSTREAMREADER_SWITCHFILE)(BITSTREAMREADER_HANDLE h, int *srcId, int *codecId, int nStreams, int diffFile);

/// \brief Set up a callback function for the bitstream reader
typedef int (*BITSTREAMREADER_SETCALLBACK)(BITSTREAMREADER_HANDLE h, BITSTREAMREADER_CALLBACK fn, void *arg);

/// \brief Ioctl for bitstream readers
typedef int (*BITSTREAMREADER_IOCTL)(BITSTREAMREADER_HANDLE h, int cmd, void *arg);

/// \brief Struct containing various callbacks that a new bitstream handler needs to implement
typedef struct
{
    BITSTREAMREADER_CREATE create;
    BITSTREAMREADER_OPEN open;
    BITSTREAMREADER_CLOSE close;
    BITSTREAMREADER_GETBLOCK getBlock;
    BITSTREAMREADER_CONFIG config;
    BITSTREAMREADER_SHOW show;
    BITSTREAMREADER_SWITCHFILE switchFile;
    BITSTREAMREADER_SETCALLBACK setCallback;
    BITSTREAMREADER_IOCTL ioctl;
} BITSTREAMREADER;

#endif
