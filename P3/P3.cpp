#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Texture.h"
#include "Random.h"
using namespace std;
struct tile {
	bool open;
	bool flag;
	bool mine;
	bool numbered;
	bool drawMine;
	sf::Sprite display;
	sf::Sprite flags;
	sf::Sprite mines;
	sf::Sprite number;
	int xcor;
	int ycor;
	
	tile(int xcor, int ycor);
};
tile::tile(int xcor, int ycor) {
	this->xcor = xcor;
	this->ycor = ycor;

	open = false;
	flag = false;
	mine = false;
	numbered = false;
	drawMine = false;

	display.setTexture(TextureManager::GetTexture("tile_hidden"));
	display.setPosition(xcor, ycor);

	flags.setTexture(TextureManager::GetTexture("flag"));
	flags.setPosition(xcor, ycor);

	mines.setTexture(TextureManager::GetTexture("mine"));
	mines.setPosition(xcor, ycor);
	
	number.setTexture(TextureManager::GetTexture("number_1"));
	number.setPosition(xcor, ycor);

}
struct board {
	int height;
	int width;
	int mines;
	int minec;
	int flagc;
	int numWin;
	bool win;
	bool lost;
	bool work;
	bool debugm;
	vector<vector<tile>> gameTile;
	
	board(int height, int width, int mines);
	vector<vector<tile>> createBoard();
	void drawBoard(sf::RenderWindow& game);
	void setMine();
	void openTiles(int a, int b);
	void newBoard();
};
void board::newBoard() {
	numWin = 0;
	lost = false;
	win = false;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (gameTile[j][i].mine = true) {
				gameTile[j][i].mine = false;
			}
			if (gameTile[j][i].flag) {
				gameTile[j][i].flag = false;
			}
			if (gameTile[j][i].open) {
				gameTile[j][i].open = false;
				gameTile[j][i].display.setTexture(TextureManager::GetTexture("tile_hidden"));
			}
			if (gameTile[j][i].numbered) {
				gameTile[j][i].numbered = false;
			}
		}
	}
}
void board::openTiles(int a, int b) {
	int count = 0;
	gameTile[a][b].open = true;
	numWin++;
	if ((a + 1) < height) {
		if (gameTile[a + 1][b].mine) {
			count++;
		}
	}
	if ((a - 1) >= 0) {
		if (gameTile[a - 1][b].mine) {
			count++;
		}
	}
	if ((b + 1) < width) {
		if (gameTile[a][b + 1].mine) {
			count++;
		}
	}
	if ((b - 1) >= 0) {
		if (gameTile[a][b - 1].mine) {
			count++;
		}
	}
	if ((a + 1) < height && (b + 1) < width) {
		if (gameTile[a + 1][b + 1].mine) {
			count++;
		}
	}
	if ((a - 1) >= 0 && (b - 1) >= 0) {
		if (gameTile[a - 1][b - 1].mine) {
			count++;
		}
	}
	if ((a + 1) < height && (b - 1) >= 0) {
		if (gameTile[a + 1][b - 1].mine) {
			count++;
		}
	}
	if ((a - 1) >= 0 && (b + 1) < width) {
		if (gameTile[a - 1][b + 1].mine) {
			count++;
		}
	}
	if (count != 0) {
		gameTile[a][b].numbered = true;
		if (count == 1) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_1"));
		}
		else if (count == 2) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_2"));
		}
		else if (count == 3) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_3"));
		}
		else if (count == 4) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_4"));
		}
		else if (count == 5) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_5"));
		}
		else if (count == 6) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_6"));
		}
		else if (count == 7) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_7"));
		}
		else if (count == 8) {
			gameTile[a][b].number.setTexture(TextureManager::GetTexture("number_8"));
		}
	}
	else {
		if ((a + 1) < height) {
			if (!gameTile[a + 1][b].mine && !gameTile[a + 1][b].open) {
				openTiles(a + 1, b);
			}
		}
		if ((a - 1) >= 0) {
			if (!gameTile[a - 1][b].mine && !gameTile[a - 1][b].open) {
				openTiles(a - 1, b);
			}
		}
		if ((b + 1) < width) {
			if (!gameTile[a][b + 1].mine && !gameTile[a][b + 1].open) {
				openTiles(a, b + 1);
			}
		}
		if ((b - 1) >= 0) {
			if (!gameTile[a][b - 1].mine && !gameTile[a][b - 1].open) {
				openTiles(a, b - 1);
			}
		}
		if ((a + 1) < height && (b + 1) < width) {
			if (!(gameTile[a + 1][b].mine && gameTile[a][b + 1].mine)) {
				if (!gameTile[a + 1][b + 1].mine && !gameTile[a + 1][b + 1].open) {
					openTiles(a + 1, b + 1);
				}
			}
		}
		if ((a - 1) >= 0 && (b - 1) >= 0) {
			if (!(gameTile[a - 1][b].mine && gameTile[a][b - 1].mine)) {
				if (!gameTile[a - 1][b - 1].mine && !gameTile[a - 1][b - 1].open) {
					openTiles(a - 1, b - 1);
				}
			}
		}
		if ((a + 1) < height && (b - 1) >= 0) {
			if (!(gameTile[a + 1][b].mine && gameTile[a][b - 1].mine)) {
				if (!gameTile[a + 1][b - 1].mine && !gameTile[a + 1][b - 1].open) {
					openTiles(a + 1, b - 1);
				}
			}
		}
		if ((a - 1) >= 0 && (b + 1) < width) {
			if (!(gameTile[a - 1][b].mine && gameTile[a][b + 1].mine)) {
				if (!gameTile[a - 1][b + 1].mine && !gameTile[a - 1][b + 1].open) {
					openTiles(a - 1, b + 1);
				}
			}
		}
	}
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if ((width * height - minec) == numWin) {
				win = true;
			}
			if (win && gameTile[j][i].mine) {
				if (!gameTile[j][i].flag) {
					flagc--;
				}
				gameTile[j][i].flag = true;
			}
			if (win && !gameTile[j][i].mine) {
				if (gameTile[j][i].flag) {
					flagc++;
				}
				gameTile[j][i].flag = false;
			}
		}
	}
}
void board::drawBoard(sf::RenderWindow& game) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (gameTile[j][i].open) {
				gameTile[j][i].display.setTexture(TextureManager::GetTexture("tile_revealed"));
				if (gameTile[j][i].flag) {
					flagc++;
				}
				gameTile[j][i].flag = false;
			}
			game.draw(gameTile[j][i].display);
			if (gameTile[j][i].numbered) {
				game.draw(gameTile[j][i].number);
			}
			if (gameTile[j][i].flag) {
				game.draw(gameTile[j][i].flags);
			}
			if (gameTile[j][i].mine && gameTile[j][i].drawMine) {
				game.draw(gameTile[j][i].mines);
			}
			if ((debugm || lost) && gameTile[j][i].mine) {
				game.draw(gameTile[j][i].mines);
			}
		}
	}
	int one = flagc % 10;
	int ten = (flagc % 100) / 10;
	int hundred = flagc / 100;
	if (one < 0) {
		one *= -1;
	}
	if (ten < 0) {
		ten *= -1;
	}
	if (hundred < 0) {
		hundred *= -1;
	}
	sf::Sprite neg(TextureManager::GetTexture("digits"));
	neg.setTextureRect(sf::IntRect(210, 0, 21, 32));
	neg.setPosition(0, height * 32);
	if (flagc < 0) {
		game.draw(neg);
	}
	else {
		sf::Sprite zero(TextureManager::GetTexture("digits"));
		zero.setTextureRect(sf::IntRect(0, 0, 21, 32));
		zero.setPosition(0, height * 32);
		game.draw(zero);
	}
	sf::Sprite ones(TextureManager::GetTexture("digits"));
	ones.setTextureRect(sf::IntRect(one * 21, 0, 21, 32));
	ones.setPosition(63, height * 32);
	game.draw(ones);

	sf::Sprite tens(TextureManager::GetTexture("digits"));
	tens.setTextureRect(sf::IntRect(ten * 21, 0, 21, 32));
	tens.setPosition(42, height * 32);
	game.draw(tens);

	sf::Sprite hundreds(TextureManager::GetTexture("digits"));
	hundreds.setTextureRect(sf::IntRect(hundred * 21, 0, 21, 32));
	hundreds.setPosition(21, height * 32);
	game.draw(hundreds);

	sf::Sprite face(TextureManager::GetTexture("face_happy"));
	face.setPosition(width * 16, height * 32);
	if (lost) {
		face.setTexture(TextureManager::GetTexture("face_lose"));
	}
	if (win) {
		face.setTexture(TextureManager::GetTexture("face_win"));
	}
	game.draw(face);

	sf::Sprite debug(TextureManager::GetTexture("debug"));
	debug.setPosition(width * 16 + 144, height * 32);
	game.draw(debug);

	sf::Sprite t1(TextureManager::GetTexture("test_1"));
	t1.setPosition(width * 16 + 208, height * 32);
	game.draw(t1);

	sf::Sprite t2(TextureManager::GetTexture("test_2"));
	t2.setPosition(width * 16 + 272, height * 32);
	game.draw(t2);

	sf::Sprite t3(TextureManager::GetTexture("test_3"));
	t3.setPosition(width * 16 + 336, height * 32);
	game.draw(t3);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2i position = sf::Mouse::getPosition(game);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (gameTile[i][j].display.getGlobalBounds().contains(position.x, position.y) && (!lost && !win)) {
					if (gameTile[i][j].flag) {
						gameTile[i][j].flag = false;
						flagc++;
					}
					else if(!gameTile[i][j].flag && !gameTile[i][j].open) {
						gameTile[i][j].flag = true;
						flagc--;
					}
				}
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i position = sf::Mouse::getPosition(game);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (gameTile[i][j].display.getGlobalBounds().contains(position.x, position.y) && !lost) {
					if (!gameTile[i][j].mine && !gameTile[i][j].open && !win && !gameTile[i][j].flag) {
						openTiles(i, j);
					}
					else if(gameTile[i][j].mine && !win && !gameTile[i][j].flag) {
						gameTile[i][j].open = true;
						lost = true;
					}
				}
				if (face.getGlobalBounds().contains(position.x, position.y)) {
					newBoard();
					minec = mines;
					flagc = mines;
					work = true;
				}
				if (t1.getGlobalBounds().contains(position.x, position.y)) {
					minec = 0;
					flagc = 0;
					newBoard();
					ifstream file("boards/testboard1.brd");
					string num;
					for (int i = 0; i < height; i++) {
						getline(file, num);
						for (int j = 0; j < width; j++) {
							if (num.at(j) == '1') {
								gameTile[i][j].mine = true;
								minec++;
								flagc++;
							}
							else {
								gameTile[i][j].mine = false;
							}
						}
					}
				}
				if (t2.getGlobalBounds().contains(position.x, position.y)) {
					minec = 0;
					flagc = 0;
					newBoard();
					ifstream file("boards/testboard2.brd");
					string num;
					for (int i = 0; i < height; i++) {
						getline(file, num);
						for (int j = 0; j < width; j++) {
							if (num.at(j) == '1') {
								gameTile[i][j].mine = true;
								minec++;
								flagc++;
							}
							else {
								gameTile[i][j].mine = false;
							}
						}
					}
				}
				if (t3.getGlobalBounds().contains(position.x, position.y)) {
					minec = 0;
					flagc = 0;
					newBoard();
					ifstream file("boards/testboard3.brd");
					string num;
					for (int i = 0; i < height; i++) {
						getline(file, num);
						for (int j = 0; j < width; j++) {
							if (num.at(j) == '1') {
								gameTile[i][j].mine = true;
								minec++;
								flagc++;
							}
							else {
								gameTile[i][j].mine = false;
							}
						}
					}
				}
			}
		}
		if (debug.getGlobalBounds().contains(position.x, position.y) && (!lost && !win)) {
			if (debugm) {
				debugm = false;
			}
			else {
				debugm = true;
			}
		}
	}
}
board::board(int height, int width, int mines) {
	this->height = height;
	this->width = width;
	this->mines = mines;
	numWin = 0;
	minec = mines;
	flagc = mines;
	win = false;
	lost = false;
	work = true;
	debugm = false;
}
vector<vector<tile>> board::createBoard() {
	int ycor = 0;
	for (int j = 0; j < height; j++) {
		vector<tile> temp;
		for (int i = 0; i < width; i++) {
			tile temps(i * 32, ycor);
			temp.push_back(temps);
		}
		gameTile.push_back(temp);
		ycor += 32;
	}
	return gameTile;
}
void board::setMine() {
	for (int i = 0; i < mines; i++) {
		int a = RandomNum::Int(0, height - 1);
		int b = RandomNum::Int(0, width - 1);
		if (gameTile[a][b].mine) {
			i--;
		}
		else {
			gameTile[a][b].mine = true;
		}
	}
};
int main() {
	ifstream file("boards/config.cfg");
	string widths;
	string heights;
	string counts;
	getline(file, widths);
	getline(file, heights);
	getline(file, counts);
	int width = stoi(widths);
	int height = stoi(heights);
	int mines = stoi(counts);
	board b = board(height, width, mines);
	sf::RenderWindow game(sf::VideoMode(width * 32, (height * 32) + 100), "Minesweeper");
	b.createBoard();
	while (game.isOpen()) {
		sf::Event e;
		while (game.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				game.close();
			}
			b.drawBoard(game);
			while (b.work) {
				b.setMine();
				b.work = false;
			}
			game.display();
		}
	}
	return 0;
}