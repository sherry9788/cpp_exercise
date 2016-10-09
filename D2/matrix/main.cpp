/*
 * 学号:1500011398
 * 姓名:秦光辉
 * 说明:
 *     题目中要求的任务已经都完成,分散在各个类中.各个类均有注释,可供查看.
 *     在我认为不合理的要求处(如分母输入为0),我用了assert处理.
 *     所有的类均有构造函数(默认构造+赋值构造+其他),析构函数和赋值运算符重载.
 *     可以使用const的地方均使用了const,可以使用unsigned的地方均使用了
 * unsigned.
 *     Matrix支持的构造函数除了默认构造函数以外,还有用vector构造,用输入流构造,
 * 用数组构造和用列表构造.
 *     矩阵的不等于意义不明,我按照自己的理解做了一个.分数类的所有不等于重载我
 * 都写了.
 *     代码一共1350行(不加main.cpp).
 */

#include "matrix.h"

int main()
{
	std::vector<std::vector<frac> > f1;
	std::vector<std::vector<frac> > f2;
	std::vector<std::vector<frac> > f3;
	std::vector<std::vector<frac> > f4;

	f1.push_back(std::vector<frac>{frac(1, 2), frac(3, 4), frac(1, 3)});
	f1.push_back(std::vector<frac>{frac(4, 2), frac(1, 4), frac(5, 2)});
	f1.push_back(std::vector<frac>{frac(3, 2), frac(3, 2), frac(3, 4)});

	Matrix<frac> m1(f1);
	
	f2.push_back(std::vector<frac>{frac(4, 13), frac(2, 17)});
	f2.push_back(std::vector<frac>{frac(2, 11), frac(4, 33)});
	f2.push_back(std::vector<frac>{frac(1, 2), frac(4, 2)});

	Matrix<frac> m2(f2);

	f3.push_back(std::vector<frac>{frac(1, 11), frac(1, 17), frac(2, 33)});
	f3.push_back(std::vector<frac>{frac(32, 11), frac(4, 23), frac(3, 22)});

	Matrix<frac> m3(f3);

	f4.push_back(std::vector<frac>{frac(1, 11), frac(1, 17)});
	f4.push_back(std::vector<frac>{frac(32, 11), frac(4, 23)});

	Matrix<frac> m4(f4);

	cout << m1 << endl;
	cout << m2 << endl;
	cout << m3 << endl;

	cout << m1 + m2 * m3 << endl;
    cout << m1.inv() * m1 << endl;

    Matrix<int> m5{{1, 2}, {3, 4}};
    cout << m5 << endl;

    Matrix<int> m6(std::cin);
    cout << m6 << endl;

    int *n_data = new int[9];
    for(int i = 0; i < 3; ++ i)
        for(int j = 0; j < 3; ++ j)
            n_data[i * 3 + j] = i + j;
    Matrix<int> m7(3, 3, n_data);
    cout << m7 << endl;
	return 0;
}
