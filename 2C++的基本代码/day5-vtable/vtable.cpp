#include <iostream>
#include "vtable.h"
using namespace std;



#if 0
int main()
{
    //test_Base_vTable();
    //test_Derive_vTable();
    test_Derive1_vTable();
    return 0;
}
#endif

void test_Base_vTable()
{
    Base b;
    Func pFunc = NULL;

    cout << sizeof(b)<<endl;//4�����麯��ָ��
    cout << "�麯�����ַ��" << (int *)(&b) << endl;
    cout << "�麯����--��һ��������ַ" << (int *)*(int *)(&b) << endl;

    // Invoke the first virtual function
    //                (&b) == �����ַ
    //                (int *)&b ǿתΪ����ָ��
    //                    * (int *)&b ǰ4�ֽ�����-->ָ��һ������-�麯����
    //                 (int *)*(int *)(&b) �������׵�ַǿתΪint *����
    //              (int *)*(int *)(&b) + 0)
    //              (Func)*((int *)*(int *)(&b) + 0) �����ÿ��Ԫ�ض��Ǻ���ָ��
    pFunc = (Func)*((int *)*(int *)(&b) + 0);
    pFunc(); // b.f()

    pFunc = (Func)*((int *)*(int *)(&b) + 1);
    pFunc();    // b.g()

    pFunc = (Func)*((int *)*(int *)(&b) + 2);
    pFunc();    // b.h()

}


void test_Derive_vTable()
{
    Derive d;
    Func pFunc = NULL;

    int i;

    cout << "�麯�����ַ��" << (int *)(&d) << endl;
    cout << "�麯����--��һ��������ַ" << (int *)*(int *)(&d) << endl;

    for(i = 0; i < 10; i++)
    {
        pFunc = (Func)*((int *)*(int *)(&d) + i);

        if(pFunc == NULL)
            break;

        pFunc();
    }
    /*
    // Invoke the first virtual function
    pFunc = (Func)*((int *)*(int *)(&b) + 0);
    pFunc();

    pFunc = (Func)*((int *)*(int *)(&b) + 1);
    pFunc();

    pFunc = (Func)*((int *)*(int *)(&b) + 2);
    pFunc();
    */
}

void test_Derive1_vTable()
{
    Base *ptr;
    Base b;
    Derive d;

    Func pFunc = NULL;

    int i;

    cout << "Base " << endl;

    cout << "�麯�����ַ��" << (int *)(&b) << endl;
    cout << "�麯����--��һ��������ַ" << (int *)*(int *)(&b) << endl;

    for(i = 0; i < 3; i++)
    {
        pFunc = (Func)*((int *)*(int *)(&b) + i);

        //cout << "pFunc " << pFunc << endl;
        //if(pFunc == NULL)
        //    break;

        pFunc();
    }

    cout << endl << endl;
    cout << "Derive1 " << endl;

    cout << "�麯�����ַ��" << (int *)(&d) << endl;
    cout << "�麯����--��һ��������ַ" << (int *)*(int *)(&d) << endl;

    for(i = 0; i < 10; i++)
    {
        pFunc = (Func)*((int *)*(int *)(&d) + i);

        if(pFunc == NULL)
            break;

        pFunc();
    }

}
