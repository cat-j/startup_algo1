#include "../include/jjoo.h"

#include <utility>
#include <algorithm>

#include "../tests/auxiliares_tests.h" /*traido para poder instanciar una compe-
                                        *tencia basura en el metodo de carga sin
                                        *tener que crear otro constructor para 
                                        *la clase de competencia, la cual pide
                                        *un arreglo de deportes en el construc-
                                        *tor.
                                        */


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

    return _cronograma[d - 1];
}

vector<Pais> JJOO::paises() const {
    unsigned int i = 0;
    vector<Pais> res;

    while (i < _atletas.size()) {
        bool ya_esta = false;
        unsigned int j = 0;

        while (j < i && !ya_esta) {
            if (res[j] == _atletas[i].nacionalidad())
                ya_esta = true;
            j++;
        }

        if (!ya_esta)
            res.push_back(_atletas[i].nacionalidad());

        i++;
    }
    return res;
}

bool JJOO::masMedallas(const Pais &p1, const Pais &p2) const {
    if (this->cantidadMedallasOro(p1) > this->cantidadMedallasOro(p2))
        return true;
    if (this->cantidadMedallasOro(p1) == this->cantidadMedallasOro(p2) &&
        this->cantidadMedallasPlata(p1) > this->cantidadMedallasPlata(p2))
        return true;
    if (this->cantidadMedallasOro(p1) == this->cantidadMedallasOro(p2) &&
        this->cantidadMedallasPlata(p1) == this->cantidadMedallasPlata(p2) &&
        this->cantidadMedallasBronce(p1) > this->cantidadMedallasBronce(p2))
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
    int actual = m.size();
    while (actual > 0) {
        int max = this->posMax(m, actual);
        this->swap(m, max, actual);
        actual = actual - 1;
    }
}

vector<Competencia> JJOO::competencias() const {

    vector<Competencia> vectorcomp;
    unsigned int i = 0;

    while (i < _cronograma.size()) {
        unsigned int j = 0;
        while (j < _cronograma[i].size()) {
            vectorcomp.push_back(_cronograma[i][j]);
            j++;
        }
        i++;
    }
    return vectorcomp;
}

int JJOO::cantidadMedallasOro(const Pais &p) const {
    int cant = 0;
    unsigned int i = 0;
    vector<Competencia> comps = this->competencias();

    while (i < comps.size()) {

        if (comps[i].finalizada()) {
            vector<Atleta> r_actual = comps[i].ranking();
            if (r_actual.size() > 0 && r_actual[0].nacionalidad() == p)
                cant++;
        }

        i++;
    }

    return cant;
}

int JJOO::cantidadMedallasPlata(const Pais &p) const {
    int cant = 0;
    unsigned int i = 0;
    vector<Competencia> comps = this->competencias();

    while (i < comps.size()) {

        if (comps[i].finalizada()) {
            vector<Atleta> r_actual = comps[i].ranking();
            if (r_actual.size() > 1 && r_actual[1].nacionalidad() == p)
                cant++;
        }

        i++;
    }

    return cant;
}

