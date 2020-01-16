// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Item.h"

    size_t Item::m_widthField=1;

    //custom constructor 
    Item::Item(const std::string& data)
    {
        std::string tempData=data;
        bool more{true};
        size_t n_pos{0};

        if(tempData.length()>0){
            //create utilities object
            Utilities util;
            //start extracting tokens
            //we will use Utilities object which can throw error
            //also stoi method can also throw error
            //so we need hanlde error if any error is thrown
            try
            {
                m_name=util.extractToken(tempData,n_pos,more);
                //erase the extracted portion of the data
                tempData.erase(n_pos, m_name.length()+1);
                std::string tempSerial=util.extractToken(tempData,n_pos,more);
                m_serialNumber=std::stoul(tempSerial);
                tempData.erase(n_pos,tempSerial.length()+1);
                //extract quantity
                std::string tempQuantity=util.extractToken(tempData,n_pos,more);
                m_quantity=std::stoul(tempQuantity);
                tempData.erase(n_pos,tempQuantity.length()+1);
                //extract description
                m_description=util.extractToken(tempData,n_pos,more);
                tempData.erase(0);

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
       get name function
       returns the value of m_name
     */
    const std::string& Item::getName()const
    {
        return m_name;
    }



    /*
       get serial number function
       this function returns the value of m_serialnumber
     */
    const unsigned int Item::getSerialNumber()
    {
        return m_serialNumber;
    }


    /*
       get quantity function
       this function returns the value of m_quantity
     */
    const unsigned int Item::getQuantity()
    {
        return m_quantity;
    }




    /*
       update quantity function 
       this function reduces the m_quantity by 1 till it is 0
     */
    void Item::updateQuantity()
    {
        m_quantity>0?(m_quantity--):m_quantity;
    }



    /*
       display function
       this function displays the Item into stream
     */
    void Item::display(std::ostream& os, bool full)const
    {
        if (full) 
        {
            os<<std::setw(m_widthField)<<m_name<<" ["
                <<std::right<<std::setfill('0')<<std::setw(6)<<m_serialNumber<<"] Quantity: "
                <<std::left<<std::setfill(' ')<<std::setw(m_widthField)<<m_quantity
                <<" Description: "<<m_description<<std::endl;
        }
        else 
        {
            os<<std::left<<std::setw(m_widthField)<<m_name<<
                " ["<<std::right<<std::setfill('0')<<std::setw(6)<<m_serialNumber<<std::left<<std::setfill(' ')<<"]"<<std::endl;
        }
    }

