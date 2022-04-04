#include <zip.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <initializer_list>

#include <limits>
#include "zipstream_types.h"

namespace zstm{

//const ZSTM_FUNCNM_T  FuncNm_

    class izipstream{

        public:
            ZSTM_BOOL_BT    OpenZip             ( const ZSTM_CSTR_BT );
            ZSTM_BOOL_BT    CloseZip            ();
            ZSTM_INT32_BT   SearchFile          ( const ZSTM_CSTR_BT );
            ZSTM_CSTR_BT    GetError            ()  const;
            ZSTM_CSTR_BT    GetZipPath          ()  const;
            ZSTM_BOOL_BT    SetErrorLevel       ( ZSTM_BOOL_BT );
            ZSTM_BOOL_BT    SetZipPassword      ( const ZSTM_CSTR_BT );
            ZSTM_INT32_BT   GetFileNum          ()  const;
            ZSTM_BOOL_BT    GetFileStat         ();
            ZSTM_BOOL_BT    Unzip               ( const ZSTM_PATH_T );

        protected:
            ZSTM_CSTR_T     ZipPath;
            ZSTM_CSTR_T     ErrorMessage;
            zip_t*          Archive ;
            ZSTM_INT32_BT   ErrorCode ;
            ZSTM_INT32_BT   FileCount;

        private:
            ZSTM_BOOL_BT    PutErrorMessage     (  ZSTM_FUNCNM_T  , std::inttializer_list<ZSTM_FUNCNM_T>  );
            ZSTM_BOOL_BT    SetBufferSize       ( const ZSTM_SIZE_T );
            ZSTM_BOOL_BT    CleanBuffer         ();
            ZSTM_CSTR_BT    ZipPassWord;
            ZSTM_INT32_BT   ErrorLevel;
            ZSTM_SIZE_T     BufferSize;
            zip_stat_t*     FileStat;
            izipstream                          ( const char* );
    }

