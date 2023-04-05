#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

using namespace std;

struct Player
{
    char name[21];

private:
    unsigned rank;

public:
    unsigned getRank(void) const {
        return this->rank;
    }

    void setRank(const unsigned rank) {
        if (rank > 5000 || rank <= 0) {
            cout << "Rank cannot be greater than 5000 or lesser than 1.";
            return;
        }
        else {
            this->rank = rank;
        }
    }
};

char fpath[] = "C:\\Users\\grade\\Desktop\\players.dat";
unsigned FSIZE = 0;
Player* players;

void fsize(unsigned& size)
{
    ifstream streamReader(fpath);

    if (streamReader.is_open()) {
        streamReader.seekg(ios::end);
        size = ((unsigned int)streamReader.tellg() / sizeof(Player));
    }

    streamReader.close();
}

void readPlayers(void)
{
    ifstream streamReader(fpath);

    if (streamReader.is_open()) {
        for (size_t i = 0; i < FSIZE; ++i) {
            streamReader.read((char*)&players[i], sizeof(Player));
            if (players[i].name == "" || players[i].getRank() < 1 || players[i].getRank() > 5000) {
                cout << "Incorrect data read from file, terminating.";
                exit(0);
            }
        }
    }

    streamReader.close();
}

template <typename T>
void mySwap(T& el1, T& el2)
{
    T temp = el1;
    el1 = el2;
    el2 = temp;
}

void sortByRank(void)
{
    for (size_t i = 0; i < FSIZE - 1; ++i) {
        for (size_t a = i; a < FSIZE; ++a) {
            if (players[i].getRank() < players[a].getRank()) {
                mySwap(players[i], players[a]);
            }
        }
    }
}

int main()
{
    //fsize(FSIZE);
    FSIZE = 3;
    players = new Player[FSIZE];
    //readPlayers();

    strcpy(players[0].name, "Ivan");
    players[0].setRank(420);

    strcpy(players[1].name, "Stoyan");
    players[1].setRank(125);

    strcpy(players[2].name, "Petkan");
    players[2].setRank(64);

    sortByRank();

    char name[21];
    cin.getline(name, 21);

    for (size_t i = 0; i < FSIZE; ++i) {
        if (strcmp(players[i].name, name) == 1) {
            cout << players[i].getRank() << ". " << players[i].name << '\n';
        }
    }

    delete[] players;
    return 0;
}
