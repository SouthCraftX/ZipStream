#include <iostream>
#include <stdint.h>
#include <cstring>
#include <cmath>

double Pow( double m ,uint32_t n ){
    if( n == 0 ){
        m=1;
    }
    else if( n < 0){
        m =  -1;
    }
    else{
        for( uint32_t count = 1 ; count < n ; count++){
            m*=m;
        }
    }
    return m;
}

char temp[20];
char* ToString( uint64_t number ){
        memset( temp , 0 , 20 );
        int pos_number = 0 , pos_str = 0 ;
        for(uint8_t step = log10(number) ; step >= 0 ; step -- ){
            pos_number = number / (uint64_t)Pow( 10 , step);
            number %= (uint64_t)Pow(10,step);
            temp[pos_str] = '0'+ pos_number;
            pos_str++;
            }
        return temp;
    }

int main(){
    std::cout << ToString(123456)<< std::endl;
    return 0;
}