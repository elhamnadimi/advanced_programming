#include<iostream>
//Need for Enum Class over Enum Type:
//Below are some of the reasons as to what are the limitations of
// Enum Type and why we need Enu// m Class to cover them.
// two enumeration cannot share the same names
//No variable can have a name which is already in some enumeration

//ENUM CLASS:
//Class enum doesn’t allow implicit conversion to int,
// and also doesn’t compare enumerators from different enumerations.
//enum class EnumName{ Value1, Value2, ... ValueN};

enum class monthclass{January, February, March, April, May, June, July, August, September, October, November, December};

class Date{

    void add_day();
    int month_size();
    void add_month();

public:
    int Day, Year;
    monthclass Month;

    Date(int, monthclass, int);
    ~Date(){};

    int day(){
        return Day;
    }

    monthclass month(){
        return Month;
    }

    int year(){
        return Year;
    }

    void add_days(const unsigned);
    void add_months(const unsigned);
};

Date::Date(int vday,monthclass vmonth,int vyear):

        Day{vday},Month{vmonth},Year{vyear}
{
    ;
}
//switch(expression) {
//  case x:
//    // code block
//    break;
//  case y:
//    // code block
//    break;
//  default:
//    // code block
//}
///add a month
void Date::add_month(){
    switch(Month){

        case monthclass::January: Month=monthclass::February;break;

        case monthclass::February: Month=monthclass::March;break;

        case monthclass::March: Month=monthclass::April;break;

        case monthclass::April: Month=monthclass::May;break;

        case monthclass::May: Month=monthclass::June;break;

        case monthclass::June: Month=monthclass::July;break;

        case monthclass::July: Month=monthclass::August;break;

        case monthclass::August: Month=monthclass::September;break;

        case monthclass::September: Month=monthclass::October;break;

        case monthclass::October: Month=monthclass::November;break;

        case monthclass::November: Month=monthclass::December;break;

        case monthclass::December: Month=monthclass::January;Year=Year+1;break;

        default:
            std::cout<<"Something is wrong"<<std::endl;
            break;
    }
}
///adding months
void Date::add_months(const unsigned n){
    for(int i{0};i<n;i++){
        add_month();
    }
}
//recognizing the number of days in a month
int Date::month_size(){
    switch(Month){
        case monthclass::November: case monthclass::April: case monthclass::June: case monthclass::September:return 30;

            case monthclass::February: if(Year%4==0&&Year%400!=0){return 29;} return 28;

            case monthclass::January: case monthclass::March: case monthclass::May: case monthclass::July:
            case monthclass::August: case monthclass::October: case monthclass::December: return 31;

        default:
            std::cout<<"Nope"<<std::endl;
            break;
    }
}
//add a single day
void Date::add_day(){

    if(Day==month_size()){ //if last day of the month
        Day=1;
        add_month();			//change month
        return;
    }
    Day=Day+1;
}
void Date::add_days(unsigned const n){

    for(int i{0};i<n;i++){
        add_day();
    }
}
// Add_year not implemented: it'd take the same effort to either call the function or write Year=Year+n.
//operators of == and !=

//returnType operator op(type1 lhs, type2 rhs);
//returnType is the type of object returned operator is a keyword
//op is the symbol for the operator
//lhs is the formal parameter for the operand on the left hand side of the expression
//rhs is the formal parameter for the operand on the right hand side of the expression

bool operator==(const Date& lhs, const Date& rhs){
    if(lhs.Month==rhs.Month && lhs.Year==rhs.Year && lhs.Day==rhs.Day){
        return true;
    }
    return false;
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs==rhs);
}
//The class istream is used for input and ostream for the output.
//The istream class: This class is responsible for handling input stream.
// It provides number of function for handling chars, strings and objects such as get,
// getline, read, ignore, putback etc..

//The ostream class: This class is responsible for handling output stream.
//It provides number of function for handling chars, strings and objects such as write, put etc..

//printing
std::ostream& operator<<(std::ostream& os, const monthclass& m){

    os<<int(m)+1;

}
//Output streams use the insertion (<<) operator for standard types.
// You can also overload the << operator for your own classes.
std::ostream& operator<<(std::ostream& os, const Date& d){

    os<<d.Day<<"/"<<d.Month<<"/"<<d.Year<<std::endl;
    os<<"dd/mm/yy";
}
int main(){

    Date data{28,monthclass::February,1604};

    data.add_days(1);

    std::cout<< data<<std::endl;
}