﻿/*8. Морской бой (дополнительное задание)
Требуется реализовать упрощённую игру в морской бой. Игровое поле размером 10 на 10 клеток. Участвуют два игрока.
В арсенале каждого из них 4 маленьких кораблика размером в одну клетку, 3 небольших корабля размером в две клетки,
2 средних корабля размером в три клетки и один большой корабль размером в четыре клетки.
Для простоты клетки поля пронумерованы по вертикали от 0 до 9 и по горизонтали от 0 до 9.
Мы не будем использовать классические наименования клеток, такие как B4, C6, а просто два индекса.
Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими.
Маленькие корабли в одну клетку расставляются с помощью указания одной клетки-точки на поле, к примеру 2,1.
Корабли размерностью от двух клеток и выше расставляются с помощью координат их начала и конца, к примеру: 0,1–0,3.
Корабли могут быть установлены только строго вертикально или горизонтально.
Установка корабля по диагонали недопустима, об этом тоже надо сообщить пользователю.
Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках) или выйдет за пределы поля,
то игроку должно быть сделано предупреждение, после которого он должен переставить корабль на новые валидные координаты.
В нашем упрощённом варианте игры мы не будем обсчитывать соприкосновения кораблей друг с другом, а потому корабли вполне можно будет размещать друг к другу вплотную,
борт к борту. После того как все корабли расставлены, начинается игра. Игроки по очереди атакуют друг друга, называя координаты выстрела.
После выстрела в консоль выводится информация о его результате: попал или мимо. Если выстрел успешен, клетка, на которой был корабль (или его фрагмент),
затирается и становится пустой. Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены. Как только это произойдёт,
в консоль выводится информация с номером игрока, который победил.

Советы и рекомендации
Действия игроков практически одинаковые, их можно объединить в функции.

В программе достаточно иметь два поля, по одному на каждого игрока.

Лучше создать три отдельные функции: одну для размещения одного корабля, еще одну как обёртку над первой (она будет размещать все корабли), а третью для удара по координате. Также вам потребуются два глобальных массива для двух отдельных участков моря:

bool field_1[10][10];
bool field_2[10][10];*/

#include <iostream>
#include <string>

//функция получения координат, возвращает трёхзначное число 1XX,
//вторая цифра - строка игрового поля
//третья цифра - колонка игрового поля
int get_coordinates(void) {
	std::string  str = "";
	std::cin >> str;
	while ((str.length() == 2 && (str[0] < 65 || str[0] > 75 || str[1] < 49 || str[1] > 57))
		|| (str.length() == 3 && (str[0] < 65 || str[0] > 75 || str[1] != 49 || str[2] != 48))
		|| str.length() > 3) {
		std::cout << "Such coordinates are incorrect. Try again: " << std::endl;
		std::cin >> str;
	}
	int column = (int)str[0] - 65;
	int line = (str.length() == 2) ? (int)str[1] - 49 : 9;
	return 100 + line * 10 + column;
}

//функция получения направления корабля при расстановке, возвращает cимвол
//r - направо
//d - вниз
int get_direction(void) {
	std::string str = "";
	std::cout << "Set the direction of your ship's location, r - to the right or d - down" << std::endl;
	std::cin >> str;
	while (str.length() != 1 || (str[0] != 'r' && str[0] != 'd')) {
		std::cout << "This direction is incorrect. Set r - to the right, or d - down: " << std::endl;
		std::cin >> str;
	}
	return str[0];
}

