#include<iostream>

using namespace std;
template <typename T>

// Request block of memory

T* allocation (std::size_t N){   //writing a function named allocation with input N (elemnts of array)
    // and output a pointer

    T* value  = NULL;      // Pointer initialized with null
    value  = new T[N];    // Request memory for the variable

    for(std::size_t i{0};i<N;i++){  // this for is for getting and returning value of array
        std::cin>>value[i];
    }
    return value;
}


template <typename T>
void reverse(T* value, int N){ //writing reverse function , it is void type becuse it does not have any return
    //it has two input , one is pionter to array and one is size of array

    for(int i{N-1};i>=0;i=i-1){   //using size_t is because after 0 an unsigned int goes to his maximum
        std::cout<<value[i]<<std::endl; // with this for we print value of array , revercely
    }
}
int main(){

    std::size_t N;
    int* value;

    std::cout<<" insert size array"<<std::endl;

    std::cin>>N;
    std::cout<<" insert elements of array"<<std::endl;

    value=allocation<int>(N);

    reverse(value,N);

    delete[]value;  //free the dynamic memory
}


