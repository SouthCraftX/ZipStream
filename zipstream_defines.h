#ifndef _ZSTM_HEADERFILE_DEFINES_
#define _ZSTM_HEADERFILE_DEFINES_

#include "zipstream_types.h"

namespace zstm{

    enum StatusCode{

        //Successful
        Okay = 0,

        //Fail
        ZipNotOpen,
        BufferSizeTooBig,
        BufferSizeTooSmall,
        AllocateMemory,
        GetFileNum,
        OpenZip,
        CloseZip,
        IndexFile,
        Int2String,
        PutErrorMsg,
        CreateLocalFile,
        CleanBuffer,
        ReadFileFromZip,
        WriteLocalFile,
        GetFileComment,
        NoSuchFileDir,
        NoComment,
        InvaildEncoding
    };
    constexpr ZSTM_FLNUM_T  SearchNoResult      =   ZIP_UINT64_MAX;

    namespace error_level{
        constexpr ZSTM_BOOL_BT  normal        =   1;
        constexpr ZSTM_BOOL_BT  lowest        =   0;
    }
    

    namespace buffer_size {
        constexpr ZSTM_SIZE_T   Default   =   8192 ;
        constexpr ZSTM_SIZE_T   Max       =   (2*1024*1024); //2MB
        constexpr ZSTM_SIZE_T   Min       =   128; 
    }
    

    namespace encoding{
        constexpr ZSTM_ENCM_T   Auto        =   ZIP_FL_ENC_GUESS;
        constexpr ZSTM_ENCM_T   CP437       =   ZIP_FL_ENC_CP437;
    }
   

    const ZSTM_UINT32_BT ZipFileIO = ZIP_FL_COMPRESSED;

    // Error Messages
    namespace ErrorText{
        ZSTM_ERRMSG_T   BufSizeTooBig_1   =  "Buffer size that you set( ";
        ZSTM_ERRMSG_T   BufSizeTooBig_2   =  "bytes) too big! It cannot be bigger than";
        ZSTM_ERRMSG_T   ZipNotOpen        =  "No compressed packages were opened.";
        ZSTM_ERRMSG_T   AllocateFail      =  "Failed to allocate memory. size=";
        ZSTM_ERRMSG_T   IndexFile         =  "Failed to index file:";
        ZSTM_ERRMSG_T   CreateLocalFile   =  "Failed to crafte local file:";
        ZSTM_ERRMSG_T   CleanBuffer       =  "Failed to clean buffer, size=";
        ZSTM_ERRMSG_T   ReadFileFromZip   =  "Failed to read a file from zip:";
        ZSTM_ERRMSG_T   WriteLocalFile    =  "Failed to waite a local file:";
        ZSTM_ERRMSG_T   SearchNoResult    =  "No such a file:";
        ZSTM_ERRMSG_T   FileNoComment     =  "No comments on this file:";
        ZSTM_ERRMSG_T   ZipNoComment      =  "No comments on the compressed package.";
        ZSTM_ERRMSG_T   InvaildEncoding   =  "Invaild encoding";

    }

    // Function Names
    namespace FunctionName{
        ZSTM_FUNCNM_T  SetEncoding      =  "SetEncoding()";
        ZSTM_FUNCNM_T  OpenFL           =  "OpenFile()";
        ZSTM_FUNCNM_T  CloseFL          =  "CloseFL()";
        ZSTM_FUNCNM_T  SerFL            =  "SearchFile()";
        ZSTM_FUNCNM_T  GetErr           =  "GetError()";
        ZSTM_FUNCNM_T  GetZipPath       =  "GetZipPath()";
        ZSTM_FUNCNM_T  SetErrLv         =  "SetErrorLevel";
        ZSTM_FUNCNM_T  SetZipPw         =  "SetZipPassword()";
        ZSTM_FUNCNM_T  GetFLNum         =  "GetFileNum()";
        ZSTM_FUNCNM_T  SetBufSize       =  "SetBuffferSize()";
        ZSTM_FUNCNM_T  ClnBuf           =  "CleanBuffer()";
        ZSTM_FUNCNM_T  GetZipStat       =  "GetZipStat()";
        ZSTM_FUNCNM_T  Unzip            =  "Unzip()";
        ZSTM_FUNCNM_T  SearchFile       =  "SearchFile()";
        ZSTM_FUNCNM_T  GetFileComment   =  "GetFileComment()";
        ZSTM_FUNCNM_T  GetZipComment   =  "GetZipComment()";
    }
    //zSTM_FUNCNM_T  
    
}

#endif
