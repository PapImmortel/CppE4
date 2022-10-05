#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Find_Motive(string dossier, string mot)
{

	int nbFrequence = 0;
	ifstream fichier(dossier, ios::in);
	if (fichier)
	{
		string letters;
		int positionLetters = -1;
		int positionSpace = -1;
		string ligne;
		while (getline(fichier, ligne))
		{
			string message;
			for (int i = 0; i < size(ligne); i++)
			{
				if ((ligne[i] != ' ') && (ligne[i] != ligne[-1]))
				{
					message = message + ligne[i];
				}
				else
				{
					string::size_type existe = message.find(mot);
					if (existe != string::npos)
					{
						nbFrequence += 1;
					}
				}
			}

		}
		cout << "The file  " + dossier + " contains " + to_string(nbFrequence) + " words containing the motive " + mot << endl;
		return 1;
	}
	else
	{
		cout << "The file " + dossier + " could not be opened" << endl;
	}
	return 0;
}

int main(void)
{
	string dossier = "";
	string mot = "";
	cout << "donne un dossier " << endl;
	cin >> dossier;
	cout << " donner le mot cherche" << endl;
	cin >> mot;
	Find_Motive(dossier, mot);

	return 0;
}
