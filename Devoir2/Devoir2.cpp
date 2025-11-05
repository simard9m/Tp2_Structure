// Devoir2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "Postfix.cpp"


int main()
{
    std::cout << "Entrez une expression infixe (entiers, + - * / %, parentheses):\n> ";

    std::string ligne;
    if (!std::getline(std::cin, ligne)) {
        return 0;
    }

    //Cancel le programme si l'expression est vide find_first_not_of(" \t\r\n\f\v") retourne npos lorsqu’aucun caractère
    if (ligne.find_first_not_of(" \t\r\n\f\v") == std::string::npos) {
        std::cerr << "expression vide rien a postfixer.\n";
        return 1;
    }

    //Construire le vectori pour le constructeur
    std::vector<char> entree;
    entree.reserve(ligne.size());
    for (size_t i = 0; i < ligne.size(); ++i) {
        entree.push_back(ligne[i]);
    }

    //Instanciation de postfix
    Postfix<std::string> post(entree);

    //Check de l<expression
    if (!post.Valider(entree)) {
        std::cerr << "Expression invalide" << std::endl;
        return 1;
    }

    //tokenisation 
    std::vector<std::string> tableauVide;
    post.transformerennombre(tableauVide);

    //conversion en postfix
    std::stack<std::string> pileTemp;
    post.transformeEnPostfixe(pileTemp, post.ObtenirTokensInfixe());
    std::cout << std::endl;
    //Evaluation
    int valeur = post.evaluerExpression(pileTemp, post.ObtenirTokensPostfixe());
    std::cout << "Resultat (int) = " << valeur << std::endl;

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
