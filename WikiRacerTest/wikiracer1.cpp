#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <queue>


/*

    ESTE PROGRAMA ES UNA VERSION REDUCIDA DEL PROGRAMA WIKIRACER 
    QUE EN VEZ DE BUSCAR EN LA WIKIPEDIA, BUSCA EN ARCHIVOS txt,
    ESTO LO HICE PARA PODER REALIZAR PRUEBAS CONSTRUYENDO CAMINOS SINTETICOS
    PARA PODER DEPURAR EL PROGRAMA.
    Ejemplos que se pueden recorrer.
    Espinal.txt->Auto.txt
    Historia.txt -> Frutas.txt
    EL PROYECTO ORIGINAL ESTA EN UN PROYECTO LLAMADO WikiRacer DONDE REEMPLACE 
    LA FUNCION findWikiLinks CON EL CONTENIDO DE ESTE ARCHIVO Y CAMBIANDO myScraper POR 
    myScraper.getLinkSet USANDO UN OBJETO TIPO WikiScraper CON NOMBRE myScraper
    
    HACER COMPARACIONES CON ESTE CODIGO A FUTURO PARA VER VELOCIDAD DE DESEMPENO
    https://github.com/kevtan/wiki-racer/tree/master/src
*/

void compararConElArchivo(std::unordered_set<std::string>& result, std::string fileAcomparar );

/* CHANGE kPath TO WHICHEVER FILE PATH LEADS TO YOUR TEXT FILES */
const std::string kPath = "";

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




