#include <iostream>
#include <cmath>

int main(){

    for(int a =0 ; a>=-50000 ; a-=100 ){
        std::cout << "num = " << a << '\t'
                  << "log10 = " << log10(a) << std::endl;
    }
    return 0;

}