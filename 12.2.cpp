#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct sb
{
public:
    sb();
    sb(initializer_list<string> ils):
        data(make_shared<vector<string> > (ils)) {}
    int sb_size()
    {
        return data -> size();
    }
    bool sb_empty()
    {
        return data -> empty();
    }
    string& sb_front() const;
    string& sb_back() const;
private:
    shared_ptr<vector<string> > data;
};

string& sb::sb_front() const
{
    return data -> front();
}

string& sb::sb_back() const
{
    return data -> back();
}

int main()
{
    return 0;
}
