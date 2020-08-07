#include <iostream>     // for cout, cin
#include <fstream>      // for ifstream
#include <sstream>      // for stringstream
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"
#include <ctime>


using std::cout;            using std::endl;
using std::ifstream;        using std::stringstream;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;   using std::cin;



template<typename T>
void print_queue(T& q) {


    while(!q.empty()) {

        std::vector <std::string> myVector= q.top();
        q.pop();

         std::cout<< "\n\n{ ";
           for(std::vector <std::string>::iterator itr = myVector.begin();
                            itr != myVector.end() ;
                            ++itr){

                          std::cout <<*itr<<" " <<std::endl;

            }
            std::cout<< " }\n\n";
    }

    std::cout << '\n';

}


 //WikiScraper myScraper;
//myScraper.getLinkSet(start_page);


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
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: 1. Once your file reading is working, replace the below
    //          return statement with "return {};".
    //       2. Make sure that you've copied over your findWikiLinks method
    //          from Part A into wikiscraper.cpp.
    //       3. Finally, implement this function per Part B in the handout!
    //
    //                Best of luck!
    //"File reading works!", start_page, end_page


    WikiScraper myScraper;
   //myScraper.getLinkSet(start_page);


     std::unordered_set <std::string>  startedLinks   = myScraper.getLinkSet(start_page);
     std::unordered_set <std::string>  targetLinks  = myScraper.getLinkSet(end_page);

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
      //  while (getline(std::cin, dato),  dato=="2") {
         while(true){

            std::cout << "\n>---------------------------------------------------------------------------------\n" << std::endl;



            /* ANADIMOS EL NOMBE DE LA PAGINA ACTUAL AL FINAL DEL VECTOR QUE VAMOS A ANALIZAR */
            vectResult.push_back( currentLink );

            std::cout << "\n>ANALISIS NUEVA PAGINA ......" << currentLink << "\n\n";





            /* 1-> COMPARA LOS LINKS ACTUALES CON EL LINK TARGET ------------------------------- */


                //while (itrStartLinks != itrEndLinks) {
                for ( std::vector<std::string> ::iterator itr2 = vectorTemporal.begin()  ;   itr2 != vectorTemporal.end() -1  ; ++itr2 ) {

                            std::cout << "Comparando " <<   *itr2   << "  con : " << end_page <<std::endl;

                            if (*itr2  ==  end_page) {

                                std::cout <<"<- ENCONTRADO  LA PRIMERA PAGINA FINAL ->"<<   *itr2  <<std::endl;
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
                                    queryLinks = myScraper.getLinkSet(*itrVec);


                                /* CONVERTIR EL RESULTADO EN UN VECTOR */
                                    std::vector<std::string> vectorConverter;
                                   // vectorConverter.reserve(queryLinks.size());


                                /* MOSTRANDO EL INICIO DEL VECTOR */
                                   // std::cout<<"\n\n { "  << std::endl ;

                                /* CONVIRTIENDO LA UNORDER_SET A UN VECTOR PARA ANADIR A LA PQ */
                                    for ( std::unordered_set<std::string>::iterator  it = queryLinks.begin();
                                            it != queryLinks.end();
                                            ++it )
                                    {
                                        vectorConverter.push_back(*it);

                                            if (*it  ==  end_page) {

                                                std::cout <<"<- ENCONTRADO  LA PRIMERA PAGINA FINAL ->"<<   *it  <<std::endl;
                                                vectResult.push_back(*itrVec);
                                                return vectResult;

                                            }
                                        //    std::cout <<*it<<" " <<std::endl;
                                    }
                                   // std::cout<<"\n }  \n \n"  << std::endl ;


                                /* GUARDAMOS EN LA ULTIMA PARTE EL NOMBRE DE ARCHIVO-LINK EN EL VECTOR */
                                    vectorConverter.push_back( *itrVec );


                                /*  ASIGNAR A LA PRIORITY QUEUE SIEMPRE Y CUANDO EL VECTOR TENGA LINKS  */
                                   //  std::cout<< "probando: "<< vectorConverter.size() <<std::endl;
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
} //End findWikiLadder













int main() {
    /* Container to store the found ladders in */
    vector< vector<string> > outputLadders;

    std::cout << "probando";
//    WikiScraper myScraper;
//    unordered_set <std::string> targetLinks = myScraper.getLinkSet("Republic_of_Colombia");

//    for ( std::unordered_set<std::string> ::iterator itr= targetLinks.begin()  ; itr != targetLinks.end() ; ++itr ) {
//                std::cout << *itr <<std::endl;
//        }



//    cout << "Enter a file name: ";
//    string filename;
//    getline(cin, filename);

    // TODO: Create a filestream from the filename.
    //       For each pair {start_page, end_page} in the input file,
    //       retrieve the result of findWikiLadder(start_page, end_page)
    //       and append that vector to outputLadders.


    // Write code here
//    std::string start_page  =  "Ibagué"   ; // "Fruit"       ; //"Ibagué";
//    std::string end_page    =  "Cundinamarca_Department_(1820)" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//    std::string start_page  =  "Fruit"   ; // "Fruit"       ; //"Ibagué";
//    std::string end_page    =  "Strawberry" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//    std::string start_page  =  "Rioblanco"   ; // "Fruit"       ; //"Ibagué";
//    std::string end_page    =  "Tolima_Department" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//    std::string start_page  =  "Rioblanco"   ; // "Fruit"       ; //"Ibagué";
//    std::string end_page    =  "Tolima_(disambiguation)" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//        std::string start_page  =  "Emu"   ; // "Fruit"       ; //"Ibagué";
//        std::string end_page    =  "Stanford_University" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";


//        std::string start_page  =  "Gummy_bear"   ; // Gummy_bear ->Vegans->University_of_California,_Los_Angeles->Stanford_University
//            std::string end_page    =  "Marc_Tessier-Lavigne" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";


//        std::string start_page  =  "Sodium"   ; // "Fruit"       ; //"Ibagué";
//        std::string end_page    =  "Catalysis" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//            std::string start_page  =  "Stanford_University"   ; //->Graduate_school->canada
//            std::string end_page    =  "Group_of_Seven" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";


//            std::string start_page  =  "Fruit"   ; // "Fruit" ->Rice->/Old_French
//            std::string end_page    =  "Old_French" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";


//            std::string start_page  =  "Fruit"   ; // "Fruit" ->Opium_poppy-> France
//            std::string end_page    =  "France" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//            std::string start_page  =  "Fruit"   ; // "Fruit" ->Wine-> France->
//            std::string end_page    =  "Regions_of_France" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//            std::string start_page  =  "Fruit"   ; // "Fruit" ->Beech-> New_Caledonia ->Overseas_territory_(France)
//            std::string end_page    =  "Overseas_department_and_region" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";


//            std::string start_page  =  "Fruit"   ; // "Fruit" ->Beech-> New_Caledonia ->Overseas_territory_(France)
//            std::string end_page    =  "South_America" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

//            std::string start_page  =  "Hampshire"   ; // "Fruit" ->olive-> South_America
//            std::string end_page    =  "Grammy_Award" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

              //  std::string start_page  =  "Albert_Einstein"   ; // Albert_Einstein ->Wayback_Machine
              //  std::string end_page    =  "Scientology" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";

                std::string start_page  =  "Fruit"   ; // 78secs => Fruit ->Human->The_Americas->Muisca_people->Tisquesusa
                std::string end_page    =  "Jorge_Gamboa_Mendoza" ; //Strawberry"  ; // "Cundinamarca_Department_(1820)";



    clock_t start = clock();
    vector<string> myResult=   findWikiLadder(start_page, end_page);

    std::cout <<"\n\nMOSTRANDO LA ESCALERA" <<std::endl;

    for ( std::vector<std::string>::iterator itr= myResult.begin()  ; itr != myResult.end() ; ++itr ) {
                   std::cout << *itr <<std::endl;
     }

    /* CALCULANDO EL TIEMPO TRANSCURRIDO */
    start = clock() - start;
    cout << "\nTest completed in ";
    cout << ((double)(start) / CLOCKS_PER_SEC);
    cout << " seconds." << endl;


    /*
     * Print out all ladders in outputLadders.
     * We've already implemented this for you!
     */


//    for (auto& ladder : outputLadders) {
//        if(ladder.empty()) {
//            cout << "No ladder found!" << endl;
//        } else {
//            cout << "Ladder found:" << endl;
//            cout << "\t" << "{";

//            std::copy(ladder.begin(), ladder.end() - 1,
//                      std::ostream_iterator<string>(cout, ", "));
//            /*
//             * The above is an alternate way to print to cout using the
//             * STL algorithms library and iterators. This is equivalent to:
//             *    for (size_t i = 0; i < ladder.size() - 1; ++i) {
//             *        cout << ladder[i] << ", ";
//             *    }
//             */
//            cout << ladder.back() << "}" << endl;
//        }
//    }


    return 0;
}







