#ifndef OBJETCONNECTE_H
#define OBJETCONNECTE_H

#include <string>
#include <iostream>

#include "message.h"
#include "Routeur.h" // j ai ajouté le include pour permettre l heritage

using namespace std;

class Routeur;
class ObjetConnecte
{
public:
	ObjetConnecte(unsigned int id = 1);

	unsigned int getId() const;
	bool getEtatDeLaConnexion() const;

	void setId(unsigned int nouveauId);
	void setEtatDeLaConnexion(bool nouveauEtat);

	void seDeconnecter(); //j ai enlevé le const parceque cette Methode change l etat de la connexion = pas const puisque elle change klk chose
	void seConnecter(Routeur* routeur);

	void envoyerMessage(const Message& message);
	void recevoirMessage(const Message& message) const;

	Routeur* getRouteur() const;
protected:

	unsigned int id_;
	
private:
 
  bool etatDeLaconnexion_ ;
  Routeur* routeur_ ;
};
#endif