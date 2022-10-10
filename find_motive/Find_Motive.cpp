#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Find_Motive(ifstream file, string motive)
{

	int nbFrequence = 0;

	string letters;
	int positionLetters = -1;
	int positionSpace = -1;
	string ligne;
	while (getline(file, ligne))
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
				string::size_type existe = message.find(motive);
				if (existe != string::npos)
				{
					nbFrequence += 1;
				}
			}
		}

	}
	return nbFrequence;
}

int main(int argc, char* argv[])
{
	string file_path = argv[1];
	string motive = argv[2];
	ifstream file;
	file.open(file_path);
	if (!file)
	{
		cout << "The file " + file_path + " could not be opened" << endl;
		file.close();
		return 1;
		
	}
	else
	{
		cout << "The file " + file_path + " contains " + to_string(Find_Motive(file, motive)) + " words containing the motive " + motive << endl;
		
	}
	file.close();
	return 1;
}
