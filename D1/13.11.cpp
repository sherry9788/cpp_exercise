 #include <string>

using namespace std;

class HasPtr {
public:
    HasPtr (string *Ps, int I):ps(Ps), i(I) {}
    HasPtr (const HasPtr &hp)  {ps = hp.ps; i = hp.i;}
    HasPtr& operator= (const HasPtr& hp)
    {
        string *Ps = new string(*hp.ps);
        delete ps;
        ps = Ps;
        i = hp.i;
        return *this;
    }
    ~HasPtr () {delete ps;}
private:
    string* ps;
    int i;
};

int main()
{
    return 0;
}
