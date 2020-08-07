#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>



/*  -- INICIO DE LA DFA QUE RECONOCE EL WIKILINK --   */

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

   // std::cout <<"IsWikiLink...  "<< input <<std::endl;
    
    struct DFA dfa_wikiChecker;
    LoadWikiDFA(dfa_wikiChecker); // Implemented elsewhere
    
   //  std::cout <<"\nvamos a reformaterar ...\n\n";
    /* Transform the string one character at a time. */ 
    for(std::string::iterator itr = input.begin();  itr != input.end();  ++itr)   
    {
        /* 
            isalnum is exported by <cctype> 
            and checks if the input is an * alphanumeric character.
        */
       // char tempS = *itr;
        
        if( isalnum(*itr) || *itr=='_' ) {
          //  std::cout << tempS<<std::endl;
            

            if( *itr !='w' &&  *itr !='i' &&  *itr !='k' ){
                
                 *itr = 'x';
                  // std::cout <<""<< *itr << std::endl;
            }
           
        } else if(*itr=='/' ){
           //  std::cout << tempS<<std::endl;
            // std::cout <<""<< *itr<<std::endl;
             *itr = *itr ;

        /* 
            If we don't have alphanumeric data, 
            we have to be a dot or at-sign * or the input is invalid.
        */
        }else if(*itr == '#' || *itr != ':') {
            // std::cout << tempS<<std::endl;
            return false;
      
        }
            
    }

   std::cout << "\n\ndespues de formatear = "<< input << std::endl;

    return SimulateDFA(dfa_wikiChecker, input);
}

/*          --     END DE LA DFA PARA EL WIKILINK --        */








int main() {

    std::ifstream input("data1.txt");


    std::multiset<std::string>  values;
    std::string currValue;
    std::string referencia1= "href";
    std::string referencia2= "\"";

    std::string::iterator itr_result1;
    std::string::iterator itr_result2;

    std::string temp;
    /* Read the data from the file */
    while (input>> currValue) {
       
        itr_result1 = std::search(currValue.begin(),   currValue.end(),   referencia1.begin(),   referencia1.end());
       
       
        if(itr_result1 != currValue.end()){
            
            itr_result2 = std::search(currValue.begin() + referencia1.size() +2  ,   currValue.end(),   referencia2.begin(),   referencia2.end());
           
          // std::copy( itr_result1,   itr_result2, temp.begin() );

             if(itr_result2 != currValue.end()){

                // std::cout << "prueba "<< std::string(itr_result1, itr_result1+4)<< "  :  ";
                // std::cout << "prueba2 "<< std::string(itr_result2, itr_result2+3)<<std::endl;

                values.insert(  std::string(itr_result1+6, itr_result2)  );
               // values.insert( currValue );
             }
             
        }
       
    }

    
    for (std::multiset<std::string>::iterator itr = values.begin(); itr !=values.end() ;  ++itr ) {
       
       //if(IsWikiLink( *itr )) {
            std::cout<< *itr << IsWikiLink( *itr )  <<std::endl;
      // }
       
       
    }

    return 0;
}