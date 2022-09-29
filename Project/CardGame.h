#pragma once
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <iterator>
#include <vector> //for shuffling list
#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>
#include <random>
#include <cstring>
#include <stdio.h>
#include <ctime>
using namespace std;
enum Color { //THE cards colors
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES,
};
typedef struct {
	string letter;
	int number;
	Color color;
} _Card;

class _Player {
public:
	_Player(string name)
	{
		this->name = name;
	}
	string name;
	list<_Card> cards;//those on the hand
};

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
class Game {
public:
	Game()
	{
		init();
	};
	Game(struct _Player& p1, struct _Player& p2)
	{
		init();
		this->players.insert(this->players.begin(), p1);
		this->players.insert(this->players.begin(), p2);
		cout << "players list size: " << this->players.size() << endl;
		currplayer = 0;
		deal();
	};
	bool play(_Player& player);
	bool isWinner() {
		list<_Player> ::iterator it;

		for (it = this->players.begin();it != this->players.end();++it)
		{
			if ((*it).cards.size() == 0)
			{
				iswon = true;
				return true;
			}
		}
		iswon = false;
		return false;
	};
	void init();
	void shuffle(list<_Card>& list);
	void showList(list<_Card> list);
	void deal();//among the players //4 4
	_Player& getNextPlayer() {
		list<_Player> ::iterator it;
		if (currplayer == 0)
		{
			this->currplayer = 1;
			it = this->players.begin();
			return (*it);
		}
		else {
			this->currplayer = 0;
			it = this->players.begin();
			++it;//next player
			return (*it);
		}

	}

private:
	bool iswon;
	int currplayer;
	//Queue queue;
	_Card topCard;
	list<_Card> usedcards;  //stores the used cards
	stack<_Card> deck;//should be a lifo
	list<struct _Player> players;
	int cardsremaining;
	bool cardsMatch(struct _Player payer);
	bool cardsIsPlaceable(string letters[], char colors[], int length, _Player player);
	_Card* getCard(list<_Card> cards, string letter);

};
_Card* Game::getCard(list<_Card> cards, string letter)
{
	list<_Card> ::iterator it;
	for (it = cards.begin();it != cards.end();++it)
	{
		if ((*it).letter == letter)
		{
			//return this card
			//_Card card = *it;
			//cout<<"assigning pointer"<<endl;
			////cout<<"letter ("<<(*it).letter<<") color("<<(*it).color<<") number("<<(*it).number<<")"<<endl;
			_Card* ret = new _Card();
			//ret = (_Card *) malloc(sizeof(_Card*));
			//cout<<"letter ("<<(*it).letter<<") color("<<(*it).color<<") number("<<(*it).number<<")"<<endl;
			ret->letter = (*it).letter;
			ret->color = (*it).color;
			ret->number = (*it).number;
			if (!ret)
			{
				//cout <<"failed to assign pointer"<<endl;
				return NULL;
			}
			//cout<<"found the card"<<endl;
			return ret;
		}
	}
	return NULL;
}
void Game::deal()
{
	//deal the cards 4 each
	//each player should have 4 so total is 8
	cout << "dealing" << endl;
	cout << "players size:" << this->players.size() << endl;
	for (int x = 0;x < 4;x++)
	{
		//cout<<"in loop"<<endl;
		list<_Player> ::iterator it;
		it = this->players.begin();
		if (this->players.size() >= 2)
		{
			//cout<<"dealing ("<<x<<")  deck size ("<<this->deck.size()<<")  player  ("<<(*it).name<<") cards size ("<<(*it).cards.size()<<")"<<endl;
			//it = this->players.begin();
			//advances to the first item in the iterator
			//std::advance(it, 0); //it will point to the item at index

			(*it).cards.push_front(this->deck.top());//assign the one on the deck to first player
			++it;
			//remove card from the deck
			this->deck.pop();
			//std::advance(it, 1); //it will point to the item at index
			(*it).cards.push_front(this->deck.top());//assign the one on the deck to second player
			//remove from the deck
			this->deck.pop();
		}
		else {
			cout << "failed to deal cards" << endl;
		}
	}
	this->usedcards.push_front(this->deck.top());//used cards
	this->deck.pop();// remove from the deck
}
void Game::init()
{
	//initializes the game variables
	//create a list of cards,, use list so that we can shuffle the list before storing in the deck stack
	list <_Card> cards;

	for (int x = 1;x <= 52;x++)
	{
		Color col;
		if (x <= 13)
		{
			col = Color::CLUBS;
		}
		else if (x <= 26)
		{
			col = Color::DIAMONDS;
		}
		else if (x <= 39)
		{
			col = Color::HEARTS;
		}
		else {
			col = Color::SPADES;
		}
		if (x % 13 == 1)
		{
			_Card c = { "A",x, col };
			cards.push_back(c);
		}
		else if (x % 13 == 11)
		{
			//card J
			_Card c = { "J",x, col };
			cards.push_back(c);
		}
		else if (x % 13 == 12)
		{
			//card Q
			_Card c = { "Q",x, col };
			cards.push_back(c);
		}
		else if (x % 13 == 0)
		{
			//card K
			_Card c = { "K",x, col };
			cards.push_back(c);
		}
		else {
			stringstream ss;
			ss << x % 13;

			_Card c = { ss.str(), x % 13, col };//add to the list the cards 1 to 10
			cards.push_back(c);
		}

	}

	//shuffle them and add to stack
	this->shuffle(cards);//must be shuffled

	list<_Card> ::iterator it;
	int x = 0;
	for (it = cards.begin(); it != cards.end(); ++it, x++)
	{

		this->deck.push(*it);// add the item in the list to the stack
		string repr = "";
		if ((*it).color == Color::CLUBS)
		{
			repr = "CLUBS";
		}
		else if ((*it).color == Color::DIAMONDS)
		{
			repr = "DIAMONDS";
		}
		else if ((*it).color == Color::HEARTS)
		{
			repr = "HEARTS";
		}
		else if ((*it).color == Color::SPADES) {
			repr = "SPADES";
		}
		cout << "\n" << (*it).letter << " " << repr;
	}
	cout << endl;

	//deal the cards

}

