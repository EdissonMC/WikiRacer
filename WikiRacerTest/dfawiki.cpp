#include<iostream>
#include<map>
#include<set>
#include<cctype>
#include<string>

/*

    ESTE PROGRAMA IMPLEMENTA UNA SIMULACION DE UNA DFA
    DETERMINISTIC FINITE AUTOMATA

*/

struct DFA {

    std::map<  std::pair<int, char>,  int > transitions;
    std::set<int> acceptingStates;
    int startState;

};




bool SimulateDFA(DFA& d, std::string input) {

    int currState = d.startState;
    
    for (std::string::iterator itr = input.begin(); itr!=input.end(); ++itr ) {
        currState = d.transitions[std::make_pair(currState, *itr)];
    }
    return d.acceptingStates.find(currState) != d.acceptingStates.end();
}



void LoadWikiDFA(struct DFA& dfa_1) {
        std::cout <<"LoadWikiDFA...";
    dfa_1.transitions [ std::make_pair(0,'w') ]= 7;
    dfa_1.transitions [ std::make_pair(1,'w') ]= 2;
    dfa_1.transitions [ std::make_pair(2,'w') ]= 7;
    dfa_1.transitions [ std::make_pair(3,'w') ]= 7;
    dfa_1.transitions [ std::make_pair(4,'w') ]= 7;
    dfa_1.transitions [ std::make_pair(5,'w') ]= 7;
    dfa_1.transitions [ std::make_pair(6,'w') ]= 6;
    dfa_1.transitions [ std::make_pair(7,'w') ]= 7;


    dfa_1.transitions [ std::make_pair(0,'i') ]= 7;
    dfa_1.transitions [ std::make_pair(1,'i') ]= 7;
    dfa_1.transitions [ std::make_pair(2,'i') ]= 3;
    dfa_1.transitions [ std::make_pair(3,'i') ]= 7;
    dfa_1.transitions [ std::make_pair(4,'i') ]= 5;
    dfa_1.transitions [ std::make_pair(5,'i') ]= 7;
    dfa_1.transitions [ std::make_pair(6,'i') ]= 6;
    dfa_1.transitions [ std::make_pair(7,'i') ]= 7;

    dfa_1.transitions [ std::make_pair(0,'k') ]= 7;
    dfa_1.transitions [ std::make_pair(1,'k') ]= 7;
    dfa_1.transitions [ std::make_pair(2,'k') ]= 7;
    dfa_1.transitions [ std::make_pair(3,'k') ]= 4;
    dfa_1.transitions [ std::make_pair(4,'k') ]= 7;
    dfa_1.transitions [ std::make_pair(5,'k') ]= 7;
    dfa_1.transitions [ std::make_pair(6,'k') ]= 6;
    dfa_1.transitions [ std::make_pair(7,'k') ]= 7;


    dfa_1.transitions [ std::make_pair(0,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(1,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(2,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(3,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(4,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(5,'x') ]= 7;
    dfa_1.transitions [ std::make_pair(6,'x') ]= 6;
    dfa_1.transitions [ std::make_pair(7,'x') ]= 7;

    dfa_1.transitions [ std::make_pair(0,'/') ]= 1;
    dfa_1.transitions [ std::make_pair(1,'/') ]= 7;
    dfa_1.transitions [ std::make_pair(2,'/') ]= 7;
    dfa_1.transitions [ std::make_pair(3,'/') ]= 7;
    dfa_1.transitions [ std::make_pair(4,'/') ]= 7;
    dfa_1.transitions [ std::make_pair(5,'/') ]= 6;
    dfa_1.transitions [ std::make_pair(6,'/') ]= 6;
    dfa_1.transitions [ std::make_pair(7,'/') ]= 7;

    dfa_1.acceptingStates.insert(6);
    
    dfa_1.startState = 0;
}





bool IsWikiLink(std::string input) {
     //DFA emailChecker ;

    std::cout <<"IsWikiLink...  "<< input <<std::endl;
    
    struct DFA dfa_wikiChecker;
    LoadWikiDFA(dfa_wikiChecker); // Implemented elsewhere
    
     std::cout <<"\nvamos a reformaterar ...\n\n";

    /* Transform the string one character at a time. */ 

     std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    std::cout <<"input en lowercase :"<< input;
    std::cout << "\ntamano string entrada" <<input.size() <<std::endl;

    for(std::string::iterator itr = input.begin();   itr != input.end();   ++itr)   
    {
        /* 
            isalnum is exported by <cctype> 
            and checks if the input is an * alphanumeric character.
        */
    
        
        //if( isalnum(*itr) || *itr=='_' || *itr=='/' || *itr=='>'   || *itr=='<' || *itr=='%' ) {
        char chartest =  ':';
         std::cout << "char "<< chartest <<std::endl;
        // if( isalnum(*itr) || *itr=='_' || *itr=='/' || *itr=='>'   || *itr=='<' || *itr=='%' ) {
        
        if(  *itr == '#' || *itr == ':' ) {
              return false;
        
        }
        else{
           
             std::cout << *itr <<std::endl;
            if( *itr !='w' &&  *itr !='i' &&  *itr !='k' &&  *itr !='/' ){
                
                 *itr = 'x';
                
            }
        }
        // else if(*itr == '#' || *itr != ':') {
        //     //std::cout << *itr <<std::endl;
        //     return false;
      
        // }
            
    }

   std::cout << "\n\ndespues de formatear = "<< input << std::endl;
     std::cout << "tamano string salida :" <<input.size() <<std::endl;
   
    return SimulateDFA(dfa_wikiChecker, input);
}


int main() {
    
    //  "/wiki/​topological_space​"
     std::string  email = "/wiki/​lindel%c3%b6f_space​" ; // "/wiki/​Separable_space​>separable</a>​)" ; //separablespace​
   
    // std::cout << "ingrese el wiki link a verificar : ";
    // std::getline(std::cin, email);

    std::cout << "\n"<< email <<"  \n";
    std::cout << IsWikiLink( email );

    return 0;
}