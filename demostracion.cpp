/* durante la demostracion, asumiremos que JJ00::competencias(), Competencia::finalizada()
 y Competencia::ranking() son correctas respecto de las especificaciones de los problemas
competencias, finalizada y ranking respectivamente. por lo tanto usaremos los observadores
de los tipos compuestos para referirnos a los valores de retorno de estas funciones

tambien asumimos que l.size() == |l|

TO DO: DEMOSTRAR FINALIZADA, RANKING Y COMPETENCIAS */

Atleta campeon(const Competencia &c) {
	//estado E0;
	res = c.ranking()[0];
	//estado E1;
	//vale res == c.ranking[0];
	//implica res == ranking(c)[0]; (porque ranking() cumple la especificacion del problema ranking)
	return res;
}
//demostramos que campeon es correcta con respecto a la especificacion del problema campeon

//DEMOSTRACION DE competenciasFinalizadasConOroEnPodio

vector <Competencia> competenciasFinalizadasConOroEnPodio(const JJOO &j) {
	//estado E0;
	vector <Competencia> res;
	//estado E1;
	//vale res == [];
	vector <Competencia> comps = j.competencias();
	//estado E2;
	//vale res == res@E1 && comps == j.competencias();

	unsigned int i = 0;
	//estado E3;
	//vale Pc: i == 0 && res == [];
	//implica I: 0 <= i <= |comps| && res == [c | c <- comps[0..i), finalizada(c) && |ranking(c)| > 0]; (porque si i==0 -> comps[0..i) es una lista vacia)

	while (i<comps.size()) {
		//estado C0;
		//variante v: |comps|-i;
		//vale I && B: 0 <= i <= comps.size() && res == [c | c <- comps[0..i), finalizada(c) && |ranking(c)| > 0] && i < |comps|;
		//implica Pif: res == [c | c <- comps[0..i), finalizada(c) && |ranking(c)| > 0]
		if (comps[i].finalizada() && |comps[i].ranking()| > 0)
			//estado ifT0;
			//vale finalizada(comps[i]) && |ranking(comps[i])| > 0; (porque finalizada y ranking cumplen con la especificacion)
			//vale i == i@C0 && Pif: res == [c | c <- comps[0..i), finalizada(c) && |ranking(c)| > 0];
			//implica res == [c | c <- comps[0..i@C0), finalizada(c) && |ranking(c)| > 0]
			res.push_back(comps[i]);
			//estado ifT1;
			//vale finalizada(comps[i@ifT0]) && |ranking(comps[i@ifT0])| > 0;
			//vale i == i@ifT0 && res == res@ifT0 ++ comps[i];
			//implica res == res@ifT0 ++ comps[i@ifT0];
			//implica res == res@C0 ++ comps[i@C0];
		    //implica res == [c | c <- comps[0..i@C0], finalizada(c) && |ranking(c)| > 0]; (porque agregamos comps[i@ifT0], que esta finalizada y tiene ranking no vacio)
		//estado C1;
		//vale i == i@C0 && res == [c | c <- comps[0..i@C0], finalizada(c) && |ranking(c)| > 0];
		//vale Qif: res == [c | c <- comps[0..i@C0], finalizada(c) && |ranking(c)| > 0];
		i++;
		//estado C2;
		//vale i == i@C1+1 && res == res@C1;
		//implica i == i@C0+1 res == [c | c <- comps[0..i@C0+1), finalizada(c) && |ranking(c)| > 0];
		//implica 0 <= i <= |comps| && res == [c | c <- comps[0..i@C2), finalizada(c) && |ranking(c)| > 0]; (porque i@C2 == i@C0+1 y 0 <= i@C0 < |comps|)
		//implica I;
		//hacer el coso de la funcion variante
	}
	//estado E4;
	//vale I && ¬B: 0 <= i <= |comps| && res == [c | c <- comps[0..i), finalizada(c) && |ranking(c)| > 0] && i >= |comps|
	//implica i == |comps|; (i <= |comps| && i >= |comps| ssi i == |comps|)
	//implica res == [c | c <- comps[0..|comps|), finalizada(c) && |ranking(c)| > 0];
	//implica res == [c | c <- comps, finalizada(c) && |ranking(c)| > 0];
	//implica res == [c | c <- competencias(j), finalizada(c) && |ranking(c)| > 0]; (comps == j.competencias() y especificacion de JJOO::competencias())
	//implica res == competenciasConOroEnPodio(j); (definicion de competenciasConOroEnPodio(j))

	return res;
}

//Pc: algunaVezSeCompitio && i == 0 && res == campeon(compsOro[0]) && mayorAnio == anioNacimiento(campeon(compsOro[0]))
//Qc: esCampeon(res,j) && (forall c en compsOro) anioNacimiento(res) >= anioNacimiento(campeon(c))
//I: algunaVezSeCompitio && 0 <= i <= |compsOro| esCampeon(res,j) && (forall c in compsOro[0..i)) anioNacimiento(res) >= anioNacimiento(campeon(c))

//Pif: 

Atleta atletaProdigio(const JJOO &j) {
	//estado E0;
	//vale algunaVezSeCompitio: |competenciasConOroEnPodio(j)| > 0; (por requiere)
	vector <Competencia> compsOro = competenciasFinalizadasConOroEnPodio(j);
	//estado E1;
	//vale algunaVezSeCompitio && compsOro == competenciasFinalizadasConOroEnPodio(j); (por estado anterior)
	Atleta res = campeon(compsOro[0]);
	//estado E2;
	//vale algunaVezSeCompitio && compsOro == compsOro@E1 && res == campeon(compsOro[0]);
	int mayorAnio = res.anioNacimiento();
	//estado E3;
	//vale algunaVezSeCompitio && compsOro == compsOro@E2 && res == res@E2 && mayorAnio == anioNacimiento(res);

	unsigned int i = 0;
	//estado E4;
	//vale algunaVezSeCompitio && compsOro == compsOro@E2 && res == res@E2 && mayorAnio == anioNacimiento(res) && i==0;
	//implica Pc: algunaVezSeCompitio && i == 0 && res == campeon(compsOro[0]) && mayorAnio == anioNacimiento(campeon(compsOro[0]));
	//implica I: algunaVezSeCompitio && 0 <= i <= |compsOro| esCampeon(res,j) && (forall c in compsOro[0..i)) anioNacimiento(res) >= anioNacimiento(campeon(c)) (porque si i == 0 entonces comps[0..i) es una lista vacia)

	while (i<compsOro.size()) {
		if (campeon(compsOro[i]).anioNacimiento() > mayorAnio) {
			res = campeon(compsOro[i]);
			mayorAnio = campeon(compsOro[i]).anioNacimiento;
		}
		i++;
	}

	return res;
}

Atleta JJOO::atletaProdigio() const {
	vector <Competencia> compsOro = competenciasFinalizadasConOroEnPodio();
	Atleta res = compsOro[0].ranking()[0];
	int mayorAnio = res.anioNacimiento();

	unsigned int i = 0;

	while (i<compsOro.size()) {
		if (campeon(compsOro[i]).anioNacimiento() > mayorAnio) {
			res = compsOro[i].ranking()[0];
			mayorAnio = compsOro[i].ranking()[0].anioNacimiento();
		}
		i++;
	}

	return res;
}