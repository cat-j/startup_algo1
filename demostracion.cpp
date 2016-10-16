//vamos a tener que demostrar correctitud de competencias()

//Pc: i == 0 && res == [] && |comps| > 0
//Qc: res == [campeon(c) | c <- competenciasConOroEnPodio(j)]
//I: 0 <= i <= |competencias| && (forall a in res) esCampeon(a)
//B: i<|comps|
//v: |comps|-i
//c: 0

//Pif: 

vector<Atleta> JJOO::campeones() const {
    //estado E0
    //vale algunaVezSeCompitio: |competenciasConOroEnPodio(j)| > 0 (por requiere)
    //implica |competencias(j)| > 0 ( porque competenciasConOroEnPodio(j) cont competencias(j) -> |competencias(j)| >= |competenciasConOroEnPodio(j)| > 0)
    vector<Atleta> res;
    //estado E1
    //vale res == [] && |competencias(j)| > 0
    vector<Competencia> comps = competencias();
    //estado E2
    //vale res == res@E1 && comps == competencias()
    //implica comps == competencias(j) (por especificacion de JJOO::competencias()) (DEMOSTRAR)
    //implica |comps| > 0 (por implica anterior && estado E1)

    int i = 0;

    //estado E3
    //vale res == res@E2 && comps == comps@E2 && i == 0
    //implica Pc: i == 0 && res == [] && |comps| > 0
    //implica I: 0 <= i <= |comps| && (forall a in res) esCampeon(a) (porque si res es vacia el predicado es verdadero)

    while (i<comps.size) {
        //estado C0
        //vale I && B
        //variante v: |comps|-i
        if (comps[i].finalizada() && comps[i].ranking().size()>0) {
            res.push_back(comps[i].ranking()[0]);
        }
        i++;
    }

    return res;
}

//TENEMOS QUE DEMOSTRAR QUE LOSCAMPEONES FUNCIONA Y DA EL CAMPEON DE CADA COMPETENCIA CON ORO EN PODIO

//Pc: i == 0 && res == losCampeones[0] && mayorAnio == losCampeones[0].anioNacimiento
//Qc: (forall a in losCampeones) res.anioNacimiento >= a.anioNacimiento
//I: 0 <= i <= |losCampeones()| && (forall a in losCampeones[0..i)) res.anioNacimiento >= a.anioNacimiento
//B: i<|losCampeones()|
//v: |losCampeones()|-i
//c: 0

//Pif: res en losCampeones[0..i) && mayorAnio == res.anioNacimiento
//Qif: (losCampeones[i].anioNacimiento > pre(mayorAnio) && res == losCampeones[i] && mayorAnio == losCampeones[i].anioNacimiento) || (losCampeones[i].anioNacimiento <= pre(mayorAnio) && res == pre(res) && mayorAnio == pre(mayorAnio))
//en vez de pre deberia decir en que estado (lo vemos mas adelante)

Atleta JJOO::atletaProdigio() const {
    <vector> Atleta losCampeones = campeones();
    Atleta res = losCampeones[0];
    int mayorAnio = losCampeones[0].anioNacimiento();

    int i = 0;

    while (i<losCampeones.size()) {
        if (losCampeones[i].anioNacimiento() > mayorAnio) {
            res = losCampeones[i];
            mayorAnio = losCampeones[i].anioNacimiento();
        }

        i++;
    }

    return res;
}