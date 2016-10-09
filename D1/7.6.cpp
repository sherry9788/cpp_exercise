#include <iostream>

using namespace std;

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
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.average_price();
    return os;
}

int main()
{
    Sales_data total;
    if (read(cin,total)){
        Sales_data trans;
        while (read(cin,trans))
            if (total.isbn() == trans.isbn())
            total.combine(trans);
            else{
                print(cout,total) << endl;
                total = trans;
            }
        print(cout,total);
    } else {
        cerr << "No data?" << endl;
    }
    return 0;
}
