// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:December 1, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef TASK_H
#define TASK_H


#include <deque>
#include <string>
#include "Item.h"
#include "CustomerOrder.h"


class Task:public Item{
    std::deque<CustomerOrder> m_orders;
    Task* m_pNextTask {nullptr};

    public:
    Task(const std::string& record);
    Task(Task&)=delete;
    Task(Task&&)=delete;
    Task& operator=(const Task&)=delete;
    Task& operator=(Task&&)=delete;
    void runProcess(std::ostream&);
    bool moveTask();
    void setNextTask(Task&);
    bool getCompleted(CustomerOrder&);
    void validate(std::ostream&);
    Task& operator+=(CustomerOrder&&);
};

#endif
