#include "Species.hh"

void Species::start_species(string dna, int k)
{
    //this->name = name;
/*
    No esta el parametro name para la especie ya que implementandola me di cuenta que si queria 
    usar un map en el conjunto de especies, usaria el nombre en el map, y seria redundante
    ponerlo tambien aqui.
    Tambien podria haber usado un list en el conjunto en vez de un map y entonces meter el name
    aqui, pero me resulto mas sencillo hacer la clase con un map.
*/
    this->dna = dna;
    //creacion del kmer a continuacion
    for (int i = 0; i < dna.size()+1-k; ++i){
        vector <char> v(k);
        for (int j = 0; j < k; ++j){
            v[j] = dna[i+j];
        }
        string s(v.begin(), v.end());
        map<string, int>::iterator it = kmer.find(s);
        if (it != kmer.end()) it -> second += 1;
        else kmer.insert(make_pair(s, 1));
    }
}

string Species::get_dna() const
{
    return dna;
}
/*
string Species::get_name()
{
    return name;
}
*/
 map<string, int> Species::get_kmer() const
 {
     return kmer;
}
