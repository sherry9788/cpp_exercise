#include <iostream>
#include <vector>
#include <string>

using namespace std;

class screen
{
    private:
        using pos = string::size_type;
        pos cursor = 0;
        pos height = 0;
        pos width = 0;
        string contents;
    public:
        screen() = default;
        screen(pos ht,pos wd,char c):
            height(ht),width(wd),contents(ht*wd,c) {}
        char get() const
        {
            return contents[cursor];
        }
        inline char get(pos ht,pos wd) const;
        screen &move(pos r,pos c);
};

int main()
{
    return 0;
}
