// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H


struct ItemInfo
{
    std::string m_itemName;
    unsigned int m_serialNumber=0;
    bool m_fillState=false;
    ItemInfo(std::string src):m_itemName(src){};
};



class CustomerOrder
{
    std::string m_name;     //stores customer name
    std::string m_product;  //the name of the product
    unsigned int m_cntItem=0; //counts the number of items in order
    ItemInfo** m_lstItem=nullptr;   //array of pointer of type ItemInfo. This is resource
    static size_t m_widthField; //for display, max width of field
    public:
    CustomerOrder();
    CustomerOrder(const std::string& OrderInfo);
    CustomerOrder(CustomerOrder&);  //copy constructor. will throw error if called
    CustomerOrder(CustomerOrder&&)noexcept; //move constructor. does not throw
    CustomerOrder& operator=(const CustomerOrder&)=delete;  //not allowed
    CustomerOrder& operator=(CustomerOrder&&);  //move assignment
    ~CustomerOrder();
    bool getItemFillState(std::string)const;    //returns m_fillState
    bool getOrderFillState()const;
    void fillItem(Item& item, std::ostream&);   //fill the item in the current order
    void display(std::ostream&)const;
};


#endif
