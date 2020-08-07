#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "wikiscraper.h"
#include "error.h"
#include <sstream>
#include <set>
using std::cout;            using std::endl;
using std::cerr;            using std::string;
using std::unordered_map;   using std::unordered_set;




/*----------------------------- START DFA -------------------------------*/

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
        // std::cout <<"LoadWikiDFA...";
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

     std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  
    // std::cout <<"input en lowercase :"<< input;
    // std::cout << "\ntamano string entrada" <<input.size() <<std::endl;

    for(std::string::iterator itr = input.begin();   itr != input.end();   ++itr)   
    {
        /* 
            isalnum is exported by <cctype> 
            and checks if the input is an * alphanumeric character.
        */
    
        
        //if( isalnum(*itr) || *itr=='_' || *itr=='/' || *itr=='>'   || *itr=='<' || *itr=='%' ) {
        //char chartest =  ':';
        //  std::cout << "char "<< chartest <<std::endl;
        // if( isalnum(*itr) || *itr=='_' || *itr=='/' || *itr=='>'   || *itr=='<' || *itr=='%' ) {
        
        if(  *itr == '#' || *itr == ':' ) {
              return false;
        
        }
        else{
           
            //  std::cout << *itr <<std::endl;
            if( *itr !='w' &&  *itr !='i' &&  *itr !='k' &&  *itr !='/' ){
                
                 *itr = 'x';
                
            }
        }
        // else if(*itr == '#' || *itr != ':') {
        //     //std::cout << *itr <<std::endl;
        //     return false;
      
        // }
            
    }

//    std::cout << "\n\ndespues de formatear = "<< input << std::endl;
//      std::cout << "tamano string salida :" <<input.size() <<std::endl;
   
    return SimulateDFA(dfa_wikiChecker, input);
}
/*----------------------------- END DFA -------------------------------*/



/*
 * You should delete the code in this function and
 * fill it in with your code from part A of the assignment.
 *
 * If you used any helper functions, just put them above this function.
 */
unordered_set<string> findWikiLinks(const string& inputString) {
     std::stringstream inputStringStream(inputString);

    std::string word;

    std::string referencia1= "href";
    std::string referencia2= "\"";
    std::string::iterator itr_result1;
    std::string::iterator itr_result2;

    std::unordered_set<std::string> setWords;
    while(inputStringStream >> word){
        
      
        
        itr_result1 = std::search(word.begin(),   word.end(),   referencia1.begin(),   referencia1.end());
        
        if(itr_result1 != word.end()){
            // std::cout<<  std::string(itr_result1+1 ,  word.end() -2) ;
            itr_result2 = std::find(itr_result1+6   ,   word.end(),  '\"'  );
            
            if(itr_result2 != word.end()){
              
                 if (  IsWikiLink(    std::string(itr_result1 +6,   itr_result2)   ) ) {
                    //   std::cout<<  std::string(itr_result1 +12,   itr_result2) <<std::endl;
                        setWords.insert( std::string(itr_result1 +12,   itr_result2) );
                 }
            
            }
            
        }

        

    }
    return setWords;

}


/*
 * ==================================================================================
 * |                           DON"T EDIT ANYTHING BELOW HERE                       |
 * ==================================================================================
 */
unordered_set<string> WikiScraper::getLinkSet(const string& page_name) {
    if(linkset_cache.find(page_name) == linkset_cache.end()) {
        auto links = findWikiLinks(getPageSource(page_name));
        linkset_cache[page_name] = links;
    }
    return linkset_cache[page_name];
}


WikiScraper::WikiScraper() {
    (void)getPageSource("Main_Page");
#ifdef _WIN32
    // define something for Windows
    system("cls");
#else
    // define it for a Unix machine
    system("clear");
#endif
}


string createPageUrl(const string& page_name) {
    return "https://en.wikipedia.org/wiki/" + page_name;
}

void notFoundError(const string& msg, const string& page_name, const string& url) {
    const string title = "    AN ERROR OCCURED DURING EXECUTION.    ";
    const string border(title.size() + 4, '*');
    cerr << endl;
    errorPrint(border);
    errorPrint("* " + title + " *");
    errorPrint(border);
    errorPrint();
    errorPrint("Reason: " + msg);
    errorPrint();
    errorPrint("Debug Information:");
    errorPrint();
    errorPrint("\t- Input parameter: " + page_name);
    errorPrint("\t- Attempted url: " + url);
    errorPrint();
}

string WikiScraper::getPageSource(const string &page_name) {
    const static string not_found = "Wikipedia does not have an article with this exact name.";
    if(page_cache.find(page_name) == page_cache.end()) {
        QUrl url(createPageUrl(page_name).c_str()); // need c string to convert to QString

        QNetworkRequest request(url);

        QNetworkReply *reply(manager.get(request));

        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()) , &loop, SLOT(quit()));
        loop.exec();

        string ret = reply->readAll().toStdString();
        if(std::search(ret.begin(), ret.end(), not_found.begin(), not_found.end()) != ret.end()){
            notFoundError("Page does not exist!", page_name, url.toString().toStdString());
            return "";
        }
        size_t indx = ret.find("plainlinks hlist navbar mini");
        if(indx != string::npos) {
            return ret.substr(0, indx);
        }
        page_cache[page_name] = ret;
    }
    return page_cache[page_name];
}





