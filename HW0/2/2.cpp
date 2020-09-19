// 2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>

using namespace std;

int delet(int (*A)[1000], int len)
{
    int num, tmp, i;
    cout << "Delete which integer? ";
    cin >> num;

    for (i = 0; i < len; i++) {
        if (num == (*A)[i]) {
            for (int j = i; j < len - 1; j++) {
                (*A)[j] = (*A)[j + 1];
            }
            i--;
            len--;
        }
    }
    return len;
}

int input(int (*A)[1000], int len)
{
    int num, tmp, i;
    cout << "Input an integer ? ";
    cin >> num;

    for (i = 0; i < len; i++) {
        if (num < (*A)[i]) break;
    }

    for (int j = i; j <= len; j++) {
        tmp = (*A)[j];
        (*A)[j] = num;
        num = tmp;
    }
    

    return ++len;
}

int main()
{
    char c;
    int A[1000];
    int len = 0;

    while (true) {
        int flag = 1;
        cout << "Input or Delete? ";
        cin >> c;
        switch (c) {
            case 'D':
                len = delet(&A, len);
                break;
            case 'I':
                len = input(&A, len);
                break;
            default:
                flag = 0;
        }
        if (flag) {
            for (int i = 0; i < len; i++) {
                cout << *(A + i) << " ";
            }
            cout << "\n";
        }
    }


}
