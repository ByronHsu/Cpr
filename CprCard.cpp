#include "CprCard.h"
#include <sstream>
 
CprCard::CprCard()
    : _cardId(-1) {
}
 
CprCard::CprCard(int id)
    : _cardId(id) {
}
 
int CprCard::suit() const {
    // TODO: return the suit of this card
    // where 0: club, 1: diamond, 2: heart, 3: spade
    // e.g. return 1 if it's with suit "club"
      /* card index from 1 to 52:
         1  - 13: Ac - Kc
         14 - 26: Ad - Kd
         27 - 39: Ah - Kh
         40 - 52: As - Ks
      */
    if(_cardId<=13)
        return 1;
    if(_cardId>=14&&_cardId<=26)
        return 2;
    if(_cardId>=27&&_cardId<=39)
        return 3;
    if(_cardId>=40&&_cardId<=52)
        return 4;
    return 0;
}
int CprCard::rank() const {
    // TODO: return the rank of this card
    // where 1: A, 2: 2, ..., 10: 10, 11: J, 12: Q, 13: K
    // e.g. return 11 if it's with rank J
    int rank=_cardId%13;
    if(rank==0)
        return 13;
    else
        return rank;
 
    return 0;
}
 
int CprCard::rankA() const {
    // DONE: similar to rank()
    // but return 14 if it's with rank A
    return (rank() == 1)? 14: rank();
}
 
bool CprCard::notStrongerThan(const CprCard &c) const {
    // TODO: if this card is weaker than or equal to c
    // with respect to rank, return true
    // Otherwise, return false
    if(rankA()<=c.rankA())
        return true;
 
    return false;
}
 
bool CprCard::sameWith(const CprCard& c) const {
    // TODO: determine if two cards are same
    if(rank()==c.rank()&&suit()==c.suit())
        return 1;
    return false;
}
 
bool CprCard::diffWith(const CprCard& c) const {
    // TODO: determine if two cards are different
    if(rank()!=c.rank()||suit()!=c.suit())
        return 1;
    return false;
}
 
 
/*  DONE: Operator Overloading  */
bool CprCard::operator<=(const CprCard &c) const {
    return this->notStrongerThan(c);
}
bool CprCard::operator < (const CprCard& c) const {
    // only for sorting purpose
    return _cardId < c._cardId;
}
bool CprCard::operator == (const CprCard& c) const {
    return this->sameWith(c);
}
bool CprCard::operator != (const CprCard& c) const {
    return this->diffWith(c);
}
 
 
 
int CprCard::SuitFromChar(const char c) {
    // TODO: return suit symbolized by char c
    // e.g. return 3 if (c == 'h' || c == 'H')
    //   (where 1: club, 2: diamond, 3: heart, 4: spade)
    // However, return -1 if c is an invalid suit char
    if (c == 'c' || c == 'C')
        return 1;
    if (c == 'd' || c == 'D')
        return 2;
    if (c == 'h' || c == 'H')
        return 3;
    if (c == 's' || c == 'S')
        return 4;
    return -1;
}
 
int CprCard::RankFromChar(const char c) {
    // TODO: return rank symbolized by char c
    // e.g. return 1 if (c == 'A' || c == 'a')
    // However, return -1 if c is an invalid rank char
    if (c == 'A' || c == 'a')
        return 1;
    if (c == 'J' || c == 'j')
        return 11;
    if (c == 'Q' || c == 'q')
        return 12;
    if (c == 'K' || c == 'k')
        return 13;
 
 
    return -1;
}
 
void CprCard::setting(int suit, int rank) {
    // TODO: modify _cardId with parameters suit and rank
    _cardId=13*(suit-1)+rank;
}
 
ostream& operator << (ostream& os, const CprCard& c) {
    /* TODO: regard os as std::cout, output the card in the following format:
        e.g.  output 3c  if this card is with rank 3 and suit club
        e.g.  output Ad  if this card is with rank A and suit diamond
        e.g.  output 10h if this card is with rank 10 and suit heart
        e.g.  output Ks  if this card is with rank K and suit spade
    */
 
    char n;
    if(c.rank()>=2&&c.rank()<=10){
        os<<c.rank();
    }
    else{
        if(c.rank()==1){
            n='A';
        }
        if(c.rank()==11){
            n='J';
        }
        if(c.rank()==12){
            n='Q';
        }
        if(c.rank()==13){
            n='K';
        }
        os<<n;
    }
    char s;
    if(c.suit()==1){
        s='c';
    }
    if(c.suit()==2){
        s='d';
    }
    if(c.suit()==3){
        s='h';
    }
    if(c.suit()==4){
        s='s';
    } 
    os << s;
    /* For example, the following line is similar to std::cout << "3c"; */
    //os << "3c";
 
    return os;  // do NOT remove this line
}
 
istream& operator >> (istream& is, CprCard& c) {
    /*
        DONE: This part has been done for you, hence You do NOT need to modify it.
        Please finish the following member functions to make
        std::cin with CprCard behave properly:
            static int SuitFromChar(const char);
            static int RankFromChar(const char);
            void setting(int suit, int rank);
    */
    string str;
    is >> str;
    if (str.empty()) {
        is.clear(ios::failbit);
        return is;
    }
 
    // 1. parse suit
    int suit = CprCard::SuitFromChar(str.back());
    if (suit == -1) {
        is.clear(ios::failbit);
        return is;
    }
    str.pop_back();
 
    // 2. parse rank
    istringstream in(str);
    int rank;
    if (in >> rank) {
    } else if (str.size() == 1) {
        rank = CprCard::RankFromChar(str.back());
    } else {
        rank = -1;
    }
    if (rank > 0 && rank <= 13) {
        c.setting(suit, rank);
    } else {
        is.clear(ios::failbit);
    }
    return is;
}
