/**
 * @file Set_Species.hh
 * @version 1.0
 * @date 17/05/2020
 * @author Sabater Andrade, Celeste
 * @brief Es la clase usada para el conjunto de especies y contiene todas sus funciones y utilidades
 */
#ifndef SET_SPECIES_HH
#define SET_SPECIES_HH

#include <iostream>
#include "Species.hh"
#ifndef NO_DIAGRAM
#include <vector>
#include <list>
#include <map>
#endif

using namespace std;

typedef vector <double> Fila;
typedef vector <Fila> Matrix;

/**
 * @class Set_Species
 * @brief Es la clase que gestiona el conjunto de especies, calcula las distancias entre estas, elimina y añade al conjunto, hace la matriz de distancias...
 */

class Set_Species {
    
private:
    
    map<string, Species> ssp; /*!< Es el conjunto de especies, el identificador es un string y luego como valor tiene una especie.*/
    Matrix dist; /*!< Es una matriz de n por n (n siendo el tamaño del map ssp) que contiene los datos de distancia en su triangular superior, solo se actualiza cuando se quiere imprimir y esta desactualizada
    y cuando se llama a la funcion Set_Species::matrix_distance().*/
    bool modified = false; /*!< Sirve para ver si se ha modificado el conjunto de especies y por lo tanto es necesario volver a hacer la matriz distancia en la funcion print_matrix_distance. */
    
    /**
     * @pre Necesita dos kmer.
     * @post Junta dos kmer en una lista de pair (el numero de apariciones de cada grupo de strings en los dos kmer).
     * @param kmer1 Es el primer kmer.
     * @param kmer2 Es el segundo kmer.
     */
    list <pair<int, int>> juntar(const map <string, int>& kmer1, const map <string, int>& kmer2);
    
    /**
     * @pre Un kmer.
     * @post Suma de toda la lista el elemento menor de cada pair.
     */
    double intersection(const list <pair<int, int>>& conjunto);
    
    /**
     * @pre Un kmer.
     * @post Suma de toda la lista el elemento mayor de cada pair.
     */
    double unionmap(const list <pair<int, int>>& conjunto);
    
public:
    
    /**
     * @pre Necesita una especie ya existente.
     * @post Añadimos la especie al conjunto, siempre que el su identificador (el nombre) no este ya repetido, si esta repetido, da error.
     * @param name Es el nombre de la especie.
     * @param nueva Es la especie que añadiremos al conjunto.
     */
    //creates a new specie with the first string as the name and the second
    //as the dna
    void add_species (string name, const Species& nueva);
    
    /**
     * @pre Necesita que se le un nombre (un identificador).
     * @post Si existe en el conjunto de especies esa especie, imprime su ADN, si no existe da un error.
     * @param name Es el identificador que se usara para buscar la especie en el conjunto.
     */
    //the function prints the dna of the species matching that name
    //if there is no species matching this name, returns an error
    void print_dna(string name) const;
    
    /**
     * @pre Necesita que se le de el nombre (identificador) de dos especies distintas.
     * @post Calcula la distancia genetica de estas dos especies y devuelve un double de 4 decimales, si una de las dos (o ambas) especies no existe, da un error.
     * @param name1 Es el identificador de la primera especie.
     * @param name2 Es el identificador de la segunda especie.
     */
    //you put the name of two different species and
    //returns the distance between the two species
    //you get an error if one of the two species (or both) doesn't exists
    double distance(string name1, string name2);
    
    /**
     * @pre Necesita que se le de el nombre (identificador) de una especie.
     * @post Si existe una especie con ese identificador, la elimina, si no existe da un error.
     * @param name Es el identificador usado para buscar esa especie.
     */
    //given a certain name, the function deletes the
    //the species with that name, if there isn't any species
    //with that name, you get an error
    void delete_species (string name);
    
    /**
     * @pre Necesita que se le de el nombre (identificador) de una especie.
     * @post Si existe la especie con ese identificador, imprime "SI", en caso contrario "NO".
     * @param name Es el identificador usado para buscar esa especie.
     */
    //this function prints true in the screen if exists an species with
    //the given name, does the opposite if it's false
    void exists (string name) const;
    
    /**
     * @pre Ninguna precondicion.
     * @post Dentro de la funcion, primero se eliminaran todas las especies del conjunto, luego leera un numero n, despues se leeran n nuevas especies para el conjunto.
     * @param k Usado para crear el kmer de las especies.
     */
    //the function first read an x integer, then eliminates all the species
    //in the map, then reads x new species
    void read_set_species(int k);
    
    /**
     * @pre Ninguna precondicion.
     * @post Imprimira todas las especies del conjunto. De cada especie primero imprime el identificador, luego el ADN.
     */
    //this function just prints the name and the dna of all the species
    void print_set_species() const;
    
    
    /**
     * @pre Ninguna precondicion.
     * @post Esta funcion asigna la matriz de la clase con una que es creada aqui. La matriz tiene el valor de las distancias entre especies, y cada fila y columna esta asignada a una especie distinta.
     */
    //this function makes a matrix with the distance between all the species
    void matrix_distance();
    
    /**
     * @pre Ninguna precondicion.
     * @post Imprime la matriz de la clase, que tiene como valor las distancias entre especies.
     */
    //this function prints the matrix that creates the previous function
    void print_matrix_distance();

    /**
     * @pre Ninguna precondicion.
     * @post Devuelve el bool modified.
     */
    bool get_modified() const;
    
    /**
     * @pre Ninguna precondicion.
     * @post Devuelve el conjunto de especies.
     */
    map<string, Species> get_ssp() const;

    /**
     * @pre Ninguna precondicion.
     * @post Devuelve la matriz distancia.
     */
    Matrix get_matrix() const;
    
};

#endif
