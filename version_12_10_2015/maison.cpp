#include <ctime>
#include <cstdio>
#include <iostream>

#include "Maison.h"


#ifdef _WIN32
#   include <Windows.h>
#   define PAUSE(x) Sleep(x * 1000)
#else
#   include <unistd.h>
#   define PAUSE(x) sleep(x)
#endif

using namespace std;

Maison::Maison(unsigned int id, const std::string& adresse, float position) : ObjetConnecte(id)
{
	adresse_ = adresse;
	positionDeLaMaison_ = position;
}

float Maison::getPosition() const
{
	return positionDeLaMaison_;
}


void Maison::setPosition(float position)
{
	positionDeLaMaison_ = position;
}

void Maison::seConnecter(Routeur* routeur)
{
	routeur->accepterConnexion(this);
}

Maison::~Maison()
{
	// A faire
}
void Maison::ajouterCellulaire(Cellulaire cellulaire)
{
	cellulairesObserves_.push_back(&cellulaire);
}


void Maison::ajouterOccupant(Personne personne) //* enlevé
{
	occupants_.push_back(&personne);//& ajouté
}


bool Maison::estOccupant(Personne* personne)
{
	bool estOccupant = false;
	for (size_t j = 0; j<occupants_.size(); j++)
	{
		if (occupants_[j]->getNumeroCellulaire == personne->getNumeroCellulaire) //pour ne pas comparer deux objet j ai ajouté ->getCellulaire
		{
			estOccupant = true;
			break;
		}
	}
	return estOccupant;
}


bool Maison::estVide() const //j ai modifié le code mais l idée est la meme (j ai laissé l encien code en commentaire)
{
	/*bool estVide = true;
	for (size_t j = 0; j<occupants_.size(); j++)
	{
		if (occupants_[j]->estALaMaison())
		{
			estVide = false;
			break;
		}
	}
	return estVide;*/

	return(!occupants_.size());

}


void Maison::observerCellulaires(float temps_observation)
{
	// boucle dans le temps
	// les cellulaires enregistres sont observes en continu.
	time_t start = time(0);
	while (difftime(time(0), start) <= temps_observation)
	{

		// Observation de tous les cellulaires, detection de proximite et ouverture du systeme de la maison si besoin.
		for (size_t i = 0; i < cellulairesObserves_.size(); i++)
		{
			if (cellulairesObserves_[i]->estProche(positionDeLaMaison_))
			{
				cellulairesObserves_[i]->getProprietaire()->setEstALaMaison(true);


				cout << "Bienvenue " << cellulairesObserves_[i]->getProprietaire()->getPrenom() << " !" << endl;

				if (estOccupant(cellulairesObserves_[i]->getProprietaire()))
				{
					cellulairesObserves_[i]->seConnecter(this->getRouteur()); //on px pas mettre this->nom d un autre objet

					for (size_t j = 0; j < listDeChauffage_.size(); j++)
					{

						this->envoyerMessage(Message(this->getId(), this->listDeChauffage_[j]->getId(), ALLUMAGE_AUTOMATIQUE)); // ici aussi pas d objet
						this->listDeChauffage_[j]->setEtat(1); //allumage de tous les chauffage
					}
				}
				else
				{
					bool unOccupantALaMaison = false;
					for (size_t i = 0; i < cellulairesObserves_.size(); i++) //size_t ala place de unsigned int
					{
						this->envoyerMessage(Message(this->getId(), this->listDeChauffage_[i]->getId(), ALLUMAGE_AUTOMATIQUE)); // ici aussi pas d objet


					}
				}
			}

			//si la persone quitte la maison
			for (size_t j = 0; j < listDeChauffage_.size(); j++)
			{
				if (!cellulairesObserves_[i]->estProche(positionDeLaMaison_))
				{
					cellulairesObserves_[i]->getProprietaire()->setEstALaMaison(false);
					cout << "Au revoir " << cellulairesObserves_[i]->getProprietaire()->getPrenom() << " !" << endl;
					cellulairesObserves_[i]->seDeconnecter();

					if (estVide())
					{
						for (size_t i = 0; i < listDeChauffage_.size(); j++)
						{
							this->envoyerMessage(Message(this->getId(), this->listDeChauffage_[i]->getId(), ETTEINDRE_CHAUFFAGE));
							this->listDeChauffage_[i]->setEtat(0);
						}
					}
				}


				// pause de une seconde. Attention, le comportement de la fonction pause() est different sous Windows et sous Linux/OSX
				PAUSE(1);

			}
		}
	}
}

string Maison::getAdresse() const
{
	return adresse_;
}


void Maison::setAdresse(string adresse)
{
	adresse_ = adresse;
}