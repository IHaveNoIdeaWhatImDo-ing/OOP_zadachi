#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#pragma warning(disable:4996)

using namespace std;

bool contains(const char* str, const char chr)
{
	unsigned i = 0;

	while (str[i] != '\0') {
		if (str[i++] == chr) {
			return true;
		}
	}

	return false;
}

class Game
{
private:
	char title[64];
	float price;
	bool isAvailable;

public:
	Game() = default;

	Game(const char title[64], const float price, const bool isAvailable) {
		strcpy(this->title, title);
		this->price = price;
		this->isAvailable = isAvailable;
	}

	Game operator=(const Game& game) {
		strcpy(this->title, game.getTitle());
		this->price = game.getPrice();
		this->isAvailable = game.getIsAvailable();
	}

	const char* getTitle(void) const {
		return this->title;
	}

	float getPrice(void) const {
		return this->price;
	}

	bool getIsAvailable(void) const {
		return this->isAvailable;
	}

	void setTitle(const char* title) {
		if (strlen(title) && !contains(title, ',')) {
			strcpy(this->title, title);
		}
		else if (contains(title, ',')) {
			cout << "Name cannot contain commas.\n";
			return;
		}
		else {
			cout << "Name cannot be empty.\n";
			return;
		}
		strcpy(this->title, title);
	}

	void setPrice(const float price) {
		if (price >= 0) {
			this->price = price;
		}
		else {
			cout << "Price canot be negative.\n";
			return;
		}
	}

	void setIsAvailable(const bool isAvailable) {
		this->isAvailable = isAvailable;
	}

	bool isFree(void) {
		return !price;
	}

	void print(void) {
		cout << "Title: " << this->title << '\n'
			 << "Price: " << this->price << "$\n"
			 << "Availability: " << boolalpha << this->isAvailable << '\n';
	}
};

class GamePlatform
{
private:
	Game games[100];

public:
	void addGame(const Game game) {
		for (unsigned short i = 0; i < 100; ++i) {
			if (!strlen(this->games[i].getTitle())) {
				this->games[i] = game;
			}
		}
	}

	void printGameByIndex(const unsigned index) {
		this->games[index].print();
	}

	void printAllGames(void) {
		for (unsigned short i = 0; i < 100; ++i) {
			printGameByIndex(i);
		}
	}

	void printMost(const bool expensive) {
		unsigned short index = 0;
		float currentMostPrice = this->games[0].getPrice();

		if (expensive) {
			for (unsigned short i = 1; i < 100; ++i) {
				if (this->games[i].getPrice() > currentMostPrice) {
					index = i;
					currentMostPrice = this->games[i].getPrice();
				}
			}
		}
		else {
			for (unsigned short i = 1; i < 100; ++i) {
				if (this->games[i].getPrice() < currentMostPrice) {
					index = i;
					currentMostPrice = this->games[i].getPrice();
				}
			}
		}

		this->games[index].print();
	}

	void printFree(void) {
		for (unsigned short i = 0; i < 100; ++i) {
			if (!this->games[i].getPrice() && strlen(this->games[i].getTitle())) {
				 this->games[i].print();
			}
		}
	}

	bool delGame(const char* title) {
		unsigned short i = 0;

		for (; i < 100; ++i) {
			if (!strcmp(this->games[i].getTitle(), title)) {
				this->games[i].setTitle('\0');
				this->games[i].setPrice(0);
				return true;
			}
		}

		return false;
	}

	bool saveToFile(const char* fpath) {
		ofstream streamWriter(fpath, ios::trunc);

		if (streamWriter.is_open()) {
			for (unsigned short i = 0; i < 100; ++i) {
				if (strlen(this->games[i].getTitle())) {
					streamWriter << this->games[i].getTitle() << ','
								 << this->games[i].getPrice() << ','
								 << this->games[i].getIsAvailable() << '\n';
				}
			}
		}
		else {
			return false;
		}
		
		streamWriter.close();
		return true;
	}

	bool readFromFile(const char* fpath) {
		ifstream streamReader(fpath);
		char line[100];
		unsigned short i = 0;

		if (streamReader.is_open()) {
			stringstream IHateThis(line);

			char tempTitle[64];
			float tempPrice;
			float tempIsAvailable;
			while (streamReader.getline(line, 100)) {
				stringstream idk(line);
				idk >> tempTitle >> tempPrice >> tempIsAvailable;

				this->games[i].setTitle(tempTitle);
				this->games[i].setPrice(tempPrice);
				this->games[i].setIsAvailable(tempIsAvailable);
			}
		}
		else {
			return false;
		}

		streamReader.close();
		return true;
	}
};

int main()
{
	return 0;
}
