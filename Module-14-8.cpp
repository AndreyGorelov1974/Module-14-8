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


int main() {
	//игровое поле первого игрока
	char play_Field_1[10][10];
	//игровое поле второго игрока
	char play_Field_2[10][10];

	//флаг игрока который выйграл
	int winnerFlag = 0;

	std::cout << "Welcome to the Battleship game!" << std::endl;


	//основной цикл, пока winnerFlag не станет 1 или 2
	while ((winnerFlag != 1)&&(winnerFlag != 2)) {


	}
}