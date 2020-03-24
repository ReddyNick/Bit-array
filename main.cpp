#include <bitarray.h>
#include <iostream>
#include <vector>

int main()
{
    try{
        bit_array a(5);
        bit_array b;
        std::cout << a.firstset(0) << std::endl;

        a.set(51, 1);
        a.set(102, 1);

        std::cout << a.check(10) << std::endl;
        std::cout << a.check(102) << std::endl;

        std::cout << "firstset(32) " << a.firstset(32) << std::endl;
        std::cout << "firstset(52) " << a.firstset(52) << std::endl;
        std::cout << a.firstclear(0) << std::endl; 

        bit_array::iterator it = a.begin();

        if (it != b.begin())
        {
            printf("a_iter != b_iter\n");
        }

        it.check();

        while (it != a.end()){
            it.set(1);
            ++it;
        }

        std::cout << a.firstclear(0) << std::endl; 
        a.set(112, 0);
        std::cout << a.firstclear(0) << std::endl; 


        a.resize(3);
        std::cout << a.check(51) << std::endl;
        std::cout << a.size() << std::endl;

        a.resize(0);
        std::cout << a.size() << std::endl;
    }
    
    catch(std::bad_alloc& exc){
        std::cout << "bad_alloc\n";
        return -1;
    }
    
    return 0;
}
