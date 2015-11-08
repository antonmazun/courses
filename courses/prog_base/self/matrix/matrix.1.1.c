#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float a[1000][1000];
 //= { 5,4,3,2,1,7,6,5,8,7,5,4,6,5,6,4,4,4,4,4,3,5,4,6,5 };
float b[1000][1000]; // масиви розміром 1000*1000 тому що не знаю як безрозмірний зробити (варіант зробити вказівник вказівкика), а практично >200 нікому не потрібно
float c[1000][1000];
void inverse_matrix();
void fillArr(float arr[],int n);
int main()
{
	srand(time(NULL));
	//fillArr(a, n);
	inverse_matrix();
	return 0;
}
void inverse_matrix()
{
	int i, j, k, n, v; // i - номер рядка, j - номер стовпця, k - потрібно щоб обнулити всі значення у початковій матриці, n - розмір квадратної матриці
	float d, det = 1; // d - число яке буде рівне відношенню значення елемента що ми обнулямо до значення елемента що стоїть на діагоналі
	printf("Rang of input matrix = ");
	scanf("%i", &n); 
	//for(i = 0; i < n; i++)
	//	for (j = 0; j < n; j++)
	//		a[i][j] = rand() % 4000 - 2000;
	for (i = 0; i < n; i++){
		printf("row %d :\n", i);
		for (j = 0; j < n; j++)
		{
			printf("A[%d,%d] = ", i, j);
			scanf("%f", &a[i][j]);
			c[i][j] = a[i][j];
		}
	}
	float got[1000];
	for (i = 0; i < n; i++){
		printf("B[%d] = ", i);
		scanf("%f", &got[i]);
	}
	printf("Input matrix :");
	for (i = 0; i < n; i++){
		printf("\n");
		for (j = 0; j < n; j++)
			printf(" %10f * x%d +", a[i][j], j); // це виведення початкової матриці, лише для оформлення
		printf("= %f", got[i]);
	}
		printf("\n---------------------------------------------------------------------------\n");
	for (i = 0; i < n; i++)
		b[i][i] = 1; // робимо одиничну матрицю
	for (i = 1; i < n; i++){
		puts("\n------------------------------");
		for (j = 0; j < i; j++)
			{
				for (v = 0; v < n; v++)
					printf("%10f", a[j][v]);
				printf (" | %10f", got[j]);
				puts(" ");
			}
		for (k = 0; k < n - i; k++){
			d = a[i + k][i - 1] / a[i - 1][i - 1];
			for (j = 0; j < n; j++){
				a[i + k][j] -= a[i - 1][j] * d; // віднімаємо від рядка [i + k] рядок [i - 1]
				b[i + k][j] -= b[i - 1][j] * d; // аналогічно із одиничною матрицею	
				printf("%10f", a[i + k][j]);
			}

			got[i + k] -= got[i - 1] * d;
			printf (" | %10f", got[i + k]);
			printf (" | (a[%i] - %f * a[%i])\n", k + i, d, i - 1);
			
		}		
	}	// після цього блоку початкова матриця уже перетворилася на нижню трикутну
	//знайдемо детермінант матриці
	for (i = 0; i < n; i++)
		det *= a[i][i];
	printf("\nDeterminant of input matrix = %f", det);
	printf("\n---------------------------------------------------------------------------");
	for (i = n - 2; i >= 0; i--){
		puts("\n------------------------------");
		
		for (k = i; k >= 0; k--){
			d = a[i - k][i + 1] / a[i + 1][i + 1];
			for (j = 0; j < n; j++){
				a[i - k][j] -= a[i + 1][j] * d;
				b[i - k][j] -= b[i + 1][j] * d;
				printf("%10f", a[i - k][j]);
			}
			got[i - k] -= got[i + 1] * d;
			printf (" | %10f", got[i - k]);
			printf (" | (a[%i] - %f * a[%i])\n", i - k, d, i + 1);
		}
		for (j = i + 1; j < n; j++)
			{
				for (v = 0; v < n; v++)
					printf("%10f", a[j][v]);
				printf (" | %10f", got[j]);
				puts(" ");
			}
	} // а після цього на діагональну
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			b[i][j] /= a[i][i]; // оскільки в нас початкова матриця діагональна але не одинична то ми кожен рядок матриці b ділимо на значення що стоїть на діаоналі в матриці а
		got[i] /= a[i][i];
	}
	printf("\nDiagonal matrix :");
	for (i = 0; i < n; i++){
		printf("\n");
		for (j = 0; j < n; j++)
			printf(" %10f ", a[i][j]); // це виведення початкової матриці, якщо у ній діагональне значення == 0 або == INF то ця матриця вироджена і оберненої не існує
	}
	printf("\n---------------------------------------------------------------------------");
	printf("\nInversed matrix :");
	for (i = 0; i < n; i++){
		printf("\n");
		for (j = 0; j < n; j++)
			printf(" %10f ", b[i][j]);
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++){
			a[i][j] = 0;
			for (k = 0; k < n; k++)
				a[i][j] += (b[i][k] * c[k][j]);
		}
	printf("\n---------------------------------------------------------------------------");
	printf("\nChecking:");	
	for (i = 0; i < n; i++){
		printf("\n");
		for (j = 0; j < n; j++)
			printf(" %10f ", a[i][j]);
	}
	printf("\n-----------------------------------------");
	for (i = 0; i < n; i++){
		printf("\nx%d = %10f ", i, got[i]);
	}
}
