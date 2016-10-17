#include "../include/atleta.h"


Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    _nombre = n;
    _genero = g;
    _anioNacimiento = a;
    _nacionalidad = p;
    _ciaNumber = c;

    pair <Deporte, int> _initdep = make_pair("Tenis", 50);
    _deportes.push_back(_initdep);
}

string Atleta::nombre() const {
    return _nombre;
}

Genero Atleta::genero() const {
    return _genero;
}

int Atleta::anioNacimiento() const {
    return _anioNacimiento;
}

Pais Atleta::nacionalidad() const {
    return _nacionalidad;
}

int Atleta::ciaNumber() const {
    return _ciaNumber;
}

vector<Deporte> Atleta::deportes() const {
    unsigned int i = 0;

    vector<Deporte> res;

    while ( i < _deportes.size() ) {
        res.push_back( _deportes[i].first );
        i++;
    }

    return res;
}

int Atleta::capacidad(const Deporte &d) const {
    int res = _deportes[0].second;
    unsigned int i = 0;

    while ( i < _deportes.size() && (_deportes[i].first != d) ) {
        i++;
        if ( _deportes[i].first == d )
            res = _deportes[i].second;
    }

    return res;
}

Deporte Atleta::especialidad() const {
    Deporte res = _deportes[0].first;
    int cap = _deportes[0].second;
    unsigned int i = 0;

    while ( i < _deportes.size() ) {
        i++;
        if ( _deportes[i].second > cap )
            res = _deportes[i].first;
    }

    return res;
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    unsigned int i = 0;
    vector<pair<Deporte, int>> deps_mod;
    pair<Deporte, int> dep_nuevo = make_pair(d,c);

    while ( (i<_deportes.size()) && (_deportes[i].first < d) ) {
       deps_mod.push_back( _deportes[i] );
        i++;
    }

    deps_mod.push_back(dep_nuevo);

    while ( i < _deportes.size() ) {
        if ( _deportes[i].first != d )
            deps_mod.push_back( _deportes[i] );
        i++;
    }

    _deportes = deps_mod;
}

void Atleta::mostrar(std::ostream &os) const {

	guardar(os);

	os<<std::endl;

}

void Atleta::guardar(std::ostream &os) const {

	os<<"A"
      <<" |"<<_nombre<<"|"
      <<" |"<<_genero<<"|"
	  <<" " <<_anioNacimiento
      <<" |"<<_nacionalidad<<"|"
      <<" " <<_ciaNumber
      <<" [";

	unsigned int i = 0;

	while(i < _deportes.size()){
		os<<"(|"
          <<_deportes[i].first<<"|, "
          <<_deportes[i].second
          <<")";

        ++i;
		if(i < _deportes.size()){
			os<<", ";
		}
    }
	os<<"]";

}

void Atleta::cargar(std::istream &is) {

	string buff;

	getline(is,buff,'|'); //Leer la A

	getline(is,_nombre,'|'); //Leer el nombre

	getline(is,buff,'|'); //Leer el pipe

	getline(is,buff,'|'); //Leer el genero

	_genero = str2Genero(buff); //Convertir los ripos

	is>>_anioNacimiento;

	getline(is,buff,'|'); //Leer el pipe

	getline(is,_nacionalidad,'|'); // Leer la nacionalidad

	is>>_ciaNumber;

	getline(is,buff,'[');

	_deportes.clear();

	while(is.peek() != ']'){

		pair<Deporte,int> d;

		getline(is,buff,'('); //Leer el parentesis
		getline(is,buff,'|'); //Leer el pipe

		getline(is,d.first,'|'); //Leer el deporte

		getline(is,buff,','); //Leer la coma
		getline(is,buff,')'); //Leer la habilidad

		d.second = atoi(buff.c_str());

		_deportes.push_back(d);

	}

}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {
	a.guardar(os);
    return os;
}

std::istream &operator>>(std::istream &is, Atleta &a) {
	a.cargar(is);
    return is;
}

bool Atleta::operator==(const Atleta &a) const {
    return ( _anioNacimiento == a._anioNacimiento && _ciaNumber == a._ciaNumber && _nacionalidad == a._nacionalidad && _nombre == a._nombre && _genero == a._genero && _deportes == a._deportes );
}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    return (*this);
}
