# Implémentation de la commande ls

## Description
Ce projet est une réimplémentation de la commande `ls` de Unix/Linux en langage C. Il reproduit les fonctionnalités principales de la commande `ls` standard avec plusieurs options couramment utilisées.

## Fonctionnalités
Cette implémentation supporte les options suivantes :

- `-a` : Affiche tous les fichiers, y compris les fichiers cachés
- `-A` : Affiche presque tous les fichiers (sauf `.` et `..`)
- `-l` : Format long, affiche les détails des fichiers
- `-R` : Listing récursif des sous-répertoires
- `-r` : Inverse l'ordre d'affichage
- `-s` : Affiche la taille des fichiers
- `-t` : Trie par date de modification
- `-L` : Suit les liens symboliques
- `-1` : Affiche un fichier par ligne
- `-g` : N'affiche pas le propriétaire
- `-G` : N'affiche pas le groupe
- `-f` : N'effectue pas de tri
- `-F` : Ajoute un indicateur de type (`/` pour les répertoires, etc.)

## Installation

### Prérequis
- GCC (GNU Compiler Collection)
- Make
- Système Unix/Linux

### Compilation
make

## Utilisation
./ls [options] [path]

## Exemples d'utilisation
### Afficher les détails des fichiers dans /var/log
./ls -l /var/log
### Afficher tous les fichiers dans /home/user/Documents
./ls -a /home/user/Documents
### Afficher tous les fichiers dans /usr/bin
./ls -R /usr/bin
### Afficher la taille des fichiers dans /etc et trier par date de modification
./ls -s -t /etc

## Structure du projet

├── include/
│ ├── flags.h
│ ├── file_ops.h
│ └── display.h
├── src/
│ ├── main.c
│ ├── flags.c
│ ├── file_ops.c
│ └── display.c
├── Makefile
└── README.md

## Architecture
Le projet est divisé en plusieurs modules :
- **flags** : Gestion des options de la ligne de commande
- **file_ops** : Opérations sur les fichiers et répertoires
- **display** : Affichage des informations

## Limitations Connues
- Certaines options avancées de la commande `ls` standard ne sont pas implémentées
- Le formatage peut légèrement différer de la commande `ls` standard

## Contribution
Les contributions sont les bienvenues ! N'hésitez pas à :
1. Fork le projet
2. Créer une branche pour votre fonctionnalité
3. Commiter vos changements
4. Pousser vers la branche
5. Ouvrir une Pull Request

## Licence
Ce projet est sous licence libre.

## Auteur
aliev_a & anzarb_y

## Contexte
- Inspiré par la commande `ls` du projet GNU coreutils
- Développé dans le cadre d'un projet éducatif