void Game::showList(list<_Card> l)
{
	list<_Card> ::iterator it1;
	it1 = this->usedcards.begin();
	string repr = "";
	if ((*it1).color == Color::CLUBS)
	{
		repr = "CLUBS";
	}
	else if ((*it1).color == Color::DIAMONDS)
	{
		repr = "DIAMONDS";
	}
	else if ((*it1).color == Color::HEARTS)
	{
		repr = "HEARTS";
	}
	else if ((*it1).color == Color::SPADES) {
		repr = "SPADES";
	}
	cout << "list size (" << l.size() << ") top card (" << (*it1).letter << " " << repr << ")" << endl;
	//using iterator
	list<_Card> ::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
	{
		//get the color representation of the color enum
		if ((*it).color == Color::CLUBS)
		{
			repr = "CLUBS";
		}
		else if ((*it).color == Color::DIAMONDS)
		{
			repr = "DIAMONDS";
		}
		else if ((*it).color == Color::HEARTS)
		{
			repr = "HEARTS";
		}
		else if ((*it).color == Color::SPADES) {
			repr = "SPADES";
		}

		cout << (*it).letter << " " << repr << endl;
	}
	cout << endl;
}

void Game::shuffle(list<_Card>& l)
{
	//shuffles a given list usign the suffle method of the std namespace
	vector<_Card> V(l.begin(), l.end());//create the vector
	std::shuffle(V.begin(), V.end(), gen);
	l.assign(V.begin(), V.end());//assign to the list

	//optionally show the list to assure that it's shuffled
	//showList(l);
}

///
//this function allows a player to play the game, eg the player can pick a card or drop cards
///
//use address operators in order to make changes to the original object
bool Game::play(_Player& player)
{

	cout << "------------(" << player.name << ")Select an option------------" << endl;
	cout << "1) pick card" << endl;
	cout << "2) drop card(s)" << endl;
	cout << "3) show cards in hand" << endl;
	cout << "0) Exit" << endl << ">>";

	int choice;
	string input;
	cin >> input;
	std::string::const_iterator sit = input.begin();
	while (sit != input.end() && std::isdigit(*sit)) ++sit;

	if (!input.empty() && sit == input.end())
	{
		choice = atoi(input.c_str());

	}
	else {
		choice = 9;
	}
	cout << "choice (" << choice << ")" << endl;
	_Card _card = { this->deck.top().letter, this->deck.top().number, this->deck.top().color };
	switch (choice)
	{
	case 1:
		cout << "picking card" << endl;
		//pop card and load it into player"s cards

		player.cards.push_back(_card);//insert one element
		this->deck.pop();//remove from the stack
		cout << player.name << " picked card: " << player.cards.size() << endl;
		//add it to the player"s card
		break;
	case 2:
		//show the cards to the user
		cout << "---Your cards---" << endl;
		this->showList(player.cards);
		//bool iscorrectorder = false;
		//ask the user to input the next card to drop
		while (true)//(!iscorrectorder)
		{
			cout << "Enter the card letters or numbers one by one followed by the character(H, S, D, or F)>> ";
			string cards[20];//maximum of 20 cards
			char colors[20];
			string letter;
			char color;
			int count = 0;

			cin >> letter >> color;
			cards[count] = letter;
			colors[count] = color;
			count++;
			/*while((cin>>letter) != NULL)
			{
				cards[count] = letter;
				count++;
				break; //use one card
			}*/

			//check if cards can be placed on the deck
			if (this->cardsIsPlaceable(cards, colors, count, player))
			{
				//withdraw all the cards from the player
				list<_Card> ::iterator usedit;
				for (usedit = player.cards.begin();usedit != player.cards.end();++usedit)
				{
					//iterate throughout the cards list
					string currletter = (*usedit).letter;
					for (int x = 0;x < count;x++)
					{
						if (currletter == cards[x])
						{
							string repr = "";
							if ((*usedit).color == Color::CLUBS)
							{
								repr = "CLUBS";
							}
							else if ((*usedit).color == Color::DIAMONDS)
							{
								repr = "DIAMONDS";
							}
							else if ((*usedit).color == Color::HEARTS)
							{
								repr = "HEARTS";
							}
							else if ((*usedit).color == Color::SPADES) {
								repr = "SPADES";
							}
							cout << "card (" << (*usedit).letter << ", " << repr << ") dropped" << endl;
							//remove the card
							list<_Card> ::iterator pitr;
							_Card  cnew = {
								(*usedit).letter,(*usedit).number, (*usedit).color
							};
							usedit = player.cards.erase(usedit);//remove the card that matched
							this->usedcards.push_front(cnew);//add to the used cards
						}
					}
				}
				cout << "Success: Player (" << player.name << ") dropped (" << count << ") cards successfully" << endl;
				break;
			}
		}
		//remove a card from the player
		//drop card
		char card;
		//if not found repeat step
		//else pick top card from deck
		if (this->isWinner())
		{
			cout << "Congraturations " << player.name << ". You won!!" << endl;
			return true;
		}
		break;
	case 3:
		//show the cards
		cout << "(" << player.name << ")...your cards are...(" << player.cards.size() << ")" << endl;
		//show all the cards in the list, the method below is used to iterate over a list
		this->showList(player.cards);
		cout << "....Now pick an action" << endl;
		//recursively ask the player to play because first time the choice was displaying the cards
		return this->play(player);
		break;
	case 0:
		cout << "You lost!!! You left game unfinished" << endl;

		return true;
		break;
	default:
		cout << "Wrong choice try again..." << endl;
		//cin.clear();
		//cin.ignore(INT_MAX);
		return this->play(player);
		break;
	}

	return false;
}

