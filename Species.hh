/**
 * @file Species.hh
 * @version 1.0
 * @date 17/05/2020
 * @author Sabater Andrade, Celeste
 * @brief Es la clase usada para una especie y contiene todas sus funciones y utilidades
 */
#ifndef SPECIES_HH
#define SPECIES_HH

#include <iostream>
#ifndef NO_DIAGRAM
#include <vector>
#include <string>
#include <map>
#endif

using namespace std;

/**
 * @class Species
 * @brief Es la clase que gestiona una especie.
 */

class Species {

private:
    
/*
    No esta el parametro name para la especie ya que implementandola me di cuenta que si queria 
    usar un map en el conjunto de especies, usaria el nombre en el map, y seria redundante
    ponerlo tambien aqui.
    Tambien podria haber usado un list en el conjunto en vez de un map y entonces meter el name
    aqui, pero me resulto mas sencillo hacer la clase con un map.
*/

    //string name;
    string dna; /*!< Es el adn de una especie.*/
    map <string, int> kmer; /*!< Es el kmer de una especie (un conjunto de strings de medida k), que es usado posteriormente para calcular la distancia genetica entre 2 especies distintas.*/
    
public:
    
    /**
     * @pre Necesita dos strings, un nombre y un adn.
     * @post Modifica el nombre de la especie y su adn concorde a los string que se le da, tambien calcula su kmer (un conjunto de strings y ints).
     * @brief Es la generadora.
     * @param dna Es el ADN que tendra la especie.
     * @param k Usado para crear el kmer de la especie.
     */
    void start_species (string dna, int k);
    
    /**
     * @pre None.
     * @post Devuelve el adn de la especie.
     */
    //the function returns the dna of the species matching that name
    string get_dna() const;
    
    //the function returns the name of the species matching that name
    //string get_name() const;
    
    /**
     * @pre None.
     * @post Devuelve el kmer de la especie.
     */
    //the function returns the kmer of the species matching that name
    map<string, int> get_kmer() const;
};

#endif
