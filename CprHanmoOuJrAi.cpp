#include "CprHanmoOuJrAi.h"
#include <cstdio>
CprHanmoOuJrAi::CprHanmoOuJrAi(){
    RFXGa=0;
}

CprHanmoOuJrAi::~CprHanmoOuJrAi() {
}

void CprHanmoOuJrAi::playerStrategy() {
    for(int i=0;i<_collection._cards.size();i++){
        c_collection._cards.push_back(_collection._cards[i]);
    }
    c_collection.resetAllHands();
    //c_collection.printByRank();
    //c_collection.printBySuit();
    //getchar();
    Set_ACR();
    for(int i=0;i<102;i++){
    	if(Dfs(101-i,2)){
            if(Order[101-i][1]==10&&Order[101-i][2]==10)RFXGa=1;
            //if(Order[101-i][0]==3&&Order[101-i][1]==3&&Order[101-i][2]==4)Special1();
            break;
    	}
    }
    prepareHand();
    c_collection._cards.clear();
    c_collection.resetAllHands();
    for(int i=0;i<=2;i++){
        L[i].clear();
    }
}

void CprHanmoOuJrAi::Delete_Card(CprCard c){
	for(int i=0;i<c_collection._availCards.size();i++){
		if(c_collection._availCards[i]==c){
			c_collection._availCards.erase(c_collection._availCards.begin()+i);
		}
	}
}

void CprHanmoOuJrAi::Set_ACR(){
	c_collection.computeACR();
	for(int i=0;i<15;i++){
		_ACR[i]=(c_collection.getACR())[i];
	}
	c_collection.computeMAX();
	for(int i=0;i<4;i++){
		_MAX[i]=(c_collection.getMAX())[i];
	}
}

