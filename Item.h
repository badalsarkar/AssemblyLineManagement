// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <string>
#include "Utilities.h"


    class Item
    {
        std::string m_name{""};
        std::string m_description{""};
        unsigned int m_serialNumber{0};
        unsigned int m_quantity{0}; 
        static size_t m_widthField;
        public:
        Item(const std::string&);
        const std::string& getName()const;
        const unsigned int getSerialNumber();
        const unsigned int  getQuantity();
        void updateQuantity();
        void display(std::ostream& os, bool full)const;
    };

#endif


