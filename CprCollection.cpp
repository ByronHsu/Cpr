#include "CprCollection.h"
#include "CprHand.h"
 
CprHand& CprCollection::hand(int n){
    return _hands[n];
}
const CardList& CprCollection::getAvailableCards() const{
    return _availCards;
}
CprCollection::CprCollection()
    :_cards(), _hands(3) {
    // DONE: now _hands.size() is 3
}
 
CprCollection::~CprCollection() {
}
/*
typedef vector<CprCollection> CollectionList;
typedef vector<CprPlayer*>        PlayerList;
typedef vector<CprHand>            HandList;
typedef vector<CprCard>            CardList;
*/
bool CprCollection::settingHand(int hidx, const CardList& cs) {
    /*
        TODO: setting hand with hidx by cs:
        (hand with hidx 0 is the 1st hand,
         hand with hidx 1 is the 2nd hand,
         hand with hidx 2 is the 3rd hand)
        Return false without modifying data memebers if:
            (i)   hand with hidx has already been set
            (ii)  there're duplicate elements in cards
            (iii) there's card in cs which is not an element of _availCards
        Otherwise, follow these steps:
            1. remove card in cs from _availCards
            2. set _hands[hidx] by cs,
            3. return true
    */
    if(!_hands[hidx].empty())return false;
    for(int i=0;i<cs.size();i++){
        for(int j=i+1;j<cs.size();j++){
                if(cs[i]==cs[j])
                return false;
        }
    }
    for(int i=0;i<cs.size();i++){
        bool find=0;
        for(int j=0;j<_availCards.size();j++){
            if(cs[i]==_availCards[j]){
                find=1;break;
            }
        }
        if(!find)
            return false;
    }
    for(int i=0;i<cs.size();i++){
        for(int j=0;j<_availCards.size();j++){
            if(cs[i]==_availCards[j]){
                _availCards.erase (_availCards.begin()+j);
            }
        }
    }
    CprHand t(cs);
    _hands[hidx]=t;
    computeACR();
    return true;
}
 
void CprCollection::resetAllHands() {
    // TODO: reset _availCards and all hands
    _availCards=_cards;
    CprHand t;
    for(int i=0;i<3;i++)
        _hands[i]=t;
    computeACR();
}
 
void CprCollection::printByRank() const {
    // TODO: print avaliable cards, sorted by rank
    // (for same rank, sorted by suit)
    // e.g. suppose _availCards is (3c 2s Jc 4d 7c)
    // then print "2c 3c 4d 7c Jc \n"
    for(int i=1;i<=13;i++){
        for(int j=1;j<=4;j++){
            CprCard t(13*(j-1)+i);
            if(isCardAvailable(t)){
                cout<<t<<" ";
            }
        }
    }
    cout<<endl;
}
 
void CprCollection::printBySuit() const {
    // TODO: print avaliable cards, sorted by suit
    // (for same suit, sorted by rank)
    // e.g. suppose _availCards is (3c 2s Jc 4d 7c)
    // then print "3c 7c Jc 4d 2s \n"
 
    for(int j=1;j<=4;j++){
        for(int i=1;i<=13;i++){
            CprCard t(13*(j-1)+i);
            if(isCardAvailable(t)){
                cout<<t<<" ";
            }
        }
    }
    cout<<endl;
}
 
void CprCollection::showCollection() const {
    // DONE: do not modify me
    if (!_availCards.empty()) {
        cout << "Available cards: " << endl << "  ";
        printByRank();
    }
    for (unsigned i = 0; i < _hands.size(); ++i) {
        const CprHand& hand = _hands.at(i);
        cout << "hand " << (i + 1) << ": ";
        hand.print();
    }
}
 
bool CprCollection::isValidSet() {
    //    TODO: determine whether all hands are set
    if(!_hands[0].empty()&&!_hands[1].empty()&&!_hands[2].empty())
        return 1;
    if(!_hands[0].empty()&&!_hands[1].empty()){
        CprHand temp(_availCards);
        _hands[2]=temp;
        return 1;
    }
    if(!_hands[1].empty()&&!_hands[2].empty()){
        CprHand temp(_availCards);
        _hands[0]=temp;
        return 1;
    }
    if(!_hands[0].empty()&&!_hands[2].empty()){
        CprHand temp(_availCards);
        _hands[1]=temp;
        return 1;
    }
    else return 0;
}
 
int CprCollection::isCardAvailable(const CprCard& c) const {
    // TODO: find whether c is in _cards
    int in=0;
    for(int i=0;i<_availCards.size();i++){
        if(_availCards[i]==c)
            {
                in++;
            }
    }
    return in;
}
void CprCollection::computeACR() {
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
 
    for(int i=0;i<15;i++){
        _ACR[i]=tem[i];
    }
}
 
const CardList * CprCollection::getACR() const {
    return _ACR;
}