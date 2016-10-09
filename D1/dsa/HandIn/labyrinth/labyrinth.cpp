#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>

//#define PRINT
using namespace std;

bool solved = false;
bool view = true;

template <typename T> class link
{
public:
//data
    T info; //info 是循环链表的储存信息，写成了模板类方便在使用过程中更改数据类型
    int loop_num; //loop_num 是这个循环链表的链结数，默认为1
    link *prev, *next;  //prev 是指向上一个 link 的指针， next 指向下一个 link
    bool isDel = 0; //isDel 设置的目的是为了在析构函数中使用，默认为0
//function
    link() = default;

    link(int n_loop_num, T n_info = T(), link *n_prev = 0, link *n_next = 0)
    {//构造函数
        info = n_info;
        prev = n_prev;
        next = n_next;
        loop_num = n_loop_num;
 //   cerr << "Construction success" << endl;
    }

    ~link()
    {//析构函数可以一次将 loop 中的所有 links 全部析构。
        if(isDel == 0)
        {
            isDel = 1;
            delete next;
        }else{
   //         cerr << "Destruction Success" << endl;
        }
        return;
    }
    
    link<T> &operator=(link<T> &Link)
    {//这是一个深层复制构造函数
        create_loop(Link.loop_num);
        link<T> *temp = this;
        link<T> *ini = &Link;
        for(int i = 0; i < loop_num; ++ i)
        {
            temp->info = ini->info;
            ini = ini->next;
            temp = temp->next;
        }
    }

    link<T> *create_loop(int num)
    {//创建一个循环链表并定位到第一个链结上
        if(num < 2)
        {
            cerr << "Error" << endl;
            return this;
        }
        loop_num = num;
        link<T> *temp_1 = new link<T>(num), *temp_2 = 0;
        temp_1->prev = this;
        this->next = temp_1;
        for(int i = 0; i < num - 2; ++ i)
        {
            temp_2 = new link<T>(num);
            temp_1->next = temp_2;
            temp_2->prev = temp_1;
            temp_1 = temp_2;
        }
        temp_1->next = this;
        this->prev = temp_1;
        return this;
    }

    link<T>(const link<T> &CL)
    {
        CL = *this;
    }

    bool append(){
        link<T> *append_link = new link<T>();
        if(!append_link){
            cerr << "Out of space" << endl;
            return false;
        }
        append_link->loop_num = loop_num;
        append_link->isDel = 0;
        append_link->prev = this;
        append_link->next = this->next;
        append_link->prev->next = append_link;
        append_link->next->prev = append_link;
        return true;
    }
};

template <typename T>
struct queue
{
//data
    link<T> *f, *r;
    size_t Max;
    size_t n;
//function
    queue<T>() = delete;

    queue<T>(int n_Max = 100)
    {
        Max = n_Max + 1;
        r = new link<T>();
        r->create_loop(Max);
        f = r;
        n = 0;
    }

    bool isEmpty()
    {
        return r == f;
    }

    bool Enter(const T &data)
    {
        if(r->next == f){
            int new_loop_num = r->loop_num + 100;
            auto ptr = r;
            for(;ptr != r; ptr = ptr->next)
                ptr->loop_num = new_loop_num;
            for(int i = 0; i < 100; ++ i){
          //      if(!ptr->append())
                    return false;
            }
            Max += 100;
        }
        f = f->prev;
        f->info = data;
        ++ n;
        return true;
    }

    bool Kick()
    {
        if(isEmpty())
            return false;

        r = r->prev;
        -- n;
        return true;
    }

    T &info()
    {
        assert(!isEmpty());
        return r->prev->info;
    }

    ~queue<T>()
    {
        delete r;
    }

    queue<T> &operator=(queue<T> &Q)
    {
        delete r;
        Max = Q.Max;
        f = new link<T>;
        *f = *Q.f;
        r = f;
        for(int i = 0; i < Q.n; ++ i)
            r = r->next;
        return Q;
    }

    queue<T>(const queue<T> &Q)
    {
        Max = Q.Max;
        f = new link<T>;
        *f = *Q.f;
        r = f;
        for(int i = 0; i < Q.n; ++ i)
            r = r->next;
    }
};

template <typename T>
struct Node
{
    T info;
    Node *next;

    Node(T x, Node *n_next)
    {
        info = x;
        next = n_next;
    }

    ~Node() = default;
};

template <typename T>
struct Stack
{
    Node<T> *top = nullptr;

    Stack() = default;

    ~Stack()
    {
        if(!isEmpty())
            pop();
    }

