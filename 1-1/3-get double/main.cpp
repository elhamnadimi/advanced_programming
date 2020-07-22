#include <iostream>
#include <string>

//write a function get_double that reads from stdin until a valid number is fed.

using namespace std;

int main(){
    double x;
    cout << "Enter only numbers\n";
    while(cin >> x){
    }
    if(!cin){
        cin.clear(); // clear error flags
        cin.ignore(100, '\n'); // ignores remainder of stream
        cout << "This is not a number\n";
    }
    return 0;
}