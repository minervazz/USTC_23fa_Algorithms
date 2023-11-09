#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direction // 表b元素类型
{
    Up,
    Left,
    Up_Left,
};

vector<vector<int>> c; // 空间复杂度 O(m*n) 的算法的表c
vector<vector<Direction>> b; // 空间复杂度 O(m*n) 的算法的表b
vector<int> lcs2_1; // 空间复杂度 O(2*min(m,n)) 的算法的第一行向量
vector<int> lcs2_2; // 空间复杂度 O(2*min(m,n)) 的算法的第二行向量
vector<int> lcs3; // 空间复杂度 O(min(m,n)) 的算法的向量

void Print_LCS(const string& X, int m, int n)
{
    if (m == 0 || n == 0)
    {
        return;
    }
    if (b[m - 1][n - 1] == Up_Left)
    {
        Print_LCS(X, m - 1, n - 1); // 向左上方移动
        cout << X[m - 1]; // 打印相等的字符
    }
    else if (b[m - 1][n - 1] == Up)
    {
        Print_LCS(X, m - 1, n); // 向上方移动
    }
    else
    {
        Print_LCS(X, m, n - 1); // 向左移动
    }
    return;
}

// 空间复杂度 O(m*n) 的算法
int LCS1(const string& text1, const string& text2)
{
    int m, n;
    m = text1.size();
    n = text2.size();

    c.resize(m + 1, vector<int>(n + 1)); // 分配内存
    b.resize(m, vector<Direction>(n)); // 分配内存

    for (int i = 1; i < m + 1; i++)
    {
        c[i][0] = 0; // 初始化第一行
    }
    for (int j = 0; j < n + 1; j++)
    {
        c[0][j] = 0; // 初始化第一列
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // 转移方程
            if (text1[i] == text2[j])
            {
                c[i + 1][j + 1] = c[i][j] + 1;
                b[i][j] = Up_Left;
            }
            else if (c[i][j + 1] >= c[i + 1][j])
            {
                c[i + 1][j + 1] = c[i][j + 1];
                b[i][j] = Up;
            }
            else
            {
                c[i + 1][j + 1] = c[i + 1][j];
                b[i][j] = Left;
            }
        }
    }
    if (c[m][n]) // 若c[m][n]不为0，则打印LCS
    {
        cout << "LCS1:\"";
        Print_LCS(text1, m, n);
        cout << "\"";
    }

    return c[m][n];
}

// 空间复杂度 O(2*min(m,n)) 的算法
int LCS2(const string& text1, const string& text2)
{
    auto m = text1.size();
    auto n = text2.size();
    auto min = std::min(m, n); // 找最小值
    lcs2_1.resize(min + 1); // 分配内存
    lcs2_2.resize(min + 1); // 分配内存
    for (int i = 0; i < min + 1; i++)
    {
        lcs2_1[i] = 0; // 初始化第一行
    }
    lcs2_2[0] = 0; // 将最左侧为0当做已知
    if (m > n)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 转移方程
                if (text1[i] == text2[j])
                {
                    lcs2_2[j + 1] = lcs2_1[j] + 1;
                }
                else
                {
                    lcs2_2[j + 1] = std::max(lcs2_2[j], lcs2_1[j + 1]);
                }
            }
            std::swap(lcs2_1, lcs2_2); // 动态滚动数组
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (text1[j] == text2[i])
                {
                    lcs2_2[j + 1] = lcs2_1[j] + 1;
                }
                else
                {
                    lcs2_2[j + 1] = std::max(lcs2_2[j], lcs2_1[j + 1]);
                }
            }
            std::swap(lcs2_1, lcs2_2);
        }
    }
    return lcs2_2[min];
}

// 空间复杂度 O(min(m,n)) 的算法
int LCS3(const string& text1, const string& text2)
{
    auto m = text1.size();
    auto n = text2.size();
    auto min = std::min(m, n);
    lcs3.resize(min + 1); // 分配内存
    for (int i = 0; i < min + 1; i++)
    {
        lcs3[i] = 0;
    }
    if (m > n)
    {
        for (int i = 0; i < m; i++)
        {
            lcs3[0] = 0;
            for (int j = 0; j < n; j++)
            {
                // 转移方程
                if (text1[i] == text2[j])
                {
                    std::swap(lcs3[j], lcs3[0]);
                    lcs3[0]++;
                }
                else
                {
                    lcs3[j] = lcs3[0];
                    lcs3[0] = std::max(lcs3[j + 1], lcs3[0]);
                }
            }
            lcs3[n] = lcs3[0];
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            lcs3[0] = 0;
            for (int j = 0; j < m; j++)
            {
                if (text1[j] == text2[i])
                {
                    std::swap(lcs3[j], lcs3[0]);
                    lcs3[0]++;
                }
                else
                {
                    lcs3[j] = lcs3[0];
                    lcs3[0] = std::max(lcs3[j + 1], lcs3[0]);
                }
            }
            lcs3[m] = lcs3[0];
        }
    }
    return lcs3[min];
}

int main()
{
    string text1, text2;
    int length;
    freopen("data.txt", "r", stdin);
    cout << "text1=  ";
    cin >> text1;
    cout << text1;
    cout << "    ";
    cout << "text2=  ";
    cin >> text2;
    cout << text2 << endl;
    length = LCS1(text1, text2);
    cout << "    " << "Length:    ";
    cout << length << endl;
    length = LCS2(text1, text2);
    cout << "LCS2    " << "Length:    ";
    cout << length << endl;
    length = LCS3(text1, text2);
    cout << "LCS3    " << "Length:    ";
    cout << length << endl;
    return 0;
}