//this function checks if the cards match ie, if the cards can be placed on the deck
bool Game::cardsMatch(struct _Player player)
{
	//using iterator
	list<_Card> ::iterator it;
	string letter = "";
	for (it = player.cards.begin(); it != player.cards.end(); ++it)
	{
		if (letter == "")
		{
			letter = (*it).letter;
			continue;//set the previous and ignore cross checking twice
		}
		//check if the player can win the match
		if ((*it).letter == "4" ||
			(*it).letter == "5" ||
			(*it).letter == "6" ||
			(*it).letter == "7" ||
			(*it).letter == "8" ||
			(*it).letter == "9" ||
			(*it).letter == "10")

		{
			if (letter == (*it).letter)
			{
				//continue
				continue;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

	}

	return true;
}

bool Game::cardsIsPlaceable(string letters[], char colors[], int length, _Player player)
{
	cout << "Checking if card is placeable dropped cards size(" << this->usedcards.size() << ")" << endl;
	list<_Card> ::iterator it;
	if (this->usedcards.size() > 0)
	{
		it = this->usedcards.begin();
		//std::advance(it, 0); //it will point to the item at index
	}
	else {
		return false;
	}

	_Card topcard;// = this->usedcards.top();
	topcard.color = (*it).color;
	topcard.letter = (*it).letter;
	topcard.number = (*it).number;

	for (int x = 0;x < length;x++)
	{
		//cout<<"looking for the first one"<<endl;
		char col = colors[x];//the color to hold
		string curr = letters[x];//the current card

		//for all cards being placed
		if (curr == "A")
		{
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
			continue;//can be placed on all the cards
		}
		else if (topcard.letter == "A")
		{
			if (curr != "A") //todo: allow for other operations here
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}

			}
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "2")
		{
			//player next should pick the cards
			if (curr != "2")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			else {
				return true;
			}
		}
		else if (topcard.letter == "3")
		{
			if (curr != "3")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			else {
				//player next should pick 3 cards
				return true;
			}
		}
		else if (topcard.letter == "4")
		{
			if (curr != "4")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "5")
		{
			if (curr != "5")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "6")
		{
			if (curr != "6")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "7")
		{
			if (curr != "7")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "8")
		{
			if (curr != "8")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "9")
		{
			if (curr != "9")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "10")
		{
			if (curr != "10")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "J")
		{
			if (curr != "J")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "Q")
		{
			if (curr != "Q")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}
			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}
		else if (topcard.letter == "K")
		{
			if (curr != "K")
			{
				if (col == 'H' && topcard.color == 2)
				{
					//is good
					continue;
				}
				else if (col == 'C' && topcard.color == 0)
				{
					//is good
					continue;
				}
				else if (col == 'S' && topcard.color == 3)
				{
					//is good
					continue;
				}
				else if (col == 'D' && topcard.color == 1)
				{
					//is good
					continue;
				}
				else {
					return false;//nothing can be done about it
				}
			}

			//place the card as the top and continue
			_Card* card = this->getCard(player.cards, curr);
			if (card != NULL)
			{
				//cout<<" copying card data"<<endl;
				topcard.color = card->color;
				topcard.letter = card->letter;
				topcard.number = card->number;
			}
			else {
				return false;
			}
		}

	}
	//if all procedures pass then the user selected the cards successfully, so return true
	//ma
	return true;
}
