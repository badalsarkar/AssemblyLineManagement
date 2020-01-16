// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"


     char Utilities::m_delimiter='\0';



    //set field width
    //this function sets the m_widthField data member
    void Utilities::setFieldWidth(size_t width)
    {
        if(width>=1)
            m_widthField=width;
    }





    //get field width
    //this function gets the value of m_fieldwidth
    size_t Utilities::getFieldWidth()const
    {    
        return m_widthField;
    }






    //extract token function
    //this function extracts 1 token starting from next_pos till delimiter
    //if extraction is successfull, it returns the token, set the more variable to true else false
    //if there are two delimiter without any token between them
    //it reports an exception
    const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        //the value of more is false to start with
        //it will be true only if the extraction is successful
        more=false;
        std::string token="";
        //check if string is not empty 
        if(str!=""&& next_pos!=std::string::npos)
        {
            //check if there are two delimiters without any 
            //token between them
            {
                char c, previous_c;
                for(size_t i=0;i<str.size();i++)
                {
                    c=str.at(i);
                    if(c==m_delimiter)
                    {
                        if(c==previous_c)
                        {
                            throw "There is delimiter between token";
                        }
                        else
                        {
                            previous_c=c;
                        }
                    }
                    else
                    {
                        previous_c=c;
                    }
                }
            }
            //extraction of token
            //find the position of the next delimiter
            size_t next_delimiter_pos=str.find(m_delimiter, next_pos);
            size_t length;
            //determine the length between next_pos and next_delimiter
            if(next_delimiter_pos==std::string::npos)
            {
                length=std::string::npos;
            }
            else
            {
                length=next_delimiter_pos-next_pos;
            }
            //extract token
            token=str.substr(next_pos, length);
           //trim the token to remove any leading and trailing space
            trim(token);
            more=true;
            if(str.find(m_delimiter,next_pos)!=std::string::npos){
                if(m_widthField<token.size())
                {
                    m_widthField=token.size();
                }
            }
        }
        return token;
    }








    /*
    trim function
    this function removes leading and trailing sapce
    from the parameter
    */
    void trim(std::string& data)
    {
        //erase leading space
        data.erase(0, data.find_first_not_of(' '));
        //erase trailing space
        data.erase(data.find_last_not_of(' ')+1);
    }







    /*
    set delimiter function
    this function sets the value for the m_delimiter member
    */
    void Utilities::setDelimiter(const char delimiter)
    {
        m_delimiter=delimiter;
    }




    /*
    get delimiter function
    this function returns the value of the m_delimiter member
    */
    const char Utilities::getDelimiter()const
    {
        return m_delimiter;
    }




