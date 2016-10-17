#include "../include/tipos.h"

ostream &operator<<(ostream &os, const Genero &g) {
    if (g == Femenino) {
        os << "Femenino";
    } else {
        os << "Masculino";
    }
    return os;
}

Genero str2Genero(const string &s){
	Genero g;

    if (s == "Femenino") {
        g = Femenino;
    } else if (s == "Masculino") {
        g = Masculino;
    } else {
        assert(false);
    }

	return g;
}

istream &operator>>(istream &is, Genero &g) {
    string s;

    is >> s;

    g = str2Genero(s);

	return is;
}



