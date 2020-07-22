//The sieve of Eratosthenes is one of the most efficient ways to find all primes smaller than n
// when n is smaller than 10 million or so



/*memset() is used to fill a block of memory with a particular value.
The syntax of memset() function is as follows :

 ptr ==> Starting address of memory to be filled
 x   ==> Value to be filled
 n   ==> Number of bytes to be filled starting 
         from ptr to be filled  
                                void *memset(void *ptr, int x, size_t n);*/

#include <bits/stdc++.h> 
using namespace std; 
  
void SieveOfEratosthenes(int n) 
{ 
    // Create a boolean array "prime[0..n]" and initialize 
    // all entries it as true. A value in prime[i] will 
    // finally be false if i is Not a prime, else true. 
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    //Starting from p2, count up in increments of p
    //and mark each of these numbers greater than or equal to p2 itself in the list.
    //These numbers will be p(p+1), p(p+2), p(p+3), etc..
    for (int p=2; p*p<=n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p greater than or  
            // equal to the square of it 
            // numbers which are multiple of p and are 
            // less than p^2 are already been marked.  
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
  
    // Print all prime numbers 
    for (int p=2; p<=n; p++) 
       if (prime[p]==true) 
          cout << p << " "; 
} 
  
//  Program to test above function 
int main() 
{ 
    int n; 
    cout << "insert n:"<< endl; 
    cin>>n;
    SieveOfEratosthenes(n); 
    return 0; 
} 
