#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

using namespace std;

struct Res;

struct TextQuery
{
private:
    shared_ptr<vector<string> > vs;
    map<string, shared_ptr<set<int> > > cnt;
public:
    TextQuery (ifstream& infile)
    {
        string s;
        while (getline(infile, s))
        {
            vs -> push_back(s);
            istringstream line(s);
            string word;
            while (line >> word)
            {
                auto &lines = cnt[word];
                if (!lines)
                    lines.reset(new set<int>);
                lines -> insert(vs->size()+1);
            }
        }
    }

    Res query(string);


};

struct Res
{
    Res(string s, shared_ptr<set<int> >sp, shared_ptr<vector<string> > vp):
        sought(s), lines(sp), f(vp) {}
    string sought;
    shared_ptr<set<int> > lines;
    shared_ptr<vector<string> > f;
};

Res TextQuery::query (string s)
{
    static shared_ptr<set<int> > nodata(new set<int>);
    auto loc = cnt.find(s);
    if(loc == cnt.end())
        return Res(s, nodata, vs);
    else
        return Res(s, loc->second, vs);
}



void print(Res res)
{
    cout << res.sought << " " << res.lines->size() << " ";
}

void runQuery (ifstream &infile)
{
    TextQuery tq(infile);
    while(1)
    {
        cout << "Enter the word to look for: " << endl;
        string str;
        if (!(cin >> str))
            break;
        print(tq.query(str));
    }
}

int main()
{
    return 0;
}
