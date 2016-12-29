/****************************************************************************
  FileName   [ CprHand.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprHand member functions ]
****************************************************************************/
 
#include "CprHand.h"
#include "CprHandMaster.h"
//new
void CprHand::setXianggong(){
    _type=(HandType)1;
}
const CprCard CprHand::getCard(int idx) const {
    return _cards.at(idx);
}
const CardList& CprHand::getCards() const {
    return _cards;
}
const CardList * CprHand::getACR() const {
    return _ACR;
}
bool CprHand::operator <= (const CprHand& hand) const{
    CprHandMaster master;
    return(master.Compare((*this),hand));
}
bool CprHand::operator >= (const CprHand& hand) const{
    CprHandMaster master;
    return(master.Compare(hand,(*this))); 
}
bool CprHand::operator > (const CprHand& hand) const{
    CprHandMaster master;
    return(!master.Compare((*this),hand)); 
}
int CprHand::isCardAvailable(const CprCard& c) const {
    // TODO: find whether c is in _cards
    int in=0;
    for(int i=0;i<_cards.size();i++){
        if(_cards[i]==c)
            {
                in++;
            }
    }
    return in;
}
void CprHand::computeACR() {
    //TODO: See Practice 2 in Week 14 Practice.pdf for more information

    CardList tem[15];
    for(int i=1;i<=13;i++){
        for(int j=1;j<=4;j++){
            CprCard t(13*(j-1)+i);
            int isCard=isCardAvailable(t);
            if(isCard){
                for(int k=0;k<isCard;k++){
                    if(i==1){
                        tem[i].push_back(t);
                        tem[14].push_back(t);
                    }
                    else{
                    tem[i].push_back(t);
                    }
                }
            }
        }
    }
    for(int i=0;i<15;i++)
        _ACR[i]=tem[i];
    return ;
}


CprHand::CprHand()
    : _type(HTUndefined) {}
 
CprHand::CprHand(const CardList & cards)
    : _cards(cards), _type(HTUndefined) {}
CprHand::CprHand(const CardList & cards, HandType type) 
    : _cards(cards), _type(type) {
}

CprHand::~CprHand() {
}
 
 
int CprHand::size() const {
    // TODO: return the size of _cards
    return _cards.size();
}
 
bool CprHand::empty() const {
    // TODO: determine whether _cards is empty (i.e. with size 0)
    if(!_cards.size())
        return true;
    else
        return false;
}
 
void CprHand::print() const {
    // TODO: print each card in _cards
    // e.g. suppose _availCards is (3c 2s Jc 4d 7c)
    // then print "3c 2s Jc 4d 7c \n"
 
    for(int i=0;i<_cards.size();i++){
        cout<<_cards[i]<<" ";
    }
    cout<<endl;
}
 
HandType CprHand::getType() const {
    // DONE
    return _type;
}