    //Open a compressed package
    ZSTM_BOOL_BT izipstream::OpenZip( const ZSTM_CSTR_T ZipperPath){

        this->Archive = zip_open( ZipperPath , ZIP_RDONLY, &(this->ErrorCode) );

        if( this->Archive == NULL ){
            this->PutErrorMessage(("Failed to open %s.Error code :%i", this->ZipPath , this->ErrorCode));
            zip_close( this-> Archive );
            return false;
        }
        else{
            if( this->ZipPassWord != NULL ){
                zip_set_default_password( this->Archive, this->ZipPassword );
                this->FileCount = zip_get_num_entries(this->Archive, ZIP_FL_UNCHANGED);
                malloc( this->FileStat , (this->FileCount)*(sizeof(zip_stat_t)) );

                for( ZSTM_FLNUM_T now ; now < (this->FileCount) ; now++ ){
                    zip_stat_index( this->Archive, now, 0, &(this->FileStat[now]);
                }
            }
            return true;
        }
    }

    //Unzip a compressed package
    ZSTM_BOOL_BT izipstream::Unzip( const ZSTM_PATH_T outdir ){
        if( this->Archive == NULL ){
            this->PutErrorMessage( FunctionName::Unzip , ErrorText::ZipNotOpen);
            return ErrorCode(ZipNotOpen);
        }
        else{

            for( ZSTM_FLNUM_T now ; now < this->FileCount ; now++){
                struct zip_file_t *file = zip_fopen_index( this->Archive , this->FileCount, 0);
                if( file == NULL ){
                    this->PutErrorMessage( FunctionName::Unzip , ErrorText::IndexFile , this->FileStat[now].name);
                    return ErrorCode(IndexFile);
                }
                else{
                    ZSTM_PATH_T outpath = NULL;
                    ZSTM_SIZE_T malloc_size = (::strlen(outdir) + :: strlen( this->FileStat[now].name) ++ )
                    outpath = ::malloc( outpath , malloc_size); 
                    if( outpath == NULL ){
                        this->PutErrorMessage( FunctionName::Unzip , ErrorText::AllocateMemory , )
                    }
                    FILE* localfile = ::fopen()
                }

            }
        }
    }

    //Get the error message
    ZSTM_CSTR_T izipstream::GetError const(){
        return this->ErrorMessage;
    }

    //Put a error message to 'this->ErrorMsg' and error stream 
    ZSTM_BOOL_BT izipstream::PutErrorMessage( const ZSTM_FUNCNM_T FuncName , std:::inttializer_list<ZSTM_FUNCNM_T> list){
        this->ErrorMessage = ErrorMsg;
        
        if( this->ErrorLevel == errlv_normal ){
            std:cerr << "at" << FuncName ;
            for( auto step = list.begin() ; step != list.end() ; step++ ){
                std::cerr << *step;
            }
            std::cerr << std:endl;
        }

        if (std::cerr.good() != true ){
            return false;
        }
        return true;
    }

    ZSTM_BOOL_BT izipstream::SetErrorLevel( const ZSTM_BOOL_BT level ){
        if( level == errlv_lowest || level == errlv_normal ){
            this->ErrorLevel = level ;
            return true;
        }
        else {
            this->PutErrorMessage("Wrong error level: %i", level );
            return false;
        }
    }

    ZSTM_BOOL_BT izipstream::SetBufferSize( const ZSTM_SIZE_T buf_size ){

        if( buf_size > MaxBufferSize ){
            this->PutErrorMessage("Buffer size that you set(%i bytes) too big! It cannot be bigger than %i bytes.", buf_size , MaxBufferSize );
            return false;
        }
        else if( buf_size < MinBufferSize ){
            this->PutErrorMessage("Buffer size that you set(%i bytes) too small! It cannot be smaller than %i bytes.", buf_size , MaxBufferSize );
            return false;
        }
        else{
            this->BufferSize = buf_size;
            return true;
        }
    }

    ZSTM_BOOL_BT izipsrream::CleanBuffer( ZSTM_CSTR_T buffer){
        buffer = malloc( this->BufferSize );
        if( buffer == NULL){
            this -> PutErrorMessage( FuncNm_CleanBuffer , AllocateFail ,);
        }
        memset( buffer , 0 , this->BufferSize);
    }

    ZSTM_BOOL_BT izipstream::SetZipPassword( const ZSTM_CSTR_T pw ){
       //if(pw != NULL ){
           this->ZipPassword = pw;
           return true;
       //}
       //else{
       //   this->PutErrorMessage("Failed to set the password for the compressed package");
       //   return false;
       //}
    }

    ZSTM_BOOL_BT izipstream::CloseZip(){
        zip_close( this->Archive );
        this -> ZipPassword = NULL;
        this -> FileCount = 0;
        this -> ErrorCode = 0;
        this -> ErrorMessage = NULL  ;
        retuen true;
    }

    unsigned int izipstream::SearchFile( const char* FileName ){

    }

    ZSTM_BOOL_BT izipstream::RenameFile( const char* oldname , const char* newname , ){
        zip_file_rename();
    }

    ZSTM_BOOL_BT izipstream::ExportFile const ( const char* filename , const char* outpath){
        char* buffer;  
        this->CleanBuffer( buffer );
        
        FILE* fileptr = fopen
    }

    //Returns the number of files in the comprssed package
    int izipstream::GetFileNum() const {
        return this->FileCount;
    }

    izipstream::izipstream( const char* zippath = NULL , size_t buffersize = DefaultBufferSize ){
        if( zippath != NULL) this->OpenZip( zippath );
        this->SetBufferSize( buffersize );
    }

    izipstream::GetZipStat(){
        if( this->Archive == NULL ){
            this->PutErrorMessage( FuncNm_GetZipStat , ZipNotOpen );
            return false;
        }
        else{
            zip_stat( this->Archive , , , *(this->zip_stat_t) );
        }

    }

    //Convert an integer to a string
    ZSTM_CSTR_BT ToString( ZSTM_INT64_BT number ){
        char temp[20];
        ZSTM_UINT8_BT pos_number = 0 , pos_str = 0 , flag = false;
        for(ZSTM_UINT8_BT step = 19 ; step > 0 ; step -- ){
            pos_number = number % Pow( 10 , step);
            if( pos_number = 0){
                if( flag == true ) {
                    temp[pos_str] = '0';
                    pos_str++;
                }
            }
            else{
                flag = true;
                temp[ pos_str ] = pos_number + '0';
            }
        }
        char* final_str = temp;
        return final_str;
    }

    ZSTM_DOUBLE_BT Pow( ZSTM_DOUBLE_BT m ,ZSTM_UINT32_BT n ){

        for( ZSTM_UINT32_BT count ; count <= n ; count++){
            m*=n;
        }

        return m;
    }
}