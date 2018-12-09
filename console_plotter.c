#include <stdio.h>
#include <math.h>

const int X_MAX = 100; // максимальное число символов по горизонтали
const int Y_MAX = 50; // максимальное число символов по вертикали

const char PLOT_CHAR = '.'; // символ для рисования точек

// функция для построения графика
double f(double x) {
	if (x == 0)
		return 1;

	return sin(x) / x;
}

// функция, переводящяая значение x из интервала [in_min, in_max] в интервал [out_min, outmax]
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// построение графика функции
void plot(double (*f)(double), double x_min, double x_max) {	
	// ищем минимальное и максимальное значение функции на отрезке
	double y_min = f(x_min);
	double y_max = f(x_max);

	for (int ix = 0; ix < X_MAX; ix++) {
		double x = map(ix, 0, X_MAX - 1, x_min, x_max);
		double y = f(x);

		if (y < y_min && y > -10000)
			y_min = y;

		if (y > y_max && y < 10000)
			y_max = y;
	}

	char field[Y_MAX][X_MAX]; // матрица символов для отрисовки

	// очищаем матрицу, проставляя везде пробелы
	for (int iy = 0; iy < Y_MAX; iy++)
		for (int ix = 0; ix < X_MAX; ix++)
			field[iy][ix] = ' ';

	int Yo = map(0, y_min, y_max, Y_MAX - 1, 0); // определяем положение оси X
	int Xo = map(0, x_min, x_max, 0, X_MAX - 1); // определяем положение оси y

	// проставляем символы вертикальной оси
	if (Xo >= 0 && Xo < X_MAX) {
		for (int iy = 0; iy < Y_MAX; iy++)
			field[iy][Xo] = '|';
	}

	// проставляем символы горизонтальной оси
	if (Yo >= 0 && Yo < Y_MAX) {
		for (int ix = 0; ix < X_MAX; ix++)
			field[Yo][ix] = '-';
	}

	// проставляем точку пересечения осей
	if (Xo >= 0 && Yo >= 0 && Xo < X_MAX && Yo < Y_MAX) {
		field[Yo][Xo] = '+';
	}

	// проставляем точки функции
	for (int ix = 0; ix < X_MAX; ix++) {
		double x = map(ix, 0, X_MAX - 1, x_min, x_max);
		double y = f(x);

		int iy = map(y, y_min, y_max, Y_MAX - 1, 0);

		field[iy][ix] = PLOT_CHAR;
	}

	// выводим засечки по X и значение по X
	if (Yo >= 0 && Yo < Y_MAX) {
		for (int ix = 3; ix < X_MAX; ix += 10) {
			field[Yo][ix] = '|';

			sprintf(&field[Yo + 1][ix - 3], "%.3lf", map(ix, 0, X_MAX - 1, x_min, x_max));
		}
	}

	// выводим обозначение оси Y
	if (Xo >= 0 && Xo <= X_MAX) {
		for (int ix = 0; ix < Xo; ix++)
			printf(" ");

		printf("Y\n");

		for (int ix = 0; ix < Xo; ix++)
			printf(" ");

		printf("^ %lf\n", y_max);
	}

	// выводим поле
	for (int iy = 0; iy < Y_MAX; iy++) {
		for (int ix = 0; ix < X_MAX; ix++)
			printf("%c", field[iy][ix]);
		
		if (iy == Yo) {
			printf("> X");
		}

		printf("\n");
	}

	// выводим минимальное значение по Y
	if (Xo >= 0 && Xo <= X_MAX) {
		for (int ix = 0; ix < Xo - 4; ix++)
			printf(" ");

		printf("%lf\n", y_min);
	}
}

// построение таблицы значений функции
void draw_table(double (*f)(double), double a, double b, double h) {
	printf("\n           Table of values function\n");
	printf("+---------------------+----------------------+\n");
	printf("|          x          |         f(x)         |\n");
	printf("+---------------------+----------------------+\n");

	for (double x = a; x <= b; x += h)
		printf("| %19lf | %20lf |\n", x, f(x));	

	printf("+---------------------+----------------------+\n");
}

int main() {
	double a, b; // границы для отрисовки графика по оси X
	double h; // шаг изменения X для отрисовки таблицы
	int answer; // нужно ли рисовать таблицу

	printf("Enter a, b: ");
	scanf("%lf %lf", &a, &b); // считываем границы для отрисовки графика

	plot(f, a, b); // строим график

	printf("Draw table? (1 - yes / 0 - no): ");
	scanf("%d", &answer); // считываем, нужно ли строить талицу

	// если нужно
	if (answer == 1) {
		printf("Enter h: ");
		scanf("%lf", &h); // считываем шаг изменения

		draw_table(f, a, b, h); // рисуем таблицу
	}
}