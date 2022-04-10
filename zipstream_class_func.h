#ifndef _ZSTM_HEADERFILE_FUNC_
#define _ZSTM_HEADERFILE_FUNC_
#include "zipstream_body.h"

namespace zstm{
    
    //Open a compressed package
    ZSTM_BOOL_BT izipstream::OpenZip( const ZSTM_PATH_T  ZipperPath){

        this->Archive = zip_open( ZipperPath , ZIP_RDONLY, &(this->ErrorCode) );

        if( this->Archive == NULL ){
            this->PutErrorMessage(("Failed to open %s.Error code :%i", this->ZipPath , this->ErrorCode));
            zip_close( this-> Archive );
            return StatusCode( OpenZip );
        }

        

        if( this->ZipPassword != NULL ){
            zip_set_default_password( this->Archive, this->ZipPassword );
            this->FileCount = zip_get_num_entries(this->Archive, ZIP_FL_UNCHANGED);
            this->FileStat = (zip_stat_t*)::malloc(  (this->FileCount)*(sizeof(zip_stat_t)) );

            for( ZSTM_FLNUM_T now ; now < (this->FileCount) ; now++ ){
                zip_stat_index( this->Archive, now, 0, &(this->FileStat[now]));
            }
        }
        return StatusCode( Okay ) ;
    }
    

    //Unzip a compressed package
    ZSTM_BOOL_BT izipstream::Unzip( const ZSTM_PATH_T outdir ) const{

        if( this->Archive == NULL ){
            this->PutErrorMessage( FunctionName::Unzip , ErrorText::ZipNotOpen);
            return StatusCode(ZipNotOpen);
        }

        for( ZSTM_FLNUM_T now = 0 ; now < this->FileCount ; now++){

            zip_file_t *file = zip_fopen_index( this->Archive , this->FileCount, 0);
            if( file == NULL ){
                this->PutErrorMessage( FunctionName::Unzip , ErrorText::IndexFile , this->FileStat[now].name);
                return StatusCode(IndexFile);
            }

            
            ZSTM_SIZE_T malloc_size = (::strlen(outdir) + ::strlen( this->FileStat[now].name) ++ );
            char outpath [malloc_size];

            ::strcpy( outpath , outdir ) ;
            ::strncat( outpath , this->stat[now].name , malloc_size );
            FILE* localfile = ::fopen( outpath , "w+" );

            if( localfile == NULL ){
                this->PutErrorMessage( FunctionName::Unzip , ErrorText::CreateLocalFile , outpath );
                ::fclose( localfile );
                return StatusCode( CreateLocalFile);
            }
                        
            ZSTM_SIZE_T now_size = 0;
            while( now_size < this->stat[now].size ){
                ZSTM_UINT8_BT* buffer;
                if( this->CleanBuffer(buffer) != StatusCode( Okay )){
                    this->PutErrorMessage( FunctionName::Unzip , ErrorText::CleanBuffer , ToString( this->BufferSize ) , "bytes.");
                    ::free( buffer ) ;
                    ::fclose( localfile );
                    return StatusCode( CleanBuffer);
                }

                if( (ZSTM_INT64_BT) ::zip_fread( file , buffer , this->BufferSize) < 0 ){
                    this->PutErrorMessage( FunctionName::Unzip , ErrorText::ReadFileFromZip , this->FileStat[now].name );
                    ::free( buffer ) ;
                    ::fclose( localfile );
                    return StatusCode( ReadFileFromZip );
                }

                if( ::fwrite( buffer , 1 , this->BufferSize , localfile ) != this->BufferSize ){
                    this->PutErrorMessage( FunctionName::Unzip , ErrorText::WriteLocalFile , outpath );
                    ::free( buffer ) ;
                    ::fclose( localfile );
                    return StatusCode( WriteLocalFile );
                }
                now_size += this->BufferSize;
            }
        }
                   
    }

    ZSTM_BOOL_BT operator>>(const izipstream & zs , const ZSTM_PATH_T outpath ){
        return zs.Unzip( outpath );
    }

    //Get the error message
    ZSTM_CSTR_BT izipstream::GetError const(){
        return this->ErrorMessage;
    }

