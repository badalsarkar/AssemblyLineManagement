// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:December 1, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <deque>
#include <string>
#include "Task.h"




class LineManager{
    std::vector<Task*> AssemblyLine;
    std::deque<CustomerOrder> ToBeFilled;
    std::deque<CustomerOrder> Completed;
    unsigned int m_cntCustomerOrder;    //the starting size of ToBeFilled
    std::string firstTaskInAssmLine;
    void setupNextTask(std::vector<Task*>&, std::string& taskA, std::string& taskB);
    public:
    LineManager(const std::string& source, std::vector<Task*>& task_list, std::vector<CustomerOrder>& order_list); 
    bool run(std::ostream&);
    void displayCompleted(std::ostream&)const;
    void validateTasks()const;
};

//free helper
std::string extractToken(std::string& s, char delimiter='\n');
std::string trim(std::string text);

#endif
