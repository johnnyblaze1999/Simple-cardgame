/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "CardGame.h"
 /* run this program using the console pauser or add your own getch, system("pause") or input loop */


// final update

// quicksort
int Partition(vector<int>&, int, int);
void Quicksort(vector<int>&, int, int);
void PrintVector(vector<int>);

// hash
class HashTable {
private:
	static const int hashGroups = 1000;
	list<pair<int, string>> table[hashGroups]; // List 1, index 0, List 2, index 1...

public:
	bool isEmpty() const;
	int hashFunction(int key);
	void insertItem(int key, string value);
	void removeItem(int key);
	//string searchTable(int key);
	void printTable();
};

// graph
class Graph {
	int V;
	list<int>* l;
public:
	Graph(int V) {
		this->V = V;
		l = new list<int>[V];
	}
	void addEdge(int x, int y) {
		l[x].push_back(y);
		l[y].push_back(x);
	}
	void printAdjlist() {
		for (int i = 0;i < V;i++) {
			cout << "Vertex " << i << "->";
			for (int nbr : l[i]) {
				cout << nbr << ", ";
			}
			cout << endl;
		}
	}
};
// final update


int main(int argc, char** argv) {

	cout << "=====================Welcome to Card Game====================" << endl;
	bool play = true;
	string name1, name2;
	cout << "First player input your name: ";
	cin >> name1;
	cout << "Second player input your name: ";
	cin >> name2;
	while (play)
	{
		//initialize player variables
		list<_Card> c1;
		list<_Card> c2;

		_Player player1(name1);// = {name1, c1}; //create two plyaers
		_Player player2(name2);// = {name2, c2};
		//create the game
		Game game(player1, player2);


		bool isfinished = false;
		int x = 1;
		while (!isfinished)
		{
			x++;

			isfinished = game.play(game.getNextPlayer());//play the 2 players
		}
		cout << "Do you want to play again? y/n";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			play = true;
		}
		else {
			play = false;
		}
	}

	// final update
	int c;
	HashTable HT;
	HT.insertItem(905, "Jim");
	HT.insertItem(201, "Tom");
	HT.insertItem(332, "Bob");
	HT.insertItem(124, "Sally");
	HT.insertItem(107, "Sandy");
	HT.insertItem(929, "Barb");
	HT.insertItem(333, "Rob");

	cout << "Before you leave. Please test my hash table using your player name along with a random key between 1 to 999." << endl;
	do {
		string v;
		int k;
		cout << endl<< "[1] View the hash table" << endl;
		cout << "[2] Insert player name and key" << endl;
		cout << "[3] Remove a player" << endl;
		cout << "[4] Sort random number" << endl;
		cout << "[5] Graph" << endl;
		cout << "[0] Exit" << endl;
		cout << "> ";
		cin >> c;

		switch (c) {
		case 1:
			HT.printTable();
			break;
		case 2:
			cout << "Enter player name: ";
			cin >> v;
			cout << "Enter key: ";
			cin >> k;
			HT.insertItem(k, v);
			break;
		case 3:
			cout << "Enter a key to remove a player: " << endl;
			cin >> k;
			HT.removeItem(k);
			break;
		case 4:
		{
			vector<int> v;
			int n = 20;
			for (int i = 0;i < n;i++) {
				v.push_back(rand() % 200);
			}

			cout << "Before sorting: " << endl;
			PrintVector(v);
			Quicksort(v, 0, v.size() - 1);
			cout << "After sorting: " << endl;
			PrintVector(v);
			break;
		}
		case 5:
			cout << "Graphing example: " << endl;
			Graph g(4);
			g.addEdge(0, 1);
			g.addEdge(0, 2);
			g.addEdge(2, 3);
			g.addEdge(1, 2);
			g.printAdjlist();
			break;
		}
	} while (c != 0);
	

	cout << "Sad to see you leave. Bye!" << endl;
	return 0;
}

// final update - hash

bool HashTable::isEmpty() const {
	int sum{};
	for (int i{};i < hashGroups;i++) {
		sum += table[i].size();
	}
	if (!sum)	return true;
	return false;
}

int HashTable::hashFunction(int key) {
	return key % hashGroups;
}

void HashTable::insertItem(int key, string value) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;

	for (;bItr != end(cell);bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr->second = value;
			cout << "[WARNING] Key exists. Player name replaced." << endl;
			break;
		}
	}

	if (!keyExists) {
		cell.emplace_back(key, value);
	}

	return;
}

void HashTable::removeItem(int key) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;

	for (;bItr != end(cell);bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr);
			cout << "[INFO] Pair removed." << endl;
			break;
		}
	}

	if (!keyExists)	cout << "[WARNING] Key not found. Pair not removed." << endl;
	return;
}

void HashTable::printTable() {
	for (int i{};i < hashGroups;i++) {
		if (table[i].size() == 0)	continue;

		auto bItr = table[i].begin();
		for (;bItr != table[i].end();bItr++) {
			cout << "[INFO] Key: " << bItr->first << " Player name: " << bItr->second << endl;
		}
	}
}

// final update - hash

// final update - quicksort

int Partition(vector<int>& v, int start, int end) {

	int pivot = end;
	int j = start;
	for (int i = start;i < end;++i) {
		if (v[i] < v[pivot]) {
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;

}

void Quicksort(vector<int>& v, int start, int end) {

	if (start < end) {
		int p = Partition(v, start, end);
		Quicksort(v, start, p - 1);
		Quicksort(v, p + 1, end);
	}

}

void PrintVector(vector<int> v) {
	for (int i = 0;i < v.size();++i)
		cout << v[i] << " ";
	cout << "\n\n";
}

// quicksort

