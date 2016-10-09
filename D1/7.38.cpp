#include <iostream>
#include <vector>
#include <string>

using namespace std;

class screen;

class windows_mgr
{
    public:
        typedef vector<screen>::size_type ScreenIndex;
        void clear(ScreenIndex);
    private:
        vector<screen> screens;
};

class screen
{
    friend void windows_mgr::clear(ScreenIndex);
    private:
        using pos = string::size_type;
        pos cursor = 0;
        pos height = 0;
        pos width = 0;
        string contents;
        void do_display(ostream &os) const
        {
            for (int i = 0;i < height;++ i){
                for (int j = 0;j < width;++ j)
                    cout << contents[i*width + j];
                cout << endl;
            }
        }
    public:
        screen() = default;
        screen(pos ht,pos wd,char c):
            height(ht),width(wd),contents(ht*wd,c) {}
        screen(pos ht,pos wd):
            height(ht),width(wd),contents(ht*wd,' ') {}
        screen(istream& = cin);
        char get() const
        {
            return contents[cursor];
        }
        inline char get(pos ht,pos wd) const;
        screen &move(pos r,pos c);
        screen &set(char c)
        {
            contents[cursor] = c;
            return *this;
        }
        screen &set(pos r,pos col,char c)
        {
            contents[width*r + col] = c;
            return *this;
        }
        screen &display(ostream &os)
        {
            do_display(os);
            return *this;
        }
        const screen &display(ostream &os) const
        {
            do_display(os);
            return *this;
        }
};

void windows_mgr::clear(ScreenIndex i)
{
    screen &s = screens[i];
    s.contents = string (s.height * s.width,' ');
}

inline screen &screen::move(pos r,pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char screen::get(pos r,pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

int main()
{
    screen myscreen(5,5,'x');
    myscreen.move(4,0).set('#').display(cout);
    cout << endl;
    const screen blank(10,10);
    blank.display(cout);
    return 0;
}

