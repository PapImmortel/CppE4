#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Find_Motive(string file_path, string motive)
{
	ifstream file;
	file.open(file_path);
	if (!file)
	{
		cout << "The file " + file_path + " could not be opened." << endl;
		file.close();
		return ;

	}
	else
	{
		int nbFrequence = 0;

		string ligne;
		while (getline(file, ligne))
		{
			string message = "";
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
		cout << "The file " + file_path + " contains " + to_string(nbFrequence) + " words containing the motive " + motive << endl;

	}

	file.close();
	return;
}
 
int main(int argc, char* argv[])
{
	string file_path = argv[1];
	string motive = argv[2];
	
	Find_Motive(file_path,motive);
}