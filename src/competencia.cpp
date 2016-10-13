#include "../include/competencia.h"


Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {
    _categoria = make_pair(d,g);
    _finalizada = false;
    _participantes = as;
}

Categoria Competencia::categoria() const {
    return _categoria;
}

vector<Atleta> Competencia::participantes() const {
    return _participantes;
}

bool Competencia::finalizada() const {
    return _finalizada;
}

vector<Atleta> Competencia::ranking() const {
    return _ranking;
}

vector<Atleta> Competencia::lesTocoControlAntiDoping() const {
    vector<Atleta> res;
    int i = 0;

    while ( i < _lesTocoControlAntiDoping.size() ) {
        res.push_back( _lesTocoControlAntiDoping[i].first );
        i++;
    }

    return res;
}

bool Competencia::leDioPositivo(const Atleta &a) const {
    bool res = false;
    int i = 0;

    while ( i < _lesTocoControlAntiDoping.size() ) {
        if ( _lesTocoControlAntiDoping[i].first == a )
            res = _lesTocoControlAntiDoping[i].second;
        i++;
    }

    return res;
}

bool Competencia::perteneceAtleta(const Atleta &a) const {
    int i = 0;

    while ( i < _participantes.size() && !(_participantes[i] == a) ) {
        i++;
    }

    return (i < _participantes.size());
}

bool Competencia::perteneceAtletaControlado(const pair<Atleta, bool> &a) const {
    int i = 0;

    while ( i < _lesTocoControlAntiDoping.size() && !(_lesTocoControlAntiDoping[i] == a) ) {
        i++;
    }

    return (i < _lesTocoControlAntiDoping.size());
}

bool Competencia::mismosAtletas(const Competencia &c) const {
    int i = 0;
    bool res = true;

    if ( _participantes.size() != c._participantes.size() ) {
        res = false;
    } else {
        while ( i < _participantes.size() ) {
            if ( !c.perteneceAtleta(_participantes[i]) )
                return false;
            i++;
        }
    }

    return res;
}

bool Competencia::mismoControl(const Competencia &c) const {
    int i = 0;
    bool res = true;

    if ( _lesTocoControlAntiDoping.size() != c._lesTocoControlAntiDoping.size() ) {
        res = false;
    } else {
        while ( i < _lesTocoControlAntiDoping.size() ) {
            if ( !c.perteneceAtletaControlado(_lesTocoControlAntiDoping[i]) )
                return false;
            i++;
        }
    }

    return res;
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control) {
    _finalizada = true;

    int i = 0;

    while ( i < posiciones.size() ) {
        int j = 0;
        while ( j < _participantes.size() ) {
            if ( _participantes[j].ciaNumber() == posiciones[i] )
                _ranking.push_back( _participantes[j] );
            j++;
        }
        i++;
    }

    i = 0;

    while ( i < control.size() ) {
        int j = 0;
        while ( j < _participantes.size() ) {
            if ( _participantes[j].ciaNumber() == control[i].first ) {
                pair <Atleta, bool> controlado = make_pair(_participantes[j],control[i].second);
                _lesTocoControlAntiDoping.push_back(controlado);
            }
            j++;
        }
        i++;
    }
}

void Competencia::linfordChristie(const int &n) {
    vector<Atleta> part_mod;
    int i = 0;

    while ( i < _participantes.size() ) {
        if ( _participantes[i].ciaNumber() != n )
            part_mod.push_back( _participantes[i] );
        i++;
    }

    _participantes = part_mod;
}

bool Competencia::gananLosMasCapaces() const {
    bool res = true;
    Deporte dep = _categoria.first;
    int i = 0;

    while ( i < _ranking.size()-1 ) {
        if ( _ranking[i].capacidad(dep) < _ranking[i+1].capacidad(dep) )
            return false;
        i++;
    }

    return res;
}

void Competencia::sancionarTramposos() {
    vector<Atleta> rank_mod;
    int i=0;

    while (i<_ranking.size()) {
        if (!this->leDioPositivo(_ranking[i]))
        {
            rank_mod.push_back(_ranking[i]);


        }
        i++;


    }
    _ranking = rank_mod;
}

void Competencia::mostrar(std::ostream &os) const {
}

void Competencia::guardar(std::ostream &os) const {
}

void Competencia::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {
    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
    return is;
}

bool Competencia::operator==(const Competencia &c) const {
    return ( _categoria == c._categoria && _finalizada == c._finalizada && this->mismosAtletas(c) && ( !_finalizada || (_ranking == c._ranking && this->mismoControl(c)) ) );
}

Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}
