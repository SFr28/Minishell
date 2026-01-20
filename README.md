# Minishell – École 42

**Projet de groupe** : Réimplémentation d'un shell basique en C, compatible avec un sous-ensemble des fonctionnalités de `bash`.

## Auteurs:
Saina Fraslin: parsing
Solenne Vincen (@Silver-444): exécution et buildins

---

## Description du projet
Minishell est un projet visant à créer un shell Unix minimaliste, capable de :
- Lire et analyser des commandes utilisateur.
- Gérer les tubes (`|`), redirections (`>`, `>>`, `<`), et variables d'environnement.
- Exécuter des commandes externes et internes (`echo`, `cd`, `exit`, etc.).

---

## Fonctionnalités implémentées
- Parsing de la ligne de commande.
- Gestion des redirections et pipes.
- Exécution des commandes avec gestion des processus (`fork`, `execve`, `waitpid`).
- Gestion des signaux (`Ctrl+C`, `Ctrl+D`).

---

## Ma contribution : Parsing
J'ai développé la partie **parsing** du projet, qui consiste à :
1. **Analyser la ligne de commande** entrée par l'utilisateur.
2. **Découper la commande en tokens** (mots-clés, arguments, opérateurs).
3. **Gérer les cas spéciaux** :
   - Guillemets simples/doubles (`'`, `"`).
   - Espaces et tabulations.
4. **Valider la syntaxe** avant l'exécution.

Cette étape est cruciale pour transformer une entrée utilisateur en une structure exploitable par le shell.
