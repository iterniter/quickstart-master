#include <iostream>
#include "Routeur.h"
#include "ObjetConnecte.h"
#include "Cellulaire.h"
#include "Chauffage.h"
#include "message.h"

using namespace std;

int main()
{
	/*###############################*/
	/*     PREPARATIFS AUX TESTS     */
	/*###############################*/

	// 1. Creer un routeur
	Routeur *routeur = new Routeur();

	// 2. Creer une maison, avec l'ID 1, une adresse et la position 14.0.
	Maison *maison = new Maison(1, "2500 Chemin Polytechnique", 14.0);
	// Connecter la maison au routeur
	maison->ObjetConnecte::seConnecter(routeur);

	// 3. Creer deux personnes: Philippe Lafrite, Mathilde Lafrite et Francois Lerigolo
	Personne* philippe = new Personne("Philippe", "Lafrite", 55);
	Personne* mathilde = new Personne("Mathilde", "Lafrite", 46);
	Personne* francois = new Personne("Francois", "Lerigolo", 33);


	// 4. Creer un cellulaire pour chaque occupant (IDs: 2, 3 et 4)
	string num1 = "514-430-9999";
	string num2 = "514-430-8888";
	string num3 = "514-430-7777";
	Cellulaire* cell1 = new Cellulaire(2, num1);
	Cellulaire* cell2 = new Cellulaire(3, num2);
	Cellulaire* cell3 = new Cellulaire(4, num3);

	philippe->attribuerCellulaire(num1);
	cell1->setProprietaire(philippe);



	// 5. Modifier la position des cellulaires de Philippe, Mathilde et Francois a 7.0, 8.0 et 6.0 respectivement
	cell1->setPosition(7.0);
	cell2->setPosition(8.0);
	cell3->setPosition(6.0);

	// 6. Ajouter Philippe et Mathilde comme occupants de la maison
	// Lorsqu'on ajoute un occupant a la maison, son cellulaire doit egalement etre ajoute.
	maison->ajouterOccupant(*philippe);
	maison->ajouterOccupant(*mathilde);

	// 7. Ajouter le cellulaire de francois aux cellulaires observes par la maison, sans que Francois soit occupant de la maison.
	maison->ajouterCellulaire(*cell3);

	// 8. Cr�er au moins 4 chauffages dont au moins 2 automatiques et les connecter au routeur
	// Attention � ne pas leur attribuer des IDs similaires aux IDs d�j� attribu�s(commencer � 5)
	Chauffage chauffage1(5);
	Chauffage chauffage2(6);
	Chauffage chauffage3(7);
	Chauffage chauffage4(8);

	chauffage3.setAutomatique(1);
	chauffage4.setAutomatique(1);

	/*###########################*/
	/*     TEST D'UN MESSAGE     */
	/*###########################*/

	// 1. Connecter le cellulaire de Phillipe au routeur
	cell1->seConnecter(routeur);

	// 2. Cr�er un message allant du cellulaire de Phillipe vers un chauffage non automatique parmis ceux cr��s plus haut
	// Le message est de type ALLUMER_CHAUFFAGE
	
	Message message(cell1->getId(),chauffage1,ALLUMAGE_AUTOMATIQUE);

	// 3. Envoyer le message depuis le cellulaire de Phillipe


	// 4. Deconnecter le cellulaire de Phillipe



	/*##################################*/
	/*     TEST DE LA CLASSE MAISON     */
	/*##################################*/

	// 1. Demarrer l'observation des cellulaires par la maison.
	// Lorsqu'un cellulaire approche de la maison, son proprietaire est identifie. S'il est occupant de la maison, le chauffage est allume, si ce n'est deja fait.
	// Deroulement du programme:
	// Mathilde rentre en premier a la maison, le maison l'identifie comme etant un occupant et active le chauffage
	// Philippe arrive ensuite, mais rien ne se passe car la maison n'est pas vide.
	// La maison detecte l'arrivee de Francois mais n'active rien car il n'est pas un occupant de la maison. La maison previent Philippe et Mathilde de l'arrivee de leur ami Francois.
	cout << endl << "Demarrage de l'observation..." << endl;
	maison->observerCellulaires();
	cout << endl << "Fin de l'observation..." << endl;

	/*#############*/
	/*     FIN     */
	/*#############*/

	// 1. Desallocation de la memoire.


	return 0;
}