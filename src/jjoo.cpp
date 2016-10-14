#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs) {

    _anio = a;
    _atletas = as;
    _cronograma = cs;
    _jornadaActual = 1;

}

int JJOO::anio() const {
    return _anio;
}

vector<Atleta> JJOO::atletas() const {
    return _atletas;
}

int JJOO::cantDias() const {
    return _cronograma.size();
}

int JJOO::jornadaActual() const {
    return _jornadaActual;
}

vector<Competencia> JJOO::cronograma(const int &d) const {

    return _cronograma[d-1];
}

vector<Pais> JJOO::paises() const {
    int i = 0;
    vector<Pais> res;

    while ( i < _atletas.size() ) {
        bool ya_esta = false;
        int j = 0;

        while ( j<i && !ya_esta) {
            if ( res[j] == _atletas[i].nacionalidad() )
                ya_esta = true;
            j++;
        }

        if ( !ya_esta )
            res.push_back( _atletas[i].nacionalidad() );

        i++;
    }
    return res;
}

bool JJOO::masMedallas(const Pais &p1, const Pais &p2) const {
    if ( this->cantidadMedallasOro(p1) > this->cantidadMedallasOro(p2) )
        return true;
    if ( this->cantidadMedallasOro(p1) == this->cantidadMedallasOro(p2) && this->cantidadMedallasPlata(p1) > this->cantidadMedallasPlata(p2) )
        return true;
    if ( this->cantidadMedallasOro(p1) == this->cantidadMedallasOro(p2) && this->cantidadMedallasPlata(p1) == this->cantidadMedallasPlata(p2) && this->cantidadMedallasBronce(p1) > this->cantidadMedallasBronce(p2) )
        return true;
    return false;
}

int JJOO::posMax(const vector<pair<Pais, vector<int> > > &m, const int a) const {
    int i = 0;
    int res = 0;

    while (i < a) {
        if (masMedallas(m[i].first, m[res].first)) {
            res = i;

        }
        i++;
    }

    return res;

}

void JJOO::swap(vector<pair<Pais, vector<int> > > &m, const int n, const int k) const {
    pair<Pais, vector<int> > temp = m[n];
    m[n] = m[k];
    m[k] = temp;
}

void JJOO::ordenarMedallero(vector<pair<Pais, vector<int> > > &m) const {
    int actual = m.size()-1;
    while (actual > 0) {
        int max = this->posMax(m,actual);
        this->swap(m,max,actual);
        actual=actual-1;
    }
}

vector<Competencia> JJOO::competencias() const {

    vector<Competencia> vectorcomp;
    int i=0;

    while (i<_cronograma.size()) {
        int j = 0;
        while (j<_cronograma[i].size()) {
            vectorcomp.push_back(_cronograma[i][j]);
            j++;
        }
    i++;
    }
    return vectorcomp;
}

int JJOO::cantidadMedallasOro(const Pais &p) const {
    int cant = 0;
    int i = 0;
    vector<Competencia> comps = this->competencias();

    while ( i < comps.size() ) {

        if ( comps[i].finalizada() ) {
            vector<Atleta> r_actual = comps[i].ranking();
            if ( r_actual.size() > 0 && r_actual[0].nacionalidad() == p )
                cant++;
        }

        i++;
    }

    return cant;
}

int JJOO::cantidadMedallasPlata(const Pais &p) const {
    int cant = 0;
    int i = 0;
    vector<Competencia> comps = this->competencias();

    while ( i < comps.size() ) {

        if ( comps[i].finalizada() ) {
            vector<Atleta> r_actual = comps[i].ranking();
            if ( r_actual.size() > 1 && r_actual[1].nacionalidad() == p )
                cant++;
        }

        i++;
    }

    return cant;
}

int JJOO::cantidadMedallasBronce(const Pais &p) const {
    int cant = 0;
    int i = 0;
    vector<Competencia> comps = this->competencias();

    while ( i < comps.size() ) {

        if ( comps[i].finalizada() ) {
            vector<Atleta> r_actual = comps[i].ranking();
            if ( r_actual.size() > 2 && r_actual[2].nacionalidad() == p )
                cant++;
        }

        i++;
    }

    return cant;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {

    vector<Competencia> comp_finconor;
    int i=0;
    vector <Competencia> comp_iterar = this->competencias();

    while (i<comp_iterar.size()){
        if (comp_iterar[i].finalizada()&&comp_iterar[i].ranking().size()>0) comp_finconor.push_back(comp_iterar[i]);

        i++;
    }



    return comp_finconor;
}

vector<Atleta> JJOO::dePaseo() const {

    vector<Atleta> res;
    vector<Competencia> comps = this->competencias();
    int i = 0;

     while (i<_atletas.size()){
         int j = 0;
         bool pasea = true;

         while ( j < comps.size() && pasea ) {
             int k = 0;
             vector<Atleta> parts_actuales = comps[j].participantes();
             int participa = false;

             while ( k < parts_actuales.size() && !participa ) {
                 if ( parts_actuales[k] == _atletas[i] ) {
                     participa = true;
                     pasea = false;
                 }
                 k++;
             }
             j++;
         }
         if ( pasea )
             res.push_back( _atletas[i] );
         i++;
     }


    return res;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Pais, vector<int> > > res;
    vector<Pais> paises = this->paises();
    int i = 0;

    while ( i < paises.size() ) {
        vector<int> medallas;
        medallas.push_back( cantidadMedallasOro(paises[i]) );
        medallas.push_back( cantidadMedallasPlata(paises[i]) );
        medallas.push_back( cantidadMedallasBronce(paises[i]) );

        pair<Pais, vector<int> > infopais = make_pair(paises[i],medallas);
        res.push_back(infopais);

        i++;
    }

    this->ordenarMedallero(res);
    return res;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    vector<vector<Competencia>> cron_mod;
    int res = 0;
    int i = 0;

    while ( i < _cronograma.size() ) {
        vector<Competencia> comps_mod;
        int j = 0;
        vector<Competencia> comps = _cronograma[i];

        while ( j < comps.size() ) {

            j++;
        }
        i++;
    }

    _cronograma = cron_mod;
    return res;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> ret;
    return ret;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    return;
}

Atleta JJOO::stevenBradbury() const {
    Atleta ret("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    return ret;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {
    return true;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    return ret;
}

void JJOO::transcurrirDia() {
    return;
}

void JJOO::mostrar(std::ostream &os) const {
}

void JJOO::guardar(std::ostream &os) const {
}

void JJOO::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {
    return is;
}

bool JJOO::operator==(const JJOO &j) const {
    return true;
}

JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}
