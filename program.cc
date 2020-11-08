#include <iostream>
#include "Species.hh"
#include "Set_Species.hh"
#include "Cluster.hh"
#include "Set_Cluster.hh"

using namespace std;
int main(){
    int k;
    cin >> k;
    Set_Species conjunto1;
    Set_Cluster conjunto2;
    string a;
    cin >> a;
    while (a != "fin"){
        if (a == "crea_especie") {
            string name, dna;
            cin >> name >> dna;
            cout << "# " << a << ' ' << name << ' ' << dna << endl;
            Species especie;
            especie.start_species(dna, k);
            conjunto1.add_species(name, especie);
            cout << endl;
        }
        else if (a == "obtener_gen"){
            string name;
            cin >> name;
            cout << "# " << a << ' ' << name << endl;
            conjunto1.print_dna(name);
            cout << endl;
        }
        else if (a == "distancia"){
            string name1, name2;
            cin >> name1 >> name2;
            cout << "# " << a << ' ' << name1 << ' ' << name2 << endl;
            double x = conjunto1.distance(name1, name2);
            if (x != -1) cout << x << endl;
            cout << endl;
        }
        else if (a == "elimina_especie"){
            string name;
            cin >> name;
            cout << "# " << a << ' ' << name <<endl;
            conjunto1.delete_species(name);
            cout << endl;
        }
        else if (a == "existe_especie"){
            string name;
            cin >> name;
            cout << "# " << a << ' ' << name << endl;
            conjunto1.exists(name);
            cout << endl;
        }
        else if (a == "lee_cjt_especies"){
            cout << "# " << a << endl;
            conjunto1.read_set_species(k);
            cout << endl;
        }
        else if (a == "imprime_cjt_especies"){
            cout << "# " << a << endl;
            conjunto1.print_set_species();
            cout << endl;
        }
        else if (a == "tabla_distancias"){
            cout << "# " << a << endl;
            conjunto1.print_matrix_distance();
            cout << endl;
        }
        else if (a == "inicializa_clusters"){
            cout << "# " << a << endl;
            if(conjunto1.get_modified())
            {
                conjunto1.matrix_distance();
            }
            conjunto2.start_cluster(conjunto1.get_ssp(), conjunto1.get_matrix());
            conjunto2.print_matrix_dist();
            cout << endl;
        }
        else if (a == "ejecuta_paso_wpgma"){
            cout << "# " << a << endl;
            if(conjunto2.step_wpgma_is_printable())
            {
                conjunto2.step_wpgma();
                conjunto2.print_matrix_dist();
            }
            else cout << "ERROR: num_clusters <= 1" << endl;;
            cout << endl;
        }
        else if (a == "imprime_cluster"){
            string name;
            cin >> name;
            cout << "# " << a << ' ' << name << endl;
            conjunto2.print_cluster(name);
            cout << endl;
        }
        else{
            cout << "# " << a << endl;
            if(conjunto1.get_modified())
            {
                conjunto1.matrix_distance();
            }
            conjunto2.print_filogen_tree(conjunto1.get_ssp(), conjunto1.get_matrix());
            cout << endl;
        } 
        cin >> a;
    }
}
