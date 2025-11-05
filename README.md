# TP2— Postfixe

**Auteurs :** Émile Simard, Xavier Boivin-Thibeault  
**Codes permanents :** SIME09050100, BOIX19050400

---

## Fonctionnement

1. Exécuter le programme.
2. Lorsque le message s’affiche : **« Entrez une expression infixe »**, saisir une expression valide.
3. Le programme affichera l’**expression postfixée** ainsi que sa **valeur d’évaluation**.

---

## Notes importantes

- **Bonus #1 (multi-digits) — Réalisé :**  
  Le programme prend en charge les **nombres à plusieurs chiffres**. En conséquence, les types de `Stack` et `Vector` ont été adaptés pour manipuler des **jetons chaîne** (`std::string`).
  
- **Caractères autorisés :** chiffres, espaces, parenthèses `(` `)`, opérateurs `+`, `-`, `*`, `/`, `%`.  
  Les priorités respectées sont :  
  `()` > `* / %` > `+ -`.

---

## Gestion des erreurs

- Les cas invalides (caractère non autorisé, parenthèses déséquilibrées, postfixe mal formée, division/modulo par zéro, opérandes manquants, etc.) sont **signalés par des exceptions** (ex. `std::runtime_error`).  

---

## Rapport de tests

Un fichier **PDF** accompagne ce projet. Il contient :
- Les **résultats** des tests effectués.
- La **démonstration** du bon fonctionnement des principales fonctions.
- La **validation** qu’aucun plantage ne survient lors d’une utilisation normale.
---
