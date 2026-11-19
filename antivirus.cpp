#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string filename;
    string line;

    cout << "Enter file name to restore: ";
    cin >> filename;

    ifstream backup("backup.txt");

    if (!backup)
    {
        cout << "No backup found!" << endl;
        return 1;
    }

    ofstream restoredFile(filename);

    while (getline(backup, line))
    {
        restoredFile << line << endl;
    }

    backup.close();
    restoredFile.close();

    cout << "File restored successfully." << endl;

    return 0;
}