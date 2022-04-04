#ifndef _ZSTM_HEADERFILE_TYPES_
#define _ZSTM_HEADERFILE_TYPES_ 

#include <stdint.h>
#include <iostream>
namespace zstm  {
    
    // Basic Types
    using ZSTM_INT32_BT     =   int32_t;
    using ZSTM_INT64_ST     =   int64_t;
    using ZSTM_INT16_BT     =   int16_t;
    using ZSTM_INT8_BT      =   int8_t;

    using ZSTM_UINT32_BT    =   uint32_t;
    using ZSTM_UINT64_BT    =   uint64_t;
    using ZSTM_UINT16_BT    =   uint16_t;
    using ZSTM_UINT8_BT     =   uint8_t;

    using ZSTM_BYTE_BT      =   ZSTM_UINT8_BT;
    using ZSTM_WORD_BT      =   ZSTM_UINT16_BT;
    using ZSTM_DWORD_BT     =   ZSTM_UINT32_BT;
    using ZSTM_QWORD_BT     =   ZSTM_UINT64_BT;

    using ZSTM_DOUBLE_BT    =   double;

    using ZSTM_BOOL_BT      =   ZSTM_INT32_BT;
    using ZSTM_CSTR_BT      =   char*;


    // Advanced Types
    using ZSTM_SIZE_T       =   ZSTM_UINT64_BT;
    using ZSTM_ERRMSG_T     =   const char* const;  
    using ZSTM_FPTR_T       =   FILE*;
    using ZSTM_FUNCNM_T     =   const char* const;
    using ZSTM_FLNUM_T      =   ZSTM_UINT64_BT;
    using ZSTM_PATH_T       =   ZSTM_CSTR_BT;
}

#endif