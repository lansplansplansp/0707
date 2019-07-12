#include <stdlib.h>

using namespace std;

//封装一个计数功能的对象CRefObject:
class CRefObject
{
public:
    CRefObject()
    {
        m_nRefCount = 0;
    }

    int GetRefCount() const
    {
        return m_nRefCount;
    }

    int AddRefCount()
    {
        return ++m_nRefCount;
    }

    int SubRefCount()
    {
        return --m_nRefCount;
    }

    void ResetRefCount()
    {
        m_nRefCount = 0;
    }

private:
    int    m_nRefCount;
};
//封装智能指针CRefPtr<T>
//T should inherit from CRefObject
template<typename T>
class CRefPtr
{
public:
    T* operator->() const
    {
        return m_pRawObj;
    }

    T& operator()() const
    {
        assert(m_pRawObj != NULL);//测试一个条件并可能使程序终止,为真不理会，假终止函数打印错误
        return *m_pRawObj;
    }

    T& operator*() const
    {
        assert(m_pRawObj != NULL);
        return *m_pRawObj;
    }

    T* GetPtr() const
    {
        return m_pRawObj;
    }

    bool IsNull() const
    {
        return m_pRawObj == NULL;
    }
//阻止不应该允许的经过转换构造函数进行的隐式转换的发生。
//声明为explicit的构造函数不能在隐式转换中使用。
    explicit CRefPtr(T* p = NULL)
    {
        m_pRawObj = p;
        if(p != NULL)
        {
            p->AddRefCount();
        }
    }

    CRefPtr(const CRefPtr& ref)
    {
        m_pRawObj = ref.m_pRawObj;
        if(m_pRawObj != NULL)
        {
            m_pRawObj->AddRefCount();
        }
    }

    ~CRefPtr()
    {
        if(m_pRawObj != NULL && m_pRawObj->SubRefCount() == 0)
        {
            delete m_pRawObj;
        }
    }

    CRefPtr& operator = (const CRefPtr& ref)
    {
        if(this != &ref)
        {
            if(m_pRawObj != NULL
                && m_pRawObj->SubRefCount() == 0)
            {
                delete m_pRawObj;
            }

            m_pRawObj = ref.m_pRawObj;

            if(m_pRawObj != NULL)
            {
                m_pRawObj->AddRefCount();
            }
        }

        return *this;
    }

    bool operator == (const CRefPtr& ref) const
    {
        return m_pRawObj == ref.m_pRawObj;
    }

private:
    T* m_pRawObj;
};