    Stack<T> &operator=(Stack<T> &ST)
    {
        if(!isEmpty())
            pop();
        if(!ST.top)
            return *this;
        vector<T> TV;
        Node<T> *tmp = ST.top;
        while(tmp)
        {
            TV.push_back(tmp->info);
            tmp = tmp->next;
        }
        auto iter = TV.end() - 1;
        for(; iter != TV.begin(); -- iter)
            push(*iter);
        
        push(*iter);
        return *this;
    }

    bool push(T x)
    {
        Node<T> *p = new Node<T>(x, this->top);
        if(p == nullptr)
        {
            cerr << "Out of space" << endl;
            return false;
        }
        else
            this->top = p;

        return true;
    }

    bool pop()
    {
        if(isEmpty())
            return false;
        Node<T> *p = top;
        top = p->next;
        delete p;

        return true;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    T &info()
    {
        return top->info;
    }
    
    Stack<T>(const Stack<T> &ST)
    {
        if(!ST.top)
            return;
        vector<T> TV;
        Node<T> *tmp = ST.top;
        while(tmp)
        {
            TV.push_back(tmp->info);
            tmp = tmp->next;
        }
        auto iter = TV.end() - 1;
        for(; iter != TV.begin(); -- iter)
            push(*iter);
        
        push(*iter);
    }

};

struct grid
{
    int x = 0, y = 0;
    int i;
    
    grid(int n_i = 0)
    {
        i = n_i;
    }

    grid(int n_x, int n_y, int n_i):
        x(n_x), y(n_y), i(n_i){}

    ~grid() = default;

    grid &operator=(grid &ret)
    {
        x = ret.x;
        y = ret.y;
        i = ret.i;
        return *this;
    }

    int coor(int n)
    {
        return x + n * y;
    }
};

struct Lab
{
//data
public:
    grid *Grid;
    int n;
    int x, y;

//function
public:
    Lab(){
        Grid = nullptr;
        n = 0;
        x = 0;
        y = 0;
    }

    Lab(grid *g, int n_n){
        x = 0;
        y = 0;
        n = n_n;
        Grid = new grid[n * n];
        for(int i = 0; i < n * n; ++ i)
            Grid[i] = g[i];
    }

    Lab &operator=(const Lab &L){
        x = L.x;
        y = L.y;
        n = L.n;
        if(Grid)
            delete []Grid;
        Grid = new grid[n * n];
        for(int i = 0; i < n * n; ++ i){
            Grid[i] = L.Grid[i];
        }
        return *this;
    }

    Lab(const Lab &L){
        x = L.x;
        y = L.y;
        n = L.n;
        Grid = new grid[n * n];
        for(int i = 0; i < n * n; ++ i){
            Grid[i] = L.Grid[i];
        }
    }

    int coor(){
        return x + y * n;
    }

    Lab east(){
        Lab new_Lab(*this);
        new_Lab.Grid[new_Lab.coor() + 1].i = 2;
        ++ new_Lab.x;
        return new_Lab;
    }
    
    Lab west(){
        Lab new_Lab(*this);
        new_Lab.Grid[new_Lab.coor() - 1].i = 2;
        -- new_Lab.x;
        return new_Lab;
    }

    Lab south(){
        Lab new_Lab(*this);
        new_Lab.Grid[new_Lab.coor() + n].i = 2;
        ++ new_Lab.y;
        return new_Lab;
    }

    Lab north(){
        Lab new_Lab(*this);
        new_Lab.Grid[new_Lab.coor() - n].i = 2;
        -- new_Lab.y;
        return new_Lab;
    }

