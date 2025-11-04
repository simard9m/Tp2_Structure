#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

template <typename Element>
class Postfix {
	private:

		//Shit que je vais avoir besoins pour les traitements internes
		std::stack<Element> Pile;
		std::vector<Element> Tableau;
		std::vector<char> entreeChar;
		std::vector<Element> tokensInfixe;
		std::vector<Element> tokensPostfixe;

		//Des utilitaires utiles 

		//Get si c<est un operatuer
		static bool EstOperateur(const Element& t) {
			return t == "+" || t == "-" || t == "*" || t == "/" || t == "%";
		}

		//Retourne la prio 
		static int Priorite(const Element& op)
		{
			if (op == "*" || op == "/" || op == "%") return 2;
			if (op == "+" || op == "-") return 1;
			return 0;
		}

		//Retourne un nombre et prend un coimpte qu<un nombre est une chain compose suelment de chiffres
		static bool EstNombre(const Element& t) {
			if (t.empty()) return false;
			for (size_t i = 0; i < t.size(); ++i) {
				if (!std::isdigit(static_cast<unsigned char>(t[i]))) return false;
			}
			return true;
		}

public:
	//Constructeur et stockage de l<expression du calvier dans entreechar
	Postfix(std::vector<char> Tableau) : entreeChar(Tableau){}

	//Destructeur (rien de dynamique a liberer pour le moment (bonus 2 peut etre))
	~Postfix() {}

	//Valider, check les les charater sont tous autorise et lequilibre des parentheses
	bool Valider(std::vector<char> Tableau) const {
		//verif des character
		for (size_t i = 0; i < Tableau.size(); ++i) {
			char c = Tableau[i];
			if (std::isspace(static_cast<unsigned char>(c))) continue;
			if (std::isdigit(static_cast<unsigned char>(c))) continue;
			if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%') continue;
			//Char non autorise
			return false;
		}

		//verif des parentheses
		int balance = 0;
		for (size_t i = 0; i < Tableau.size(); ++i) {
			//Check pour un parenthese ouvrante
			if (Tableau[i] == '(')
				++balance;
			//check pour la fermante
			else if (Tableau[i] == ')') {
				--balance;
				//Si a ce moment la balance est negative nous avons un arrangement de parenthese impossible et illegal dans une equation
				if (balance < 0)
					return false;
			}
				
		}
		return true;
	}

	//MEthode pour recheck les les prenthese sont encore good apres transofrmation ou tokenisation
	bool parenthese(std::vector<Element> Tableau) const {
		int balance = 0;
		for (size_t i = 0; i < Tableau.size(); ++i)
			if (Tableau[i] == "(") ++balance;
			else if (Tableau[i] == ")") {
				--balance;
				//Si a ce moment la balance est negative nous avons un arrangement de parenthese impossible et illegal dans une equation
				if (balance < 0)
					return false;
			}

		return balance == 0;
	}

	//Transformer l>entree en token et split les nombres et remplis tokeninfixes
	void transformerennombre(std::vector<Element>) {
		//s'assure que token infixe est vide
		tokensInfixe.clear();

		std::string nbEnCours = "";
		for (size_t i = 0; i < entreeChar.size(); ++i) {
			char c = entreeChar[i];

			if (std::isspace(static_cast<unsigned char>(c))) {
				//peut etre fin du nombre en cours
				if (!nbEnCours.empty()) {
					tokensInfixe.push_back(nbEnCours);
					nbEnCours.clear();
				}
				continue;
			}

			if (std::isdigit(static_cast<unsigned char>(c))) {
				//accumule un nombre multidigits
				nbEnCours.push_back(c);
				continue;
			}

			//Si on est la c<est une parenthese ou un operatuer
			if (!nbEnCours.empty()) {
				tokensInfixe.push_back(nbEnCours);
				nbEnCours.clear();
			}

			std::string jeton(1, c);
			tokensInfixe.push_back(jeton);
		}

		if (!nbEnCours.empty()) {
			tokensInfixe.push_back(nbEnCours);
			nbEnCours.clear();
		}

		//pour double on chek on regarde si les parenthese son encore balancee
		//if (parenthese(tokensInfixe)) {
		//	throw std::runtime_error("Desequilibre des parenthese apres la tokenisation");
		//}
	}

