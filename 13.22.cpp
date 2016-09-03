#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr(const string& s = string()) : ps(new string(s)), i(0)
    {
    }
    HasPtr(const HasPtr& hp) : ps(new string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr& hp)
    {
        auto new_p = new string(*hp.ps);
        delete ps;
        ps = new_p;
        i = hp.i;
        return *this;
    }
    ~HasPtr() { delete ps; }
private:
    string* ps;
    int i;
};

int main()
{
    return 0;
}
