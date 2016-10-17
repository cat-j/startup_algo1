#ifndef __JJOO__
#define __JJOO__

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"


class JJOO {

private:
    int _anio;
    vector<Atleta> _atletas;
    vector<vector<Competencia> > _cronograma;
    int _jornadaActual;
    vector<Pais> paises() const;
    int cantidadMedallasOro(const Pais &p) const;
    int cantidadMedallasPlata(const Pais &p) const;
    int cantidadMedallasBronce(const Pais &p) const;
    bool masMedallas(const Pais &p1, const Pais &p2) const;
    int posMax(const vector<pair<Pais, vector<int> > > &m, const int n) const;
    void swap(vector<pair<Pais, vector<int> > > &m, const int n, const int k) const;
    void ordenarMedallero(vector<pair<Pais, vector<int> > > &m) const;
    Competencia sacarPais(const Competencia &c, const Pais &p) const;
    vector<Atleta> atletasDelPais(const Pais &p)const;
    int cantCompetencias(const Atleta &a)const;
    vector<Atleta> losMasParticipantes(const vector<Atleta> &as)const;
    int cantidadMedallas(const Atleta &a)const;
    vector <pair <Atleta, Categoria>> medallistasDeOro() const;
    int oroPorPais(const Pais &p, const vector<Competencia> &cs) const;
    Pais mejorPais(const unsigned int &d) const;
    int masDiasSinMedallas (const Pais &p) const;
    bool ganoMedalla (const Pais &p, const int &d) const;
    int maxDif (const vector<int> &ds) const;
    vector<Competencia> finalizarDia (const vector<Competencia> &cs) const;
    Competencia finalizar (const Competencia &c) const;
    vector <int> generarRanking(const Competencia &c) const;
    int maximaCapacidad(const vector<Atleta> &as,const int &a,const Deporte &d) const;
    vector <Atleta> swap2 (const vector<Atleta> &as, const int &m, const int &a) const;

    friend class jjoo_tests_competencias_al_transcurrir_un_dia_Test;

    friend class jjoo_tests_competencias_al_transcurrir_dos_dias_Test;

    friend class jjoo_tests_sequias_olimpicas_y_los_mas_fracasados_Test;

    friend class jjoo_tests_hay_un_patron_Test;

    friend class jjoo_tests_liu_song_Test;

public:
    JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs);

    int anio() const;

    vector<Atleta> atletas() const;

    int cantDias() const;

    int jornadaActual() const;

    vector<Competencia> cronograma(const int &d) const;

    vector<Competencia> competencias() const;

    vector<Competencia> competenciasFinalizadasConOroEnPodio() const;

    vector<Atleta> dePaseo() const;

    vector<pair<Pais, vector<int> > > medallero() const;

    int boicotPorDisciplina(const Categoria &c, const Pais &p);

    vector<Atleta> losMasFracasados(const Pais &p) const;

    void liuSong(const Atleta &a, const Pais &p);

    Atleta stevenBradbury() const;

    bool uyOrdenadoAsiHayUnPatron() const;

    vector<Pais> sequiaOlimpica() const;

    void transcurrirDia();

    bool operator==(const JJOO &j) const;

    JJOO operator=(const JJOO &j);

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const JJOO &j);

std::istream &operator>>(std::istream &is, JJOO &j);

#endif /*__JJOO__*/