int JJOO::cantidadMedallasBronce(const Pais &p) const {
    int cant = 0;
    unsigned int i = 0;
    vector<Competencia> comps = this->competencias();

    while (i < comps.size()) {

        if (comps[i].finalizada()) {
            vector<Atleta> r_actual = comps[i].ranking();
            if (r_actual.size() > 2 && r_actual[2].nacionalidad() == p)
                cant++;
        }

        i++;
    }

    return cant;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {

    vector<Competencia> comp_finconor;
    unsigned int i = 0;
    vector<Competencia> comp_iterar = this->competencias();

    while (i < comp_iterar.size()) {
        if (comp_iterar[i].finalizada() && comp_iterar[i].ranking().size() > 0) comp_finconor.push_back(comp_iterar[i]);

        i++;
    }


    return comp_finconor;
}

vector<Atleta> JJOO::dePaseo() const {

    vector<Atleta> res;
    vector<Competencia> comps = this->competencias();
    unsigned int i = 0;

    while (i < _atletas.size()) {
        unsigned int j = 0;
        bool pasea = true;

        while (j < comps.size() && pasea) {
            unsigned int k = 0;
            vector<Atleta> parts_actuales = comps[j].participantes();
            int participa = false;

            while (k < parts_actuales.size() && !participa) {
                if (parts_actuales[k] == _atletas[i]) {
                    participa = true;
                    pasea = false;
                }
                k++;
            }
            j++;
        }
        if (pasea)
            res.push_back(_atletas[i]);
        i++;
    }


    return res;
}

vector<pair<Pais, vector<int> > > JJOO::medallero() const {
    vector<pair<Pais, vector<int> > > res;
    vector<Pais> paises = this->paises();
    unsigned int i = 0;

    while (i < paises.size()) {
        vector<int> medallas;
        medallas.push_back(cantidadMedallasOro(paises[i]));
        medallas.push_back(cantidadMedallasPlata(paises[i]));
        medallas.push_back(cantidadMedallasBronce(paises[i]));

        pair<Pais, vector<int> > infopais = make_pair(paises[i], medallas);
        res.push_back(infopais);

        i++;
    }

    this->ordenarMedallero(res);
    return res;
}

Competencia JJOO::sacarPais(const Competencia &c, const Pais &p) const {
    vector<Atleta> atletas_mod;

    unsigned int i = 0;

    while (i < c.participantes().size()) {
        if (c.participantes()[i].nacionalidad() != p)
            atletas_mod.push_back(c.participantes()[i]);
        i++;
    }

    Competencia res = Competencia(c.categoria().first, c.categoria().second, atletas_mod);

    if (c.finalizada()) {
        vector<int> posiciones_mod;
        vector<pair<int, bool> > antidoping_mod;

        i = 0;

        while (i < c.ranking().size()) {
            if (c.ranking()[i].nacionalidad() != p)
                posiciones_mod.push_back(c.ranking()[i].ciaNumber());
            i++;
        }

        i = 0;

        while (i < c.lesTocoControlAntiDoping().size()) {
            Atleta atleta_actual = c.lesTocoControlAntiDoping()[i];

            if (atleta_actual.nacionalidad() != p) {
                pair<int, bool> atleta_append = make_pair(atleta_actual.ciaNumber(), c.leDioPositivo(atleta_actual));
                antidoping_mod.push_back(atleta_append);
            }
            i++;
        }

        res.finalizar(posiciones_mod, antidoping_mod);
    }

//                fijarse si la competencia está finalizada.
//                generar vector posiciones y vector control ( con cianumbers)
//                finalizar las no finalizadas.
//                Gracias.
    return res;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    vector<vector<Competencia>> cron_mod;
    int res = 0;
    unsigned int i = 0;

    while (i < _cronograma.size()) {
        unsigned int j = 0;
        vector<Competencia> dia_actual = _cronograma[i];

        while (j < dia_actual.size()) {
            vector<Competencia> comps_mod;

            if (dia_actual[j].categoria() != c)
                comps_mod.push_back(dia_actual[j]);
            else
                comps_mod.push_back(sacarPais(dia_actual[j], p));
            j++;

            cron_mod.push_back(comps_mod);
        }

        i++;
    }
    _cronograma = cron_mod;
    return res;
}

vector<Atleta> JJOO::atletasDelPais(const Pais &p) const {

    vector<Atleta> res;
    unsigned int i = 0;

    while (i < _atletas.size()) {
        if (_atletas[i].nacionalidad() == p)
            res.push_back(_atletas[i]);
        i++;
    }
    return res;
}

int JJOO::cantCompetencias(const Atleta &a) const {
    int res = 0;
    unsigned int i = 0;

    vector<Competencia> comps = competencias();

    while (i < comps.size()) {
        unsigned int j = 0;
        while (j < comps[i].participantes().size()) {
            if (a == comps[i].participantes()[j]) {
                res++;
            }
            j++;
        }
        i++;
    }
    return res;
}

vector<Atleta> JJOO::losMasParticipantes(const vector<Atleta> &as) const {
    vector<Atleta> res;
    unsigned int i = 0;
    int max = 0;

    while (i < as.size()) {
        if (cantCompetencias(as[i]) > max)
            max = cantCompetencias(as[i]);
    }


    while (i < as.size()) {
        if (cantCompetencias(as[i]) == max)
            res.push_back(as[i]);
    }

    return res;
}


int JJOO::cantidadMedallas(const Atleta &a) const {
    int res = 0;
    unsigned int i = 0;

    vector<Competencia> comps = competencias();

    while (i < comps.size()) {
        if (comps[i].finalizada() && comps[i].ranking().size() > 0 && comps[i].ranking()[0] == a)
            res++;
        if (comps[i].finalizada() && comps[i].ranking().size() > 1 && comps[i].ranking()[1] == a)
            res++;
        if (comps[i].finalizada() && comps[i].ranking().size() > 2 && comps[i].ranking()[2] == a)
            res++;
    }

    return res;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> res;
    vector<Atleta> as = losMasParticipantes(atletasDelPais(p));
    unsigned int i = 0;

    while (i < as.size()) {
        if (cantidadMedallas(as[i]) == 0) {
            res.push_back(as[i]);
        }
        i++;
    }

    return res;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    Atleta nuevoAtleta(a.nombre(), a.genero(), a.anioNacimiento(), p, a.ciaNumber());
    vector<Atleta> atletasNuevos;
//Cambiar los participantes de los juegos
    unsigned int i = 0;
    while (i < _atletas.size()) {
        if (_atletas[i] == a) {
            atletasNuevos.push_back(nuevoAtleta);
        } else {
            atletasNuevos.push_back(a);
        }
        i++;
    }
// Cambiar los  participatnes de todas las competencias

    vector<vector<Competencia> > cronModificado;
    i = 0;
    while (i < _cronograma.size()) {
        unsigned int j = 0;
        vector<Competencia> diaActual = _cronograma[i];
        vector<Competencia> compsModificadas;

        while (j < diaActual.size()) {
            Competencia comp = diaActual[j];
//Cambiamos la nacionalidad del participante en la competencia actual
            vector<Atleta> participantesNuevos;
            unsigned int k = 0;
            while (k < comp.participantes().size()) {
                if (comp.participantes()[k] == a) {
                    participantesNuevos.push_back(nuevoAtleta);
                } else {
                    participantesNuevos.push_back(comp.participantes()[k]);
                }
                k++;
            }

            Competencia compModificada(comp.categoria().first, comp.categoria().second, participantesNuevos);

// Si la competencia actual esta finalizada, creamos un ranking con el atleta modificado.
            if (comp.finalizada()) {
                vector<int> ciasParaRanking;
                vector<pair<int, bool> > resultadosAntiDoping;
                unsigned int m = 0;

                while (m < comp.ranking().size()) {
                    ciasParaRanking.push_back(comp.ranking()[m].ciaNumber());
                    m++;
                }

                m = 0;
                // Creamos una lista de pares (ciaNumber, resultado del control) para el control anti doping de la competencia finalizada.
                while (m < comp.lesTocoControlAntiDoping().size()) {
                    pair<int, bool> controlPush = make_pair(comp.lesTocoControlAntiDoping()[m].ciaNumber(),
                                                            comp.leDioPositivo(comp.lesTocoControlAntiDoping()[m]));
                    resultadosAntiDoping.push_back(controlPush);
                    m++;
                }

                compModificada.finalizar(ciasParaRanking, resultadosAntiDoping);
            }
            compsModificadas.push_back(compModificada);
            j++;
        }
        cronModificado.push_back(compsModificadas);
        i++;
    }
    _atletas = atletasNuevos;
    _cronograma = cronModificado;
}

vector<pair<Atleta, Categoria>> JJOO::medallistasDeOro() const {
    unsigned int i = 0;
    vector<pair<Atleta, Categoria>> res;
    while (i < competencias().size()) {
        Competencia comp = competencias()[i];
        if (comp.finalizada() && comp.ranking().size() > 0) {
            pair<Atleta, Categoria> oro = make_pair(comp.ranking()[0], comp.categoria());
            res.push_back(oro);
        }
        i++;
    }
    return res;
}


Atleta JJOO::stevenBradbury() const {
//    Devolvemos al atleta que tiene la menor capacidad en algun deporte en el que haya ganado oro.

//    Conseguimos los medallistas de oro de los JJOO
    vector<pair<Atleta, Categoria>> oros = medallistasDeOro();
//    Conseguimos cual es el que tiene la menor capacidad en la categoria en la que gano
    Atleta elMenosCapaz = oros[0].first;
    int menorCapacidad = oros[0].first.capacidad(oros[0].second.first);

    unsigned int i = 0;
    while (i < oros.size()) {
        Deporte dep_actual = oros[i].second.first;
        if (oros[i].first.capacidad(dep_actual) < menorCapacidad)
            elMenosCapaz = oros[i].first;
        i++;
    }

    return elMenosCapaz;
}

int JJOO::oroPorPais(const Pais &p, const vector<Competencia> &cs) const {
    int res = 0;
    unsigned int i = 0;

    while (i < cs.size()) {
        Competencia comp = cs[i];
        if (comp.finalizada() && comp.ranking().size() > 0 && comp.ranking()[0].nacionalidad() == p)
            res++;
        i++;
    }

    return res;
}

Pais JJOO::mejorPais(const unsigned int &d) const {
    Pais ganadorDelDia = paises()[0];
    int medallasDelGanador = oroPorPais(paises()[0], cronograma(d));
    unsigned int i = 0;

    while (i < paises().size()) {
        if (medallasDelGanador < oroPorPais(paises()[i], cronograma(d))) {
            medallasDelGanador = oroPorPais(paises()[i], cronograma(d));
            ganadorDelDia = paises()[i];
        } else if (medallasDelGanador == oroPorPais(paises()[i], cronograma(d)) && paises()[i] < ganadorDelDia) {
            ganadorDelDia = paises()[i];
        }
        i++;
    }
    return ganadorDelDia;
}


bool JJOO::uyOrdenadoAsiHayUnPatron() const {

    vector<Pais> mp;
    int j = 1;

    while (j < jornadaActual() + 1) {
        mp.push_back(mejorPais(j));
        j++;
    }
    vector<Pais> mejoresPaises = mp;

    bool hayUnPatron = true;
    int posicionDelPrimerRepetido = 0;
    unsigned int i = 0;

    while (i < mejoresPaises.size()) {
        unsigned int j = 0;
        while (j < i && posicionDelPrimerRepetido == 0) {
            if (mejoresPaises[j] == mejoresPaises[i]) {
                posicionDelPrimerRepetido = i;
            }
            j++;
        }
        i++;
    }

    if (posicionDelPrimerRepetido != 0) {
        unsigned int k = 0;
        while (k < mejoresPaises.size()) {
            if (mejoresPaises[k] != mejoresPaises[k % posicionDelPrimerRepetido]) {
                hayUnPatron = false;

            }
            k++;
        }
    }
    return hayUnPatron;
}

bool JJOO::ganoMedalla(const Pais &p, const int &d) const {
    bool res = false;

    unsigned int i = 0;

    while (i < cronograma(d).size()) {
        Competencia comp = cronograma(d)[i];
        if (comp.finalizada() && comp.ranking().size() > 0 && comp.ranking()[0].nacionalidad() == p) {
            res = true;
        }
        if (comp.finalizada() && comp.ranking().size() > 1 && comp.ranking()[1].nacionalidad() == p) {
            res = true;
        }
        if (comp.finalizada() && comp.ranking().size() > 2 && comp.ranking()[2].nacionalidad() == p) {
            res = true;
        }
        i++;
    }

    return res;
}

int JJOO::maxDif(const vector<int> &ds) const {
    int res = 0;
    unsigned int i = 1;

    while (i < ds.size()) {
        if ((ds[i] - ds[i - 1]) > res) {
            res = (ds[i] - ds[i - 1]);
        }
        i++;
    }
    return res;
}

int JJOO::masDiasSinMedallas(const Pais &p) const {
    vector<int> diasEnLosQueGanoMedalla;
    diasEnLosQueGanoMedalla.push_back(0);

    unsigned int i = 1;

    while (i < jornadaActual()) {
        if (ganoMedalla(p, i)) {
            diasEnLosQueGanoMedalla.push_back(i);
        }
    }

    diasEnLosQueGanoMedalla.push_back(jornadaActual());

    int res = maxDif(diasEnLosQueGanoMedalla);

    return res;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;

    int maxDias;
    unsigned int i = 0;

    while (i < paises().size()) {
        if (masDiasSinMedallas(paises()[i]) > maxDias) {
            maxDias = masDiasSinMedallas(paises()[i]);
        }
        i++;
    }

    i = 0;

    while (i < paises().size()) {
        if (masDiasSinMedallas(paises()[i]) == maxDias) {
            ret.push_back(paises()[i]);
        }
        i++;
    }


    return ret;
}

int JJOO::maximaCapacidad(const vector<Atleta> &as,const int &a, const Deporte &d) const {
    int max = 0;
    int b = a;
    int posMax;

    while (b < as.size()) {
        if (as[b].capacidad(d) > max) {
            max = as[b].capacidad(d);
            posMax = b;
        }
        b++;
    }
    return posMax;
}

vector<Atleta> JJOO::swap2(const vector<Atleta> &as, const int &m, const int &a) const {

    vector<Atleta> as2 = as;

    Atleta pivot = as2[m];
    as2[m] = as2[a];
    as2[a] = pivot;
    return as2;
}

vector<int> JJOO::generarRanking(const Competencia &c) const {
    Deporte d = c.categoria().first;
    vector<Atleta> ranking = c.participantes();
    vector<int> rankingDeCias;
    unsigned int i = 0;

    int actual = 0;

    while (actual < ranking.size()) {
        int max = maximaCapacidad(ranking, actual, d);
//        ranking = swap2(ranking, max, actual);
        actual++;
    }

    unsigned int j = 0;
    while (j < ranking.size()) {
        rankingDeCias.push_back(ranking[i].ciaNumber());
        j++;
    }


    return rankingDeCias;
}

vector<Competencia> JJOO::finalizarDia(const vector<Competencia> &cs) const{
    vector<Competencia> cs2 = cs;
    vector<Competencia> compsMod;

    unsigned int j = 0;
//Iteramos sobre todas las competencias del dia. Nos fijamos si no estan finalizadas y las finalizamos
//Creamos un vector de competencias modificadas, donde estaran  todas finalizadas y lo devolvemos
    while (j < cs2.size()) {
        if (cs2[j].finalizada()) {
            compsMod.push_back(cs2[j]);
        }
        else {
//            Generamos el ranking
            vector<int> posMod = generarRanking(cs2[j]);

//            Generamos el antidoping y sus resultados
            unsigned int k = 0;

            vector<pair<int, bool>> atletaControl;
            while (k < cs2[j].lesTocoControlAntiDoping().size()) {
                atletaControl.push_back(make_pair(cs2[j].lesTocoControlAntiDoping()[k].ciaNumber(),
                                                  cs2[j].leDioPositivo(cs2[j].lesTocoControlAntiDoping()[k])));
                k++;

            }
//            Finalizamos la competencia pasandole los dos parametros anteriores con el metodo publico.
            cs2[j].finalizar(posMod, atletaControl);
            compsMod.push_back(cs2[j]);
        }
        j++;
    }
    return compsMod;
}

void JJOO::transcurrirDia() {

    vector<vector<Competencia>> cronMod;
    unsigned int i = 1;

    while (i <= cantDias()) {
        if (i != jornadaActual()) {
            cronMod.push_back(cronograma(i));
        }
        else {
            cronMod.push_back(finalizarDia(cronograma(i)));
        }
        i++;
    }


    return;
}

void JJOO::mostrar(std::ostream &os) const {
    guardar(os);
    os << std::endl;
}

void JJOO::guardar(std::ostream &os) const {
    os << "J " << _anio
       << " " << _jornadaActual
       << "[";

    unsigned int i = 0;

    while (i < _atletas.size()) {

        os << "(" << _atletas[i] << ")";

        i++;

        if (i < _atletas.size()) {
            os << ", ";
        }
    }
    os << "]";

    unsigned int j;
    i = 0;

    os << "[";
    while (i < _cronograma.size()) {

        j = 0;

        os << "[";
        while (j < _cronograma[i].size()) {

            os << "(" << _cronograma[i][j] << ")";

            j++;

            if (j < _cronograma[i].size()) {
                os << ", ";
            }
        }
        os << "]";

        i++;

        if (i < _cronograma.size()) {
            os << ", ";
        }
    }
    os << "]";

}

void JJOO::cargar(std::istream &is) {
    string buff;

    is >> buff >> _anio >> _jornadaActual;

    _atletas.clear();

    getline(is, buff, '[');
    while (is.peek() != ']') {

        Atleta a("a", Genero::Masculino, 1, "a", 2); //Atleta con basura

        getline(is, buff, '(');

        a.cargar(is);

        getline(is, buff, ')');

        _atletas.push_back(a);
    }


    _cronograma.clear();
    getline(is, buff, '[');
    while (is.peek() != ']') {

        vector<Competencia> vc;

        getline(is, buff, '[');
        while (is.peek() != ']') {

            Competencia c = Competencia(deportes[5], Genero::Femenino, std::vector<Atleta>());//competencia con basura

            getline(is, buff, '(');

            c.cargar(is);

            getline(is, buff, ')');

            vc.push_back(c);

        }

        is.get();

        _cronograma.push_back(vc);

        if (is.peek() != ']') {
            vc.clear();
        }
    }

}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    j.guardar(os);
    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {
    j.cargar(is);
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
