#include <iostream>
#include <string>

//write a function get_int that reads from stdin until a valid number is fed

using namespace std;

int main(){
    int x;
    cout << "Enter only integers\n";
    while(cin >> x){
    }
    if(!cin){
        cin.clear(); // clear error flags
        cin.ignore(100, '\n'); // ignores remainder of stream
        cout << "This is not an integer\n";
    }
    return 0;
}