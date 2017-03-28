#include "info.h"

Info::Info()
{
    isRecover=false;
}
void Info::setROOT_PASSWORD(string ROOT_PASSWORD){
    this->ROOT_PASSWORD = ROOT_PASSWORD;
}

string Info::getROOT_PASSWORD(){
    return ROOT_PASSWORD;
}

void Info::setLOCK_PASSWORD(string LOCK_PASSWORD){
    this->LOCK_PASSWORD = LOCK_PASSWORD;
}

string Info::getLOCK_PASSWORD(){
     return LOCK_PASSWORD;
}

void Info::setWEATHER(string WEATHER){
    this->WEATHER = WEATHER;
}
string Info::getWEATHER(){
     return WEATHER;
}

void Info::setWELCOME(string WELCOME){
    this->WELCOME = WELCOME;
}
string Info::getWELCOME(){
     return WELCOME;
}

void Info::setWELCOME_TEXT(string WELCOME_TEXT){
    this->WELCOME_TEXT = WELCOME_TEXT;
}
string Info::getWELCOME_TEXT(){
     return WELCOME_TEXT;
}

void Info::setDYNAMIC_UPDATE_LOCK(string DYNAMIC_UPDATE_LOCK){
    this->DYNAMIC_UPDATE_LOCK = DYNAMIC_UPDATE_LOCK;
}
string Info::getDYNAMIC_UPDATE_LOCK(){
     return DYNAMIC_UPDATE_LOCK;
}

void Info::setisRecover(bool state){
    this->isRecover=state;
}

bool Info::getisRecover(){
    return isRecover;
}