std::string fileToString(std::ifstream& inp) {
    std::string ret;
    std::string line;
    while(std::getline(inp, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        ret += line + " ";
       
    }
    return ret;
}




 std::unordered_set<std::string> findWikiLinks(std::string& inputString){

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


std::unordered_set<std::string> myScraper(std::string archivo) {

    std::ifstream file1(kPath + archivo ); //"suarez.txt");
    std::string fileInString = fileToString(file1);
    std::unordered_set<std::string> result = findWikiLinks(fileInString  );

    return result;
}






/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
std::vector<std::string> findWikiLadder(const std::string& start_page,   const std::string& end_page) {
    // TODO: 1. Once your file reading is working, replace the below
    //          return statement with "return {};".
    //       2. Make sure that you've copied over your findWikiLinks method
    //          from Part A into wikiscraper.cpp.
    //       3. Finally, implement this function per Part B in the handout!
    //
    //                Best of luck!
    //"File reading works!", start_page, end_page


   

     std::unordered_set <std::string>  startedLinks   = myScraper(start_page);
     std::unordered_set <std::string>  targetLinks  = myScraper(end_page);
    
//    std::cout << "\nmostrando los links de " << start_page << "\n";

//     for ( std::unordered_set<std::string> ::iterator itr= startedLinks.begin()  ; itr != startedLinks.end() ; ++itr ) {
//             std::cout << *itr <<std::endl;
//     }

//     std::cout << "\nmostrando los links de " << end_page << "\n";
//     for ( std::unordered_set<std::string> ::iterator itr2= targetLinks.begin()  ; itr2 != targetLinks.end() ; ++itr2 ) {
//             std::cout << *itr2 <<std::endl;
//     }
//     return {};

    /* CONVERTIR EL RESULTADO DE startedLinks EN UN VECTOR */
        std::vector<std::string> vectorConverter1;
        vectorConverter1.reserve(startedLinks.size());

        for ( std::unordered_set<std::string>::iterator  it = startedLinks.begin();
              it != startedLinks.end(); ++it )
        {
            vectorConverter1.push_back(*it);
        }
        vectorConverter1.push_back(start_page);

        // std::vector <std::string>::iterator itrStartLinks  =  vectorConverter1.begin();
        // std::vector <std::string>::iterator itrEndLinks    =  vectorConverter1.end();
    /*  HASTA AQUI VA LA CONVERSION   */




    /* DEFINIMOS EL VECTOR QUE RETORNARA LA FUNCION*/
    std::vector<std::string> vectResult;
    std::string currentLink =start_page;





    /* FUNCION DE COMPARACION */

        auto compareFn = [&targetLinks] ( std::vector <std::string> vector1 ,  std::vector <std::string> vector2 ) {
        
            std::vector <std::string>::iterator  itrStartVector1  =  vector1.begin();
            std::vector <std::string>::iterator  itrEndVector1    =  vector1.end();

            int counterLinksVector1=0;

            /* 1- COMPARA LOS LINKS VECTOR1  CON EL LINK TARGET */

                while (itrStartVector1 != itrEndVector1) {

                // std::cout << *itrStartLinks<<std::endl;

                        for(std::unordered_set <std::string>::iterator itrTarget = targetLinks.begin();
                                itrTarget != targetLinks.end() ;
                                ++itrTarget)
                        {

                            if(*itrStartVector1 == *itrTarget)  {
                                    counterLinksVector1++;
                            }

                        }


                ++itrStartVector1;
                }

            /* 1- FIN COMPARACION LINKS VECTOR1 */






            /* 2- COMPARA LOS LINKS VECTOR2  CON EL LINK TARGET */
                std::vector <std::string>::iterator  itrStartVector2  =  vector2.begin();
                std::vector <std::string>::iterator  itrEndVector2    =  vector2.end();

                int counterLinksVector2=0;
                while (itrStartVector2 != itrEndVector2) {

                // std::cout << *itrStartLinks<<std::endl;

                        for(std::unordered_set <std::string>::iterator itrTarget = targetLinks.begin();
                                itrTarget != targetLinks.end() ;
                                ++itrTarget)
                        {

                            if(*itrStartVector2 == *itrTarget)  {
                                    counterLinksVector2++;
                            }

                        }

                    ++itrStartVector2;

                }

            /* 2- FIN COMPARACION LINKS VECTOR1 */ 



            // std::cout <<"counterLinksVector1 :" <<counterLinksVector1<<std::endl;
            // std::cout <<"counterLinksVector2 :" <<counterLinksVector2<<std::endl;

            if(counterLinksVector1==0 && counterLinksVector2==0){
                //   std::cout <<"comparamos por tamano del vector :";
                //  std::cout <<"vector1.size() :" <<vector1.size()<<std::endl;
                // std::cout <<"vector2.size() :" <<vector2.size()<<std::endl;
                return (vector1.size())< (vector2.size());
            }


            return (counterLinksVector1 ) < ( counterLinksVector2 );
        };
    /* - FIN DE LA FUNCION DE COMPARACION -------------------------------------------------------------- */









    /* CREAMOS LA PRIORITY QUEUE */
       std::priority_queue < std::vector<std::string>,
                            std::vector< std::vector<std::string> >,
                            decltype(compareFn)  >     ladderQueue(compareFn);



    /* ANADIMOS EL VECTOR INICIAL DE LINKS */
       // ladderQueue.push(vectorConverter1);
          /* 3- ELIMINAMOS */
        //      ladderQueue.pop();




    /* COMPARACION GENERAL DE PAGINAS */
    std::string dato="";
    std::cout << "\n\n\n\n\n\n\n\n\n->INIANDO : ............................................................................\n";
    std::cout << ".......................................................................................\n";
    std::cout <<  "\nINGRESE CONTINUADOR INICIAL :  " ;
 
   // std::vector<std::string> vectorAIterar  =  vectorConverter1;
  std::vector<std::string> vectorTemporal= vectorConverter1;
    
    /* <------------------------------  LAZO PRINCIPAL ---------------------------------->*/
        while (getline(std::cin, dato),  dato=="2") {
        // while(true){

            std::cout << "\n>---------------------------------------------------------------------------------\n" << std::endl;
    
        

            /* ANADIMOS EL NOMBE DE LA PAGINA ACTUAL AL FINAL DEL VECTOR QUE VAMOS A ANALIZAR */
            vectResult.push_back( currentLink );
            
            std::cout << "\n>ANALISIS NUEVA PAGINA ......" << currentLink << "\n\n";





            /* 1-> COMPARA LOS LINKS ACTUALES CON EL LINK TARGET ------------------------------- */

            
                //while (itrStartLinks != itrEndLinks) {
                for ( std::vector<std::string> ::iterator itr2 = vectorTemporal.begin()  ;   itr2 != vectorTemporal.end() -1  ; ++itr2 ) {
            
                            std::cout << "Comparando " <<   *itr2   << "  con : " << end_page <<std::endl;

                            if (*itr2  ==  end_page) {

                                std::cout <<"ENCONTRADO EN LA PRIMERA PAGINA"<<   *itr2  <<std::endl;
                                return vectResult;

                            }

                // itrStartLinks++;
                }
            /* 1- FIN DE LA COMPARACION DE LINKS -------------------------------------------------  */




            
            
            std::cout << "\n\n>NINGUN LINK HIZO MACH con : " << currentLink << std::endl;

            std::cout << ">TAMANO DEL VECTOR : "<< vectorTemporal.size() << std::endl<< "\n\n";




            /* 2->SI EL VECTOR ESTA VACIO ENTONCES SACA OTRO VECTOR DE PQ */
            if(vectorTemporal.size()<=1){

                    std::cout << "\n>LA ACTUAL PAGINA NO TIENE LINKS ........\n" << std::endl;


                    /* SACAMOS OTRO VECTOR DE LA PQ */
                    //ladderQueue.pop();
                    

                    /* ASGINAMOS EL VECTOR */
                    //std::vector<std::string> auxVect = ladderQueue.top();
                // vectorTemporal = ladderQueue.top();


                

                    while ( vectorTemporal.size()<=1 )
                    {
                        std::cout << "\n\n->ESTA VACIO  VECTOR SACADO ......\n\n" << std::endl;
                
                        std::cout << "\n->OTRO INTENTO, SACAMOS OTRO VECTOR DE LA PRIORITY QUEUE ......\n\n" << std::endl;
                        
                        if ( ladderQueue.empty() ) return {};
                            
                        ladderQueue.pop();
                        vectorTemporal  = ladderQueue.top();
                        std::cout << "\n\n> SACAMOS UN VECTOR DE LA PRIORITY QUEUE ......\n\n" << vectorTemporal.size()<< std::endl;
                

                    }
            }
            
        /* 2- FIN DE LA REVISION DEL VECTOR ACTUAL -------------------------------------------------  */




          







            /* 4 -> AGREGAR EL VECTOR A LA PRIORITY QUEUE */

                std::cout << "\n INICIANDO LA BUSQUEDA DE TODOS LOS LINKS PARA CADA link DE LA PAGINA ACTUAL  ......\n" << std::endl;

                /* RECORRER EL VECTOR PARA EXTRAER LOS LINKS DE CADA LINK*/
                for (std::vector<std::string>::iterator itrVec = vectorTemporal.begin() ;
                    itrVec != vectorTemporal.end() - 1  ;
                    ++itrVec)
                {

                      

                                /* CREAMOS UN UNORDERED SET PARA ALMACENAR LO LINKS */
                                    std::unordered_set<std::string>  queryLinks;


                                /* EXTRACCION DE LINKS */
                                    std::cout<< "\n\n->EXTRAYENDO DATOS DEL ARCHIVO-LINK : "<< *itrVec <<std::endl;
                                    queryLinks = myScraper(*itrVec);
                                
                            
                                /* CONVERTIR EL RESULTADO EN UN VECTOR */
                                    std::vector<std::string> vectorConverter;
                                   // vectorConverter.reserve(queryLinks.size());
                            

                                /* MOSTRANDO EL INICIO DEL VECTOR */
                                    std::cout<<"\n\n { "  << std::endl ;

                                /* CONVIRTIENDO LA UNORDER_SET A UN VECTOR PARA ANADIR A LA PQ */
                                    for ( std::unordered_set<std::string>::iterator  it = queryLinks.begin();
                                            it != queryLinks.end(); 
                                            ++it )
                                    {
                                        vectorConverter.push_back(*it);
                                            std::cout <<*it<<" " <<std::endl;
                                    }
                                    std::cout<<"\n }  \n \n"  << std::endl ;


                                /* GUARDAMOS EN LA ULTIMA PARTE EL NOMBRE DE ARCHIVO-LINK EN EL VECTOR */
                                    vectorConverter.push_back( *itrVec );


                                /*  ASIGNAR A LA PRIORITY QUEUE SIEMPRE Y CUANDO EL VECTOR TENGA LINKS  */
                                     std::cout<< "probando: "<< vectorConverter.size() <<std::endl;
                                    if(  vectorConverter.size() <=1 ) {
                                         std::cout<< "EL VECTOR NO FUE ANADIDO" <<std::endl;
                                    }else{
                                        ladderQueue.push(vectorConverter);
                                    }
                                    


                }  
                /* FIN - RECORRER EL VECTOR PARA EXTRAER LOS LINKS DE CADA LINK*/



                //std::priority_queue <std::string>:: pointerStart= ladderQueue.






                std::cout << "\n\n<---------- TERMINE DE IMPRIMIR TODA LA PRIORITY QUEUE ---------->\n\n\n\n" << std::endl;

               
                /* CHEQUEANDO QUE LA ESCALERA NO ESTE VACIA */
                if ( ladderQueue.empty() ) {
                        
                    std::cout<< "LA PRIORITY QUEUE ESTA VACIA ";
                    return {};
                 
                } // END if ( ladderQueue.empty())


                vectorTemporal= ladderQueue.top();
                ladderQueue.pop();
                std::cout << "\n\n> SACAMOS UN VECTOR DE LA PRIORITY QUEUE ......\n\n" << vectorTemporal.size()<< std::endl;
            
            


            /* 2->SI EL VECTOR ESTA VACIO ENTONCES SACA OTRO VECTOR DE PQ */
                if( vectorTemporal.size()<=1 ) {

                        std::cout << "\n>LA PAGINA ELEGIDA NO TIENE LINKS ........\n" << std::endl;


                        while ( vectorTemporal.size()<=1 )
                        {
                            std::cout << "\n\n->EL VECTOR SACADO ESTA VACIO ......\n\n" << std::endl;
                    
                            std::cout << "\n->OTRO INTENTO, SACAMOS OTRO VECTOR DE LA PRIORITY QUEUE ......\n\n" << std::endl;
                            
                            if ( ladderQueue.empty() ) return {};
                                
                            ladderQueue.pop();
                            vectorTemporal  = ladderQueue.top();
                            std::cout << "\n\n> SACAMOS UN VECTOR DE LA PRIORITY QUEUE ......\n\n" << vectorTemporal.size()<< std::endl;
                    

                        }
                }
                
            /* 2- FIN DE LA REVISION DEL VECTOR ACTUAL -------------------------------------------------  */



                

                currentLink    =  vectorTemporal.back();
                std::cout << "\n>LINKS DE LA  NUEVA PAGINA QUE VAMOS A BUSCAR : \n\n"<< currentLink << "{\n\n";
                for ( std::vector<std::string> ::iterator itr2= vectorTemporal.begin()  ;
                         itr2 != vectorTemporal.end() -1; 
                         ++itr2 ) 
                {
                    std::cout << *itr2 <<std::endl;
                }

                std::cout <<"\n}\n\n";

            
                

                std::cout << "\n\n>INGRESANDO CONTINUADOR : " ;


        }// FIND while(true)



    return {};

}// END findWikiLadder















int main(){

    // std::ifstream file1(kPath+"datasimple.txt");
    
//   std::ifstream file1(kPath + "suarez.txt" ); //);
//     std::string fileInString = fileToString(file1);
//      std::unordered_set<std::string> result = findWikiLinks(fileInString  );
    

    

    //compararConElArchivo(result,"[output]-quokka.txt");
    
    
    std::string start_page   =  "espinal.txt"   ; // "Fruit"       ; //"Ibagué";
    std::string end_page    =  "auto.txt" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

    //  std::string start_page  =  "historia.txt"   ; // "Fruit"       ; //"Ibagué";
    // std::string end_page     =  "frutas.txt" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

   
    std::vector<std::string> myResult=   findWikiLadder(start_page, end_page);


    for ( std::vector<std::string> ::iterator itr= myResult.begin()  ; itr != myResult.end() ; ++itr ) {
            std::cout << *itr <<std::endl;
    }
    
  
    return 0;
} 











void compararConElArchivo(std::unordered_set<std::string>& result, std::string fileAcomparar ){
    /*PRUEBA DE COMPARACION*/
    std::ifstream fileReferencia(kPath+fileAcomparar);
    std::string fileRefInString = fileToString(fileReferencia);
    std::stringstream streamReferencia(fileRefInString);

    std::string palabra;
    while (streamReferencia >> palabra){

            if (result.count(palabra)){
                    std::cout << palabra << " : "<<result.count(palabra) <<std::endl;
            }else{
                  std::cout << "ERROR ----palabra no encontrada"; 
                return;
            }
            
    }
    std::cout<< "LLEGUE AL FINAL RESULTADO CORRECTO";
}