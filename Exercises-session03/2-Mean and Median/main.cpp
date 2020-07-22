#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>


const std::vector<double> import_values(std::string filename)
{
    double value = 0.0;
    std::ifstream file(filename);  //ifstream: Stream class to read from files
    std::string line;
    std::vector<double> values;

    while (file >> value)
    {
        values.push_back(value);
    }

    return values;
}


const double mean(std::vector<double> values)
{
    double sum = 0.0;

    for (double val : values)
    {
        sum += val;
    }

    return sum / values.size();
}

const double median(std::vector<double> values)
{
    std::sort(values.begin(), values.end());
    int size = values.size();
    double median;
    if (size % 2 == 0 )
    {
        median = (values[size / 2] + values[(size / 2) - 1]) / 2.0;
    }   //Input  : {1, 3, 4, 2, 6, 5, 8, 7}
        //Since number of elements are even, median
        //is average of 4th and 5th largest elements.
        //which means (4 + 5)/2 = 4.5
    else
    {
        median = values[size / 2];
    }
    return median;
}

int main()
{
    std::vector<double> temp = import_values("temperatures.txt");
    std::cout << "Mean: " << mean(temp) << std::endl;
    std::cout << "Median: " << median(temp) << std::endl;
    return 0;
}