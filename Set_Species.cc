#include "Set_Species.hh"

//////////////////////////
/*private  functions*/////
//////////////////////////

list <pair<int, int>> Set_Species::juntar(const map <string, int>& kmer1, const map <string, int>& kmer2)
{
    map<string, int>::const_iterator it1 = kmer1.begin();
    map<string, int>::const_iterator it2 = kmer2.begin();
    list <pair<int, int>> conjunto;
    while (it1 != kmer1.end() and it2 != kmer2.end()){
        string one = it1 -> first;
        string two = it2 -> first;
        if (one < two){
            conjunto.insert(conjunto.end(), make_pair(it1 -> second, 0));
            ++it1;
        }
        else if (one > two){
            conjunto.insert(conjunto.end(), make_pair(0, it2 -> second));
            ++it2;
        }
        else{
            conjunto.insert(conjunto.end(), make_pair(it1 -> second, it2 -> second));
            ++it1;
            ++it2;
        }
    }
    if (it1 != kmer1.end()){
        while (it1 != kmer1.end()){
            conjunto.insert(conjunto.end(), make_pair(it1 -> second, 0));
            ++it1;
        }
    }
    else if (it2 != kmer2.end()){
        while (it2 != kmer2.end()){
            conjunto.insert(conjunto.end(), make_pair(0, it2 -> second));
            ++it2;
        }
    }
    return conjunto;
}

double Set_Species::intersection(const list <pair<int, int>>& conjunto)
{
    double number = 0;
    list <pair<int, int>>::const_iterator it;
    for (it = conjunto.begin(); it != conjunto.end(); ++it){
        double one = it -> first;
        double two = it -> second;
        if (one < two) number += one;
        else number += two;
    }
    return number;
}

double Set_Species::unionmap(const list <pair<int, int>>& conjunto)
{
    double number = 0;
    list <pair<int, int>>::const_iterator it;
    for (it = conjunto.begin(); it != conjunto.end(); ++it){
        double one = it -> first;
        double two = it -> second;
        if (one > two) number += one;
        else number += two;
    }
    return number;
}

//////////////////////////
/*main functions*/////////
//////////////////////////

void Set_Species::add_species(string name, const Species& nueva)
{
    map<string, Species>::const_iterator it = ssp.find(name);
    if (it != ssp.end()) cout << "ERROR: La especie " << name << " ya existe." << endl;
    else {
        ssp.insert(make_pair(name, nueva));
        modified = true;
    }
}

void Set_Species::print_dna(string name) const
{
    map<string, Species>::const_iterator it = ssp.find(name);
    if (it != ssp.end()) cout << it -> second.get_dna() << endl;
    else cout << "ERROR: La especie " << name << " no existe." << endl;
}

double Set_Species::distance(string name1, string name2) 
{
    map<string, Species>::const_iterator it1 = ssp.find(name1);
    map<string, Species>::const_iterator it2 = ssp.find(name2);
    if ((it1 == ssp.end()) and (it2 == ssp.end())){ 
        cout << "ERROR: La especie " << name1 << " y la especie " << name2  << " no existen." << endl;
        return -1;
    }
    else if (it1 == ssp.end()) {
        cout << "ERROR: La especie " << name1 << " no existe." << endl;
        return -1;
    }
    else if (it2 == ssp.end()) {
        cout << "ERROR: La especie " << name2 << " no existe." << endl;
        return -1;
    }
    else {
        map <string, int> kmer1 = it1 -> second.get_kmer();
        map <string, int> kmer2 = it2 -> second.get_kmer();
        list <pair<int, int>> conjunto;
        conjunto = juntar(kmer1, kmer2);
        //first we will calculate the intersection
        double ene1 = intersection(conjunto);
        //then we will calculate the union
        double ene2 = unionmap(conjunto);
        return ((1 - (ene1 / ene2)) * 100);
    }
}

void Set_Species::delete_species (string name)
{
    map<string, Species>::iterator it = ssp.find(name);
    if (it != ssp.end()){ 
        ssp.erase(name);
        modified = true;
    }
    else cout << "ERROR: La especie " << name << " no existe." << endl;;
}

void Set_Species::exists(string name) const
{
    map<string, Species>::const_iterator it = ssp.find(name);
    if (it != ssp.end()) cout << "SI" << endl;
    else cout << "NO" << endl;
}

void Set_Species::read_set_species(int k)
{
    int n;
    cin >> n;
    //este if lo pongo para no meterlo en el while,
    //asi ahorramos ejecutar esto siempre en el bucle, pero nos
    //aseguramos que si tiene elementos ponemos el bool
    //modified en true,
    //todo esto es por si se da el caso que el conjunto esta
    //vacio y n = 0
    if (ssp.begin() != ssp.end()) modified = true;
    while (ssp.begin() != ssp.end()){
        ssp.erase(ssp.begin() -> first);
    }
    for (int i = 0; i < n; ++i){
        string name, dna;
        cin >> name >> dna;
            Species especie;
            especie.start_species(dna, k);
            add_species(name, especie);
    }
}

void Set_Species::print_set_species() const
{
    map<string, Species>::const_iterator it;
    for (it = ssp.begin(); it != ssp.end(); ++it)
    {
        cout << it -> first << ' ' << it -> second.get_dna() << endl;
        
    }
}

void Set_Species::matrix_distance() 
{
    int n = ssp.size();
    Matrix hola(n, Fila(n));
    int i = 0;
    map<string, Species>::const_iterator it1;
    map<string, Species>::const_iterator it2;
    for (it1 = ssp.begin(); it1 != ssp.end(); ++it1){
        int j = i + 1;
        map<string, Species>::const_iterator aux = it1;
        ++aux;
        for (it2 = aux; it2 != ssp.end(); ++it2){
            hola[i][j] = distance(it1 -> first, it2 -> first);
            ++j;
        }
        ++i;
    }
    dist = hola;
    modified = false;
}

void Set_Species::print_matrix_distance()
{
    if (modified) matrix_distance();
    int i = -1;
    map<string, Species>::const_iterator it1;
    map<string, Species>::const_iterator it2;
    for (it1 = ssp.begin(); it1 != ssp.end(); ++it1){
        cout << it1->first << ':' ;
        ++i;
        int j = i + 1;
        map<string, Species>::const_iterator aux = it1;
        ++aux;
        for (it2 = aux; it2 != ssp.end(); ++it2){
            cout << ' ' << it2-> first << ' ' << '(' << dist[i][j] << ')';    
            ++j;
        }
        cout << endl;
    }
}

bool Set_Species::get_modified() const
{
    return modified;
}

map<string, Species> Set_Species::get_ssp() const
{
    return ssp;
}

Matrix Set_Species::get_matrix() const
{
    return dist;
}