bool CprHanmoOuJrAi::Dfs(int type,int count){
	CprCollection t_col=c_collection;
	if(Order[type][count]==3){//onepair
		for(int i=14;i>=2;i--){
			if(_ACR[i].size()>=2){
                for(int p1=_ACR[i].size()-1;p1>=1;p1--){
                    for(int p2=p1-1;p2>=0;p2--){
                        L[count].push_back(_ACR[i][p1]);
                        L[count].push_back(_ACR[i][p2]);
                        Delete_Card(_ACR[i][p1]);
                        Delete_Card(_ACR[i][p2]);
                        Set_ACR();
                        if(count==0)return 1;
                        if(Dfs(type,count-1))
                            return 1;
                        else{
                            L[count].clear();
                            c_collection=t_col;
                            Set_ACR();
                        }
                    }
                }
			}
		}
	}
	if(Order[type][count]==4){//twopair
        for(int i=14;i>=3;i--){
            if(_ACR[i].size()>=2){
                for(int j=3;j<i;j++){
                    if(_ACR[j].size()>=2){
                        for(int p1=_ACR[i].size()-1;p1>=1;p1--){
                            for(int p2=p1-1;p2>=0;p2--){
                                for(int q1=_ACR[j].size()-1;q1>=1;q1--){
                                    for(int q2=q1-1;q2>=0;q2--){
                                        L[count].push_back(_ACR[i][p1]);
                                        L[count].push_back(_ACR[i][p2]);
                                        L[count].push_back(_ACR[j][q1]);
                                        L[count].push_back(_ACR[j][q2]);
                                        Delete_Card(_ACR[i][p1]);
                                        Delete_Card(_ACR[i][p2]);
                                        Delete_Card(_ACR[j][q1]);
                                        Delete_Card(_ACR[j][q2]);
                                        Set_ACR();
                                        if(count==0)return 1;
                                        if(Dfs(type,count-1))
                                            return 1;
                                        else{
                                            L[count].clear();
                                            c_collection=t_col;
                                            Set_ACR();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
	}
	if(Order[type][count]==5){//threeofakind
        for(int i=14;i>=2;i--){
			if(_ACR[i].size()>=3){
                 for(int p1=_ACR[i].size()-1;p1>=2;p1--){
                    for(int p2=p1-1;p2>=1;p2--){
                        for(int p3=p2-1;p3>=0;p3--){
                            L[count].push_back(_ACR[i][p1]);
                            L[count].push_back(_ACR[i][p2]);
                            L[count].push_back(_ACR[i][p3]);
                            Delete_Card(_ACR[i][p1]);
                            Delete_Card(_ACR[i][p2]);
                            Delete_Card(_ACR[i][p3]);
                            Set_ACR();
                            if(count==0)return 1;
                            if(Dfs(type,count-1))
                                return 1;
                            else{
                                L[count].clear();
                                c_collection=t_col;
                                Set_ACR();
                            }
                        }
                    }
                 }
			}
		}
		return 0;
	}
	if(Order[type][count]==6){//straight
        for(int i=14;i>=5;i--){
            if(_ACR[i].size()&&_ACR[i-1].size()&&_ACR[i-2].size()&&_ACR[i-3].size()&&_ACR[i-4].size()){
                for(int p1=_ACR[i].size()-1;p1>=0;p1--){
                    for(int p2=_ACR[i-1].size()-1;p2>=0;p2--){
                        for(int p3=_ACR[i-2].size()-1;p3>=0;p3--){
                            for(int p4=_ACR[i-3].size()-1;p4>=0;p4--){
                                for(int p5=_ACR[i-4].size()-1;p5>=0;p5--){
                                    L[count].push_back(_ACR[i][p1]);
                                    L[count].push_back(_ACR[i-1][p2]);
                                    L[count].push_back(_ACR[i-2][p3]);
                                    L[count].push_back(_ACR[i-3][p4]);
                                    L[count].push_back(_ACR[i-4][p5]);
                                    Delete_Card(_ACR[i][p1]);
                                    Delete_Card(_ACR[i-1][p2]);
                                    Delete_Card(_ACR[i-2][p3]);
                                    Delete_Card(_ACR[i-3][p4]);
                                    Delete_Card(_ACR[i-4][p5]);
                                    Set_ACR();
                                    if(count==0)return 1;
                                    if(Dfs(type,count-1))
                                        return 1;
                                    else{
                                        L[count].clear();
                                        c_collection=t_col;
                                        Set_ACR();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
	}
	if(Order[type][count]==7){//flush
        int che[2]={4,4},counter=0;
        for(int i=0;i<=3;i++){
            if(_MAX[i].size()>=5){che[counter]=i;counter++;}
        }
        if(counter==1){
            for(int p1=_MAX[che[0]].size()-1;p1>=4;p1--){
                for(int p2=p1-1;p2>=3;p2--){
                    for(int p3=p2-1;p3>=2;p3--){
                        for(int p4=p3-1;p4>=1;p4--){
                            for(int p5=p4-1;p5>=0;p5--){
                                L[count].push_back(_MAX[che[0]][p1]);
                                L[count].push_back(_MAX[che[0]][p2]);
                                L[count].push_back(_MAX[che[0]][p3]);
                                L[count].push_back(_MAX[che[0]][p4]);
                                L[count].push_back(_MAX[che[0]][p5]);
                                Delete_Card(_MAX[che[0]][p1]);
                                Delete_Card(_MAX[che[0]][p2]);
                                Delete_Card(_MAX[che[0]][p3]);
                                Delete_Card(_MAX[che[0]][p4]);
                                Delete_Card(_MAX[che[0]][p5]);
                                Set_ACR();
                                if(count==0)return 1;
                                if(Dfs(type,count-1))
                                    return 1;
                                else{
                                    L[count].clear();
                                    c_collection=t_col;
                                    Set_ACR();
                                }
                            }
                        }
                    }
                }
            }
        }
        if(counter==2){
            int s;
            CardList V[2],M,smallA,smallB,small;
            for(int i=0;i<=4;i++){
                V[0].push_back(_MAX[che[0]][_MAX[che[0]].size()-i-1]);
                V[1].push_back(_MAX[che[1]][_MAX[che[1]].size()-i-1]);
                smallA.push_back(_MAX[che[0]][_MAX[che[0]].size()-i-1]);
                smallB.push_back(_MAX[che[1]][_MAX[che[1]].size()-i-1]);
            }
            if(compareFlush(smallA,smallB)==1){
                small=smallA;
            }else small=smallB;
            if(compareFlush(V[0],V[1])==2){
                M=V[1];
                s=1;
            }
            else{
                M=V[0];
                s=0;
            }
            L[count]=M;
            for(int i=4;i>=0;i--){
                Delete_Card(L[count][i]);
            }
            Set_ACR();
            if(Dfs(type,count-1))
                return 1;
            else{
                L[count].clear();
                c_collection=t_col;
                Set_ACR();
            }
            while(true){
                for(int sui=0;sui<=1;sui++){
                    for(int p1=_MAX[che[sui]].size()-1;p1>=4;p1--){
                        for(int p2=p1-1;p2>=3;p2--){
                            for(int p3=p2-1;p3>=2;p3--){
                                for(int p4=p3-1;p4>=1;p4--){
                                    for(int p5=p4-1;p5>=0;p5--){
                                        V[sui].push_back(_MAX[che[sui]][p1]);
                                        V[sui].push_back(_MAX[che[sui]][p2]);
                                        V[sui].push_back(_MAX[che[sui]][p3]);
                                        V[sui].push_back(_MAX[che[sui]][p4]);
                                        V[sui].push_back(_MAX[che[sui]][p5]);
                                        int checking=compareFlush(M,V[sui]);
                                        if(p1==4)goto Wildcardround;
                                        if(checking==0&&s==0&&sui==0)continue;
                                        if(checking==0&&s==1)continue;
                                        if(checking-1)continue;
                                        goto Wildcardround;

                                    }
                                }
                            }
                        }
                    }
                }
                Wildcardround:
                if(compareFlush(V[0],V[1])-1){
                    M=V[1];
                    s=1;
                }
                else{
                    M=V[0];
                    s=0;
                }
                L[count]=M;
                for(int i=4;i>=0;i--){
                    Delete_Card(M[i]);
                }
                Set_ACR();
                if(count==0)return 1;
                if(Dfs(type,count-1))
                    return 1;
                else{
                    L[count].clear();
                    c_collection=t_col;
                    Set_ACR();
                }
                if(compareFlush(small,M)==0){break;}
            }
        }
	}
	if(Order[type][count]==8){//fullhouse
        for(int i=14;i>=2;i--){
            if(_ACR[i].size()>=3){
                for(int j=2;j<=14;j++){
                    if(i==j)continue;
                    if(_ACR[j].size()>=2){
                        for(int p1=_ACR[i].size()-1;p1>=2;p1--){
                            for(int p2=p1-1;p2>=1;p2--){
                                for(int p3=p2-1;p3>=0;p3--){
                                    for(int q1=_ACR[j].size()-1;q1>=1;q1--){
                                        for(int q2=q1-1;q2>=0;q2--){
                                            L[count].push_back(_ACR[i][p1]);
                                            L[count].push_back(_ACR[i][p2]);
                                            L[count].push_back(_ACR[i][p3]);
                                            L[count].push_back(_ACR[j][q1]);
                                            L[count].push_back(_ACR[j][q2]);
                                            Delete_Card(_ACR[i][p1]);
                                            Delete_Card(_ACR[i][p2]);
                                            Delete_Card(_ACR[i][p3]);
                                            Delete_Card(_ACR[j][q1]);
                                            Delete_Card(_ACR[j][q2]);
                                            Set_ACR();
                                            if(count==0)return 1;
                                            if(Dfs(type,count-1))
                                                return 1;
                                            else{
                                                L[count].clear();
                                                c_collection=t_col;
                                                Set_ACR();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
	}
	if(Order[type][count]==9){//fourofakind
        for(int i=14;i>=2;i--){
			if(_ACR[i].size()>=4){
				for(int j=3;j>=0;j--){
					L[count].push_back(_ACR[i][j]);
					Delete_Card(_ACR[i][j]);
				}
				Set_ACR();
				if(count==0)return 1;
				if(Dfs(type,count-1))
					return 1;
				else{
					L[count].clear();
					c_collection=t_col;
					Set_ACR();
				}
			}
		}
	}
	if(Order[type][count]==10){//straightflush
        for(int i=0;i<=3;i++){
            if(_MAX[i].size()>=5){
                for(int s=_MAX[i].size()-1;s>=4;s--){
                    if(_MAX[i][s-1].rankA()==_MAX[i][s-2].rankA()+1&&_MAX[i][s-2].rankA()==_MAX[i][s-3].rankA()+1&&_MAX[i][s-3].rankA()==_MAX[i][s-4].rankA()+1){
                        //cout<<"check1"<<endl;
                        if(_MAX[i][s].rankA()==_MAX[i][s-1].rankA()+1){
                            //cout<<"check"<<endl;
                            L[count].push_back(_MAX[i][s]);
                            L[count].push_back(_MAX[i][s-1]);
                            L[count].push_back(_MAX[i][s-2]);
                            L[count].push_back(_MAX[i][s-3]);
                            L[count].push_back(_MAX[i][s-4]);
                            Delete_Card(_MAX[i][s]);
                            Delete_Card(_MAX[i][s-1]);
                            Delete_Card(_MAX[i][s-2]);
                            Delete_Card(_MAX[i][s-3]);
                            Delete_Card(_MAX[i][s-4]);
                            Set_ACR();
                            if(count==0)return 1;
                            if(Dfs(type,count-1))
                                return 1;
                            else{
                                L[count].clear();
                                c_collection=t_col;
                                Set_ACR();
                            }
                        }
                        if(s==4&&_MAX[i][0].rankA()==2&&_MAX[i][_MAX[i].size()-1].rankA()==14){
                            //cout<<_MAX[i][0]<<_MAX[i][_MAX[i].size()-1]<<"SFA2345"<<endl;
                            L[count].push_back(_MAX[i][_MAX[i].size()-1]);
                            L[count].push_back(_MAX[i][s-1]);
                            L[count].push_back(_MAX[i][s-2]);
                            L[count].push_back(_MAX[i][s-3]);
                            L[count].push_back(_MAX[i][s-4]);
                            Delete_Card(_MAX[i][_MAX[i].size()-1]);
                            Delete_Card(_MAX[i][s-1]);
                            Delete_Card(_MAX[i][s-2]);
                            Delete_Card(_MAX[i][s-3]);
                            Delete_Card(_MAX[i][s-4]);
                            Set_ACR();
                            if(count==0)return 1;
                            if(Dfs(type,count-1))
                                return 1;
                            else{
                                L[count].clear();
                                c_collection=t_col;
                                Set_ACR();
                            }
                        }
                    }
                }
            }
        }
	}
    if(Order[type][count]==2){return 1;}
	return 0;

}

void CprHanmoOuJrAi::prepareHand(){
    if(RFXGa){
        if(compareStraightFlush()){
            swap(L[1],L[2]);
        }
    }
    for(int i=2;i>=0;i--){
        if(L[i].size()==0){
            int num;
            if(i)num=5;
            else num=3;
            while(L[i].size()<num){
                for(int j=14;j>=2;j--){
                    if((_ACR[j]).size()){
                       (L[i]).push_back((_ACR[j])[0]);
                        Delete_Card(_ACR[j][0]);
                        Set_ACR();
                        break;
                    }
                }
            }
        }
    }
    for(int i=0;i<=2;i++){
        int num;
        if(i)num=5;
        else num=3;
        while(L[i].size()<num){
            for(int j=14;j>=2;j--){
                if((_ACR[j]).size()){
                    L[i].push_back(_ACR[j][0]);
                    Delete_Card(_ACR[j][0]);
                    Set_ACR();
                    break;
                }
            }
        }
    }
    _collection.settingHand(0,L[0]);
    _collection.settingHand(1,L[1]);
    _collection.settingHand(2,L[2]);
    return;
}

int CprHanmoOuJrAi::compareFlush(const CardList &a,const CardList &b){
    for(int i=0;i<=4;i++){
        if(a[i].rankA()>b[i].rankA())return 1;
        if(a[i].rankA()<b[i].rankA())return 2;
    }
    return 0;
}

bool CprHanmoOuJrAi::compareStraightFlush(){
    for(int i=0;i<=4;i++){
        if(L[1][i].rankA()>L[2][i].rankA())return 1;
    }
    return 0;
}

void CprHanmoOuJrAi::Special1(){
    for(int i=0;i<=2;i++){
        L[i].clear();
    }
    c_collection=_collection;
    Set_ACR();
    int counter=0;
    for(int i=2;i<=14;i++){
        if(counter==2)break;
        if(_ACR[i].size()>=2){
            L[2].push_back(_ACR[i][_ACR[i].size()-1]);
            L[2].push_back(_ACR[i][_ACR[i].size()-2]);
            Delete_Card(_ACR[i][_ACR[i].size()-1]);
            Delete_Card(_ACR[i][_ACR[i].size()-2]);
            Set_ACR();
            counter++;
        }
    }
    counter=0;
    for(int i=14;i>=2;i--){
        if(counter==2)break;
        if(_ACR[i].size()>=2){
            L[1-counter].push_back(_ACR[i][_ACR[i].size()-1]);
            L[1-counter].push_back(_ACR[i][_ACR[i].size()-2]);
            Delete_Card(_ACR[i][_ACR[i].size()-1]);
            Delete_Card(_ACR[i][_ACR[i].size()-2]);
            Set_ACR();
            counter++;
        }
    }
    return;
}
