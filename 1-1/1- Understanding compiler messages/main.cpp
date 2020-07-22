
#include <iostream>
using namespace std;

int main()
{
    int firstNumber, secondNumber, sumOfTwoNumbers;
    
    cout << "Enter two integers: ";
    cin >> firstNumber >> secondNumber;

    // sum of two numbers in stored in variable sumOfTwoNumbers
    sumOfTwoNumbers = firstNumber + secondNumber;

    // Prints sum 
    cout << firstNumber << " + " <<  secondNumber << " = " << sumOfTwoNumbers;     

    return 0;
}

//forget to #include <iostream>    In order to read or write to the standard input/output streams you need to include it.  cin is not decleard in this scope
//forget to put ; expected ; after return, we should put ; afetr every function, defenition
//[Error] two or more data types in declaration of 'firstNumber'
//typos in variable name: if we put char instead of int the final sum up bring a char insted of summ of two int 
//typos in function name: should be as same as variable type
//pass wrong type of argument to a function : for example if we sumup two decleard number with one not decleard number we will get error in order to decleration of third number too
//or wen we 





