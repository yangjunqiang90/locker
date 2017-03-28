#ifndef INFO_H
#define INFO_H
#include<string>
using namespace std;
class Info
{
private:
        // String BUTLERID;

         string   ROOT_PASSWORD;
         string LOCK_PASSWORD;
         string  WEATHER;
         string   WELCOME;
         string   WELCOME_TEXT;
         string   DYNAMIC_UPDATE_LOCK;
         bool   isRecover;
public:
    Info();
  // void setBUTLERID(String BUTLERID);
   //String getBUTLERID();

   void setROOT_PASSWORD(string ROOT_PASSWORD);
   string getROOT_PASSWORD();

   void setLOCK_PASSWORD(string LOCK_PASSWORD);
   string getLOCK_PASSWORD();

   void setWEATHER(string WEATHER);
   string getWEATHER();

   void setWELCOME(string WELCOME);
   string getWELCOME();

   void setWELCOME_TEXT(string WELCOME_TEXT);
   string getWELCOME_TEXT();

   void setDYNAMIC_UPDATE_LOCK(string DYNAMIC_UPDATE_LOCK);
   string getDYNAMIC_UPDATE_LOCK();

   void setisRecover(bool state);
   bool getisRecover();


};

#endif // INFO_H
