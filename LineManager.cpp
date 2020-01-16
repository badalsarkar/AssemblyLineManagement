// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:December 1, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <iostream>
#include <algorithm>
#include "LineManager.h"



/**********************************************************************************************
custom constructor
parameter:1)a file name as string, this contains information about next task to be performed
        2) reference to a vector of Task* 
        3) reference to a vector of CustomerOrder
steps:  1. read one line from the file, extract two tokens.
        2. find second token in the 2nd parameter and store the address, find the first token in the 2nd parameter \
            and update the m_pNextTak with the address from step 2
        3. if there is only one token, put the m_pNextTask of the token as nullptr
        4. store the first token in firstTaskInAssmLine. This will be used to identify 
            the starting point in the AssemblyLine
        5. do this for all the records from the file
        6. copy each element from 2nd parameter into data member AssemblyLine
        7. move each element from 3rd parameter into data member ToBeFilled
        8. update the value of m_cntCustomerOrder with the size of ToBeFilled
*************************************************************************************************/
LineManager::LineManager(const std::string& source, std::vector<Task*>& task_list, std::vector<CustomerOrder>& order_list)
{
    //step 1-4:
    if(source!="")
    {
        std::ifstream file (source);
        if(file)
        {
            std::string line;
            bool firstLine{true};
            while (std::getline(file, line))
            {
                std::string token1{""}, token2{""};
                token1=trim(extractToken(line, '|'));
                token2=trim(extractToken(line));
                //step 2, 3: 
                if(token2 !=""){
                    setupNextTask(task_list, token1, token2);
                }
                //step 4:
                if(firstLine)
                {
                    firstTaskInAssmLine=token1;
                    firstLine=false;
                }

                line="";
            }
            file.clear();
            file.close();
        }
    }
    //step 5:
    //resize may throw exception
    AssemblyLine.resize(task_list.size());
    std::copy(task_list.begin(), task_list.end(), AssemblyLine.begin());
    //step 6:
    /*
    ToBeFilled.resize(order_list.size());
    std::move(order_list.begin(), order_list.end(), ToBeFilled.begin());
    */
    for(size_t i=0; i<order_list.size();i++)
    {
        ToBeFilled.push_front(std::move(order_list[i]));
    }

    //step 7:
    m_cntCustomerOrder=ToBeFilled.size();
}











/**************************************************************************
setupnexttask function
parameter: a vector of pointer to Task, the name of first Task(TaskA), 
            the name of second Task(TaskB)
step 1: find TaskA and TaskB in the vector
    2: call setNextTask method on TaskA- this will store the reference of the 
        TaskB in the m_pNextTask of the TaskA
***************************************************************************/
void LineManager::setupNextTask(std::vector<Task*>& task_list, std::string& taskA, std::string& taskB)
{
    //step 1:
    auto taskA_iter=std::find_if(task_list.begin(), task_list.end(), [&taskA](Task* theTask){
            return (theTask->getName()==taskA);
            });
    auto taskB_iter=std::find_if(task_list.begin(), task_list.end(), [&taskB](Task* theTask){
            return (theTask->getName()==taskB);
            });

    //setp2:
    if(taskA_iter!=task_list.end() && taskB_iter!=task_list.end())
        (*taskA_iter)->setNextTask(*(*taskB_iter));
}











/******************************************************************************
run function
steps: 1. check if ToBeFilled is empty or not
        2. if not empty, Identify the starting point of the AssemblyLine
        2. move the last element(CustomerOrder) to the starting task
            in the AssemblyLine. CustomerOrder will be added to the front of the 
            m_orders deque, of the starting task, of the AssemblyLine
        3. loop through the AssemblyLine and for each element do the following
            - call runProcess(),
            - check the order fill state, if it is true, move the order to the Completed deque
            - if order fill state is false, call moveTask()
        4. if the size of Completed deque is equal to m_cntCustomerOrder, it means
            all CustomerOrders have been filled. so return true otherwise false
******************************************************************************/
bool LineManager::run(std::ostream& os)
{
    bool result {false};
    //step 1:
    if(!ToBeFilled.empty())
    {
        auto firstTask=std::find_if(AssemblyLine.begin(), AssemblyLine.end(),[&](Task* theTask){
                return (theTask->getName()==firstTaskInAssmLine);
                });
        //step 2:
        (*(*firstTask))+=std::move(ToBeFilled.back());
        ToBeFilled.pop_back();
    }
    //step 3:
    std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Task* theTask)
        {
            theTask->runProcess(os);
            CustomerOrder temp;
            if(theTask->getCompleted(temp))
            {
                Completed.push_back(std::move(temp));
            }
        });
    std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Task* theTask)
        {
            theTask->moveTask();
        });

    //step : 4
    if(Completed.size()==m_cntCustomerOrder)
    {
        result=true;
    }
    return result;
}









/**************************************************************************
displaycompleted function
parameter: ostream
steps: 1. loop through Completed deque and call display function
**************************************************************************/
void LineManager::displayCompleted(std::ostream& os)const
{
    if(!Completed.empty())
    {
        std::for_each(Completed.begin(), Completed.end(), [&](const CustomerOrder& theOrder){
                    theOrder.display(os);
                });
    }
}








/*********************************************************************
validatetask function
steps: 1. loop through AssemblyLine and call function validate() on each 
        element
*********************************************************************/
void LineManager::validateTasks()const
{
    if(!AssemblyLine.empty())
    {
        std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [](Task* theTask)
                {
                    theTask->validate(std::cout);
                });
    }
}








/**************************************************************************
extracttoken function
this free helper function extracts sbustring till the delimiter,
if delimiter is not found whole string is returned
after extraction, it erases the extracted portion from original string
it returns the extracted string
**************************************************************************/
std::string extractToken(std::string& s, char delimiter)
{
    size_t delimiterPos=s.find(delimiter);
    std::string extractedString=s.substr(0,delimiterPos);
    if(delimiterPos==std::string::npos)
    {
        s.erase(0, delimiterPos);
    }
    else
    {
        s.erase(0, delimiterPos+1);
    }
    return extractedString;
}








/*************************************************************************
trim function
this function removes leading and trailing space
returns the trimmed string
*************************************************************************/
std::string trim(std::string text)
{
    try{
        size_t startPos=text.find_first_not_of(' ');
        size_t endPos=text.find_last_not_of(' ');
        text=text.substr(startPos, ((endPos-startPos)+1));
    }catch(...){
        //empty
    };
    return text;
}