    ~Lab(){
        if(Grid)
            delete []Grid;
    }
};

void printlab(grid *lab, int n)
{
        for(int j = 0; j < n; ++ j)
        {
            for(int i = 0; i < n; ++ i)
                if(lab[i + j * n].i == 0)
                    cout << "  ";
                else if(lab[i + j * n].i == 1)
                    cout << "X ";
                else if(lab[i + j * n].i == 2)
                    cout << "o ";
                else
                    cout << "  ";
            cout << endl;
        }
}

void printlab(const Lab &L){
    printlab(L.Grid, L.n);
}

void create_labrinth(grid *lab, int n,  bool view = true, int *in = nullptr)
{
    srand(time(NULL));
    if(in == nullptr)
        for(int i = 0; i < n; ++ i)
            for(int j = 0; j < n; ++ j)
                if(rand() % 10 < 3)
                    lab[i + j * n].i = 1;
                else
                    lab[i + j * n].i = 0;
    else
        for(int i = 0; i < n * n; ++ i)
            lab[i].i = in[i];
    
    lab[0].i = 0;
    lab[n * n - 1].i = 0;
    if(view)
    {
        printlab(lab, n);
    }

    for(int i = 0; i < n; ++ i)
       for(int j = 0; j < n; ++ j)
       {
          lab[i + j * n].x = i; 
          lab[i + j * n].y = j;
       }
}

void solve_lab(grid *lab, int n)
{
    Stack<grid *> SL;
    SL.push(&lab[0]);
    lab[0].i = 2;
    while(!SL.isEmpty() && SL.info()->coor(n) != n * n - 1)
    {
        if(SL.info()->x < n - 1 && lab[SL.info()->coor(n) + 1].i == 0)
        {
            SL.push(&lab[SL.info()->coor(n) + 1]);
            SL.info()->i = 2;
        }
        else if(SL.info()->y < n - 1 && lab[SL.info()->coor(n) + n].i == 0)
        {
            SL.push(&lab[SL.info()->coor(n) + n]);
            SL.info()->i = 2;
        }
        else if(SL.info()->x > 0 && lab[SL.info()->coor(n) - 1].i == 0)
        {
            SL.push(&lab[SL.info()->coor(n) - 1]);
            SL.info()->i = 2;
        }
        else if(SL.info()->y > 0 && lab[SL.info()->coor(n) - n].i == 0)
        {
            SL.push(&lab[SL.info()->coor(n) - n]);
            SL.info()->i = 2;
        }
        else
        {
            SL.pop();
        }
    }

    if(SL.isEmpty())
        cerr << "No Route" << endl;
    else
    {
        while(!SL.isEmpty())
        {
            cerr << SL.info()->x << " " << SL.info()->y << endl;
            SL.pop();
        }
    }

}

void recursion(grid *lab, int n, int x = 0, int y = 0)
{
    if(x == n - 1 && y == n - 1)
    {
        cerr << "The labrinth can be solved" << endl;
        solved = true;
        return;
    }

    if(x < n - 1 && lab[x + 1 + y * n].i == 0)
    {
        lab[x - 1 + y * n].i = 2;
        recursion(lab, n, x + 1, y);
        if(solved)
        {
            cerr << "Go Right" << endl;
            return;
        }
    }
    
    if(y < n - 1 && lab[x + y * n + n].i == 0)
    {
        lab[x + y * n + n].i = 2;
        recursion(lab, n, x, y + 1);
        if(solved)
        {
            cerr << "Go Down" << endl;
            return;
        }
    }
    
    if(x > 0 && lab[x - 1 + y * n].i == 0)
    {
        lab[x - 1 + y * n].i = 2;
        recursion(lab, n, x - 1, y);
        if(solved)
        {
            cerr << "Go Left" << endl;
            return;
        }
    }
    
    if(y > 0 && lab[x + y * n - n].i == 0)
    {
        lab[x + y * n - n].i = 2;
        recursion(lab, n, x, y - 1);
        if(solved)
        {
            cerr << "Go Up" << endl;
            return;
        }
    }

    if(x == 0 && y == 0 && !solved && lab[n].i != 0 && lab[1].i != 0)
        cerr << "No route" << endl;
    
    return;    
}

void shortest(grid *lab, int n)
{
    queue<grid *> *QL = new queue<grid *>(n * n);
    QL->Enter(&lab[0]);
    lab[0].i = 3;
    grid *route = new grid[n * n];
    while(!QL->isEmpty() && QL->info()->coor(n) != n * n - 1)
    {
        grid *temp = QL->info();
        QL->Kick();
        int temp_x = temp->x;
        int temp_y = temp->y;
        if(temp_x < n - 1 && lab[temp_x + 1 + temp_y * n].i == 0)
        {
            QL->Enter(&lab[temp_x + 1 + temp_y * n]);
            lab[temp_x + 1 + temp_y * n].i = 3;
            route[temp_x + 1 + temp_y * n].x = temp_x;
            route[temp_x + 1 + temp_y * n].y = temp_y;
        }
        if(temp_y < n - 1 && lab[temp_x + temp_y * n + n].i == 0)
        {
            QL->Enter(&lab[temp_x + temp_y * n + n]);
            lab[temp_x + temp_y * n + n].i = 3;
            route[temp_x + temp_y * n + n].x = temp_x;
            route[temp_x + temp_y * n + n].y = temp_y;
        }
        if(temp_x > 0 && lab[temp_x - 1 + temp_y * n].i == 0)
        {
            QL->Enter(&lab[temp_x - 1 + temp_y * n]);
            lab[temp_x - 1 + temp_y * n].i = 3;
            route[temp_x - 1 + temp_y * n].x = temp_x;
            route[temp_x - 1 + temp_y * n].y = temp_y;
        }
        if(temp_y > 0 && lab[temp_x + temp_y * n - n].i == 0)
        {
            QL->Enter(&lab[temp_x + temp_y * n - n]);
            lab[temp_x + temp_y * n - n].i = 3;
            route[temp_x + temp_y * n - n].x = temp_x;
            route[temp_x + temp_y * n - n].y = temp_y;
        }
    }

    
    if(!QL->isEmpty())
    {
        cerr << "The Labrinth Can Be Solved" << endl;
        int x = n - 1, y = n - 1;
        int coor = 1;
#ifdef PRINT
        while(coor != 0)
        {
            cerr << x << ' ' << y << endl;
            coor = x + y * n;
            x = route[coor].x;
            y = route[coor].y;
        }
#else
        while(coor != 0)
        {
            coor = x + y * n;
            lab[coor].i = 2;
            x = route[coor].x;
            y = route[coor].y;
        }
        printlab(lab, n);
#endif

    }
    else
        cerr << "No Route" << endl;
    

    delete QL;
    delete []route;
}

void all_route(grid *lab, int n)
{
    Lab ini(lab, n);
    ini.Grid[0].i = 2;
    queue<Lab> QL(100);
    QL.Enter(ini);
    vector<Lab> vL;
    while(!QL.isEmpty()){
       auto tmp = QL.info();
       QL.Kick(); 
       if(tmp.coor() == n * n - 1){
           vL.push_back(tmp);
           continue;
       }

       if(tmp.x < n - 1 && tmp.Grid[tmp.coor() + 1].i == 0)
           QL.Enter(tmp.east());

       if(tmp.x > 0 && tmp.Grid[tmp.coor() - 1].i == 0)
           QL.Enter(tmp.west());

       if(tmp.y < n - 1 && tmp.Grid[tmp.coor() + n].i == 0)
           QL.Enter(tmp.south());

       if(tmp.y > 0 && tmp.Grid[tmp.coor() - n].i == 0)
           QL.Enter(tmp.north());
    }
    
    if(vL.empty())
        cerr << "No Route" << endl;
    else{
        cerr << "The Labrinth Can Be Solved" << endl;
        int i;
        cerr << "Do you want to print the labrinth? 1/0" << endl;
        do{
            cin >> i;
        }while(i != 0 && i != 1);

        if(i == 1){
            for(auto iter = vL.begin(); iter != vL.end(); ++ iter){
                printlab(*iter);
                system("pause");
            }
        }else{
            cerr << vL.size() << endl;
        }
    }
}

int main()
{
    int n;
loop:
    cin >> n;
    grid *g = new grid[n * n];
    create_labrinth(g, n);
    all_route(g, n);
    goto loop;
    cerr << 1 << endl;
    return 0;
}

/*
    while(!(sol.info().x == n - 1 && sol.info().y == n - 1))
    {
        if(sol.info().y < n - 1 && lab[sol.info().coor(n)].info[1] == 0
               && lab[sol.info().coor(n) + n].i == 0)
        {
            lab[sol.info().coor(n)].info[1] = 1;
            sol.push(lab[sol.info().coor(n) + n]);
#ifdef PRINT
            cout << "DOWN" << endl;
#endif
        } 
        else if(sol.info().x < n - 1 && lab[sol.info().coor(n)].info[3] == 0
               && lab[sol.info().coor(n) + 1].i == 0)
        {
            lab[sol.info().coor(n)].info[3] = 1;
            sol.push(lab[sol.info().coor(n) + 1]);
#ifdef PRINT
            cout << "RIGHT" << endl;
#endif
        }
        else if(sol.info().x > 0 && lab[sol.info().coor(n)].info[2] == 0 
                && lab[sol.info().coor(n) - 1].i == 0)
        {
            lab[sol.info().coor(n)].info[2] = 1;
            sol.push(lab[sol.info().coor(n) - 1]);
#ifdef PRINT
            cout << "LEFT" << endl;
#endif
        }            
        else if(sol.info().y > 0 && lab[sol.info().coor(n)].info[0] == 0 
                && lab[sol.info().coor(n) - n].i == 0)
        {
            lab[sol.info().coor(n)].info[0] = 1;
            sol.push(lab[sol.info().coor(n) - n]);
#ifdef  COUT
            cout << "UP" << endl;
#endif
        }
        else
        {
            sol.pop();
#ifdef PRINT
            cout << "BACK" << endl;
#endif
        }

        if(sol.isEmpty())
        {
            return;
        }
#ifdef PRINT
        cout << sol.info().x << ' ' << sol.info().y << ' ' << endl;
#endif
    }

    cout << "This labrinth Can Be Solved" << endl;

    while(!(sol.isEmpty()))
    {
        lab[sol.info().coor(n)].i += 2;
        sol.pop();
    }

    if(view)
        printlab(lab, n);
        */
