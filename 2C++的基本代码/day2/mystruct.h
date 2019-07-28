#ifndef MYSTRUCT_H
#define MYSTRUCT_H
//结构体类型
#if 1
typedef struct stu
{
  int sno;
  char sex;
  short age;
}stu_t;
#endif
// C++ 类
#if 0
class STU
{
    int sno;
    char sex;
    short age;
};
#endif

class STU
{
private:
    int sno;  //私有的
public:
    char sex; //公有的 成员数据--属性
    int getSno()   //成员函数--行为
    {//类内函数
        return 2 * sno;
    }   //类的大小与函数无关
    void setSno(int no);
    //开放接口去访问私有成员--间接
    //隐藏了内部的细节
protected:
    short age;  //保护的
};

void test_struct_class();
void test2_class();

#endif // MYSTRUCT_H
