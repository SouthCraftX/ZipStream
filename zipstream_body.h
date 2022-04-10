#ifndef _ZSTM_HEADERFILE_BODY_
#define _ZSTM_HEADERFILE_BODY_

#include <zip.h>
#include <cstring>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include "zipstream_defines.h"
namespace zstm{

//const ZSTM_FUNCNM_T  FuncNm_

    class izipstream{

        public:
            ZSTM_BOOL_BT    GetZipArchiveFlag       ();
            ZSTM_BOOL_BT    OpenZip                 ( const ZSTM_CSTR_BT );
            ZSTM_BOOL_BT    CloseZip                ();
            ZSTM_INT32_BT   SearchFile              ( const ZSTM_CSTR_BT );
            ZSTM_CSTR_BT    GetError                ()  const;
            ZSTM_CSTR_BT    GetZipPath              ()  const;
            ZSTM_BOOL_BT    SetErrorLevel           ( ZSTM_BOOL_BT );
            ZSTM_BOOL_BT    SetZipPassword          ( const ZSTM_CSTR_BT );
            ZSTM_INT32_BT   GetFileNum              ()  const;
            ZSTM_BOOL_BT    GetFileStat             ();
            ZSTM_BOOL_BT    Unzip                   ( const ZSTM_PATH_T );
            ZSTM_BOOL_BT    operator>>              ( const ZSTM_PATH_T );
            ZSTM_SIZE_T     GetFileSize             ( const ZSTM_PATH_T );
            ZSTM_CSTR_BT    GetFileComment          ( const ZSTM_PATH_T , const ZSTN_CSTR_BT , const ZSTM_ENCM_T);
            ZSTM_CSTR_BT    GetZipComment           ( const ZSTN_CSTR_BT , const ZSTM_ENCM_T);
            ZSTM_BOOL_BT    SetEncoding             ( const ZSTM_ENCM_T );
            ZSTM_UINT32_BT  GetFileCrc              ( const ZSTM_PATH_T ) const;
            ZSTM_UINT32_BT  GetFileCompressedSize   ( const ZSTM_PATH_T ) const;

        protected:
            ZSTM_CSTR_BT     ZipPath;
            ZSTM_CSTR_BT     ErrorMessage;
            zip_t*           Archive ;
            ZSTM_INT32_BT    ErrorCode ;
            ZSTM_INT32_BT    FileCount;

        private:
            ZSTM_BOOL_BT    PutErrorMessage     (  ZSTM_FUNCNM_T  , std::inttializer_list<ZSTM_FUNCNM_T>  );
            ZSTM_BOOL_BT    SetBufferSize       ( const ZSTM_SIZE_T );
            ZSTM_BOOL_BT    CleanBuffer         ();
            ZSTM_BOOL_BT    IsZipOpen();
            ZSTM_CSTR_BT    ZipPassword;
            ZSTM_INT32_BT   ErrorLevel;
            ZSTM_SIZE_T     BufferSize;
            zip_stat_t*     FileStat;
            ZSTM_ENCM_T     Encoding;
            izipstream                          ( const char* );
    }

}

#endif