#include "Ranking.h"
Ranking::Ranking(){
	_pl = new std::vector<Player>;
	_plcolocados = new std::stack<Player>;
	_puntosUltimoplayer = 0;
}
Ranking::~Ranking(){}
void Ranking::leerPlayeryPuntos(){
	ifstream in("./ranking.txt"); 
	string s;
  	while(getline(in, s)){ 
    	cout << s <<  endl; 
    	crearvectorPlayers(s);
    }
    colocarJugadoresPILA();
}
void Ranking::acturanking(){
	CEGUI::Window *sheet=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window *ranking = sheet-> getChild("RankingL");
	CEGUI::Window *uno = ranking-> getChild("Name1");
	int lugar = 1; 		
	std::stack<Player>* _plcolORDEN = new std::stack<Player>;
	while(!_plcolocados->empty()){
		_plcolORDEN -> push(_plcolocados->top());
		_plcolocados-> pop();
	}
	while(!_plcolORDEN->empty()){
		ostringstream osN;
		ostringstream osP;
		osN << "Name" << lugar;
		osP << "Pun" << lugar;
		uno = ranking -> getChild(osN.str());
		uno -> setText(_plcolORDEN->top().getname());
		uno = ranking -> getChild(osP.str());
		uno -> setText(_plcolORDEN->top().getpuntos());
		if (lugar==8){
			setpuntosultimo(atoi(_plcolORDEN->top().getpuntos().c_str()));
			cout << "Puntos del Ultimo" << _puntosUltimoplayer << endl;
		}
		lugar++;
		_plcolORDEN->pop();		
	}
}
void Ranking::crearvectorPlayers(string s){
	string name;
	string puntos;
	int separacion = 0;
	for (unsigned int i = 0; i < s.size(); ++i){
		if(s[i]==' '){
			separacion = i;
		}
	}
	name = s.substr(0,separacion);
	puntos = s.substr(separacion + 1, s.size()-1);
	Player *player = new Player(name, puntos);
	_pl -> push_back(*player);
}
void Ranking::colocarJugadoresPILA(){
	vector<Player>::iterator it;
	int puntos = 0;
	int poseliminar = 0; int i = 0;
	int tampila = 1;
	while(!_pl->empty()){
		i = 0;
		poseliminar = 0;
		puntos = atoi(_pl->front().getpuntos().c_str());
		for (it = _pl->begin(); it != _pl->end();++it){
			if (puntos >= atoi(it -> getpuntos().c_str())){
			}else{
				puntos = atoi(it-> getpuntos().c_str());
				poseliminar = i;
			}
			i++;	
		}
		if (tampila <= 8 ){
			_plcolocados -> push(_pl->at(poseliminar));	
			tampila ++;
		}
		_pl->erase(_pl->begin() + poseliminar);
		cout << puntos << endl;
		cout << poseliminar << endl;		
	}		
}

void Ranking::setpuntosultimo(int puntosnew){
	_puntosUltimoplayer = puntosnew;
}
int Ranking::getpuntosultimo(){
	return _puntosUltimoplayer;
}

void Ranking::setrankingtxt(string name, string puntos){
    cout << "Modificando Ranking" << endl; 
    std::fstream fs;
  	fs.open ("./ranking.txt", std::fstream::out | std::fstream::app);
	fs << name << " " << puntos << endl;
	fs.close();
}

/* Cristal 89
size() --> 10	
Emp 0 Termina 9
*/