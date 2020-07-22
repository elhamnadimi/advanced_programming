#include<iostream>



void read_measure()
{
   std::string measure;
   std::string measure_converted;

   std::cout << "enter the value followed by the measure unit\n";
   double i ;
   
   std::cin >> measure;
   if(measure=="inch")
   {
    i = 0.0254*i;
    measure_converted = "m";
    std::cout << i << " " << measure_converted << std::endl;
   }  
   else if(measure=="m")
   {
    i = i/0.0254;
    measure_converted = "inch" ;
    std::cout << i << " " << measure_converted << std::endl;
   }
   else
   {
    std::cout << "something goes wrong with your pc\n";
   }
}


int main()
{
  read_measure();
}
