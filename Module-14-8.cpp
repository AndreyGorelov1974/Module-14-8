/*8. Морской бой (дополнительное задание)
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

//символьные константы
const char shipSimbol = 'O';
const char horizontalShipSimbol = 'r';
const char verticalShipSimbol = 'd';
const char hitSimbol = 'X';
const char missSimbol = '*';
const char blankSimbol = '~';

//границы поля игры
const int minLimitArray = 0;
const int maxLimitArray = 9;

//максимальное количество кораблей и палуб
const int maxShips = 4;
const int maxDeck = 4;

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
//horizontalShipSimbol - направо
//verticalShipSimbol - вниз
int get_direction(void) {
	std::string str = "";
	std::cout << "Set the direction of your ship's location, " << horizontalShipSimbol << " - to the right or " << verticalShipSimbol << " - down" << std::endl;
	std::cin >> str;
	while (str.length() != 1 || (str[0] != horizontalShipSimbol && str[0] != verticalShipSimbol)) {
		std::cout << "This direction is incorrect. Set " << horizontalShipSimbol << " - to the right, or " << verticalShipSimbol << " - down: " << std::endl;
		std::cin >> str;
	}
	return str[0];
}

//функция отображения игрового поля
void display_play_field(char arr[][maxLimitArray + 1]) {

	std::cout << "  A B C D E F G H I J" << std::endl;
	for (int i = minLimitArray; i < maxLimitArray + 1; ++i) {
		//вставляем пробелы где однозначные номера
		if (i < maxLimitArray) {
			std::cout << i + 1 << " ";
		}
		else {
			std::cout << i + 1;
		}
		for (int j = minLimitArray; j < maxLimitArray + 1; ++j) {
			//заменяем служебные символы кораблей на красивые
			if (arr[i][j] == horizontalShipSimbol || arr[i][j] == verticalShipSimbol) {
				std::cout << shipSimbol << " ";
			}
			else {
				std::cout << arr[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	return;
}

//функция рассстановки кораблей на игровом поле
void set_ship_to_play_field(char arr[][maxLimitArray + 1], int deck, std::string player_name) {
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
	char direction = horizontalShipSimbol;
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
		if ((direction == horizontalShipSimbol && (column + deck) > maxLimitArray) || (direction == verticalShipSimbol && (line + deck) > maxLimitArray)) {
			std::cout << "It is impossible to put a ship in this place! Enter the coordinates again: ";
		}
		else {
			//задаём границы поля проверки соседних кораблей при направлении корабля горизонтально
			if (direction == horizontalShipSimbol) {
				topBorder = line - 1;
				bottomBorder = line + 1;
				leftBorder = column - 1;
				rightBorder = column + deck + 1;
			}
			//задаём границы поля проверки соседних кораблей при направлении корабля вертикально
			if (direction == verticalShipSimbol) {
				topBorder = line - 1;
				bottomBorder = line + deck + 1;
				leftBorder = column - 1;
				rightBorder = column + 1;
			}
			//корректируем границы если корабль расположен на краю
			if (leftBorder < minLimitArray) {
				leftBorder = minLimitArray;
			}
			if (rightBorder > maxLimitArray) {
				rightBorder = maxLimitArray;
			}
			if (topBorder < minLimitArray) {
				topBorder = minLimitArray;
			}
			if (bottomBorder > maxLimitArray) {
				bottomBorder = maxLimitArray;
			}
			bool correct = true;
			//проверяем наличие кораблей в поле корабля
			for (int i = topBorder; i <= bottomBorder; ++i) {
				for (int j = leftBorder; j <= rightBorder; ++j) {
					if (arr[i][j] == horizontalShipSimbol || arr[i][j] == verticalShipSimbol) {
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
				std::cout << "It is impossible to put a ship in this place!  Enter the coordinates again: ";
			}
		}
	}
	//устанавливаем горизонтальный  корабль
	if (direction == horizontalShipSimbol) {
		for (int i = column; i <= column + deck; ++i) {
			arr[line][i] = horizontalShipSimbol;
		}
	}
	//устанавливаем вертикальный корабль
	if (direction == verticalShipSimbol) {
		for (int i = line; i <= line + deck; ++i) {
			arr[i][column] = verticalShipSimbol;
		}
	}
	return;
}

//функция выстрела, если есть попадание возвращает true
bool shot_to_ship(char arr1[][maxLimitArray + 1], char arr2[][maxLimitArray + 1], int line, int column) {
	//инициализируем границы поля промахов вокруг корабля
	int leftBorder = 0;
	int rightBorder = 0;
	int topBorder = 0;
	int bottomBorder = 0;

	//если нет корабля рисуем промах и выходим с false
	if (arr2[line][column] == blankSimbol || arr2[line][column] == missSimbol) {
		arr1[line][column] = missSimbol;
		return false;
	}
	//если палуба горизонтального корабля
	else if (arr2[line][column] == horizontalShipSimbol) {
		//рисуем попадание на обоих полях
		arr2[line][column] = 'X';
		arr1[line][column] = 'X';
		//выставляем верхнюю и нижнюю границы для разных положений на краю и нет
		if (line == minLimitArray) {
			topBorder = line + 1;
			bottomBorder = line + 1;
		}
		else if (line == maxLimitArray) {
			topBorder = line - 1;
			bottomBorder = line - 1;
		}
		else {
			topBorder = line - 1;
			bottomBorder = line + 1;
		}
		rightBorder = column;
		leftBorder = column;

		//если не правая граница поля ищем крайнее правое попадание
		if (rightBorder < maxLimitArray) {
			while (arr2[line][rightBorder] == hitSimbol) {
				++rightBorder;
			}
			//если нашли целую палубу выходим с true 
			if (arr2[line][rightBorder] == horizontalShipSimbol) {
				return true;
			}
		}
		//если не левая граница поля ищем крайнее левое попадание
		if (leftBorder > minLimitArray) {
			while (arr2[line][leftBorder] == hitSimbol) {
				--leftBorder;
			}
			//если нашли целую палубу выходим с true 
			if (arr2[line][leftBorder] == horizontalShipSimbol) {
				return true;
			}
		}
		for (int i = leftBorder; i <= rightBorder; ++i) {
			arr1[topBorder][i] = missSimbol;
			arr1[bottomBorder][i] = missSimbol;
		}
		if (arr1[line][leftBorder] != hitSimbol) {
			arr1[line][leftBorder] = missSimbol;
		}
		if (arr1[line][rightBorder] != hitSimbol) {
			arr1[line][rightBorder] = missSimbol;
		}
		return true;
	}
	//если палуба вертикального корабля
	else if (arr2[line][column] == 'd') {
		//если не правый край рисуем справа промах
		if (column < 9) {
			arr1[line][column + 1] = '*';
		}
		//если не левый край рисуем слева промах
		if (column > 0) {
			arr1[line][column - 1] = '*';
		}
		//если не нижний край и нет палубы внизу
		if (line < 9 && arr2[line + 1][column] == '~') {
			//рисуем внизу три промаха
			for (int i = column - 1; i <= column + 1; ++i) {
				//проверяем границы поля
				if (i >= 0 && i <= 9) {
					arr1[line + 1][i] = '*';
				}
			}
		}
		//если не верхний край и нет палубы сверху
		if (line > 0 && arr2[line - 1][column] == '~') {
			//рисуем сверху три промаха
			for (int i = column - 1; i <= column + 1; ++i) {
				//проверяем границы поля
				if (i >= 0 && i <= 9) {
					arr1[line - 1][i] = '*';
				}
			}
		}
		//рисуем попадание на обоих полях и выходим с true
		arr2[line][column] = 'X';
		arr1[line][column] = 'X';
		return true;
	}
	//если выстрел в старое место попадания выходим с false
	else if (arr2[line][column] == 'X') {
		return false;
	}
}

int main() {
	//поле расстановки кораблей первого игрока
	char setShipsFieldPlayer_1[maxLimitArray + 1][maxLimitArray + 1];
	//поле расстановки кораблей второго игрока
	char setShipsFieldPlayer_2[maxLimitArray + 1][maxLimitArray + 1];
	//игровое поле первого игрока
	char playFieldPlayer_1[maxLimitArray + 1][maxLimitArray + 1];
	//игровое поле второго игрока
	char playFieldPlayer_2[maxLimitArray + 1][maxLimitArray + 1];

	//заполняем все массивы символами пустой клеточки
	for (int i = minLimitArray; i <= maxLimitArray; ++i) {
		for (int j = minLimitArray; j <= maxLimitArray; ++j) {
			setShipsFieldPlayer_1[i][j] = blankSimbol;
			setShipsFieldPlayer_2[i][j] = blankSimbol;
			playFieldPlayer_1[i][j] = blankSimbol;
			playFieldPlayer_2[i][j] = blankSimbol;
		}
	}

	//количество палуб оставшихся у 1 и 2 игроков
	int player_1Deck = 2;
	int player_2Deck = 2;

	//флаг указывающий у кого текущий ход
	std::string cureentMove = "Player 1";

	std::cout << "Welcome to the Battleship game!" << std::endl;

	//расстановка кораблей первого игрока
	//внешний цикл по количеству палуб
	//for (int i = 1; i < 5; ++i) {
	int i = 2;
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

	//основной цикл, пока количество палуб одно из игроков не станет 0
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