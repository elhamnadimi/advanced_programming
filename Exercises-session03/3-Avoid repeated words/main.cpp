#include <iostream>
#include <string>
#include<vector>
using namespace std;

int main()
{
    vector<string> data;
  string name;
  int count=0;
  cout<<"Enter words and then insert a END to finish."<<endl;
  while(cin>>name)
  {
      data.push_back(name);
      count=count+1;
      if (name =="END") break;
  }
  int FoundSimilar=0;
  cout<<"Not-repeated Words are: "<<endl;
 for(int i=0; i<count-1; i++)
 {
    for(int j=i+1; j<count-1; j++)
     if (data[i]==data[j] )//&& data[i]!="repeat")
     {FoundSimilar=1; } //data[i]="repeat";}
    if( FoundSimilar==0 )//&& data[i]!="repeat")
    {cout<<data[i]<<endl;}
    else{
    FoundSimilar=0;}
 }
}