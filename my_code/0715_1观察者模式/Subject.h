#ifndef __SUBJECT_H_
#define __SUBJECT_H_

class Observer;//没有加分号:multiple types in one declaration(一个声明中有多个类型)
class Subject
{
public:
	virtual ~Subject() = 0;
	virtual void registerObserver(Observer *) = 0;
	virtual void removeObserver(Observer *) = 0;
	virtual void notifyObserver() const = 0;
};

Subject::~Subject()
{}

#endif