//функция отображения игрового поля
void display_play_field(char arr[][10]) {

	std::cout << "  A B C D E F G H I J" << std::endl;
	for (int i = 0; i < 10; ++i) {
		if (i < 9) {
			std::cout << i + 1 << " ";
		}
		else {
			std::cout << i + 1;
		}
		for (int j = 0; j < 10; ++j) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return;
}

//функция рассстановки кораблей на игровом поле
void set_ship_to_play_field(char arr[][10], int deck, std::string player_name) {
	system("cls");
	display_play_field(arr);
	std::cout << player_name << " enter coordinates begin " << deck << " deck ship: ";
	//уменьшаем количество палуб для упрощения расчётов
	--deck;
	//инициализируем границы поля проверки соседних кораблей
	int leftBorder = 0;
	int rightBorder = 0;
	int topBorder = 0;
	int bottomBorder = 0;
	int line = 0;
	int column = 0;
	//направление по умолчанию горизонтальное
	char direction = 'r';
	while (true) {
		int coordinates = get_coordinates();
		//получаем номер строки и столбца на игровом поле
		column = coordinates % 10;
		line = (coordinates % 100) / 10;
		//если 1 палуба то направление корабля не нужно
		if (deck != 0) {
			direction = get_direction();
		}
		//если выходит за границы игрового поля предупреждаеми и возвращаемся к вводу координат
		if ((direction == 'r' && (column + deck) > 9) || (direction == 'd' && (line + deck) > 9)) {
			std::cout << "It is impossible to put a ship in this place!" << std::endl;
		}
		else {
			//задаём границы поля проверки соседних кораблей при направлении корабля горизонтально
			if (direction == 'r') {
				topBorder = line - 1;
				bottomBorder = line + 1;
				leftBorder = column - 1;
				rightBorder = column + deck + 1;
			}
			//задаём границы поля проверки соседних кораблей при направлении корабля вертикально
			if (direction == 'd') {
				topBorder = line - 1;
				bottomBorder = line + deck + 1;
				leftBorder = column - 1;
				rightBorder = column + 1;
			}
			//корректируем границы если корабль расположен на краю
			if (leftBorder < 0) {
				leftBorder = 0;
			}
			if (rightBorder > 9) {
				rightBorder = 9;
			}
			if (topBorder < 0) {
				topBorder = 0;
			}
			if (bottomBorder > 9) {
				bottomBorder = 9;
			}
			bool correct = true;
			//проверяем наличие кораблей в поле корабля
			for (int i = topBorder; i <= bottomBorder; ++i) {
				for (int j = leftBorder; j <= rightBorder; ++j) {
					if (arr[i][j] == 'r' || arr[i][j] == 'd') {
						correct = false;
					}
				}
			}
			//если рядом нет кораблей выходим из цикла
			if (correct) {
				break;
			}
			//иначе перходим снова к вводу координат
			else {
				std::cout << "It is impossible to put a ship in this place!" << std::endl;
			}
		}
	}
	//устанавливаем горизонтальный  корабль
	if (direction == 'r') {
		for (int i = column; i <= column + deck; ++i) {
			arr[line][i] = 'r';
		}
	}
	//устанавливаем вертикальный корабль
	if (direction == 'd') {
		for (int i = line; i <= line + deck; ++i) {
			arr[i][column] = 'd';
		}
	}
	return;
}

//функция выстрела, если есть попадание возвращает true
bool shot_to_ship(char arr1[][10], char arr2[][10], int line, int column) {
	if (arr2[line][column] == '~') {
		arr1[line][column] = '*';
		return false;
	}
	else if (arr2[line][column] == 'r') {
		if (line < 9) {
			arr1[line + 1][column] = '*';
		}
		if (line > 0) {
			arr1[line - 1][column] = '*';
		}
		if (column < 9 && arr2[line][column + 1] == '~') {
			for (int i = line - 1; i <= line + 1; ++i) {
				arr1[i][column + 1] = '*';
			}
		}
		if (column > 0 && arr2[line][column - 1] == '~') {
			for (int i = line - 1; i <= line + 1; ++i) {
				arr1[i][column - 1] = '*';
			}
		}
		arr2[line][column] = 'X';
		arr1[line][column] = 'X';
		return true;
	}
	else if (arr2[line][column] == 'd') {
		if (column < 9) {
			arr1[line][column + 1] = '*';
		}
		if (column > 0) {
			arr1[line][column - 1] = '*';
		}
		if (line < 9 && arr2[line + 1][column] == '~') {
			for (int i = column - 1; i <= column + 1; ++i) {
				if (i >= 0 && i <= 9) {
					arr1[line + 1][i] = '*';
				}
			}
		}
		if (line > 0 && arr2[line - 1][column] == '~') {
			for (int i = column - 1; i <= column + 1; ++i) {
				if (i >= 0 && i <= 9) {
					arr1[line - 1][i] = '*';
				}
			}
		}
		arr2[line][column] = 'X';
		arr1[line][column] = 'X';
		return true;
	}
	else if (arr2[line][column] == 'X') {
		return false;
	}
}

int main() {
	//поле расстановки кораблей первого игрока
	char setShipsFieldPlayer_1[10][10] = {
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'}, };
	//поле расстановки кораблей второго игрока
	char setShipsFieldPlayer_2[10][10] = {
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'}, };
	//игровое поле первого игрока
	char playFieldPlayer_1[10][10] = {
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'}, };
	//игровое поле второго игрока
	char playFieldPlayer_2[10][10] = {
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'},
	{'~','~','~','~','~','~','~','~','~','~'}, };

	//количество палуб оставшихся у 1 и 2 игроков
	int player_1Deck = 2;
	int player_2Deck = 2;

	//флаг указывающий у кого текущий ход
	std::string cureentMove = "Player 1";

	std::cout << "Welcome to the Battleship game!" << std::endl;

	//расстановка кораблей первого игрока
	//внешний цикл по количеству палуб
	//for (int i = 1; i < 5; ++i) {
	int i = 1;
		//внутренний цикл по количеству кораблей
		for (int j = 3 - i; j > 0; --j) {
			set_ship_to_play_field(setShipsFieldPlayer_1, i, "Player 1");
		}
	//}

	//расстановка кораблей второго игрока
	//for (int i = 1; i < 5; ++i) {
		for (int j = 3 - i; j > 0; --j) {
			set_ship_to_play_field(setShipsFieldPlayer_2, i, "Player 2");
		}
	//}

	//основной цикл, пока winnerFlag не станет 1 или 2
	while (player_1Deck > 0 && player_2Deck > 0) {
		system("cls");
		//отображение игрового поля в зависимости от хода
		cureentMove == "Player 1" ? display_play_field(playFieldPlayer_1) : display_play_field(playFieldPlayer_2);

		std::cout << cureentMove << " enter the coordinates of your shot ";
		int coordinates = get_coordinates();
		//получаем номер строки и столбца на игровом поле
		int column = coordinates % 10;
		int line = (coordinates % 100) / 10;
		//переменная для результата выстрела
		bool shot = false;
		//вызываем функцию выстрела в зависимости от хода
		cureentMove == "Player 1" ? shot = shot_to_ship(playFieldPlayer_1, setShipsFieldPlayer_2, line, column) :
									shot = shot_to_ship(playFieldPlayer_2, setShipsFieldPlayer_1, line, column);

		//если есть попадание
		if (shot) {
			//ход остаётся у текущего игрока
			cureentMove == "Player 1" ? cureentMove = "Player 1" : cureentMove = "Player 2";
			cureentMove == "Player 1" ? --player_2Deck : --player_1Deck;
		}
		else {
			//при промахе передаём ход другому игроку
			cureentMove == "Player 1" ? cureentMove = "Player 2" : cureentMove = "Player 1";
		}
	}
	system("cls");
	cureentMove == "Player 1" ? display_play_field(playFieldPlayer_1) : display_play_field(playFieldPlayer_2);
	std::cout << cureentMove << " win!";
}