    ZSTM_SIZE_T GetFileSize( const ZSTM_PATH_T ){

    }

    //Put a error message to 'this->ErrorMsg' and error stream 
    ZSTM_BOOL_BT izipstream::PutErrorMessage( const ZSTM_FUNCNM_T FuncName , std::inttializer_list<ZSTM_FUNCNM_T> list){
        this->ErrorMessage = ErrorMsg;
        
        if( this->ErrorLevel == errlv_normal ){
            std:cerr << "at" << FuncName ;
            for( auto step = list.begin() ; step != list.end() ; step++ ){
                std::cerr << *step;
            }
            std::cerr << std:endl;
        }

        if (std::cerr.good() != true ){
            return StatusCode( PutErrorMsg );
        }
        return StatusCode( Okay );
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

    ZSTM_UINT32_BT  GetFileComment( const ZSTM_PATH_T filename , ZSTM_ENCM_T encoding , ZSTM_CSTR_BT comment, ZSTM_ENCM_T encoding ){
        
        // The length of the comment
        ZSTM_UINT32_BT length; 

        ZSTM_INDEX_T index = this->SearchFile( filename );
        if( index == SearchNoResult ){
            return StatusCode( NoSuchFileDir );
        }
        comment = zip_file_get_comment( this->Archive , index , length , this->Encoding );
        if( comment == NULL ){
            this->PutErrorMessage( FunctionName::GetFileComment , ErrorText::FileMoComment , filename );
            return StatusCode( NoComment );
        }
    }

    ZSTM_UINT32_BT  GetZipComment(ZSTM_ENCM_T encoding , ZSTM_CSTR_BT comment, ZSTM_ENCM_T encoding ){
        
        // The length of the comment
        ZSTM_UINT32_BT length; 

        comment = zip_get_archive_comment( this->Archive , length , this->Encoding );
        if( comment == NULL ){
            this->PutErrorMessage( FunctionName::GetZipComment , ErrorText::FileMoComment  );
            return StatusCode( NoComment );
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

        if( buffer != NULL ){
            free( buffer );
            buffer = NULL;
            return StatusCode( Okay );
        }

        buffer = (ZSTM_CSTR_BT)::malloc( this->BufferSize++ );
        if( buffer == NULL){
            this -> PutErrorMessage( FunctionName::CleanBuffer , ErrorText::AllocateFail , ToString( this->BufferSize ));
        }
        memset( buffer , 0 , this->BufferSize );
        return StatusCode( Okay );
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
        this->CleanBuffer( this->FileStat );
        this -> ZipPassword = NULL;
        this -> FileCount = 0;
        this -> ErrorCode = 0;
        this -> ErrorMessage = NULL  ;
        return StatusCOde( Okay );
    }

    //Search file  named @filename in compressed package 
    ZSTM_INDEX_T izipstream::SearchFile( const ZSTM_PATH_T filename ) const{

        for( ZSTM_FLNUM_T now = 0 ; now < this-p>FileCount ; now ++ ){

            if( ::strcmp( FileName , this->FileStat[now].name) == 0 ){
                return this->FileStat[now].index;
            }

        }
        this->PutErrorMessage( FunctionName::SearchFile , ErrorText::SearchFile , filename );
        return SearchNoResult;
    }

    ZSTM_BOOL_BT izipstream::RenameFile( const char* oldname , const char* newname , ){
        zip_file_rename();
    }

    ZSTM_BOOL_BT izipstream::ExportFile  ( const ZSTM_PATH_t filename , const char* outpath) const {
        ZSTM_UINT8_BT* buffer = NULL;  
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
            this->PutErrorMessage( FunctionName::GetZipStat , ErrorText::ZipNotOpen );
            return ErrorCode( GetZipStat );
        }
        else{
            zip_stat( this->Archive , , , *(this->zip_stat_t) );
        }

    }

    //Convert an integer to a string
    ZSTM_CSTR_BT ToString( ZSTM_INT64_BT number ){
        static char temp[21];
        memset( temp , 0 ,  21 ) ;
        if( sprintf( temp , "%ld ", number) < 0 ){
            return StatusCode( Int2String );
        }
        return StatusCode( Okay);
}

#endif
