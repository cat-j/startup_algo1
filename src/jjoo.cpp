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

    vector<Atleta> at_pasea;
    int i = 0;

    while (i<_atletas.size()){



    }


    return ret;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Pais, vector<int> > > ret;
    return ret;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    return 0;
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
