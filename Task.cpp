// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:December 1, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include "Task.h"


/*********************************************
custom constructor
parameter:a single record that holds information about item
action: instantiate item object 
        put m_pNextTask in safe state
**********************************************/
Task::Task(const std::string& record):Item(record)
{
    //m_pNextTask is already in safe state
}






/***********************************************
runprocess function
parameter: 1. ostream as it will be passed to another function (fillItem)
steps: 1. check if the m_orders is empty or not. If not empty, get
        the last element
        2. check the fill status of the current task in the last element(customerOrder)
        3. if it is not filled, fill it
*************************************************/
void Task::runProcess(std::ostream& os)
{
    //step 1:
    if(!m_orders.empty())
    {
        //step 2:
        if(!m_orders.back().getItemFillState(getName()))
        {
            //step 3:
            m_orders.back().fillItem(*this, os);
        }
    }
}






/*****************************************************
movetask function
steps: 1.check if m_orders is not empty 
        2. check if the fill status of the current task for the
        last CustomerOrder in the m_orders is true(if false do nothing)
        3. if true move the CustomerOrder to the m_pNextTask
        as the first element of the m_orders(use operator+=)
        4. return true (or false if m_orders is empty)
******************************************************/
bool Task::moveTask()
{
    bool result {false};
    //step 1:
    if(!m_orders.empty())
    {
        //step 2:
        if(m_orders.back().getItemFillState(this->getName()))
        {
            //step 3:
            if(m_pNextTask!=nullptr){
                (*m_pNextTask)+=std::move(m_orders.back());
                m_orders.pop_back();
                result=true;
            }
        }
    }
    return result;
}








/*************************************************************
setnexttask function
parameter: a reference to a Task object
step: assign the reference to m_pNextTask
**************************************************************/
void Task::setNextTask(Task& nextTask)
{
    m_pNextTask=&nextTask;
}








/**************************************************************
getcompleted function
parameter: reference to CustomerOrder
steps: 1. check that m_orders is not empty
        2. pop the last element from m_order
        3. move the popped element to the parameter (CustomerOrder)
****************************************************************/
bool Task::getCompleted(CustomerOrder& completedOrder)
{
    bool result {false};
    if(!m_orders.empty())
    {
        if(m_orders.back().getOrderFillState()){
            completedOrder=std::move(m_orders.back());
            m_orders.pop_back();
            result=true;
        }
    }
    return result;
}









/**************************************************************
validate function
prints task name
**************************************************************/
void Task::validate(std::ostream& os)
{
    if(m_pNextTask!=nullptr)
    {
        os<<getName()<<" --> "<<m_pNextTask->getName()<<std::endl;
    }
    else
    {
        os<<getName()<<" --> "<<"END OF LINE"<<std::endl;
    }
}










/************************************************************
operator+= function
parameter: rvalue reference to CustomerOrder object
steps: 1. moves the parameter at the front of m_orders
************************************************************/
Task& Task::operator+=(CustomerOrder&& order)
{
    m_orders.push_front(std::move(order));
    return *this;
}


