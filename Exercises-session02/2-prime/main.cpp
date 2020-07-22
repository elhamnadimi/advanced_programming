#include <iostream>
#include <iomanip>      // std::setw

using namespace std;

int main()
{
    int i,j,count,MaxNum;
    int k=0;
    int a[100];
    cout << "Enter the number:  ";
    cin >> MaxNum;
    for(i = 1;i<=MaxNum;i++){
        count = 0;  // just for prime number count is zero
        for(j=2;j<=i/2;j++){
            if(i%j==0){
                count++;  //with this count we just point  numbers  that are not prime.
                break;
            }
        }

        if(count==0 && i!= 1){
            a[k]=i;

            cout << " a["<<k<<"]="<<a[k] << setw(2);
            k=k+1;}
    }
    return 0;
}