	//Transforme l'infize en postfixe a l<aide du principe shunting yard, s<effectue sur la tokenisation effectuee plus tot 
	void transformeEnPostfixe(std::stack<Element>, std::vector<Element> TableauInfixe) {
		//s'assure que le postfixe est clear
		tokensPostfixe.clear();

		//pile d<operateurs
		std::stack<Element> pileOperateurs;

		for (size_t i = 0; i < TableauInfixe.size(); ++i) {
			const Element& tok = TableauInfixe[i];
			
			if (EstNombre(tok)) {
				tokensPostfixe.push_back(tok);
			}
			else if (tok == "(") {
				pileOperateurs.push(tok);
			}
			else if (tok == ")") {
				//vider jusqua (
				while (!pileOperateurs.empty() && pileOperateurs.top() != "(") {
					tokensPostfixe.push_back(pileOperateurs.top());
					pileOperateurs.pop();
				}
				if (pileOperateurs.empty()) {
					throw std::runtime_error("Parenthese oublie pendant la tokenisation");
				}
				//retire le (
				pileOperateurs.pop();
			}
			else if (EstOperateur(tok)) {
				while (!pileOperateurs.empty() && pileOperateurs.top() != "(" && Priorite(pileOperateurs.top()) >= Priorite(tok)) {
					tokensPostfixe.push_back(pileOperateurs.top());
					pileOperateurs.pop();
				}
				pileOperateurs.push(tok);

			}
			else {
				throw std::runtime_error("Token inconnu pendant la conversion en postfix");
			}
		}

		//vider le pile doperateurs
		while (!pileOperateurs.empty()) {
			if (pileOperateurs.top() == "(") {
				throw std::runtime_error("Parenthese oublie pendant la tokenisation");
			}
			tokensPostfixe.push_back(pileOperateurs.top());
			pileOperateurs.pop();
		}

		//Affichage
		std::cout << "Expression postfixee : ";
		for (size_t i = 0; i < tokensPostfixe.size(); ++i) {
			if (i > 0) std::cout << ' ';
			std::cout << tokensPostfixe[i];
		}

		Tableau = tokensPostfixe;
	}

	int evaluerExpression(std::stack<Element>, std::vector<Element>TableauPostfixe) {
		std::stack<long long> PileValeur;

		for (size_t i = 0; i < TableauPostfixe.size(); ++i) {
			const Element& tok = TableauPostfixe[i];

			if (EstNombre(tok)) {
				//conversion sur avec une petit parser
				long long valeur = 0;
				for (size_t j = 0; j < tok.size(); ++j) {
					valeur = valeur * 10 + static_cast<long long>(tok[j] - '0');
				}
				PileValeur.push(valeur);
			}
			else if(EstOperateur(tok)){
				if (PileValeur.size() < 2) {
					throw std::runtime_error("Expression postfixe invalide. evaluation impossible");
				}

				long long b = PileValeur.top();
				PileValeur.pop();
				long long a = PileValeur.top();
				PileValeur.pop();

				long long r = 0;

				if (tok == "+")r = a + b;
				else if (tok == "-")r = a - b;
				else if (tok == "*")r = a * b;
				else if (tok == "/") {
					if (b == 0) throw std::runtime_error("Division par zero.");
					//division entiere
					r = a / b; 
				}
				else if (tok == "%") {
					if (b == 0) throw std::runtime_error("Modulo par zero.");
					r = a % b;
				}
				else {
					throw std::runtime_error("Operateur inconnu a l'evaluation");
				}
				PileValeur.push(r);
			}
			else {
				throw std::runtime_error("Expression postfixe invalide");
			}
		}

		if (PileValeur.size() != 1) {
			throw std::runtime_error("Expression postfixee invalide (trop d'operandes).");
		}

		long long resultat = PileValeur.top();

		return static_cast<int>(resultat);
	}

	//Accesseur poue les appels dans le main
	const std::vector<Element>& ObtenirTokensInfixe() const { return tokensInfixe; }
	const std::vector<Element>& ObtenirTokensPostfixe() const { return tokensPostfixe; }
};