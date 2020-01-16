// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Utilities.h"
#include "Item.h"
#include "CustomerOrder.h"


//initialize class variable
size_t CustomerOrder::m_widthField=1;

//default constructor
CustomerOrder::CustomerOrder():m_name{""},m_product{""},m_cntItem{0},m_lstItem{nullptr}
{

}



//one argument constructor
//extracts tokens using the Utilities object from the parameter
//stores the token into data members
//updates the m_widthField, if needed
CustomerOrder::CustomerOrder(const std::string& OrderInfo)
{
    if(OrderInfo!="")
    {
        Utilities util;
        //find out how many delimiters are in the OrderInfo
        //This is used to determin how many items are in the order
        //if there is two delimiters, that means there is(2-1)one item
        //3 delimiters means(3-1) 2 items
        //minimum three delimiters are required
        const char delimiter=util.getDelimiter();
        m_cntItem=(std::count(OrderInfo.begin(),OrderInfo.end(),delimiter))-1;
        //alocate dynamic memory for items
        m_lstItem=new (std::nothrow) ItemInfo*[m_cntItem];
        //Utilities object may throw exception
        try
        {
            std::string tempData=OrderInfo;
            size_t n_pos{0};
            bool more {true};
            m_name=util.extractToken(tempData,n_pos,more);
            tempData.erase(n_pos, m_name.length()+1);
            m_product=util.extractToken(tempData,n_pos,more);
            tempData.erase(n_pos,m_product.length()+1);
            //loop for extracting items
            for (unsigned int i=0;i<m_cntItem;i++)
            {
                std::string tempToken=util.extractToken(tempData,n_pos,more);
                tempData.erase(n_pos, tempToken.length()+1);
                //create an instance of ItemInfo
                ItemInfo tempItem(tempToken);
                //move construct an element in m_lstItem using tempItem
                m_lstItem[i]=new ItemInfo(std::move(tempItem));
            }
            //extract quantity
            //update the m_widthField
            if(m_widthField<util.getFieldWidth())
            {
                m_widthField=util.getFieldWidth();
            }
            
        }
        catch(...)
        {
            //intentionally empty as there is no instruction 
            //how to handle the error

        }
    }
}





/*
   copy constructor
   throws error if called
*/
CustomerOrder::CustomerOrder(CustomerOrder& src)
{
    throw "Copy not allowed";
}



/*
   move constructor
   does not throw exception
*/

CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept
{
    *this=std::move(src);
}



/*
   move assignment operator
*/

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rhs)
{
    if(this!=&rhs)
    {
        for(unsigned int i=0;i<m_cntItem;i++)
        {
            delete m_lstItem[i];
        }
        delete [] m_lstItem;
        m_name=rhs.m_name;
        m_product=rhs.m_product;
        m_cntItem=rhs.m_cntItem;
        m_widthField=rhs.m_widthField;
        m_lstItem=rhs.m_lstItem;
        rhs.m_lstItem=nullptr;
        rhs.m_name="";
        rhs.m_product="";
        rhs.m_cntItem=0;
    }
    return *this;
}




/*
   destructor

   */
CustomerOrder::~CustomerOrder()
{
    for(unsigned int i=0;i<m_cntItem;i++)
    {
        delete m_lstItem[i];
    }
    delete [] m_lstItem;
}




/*
   getitemfillstate function
   searches the item in the parameter in the m_lstItem
   if found, returns the m_fillState for that item
   otherwise returns true
   */
bool CustomerOrder::getItemFillState(std::string item)const
{
    bool result {true};
    //find the item in the m_lstItem
    std::for_each(m_lstItem, (m_lstItem+m_cntItem), [&](ItemInfo* itemInList){
            if(itemInList->m_itemName==item&& itemInList->m_fillState==false)
                {
                    result=false;
                }

            });

   return result;
}




/*
   getorderfillstate function
   this function checks whether all item in the m_lstItem
   has m_fillState as true
*/
bool CustomerOrder::getOrderFillState()const
{
    return std::all_of(m_lstItem, (m_lstItem+m_cntItem),[](ItemInfo* itemInList){
            return itemInList->m_fillState==true;
            });
}





/*
   fillitem function
   finds the item in the m_lstItem
   if found, checks if there is available inventory
   if there is inventory, deducts 1 from inventory, then 
   updates the m_serialNumber and m_fillState of the item in m_lstItem
   prints a confirmation message
   if the item is not found in the m_lstIem the function does nothing
   if there is no inventory, it prints a message about it
*/
void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
    auto i=std::find_if(m_lstItem, (m_lstItem+m_cntItem),[&](ItemInfo* itemInList)
            {
                return (itemInList->m_itemName==item.getName() && itemInList->m_fillState==false);
            });
    //if found
    if(i!=(m_lstItem+m_cntItem))
    {
        if(item.getQuantity()>0)
        {
            item.updateQuantity();
            (*i)->m_serialNumber=item.getSerialNumber();
            (*i)->m_fillState=true;
            os<<"Filled "<<m_name<<", "<<m_product<<"["<<(*i)->m_itemName<<"]"<<std::endl;
        }
        else
        {
            os<<"Unable to fill "<<m_name<<", "<<m_product<<"["<<(*i)->m_itemName<<"]"<<std::endl;
        
        }
    
    }

}




/*
   display function
   this function displays the CustomerOrder
*/
   
void CustomerOrder::display(std::ostream& os)const
{
    os<<m_name<<" - "<<m_product<<std::endl;
    std::for_each(m_lstItem, (m_lstItem+m_cntItem),[&os](ItemInfo* itemInList){
           os<<"["<<std::setw(6)<<std::setfill('0')<<itemInList->m_serialNumber<<"] "<<std::setfill(' ')
           <<std::setw(m_widthField)<<itemInList->m_itemName<<" - "
           <<(itemInList->m_fillState==true?"FILLED":"MISSING")<<std::endl;
           });
}
