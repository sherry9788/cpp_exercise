#include <iostream>
#include <fstream>

using namespace std;

struct Sales_data;
istream &read(istream &,Sales_data &);

struct Sales_data {
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    string isbn() const
    {
        return bookNo;
    }
    Sales_data& combine(const Sales_data&);
    double average_price() const;
    Sales_data() = default;
    Sales_data(istream &is)
    {
        read(is,*this);
    }
};

double Sales_data::average_price() const
{
    if(units_sold)
        return revenue/units_sold;
    else
        return 0.;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream &read(istream &is,Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

ostream &print(ostream &os,const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.average_price() << endl;
    return os;
}

int main()
{
    Sales_data total;
    ifstream inf("sherry.txt");
    ofstream ouf("sherry1.txt",fstream::app);
    if (read(inf,total)){
        Sales_data trans;
        while (read(inf,trans))
            if (total.isbn() == trans.isbn())
            total.combine(trans);
            else{
                print(ouf,total) << endl;
                total = trans;
            }
        print(ouf,total);
    } else {
        cerr << "No data?" << endl;
    }
    return 0;
}
