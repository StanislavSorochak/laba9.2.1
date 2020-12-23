#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Special { АВ, БІ, ІК, МН, ТР };

string s_special[] = { "Авіоніка",
					   "Біомедична інженерія",
					   "Інформаційно-комунікаційні системи",
					   "Мікро- та наносиситемна техніка",
					   "Тклекомунікаціїї та радіотехніка" };

struct student
{
	string surname;
	int kurs;
	Special specialization;
	int phisuka;
	int matematic;
	int informatic;
};

void Create(student* s, const int kilkist);
void Print(student* s, const int kilkist);
void Sort(student* s, const int kilkist);
int* IndexSort(student* s, const int kilkist);
void PrintIndexSorted(student* s, int* I, const int kilkist);
int BinSearch(student* s, const int kilkist, const string surname, const int kurs, const int matematic);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_student;
	cout << "Введіть кількість студентів: "; cin >> kil_student;
	cout << endl;
	student* s = new student[kil_student];

	string surname;
	int kurs;
	int matematic;
	int found;

	int menuItem;
	do {
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;
		switch (menuItem)
		{
		case 1:
			Create(s, kil_student);
			break;
		case 2:
			Print(s, kil_student);
			break;
		case 3:
			Sort(s, kil_student);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, kil_student), kil_student);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get();
			cin.sync();
			cout << " прізвище: ";
			getline(cin, surname);

			cout << " курс: ";
			cin >> kurs;

			cout << " бал з математики: "; cin >> matematic;
			cout << endl;
			if ((found = BinSearch(s, kil_student, surname, kurs, matematic)) != -1)
				cout << "Знайдено студента в списку під номером " << found + 1 << endl;
			else
				cout << "Шуканого студента в списку не знайдено" << endl;
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menuItem != 0);

	delete[] s;
}

void Create(student* s, const int kilkist)
{
	int kurs, special;
	for (int i = 0; i < kilkist; i++)
	{
		cout << endl;
		cout << "студент № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  прізвище: "; getline(cin, s[i].surname);
		cout << "  курс: "; cin >> s[i].kurs;
		cout << "  спеціальність (0 - Авіоніка, 1 - Біомедична інженерія, 2 - Інформаційно-комунікаційні системи, 3 - Мікро- та наносиситемна техніка, 4 - Тклекомунікаціїї та радіотехніка ): "; cin >> special;
		s[i].specialization = (Special)special;
		cout << "  оцінка з фізики: "; cin >> s[i].phisuka;
		cout << "  оцінка з математики: "; cin >> s[i].matematic;
		cout << "  оцінка з інформатики: "; cin >> s[i].informatic;
	}
}

void Print(student* s, const int kilkist)
{
	cout << "====================================================================================================="
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність                     | Фізика | Математика  | Інформатика |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].surname
			<< "| " << setw(3) << right << s[i].kurs << "  "
			<< "| " << setw(30) << left << s_special[s[i].specialization] << ""
			<< "| " << setw(4) << right << s[i].phisuka << "   "
			<< "| " << setw(6) << right << s[i].matematic << "      "
			<< "| " << setw(6) << right << s[i].informatic << "     |" << endl;
	}
	cout << "======================================================================================================" << endl;
}

void Sort(student* s, const int kilkist)
{
	student tmp;

	for (int i0 = 0; i0 < kilkist - 1; i0++)
		for (int i1 = 0; i1 < kilkist - i0 - 1; i1++)
		{
			if ((s[i1].kurs > s[i1 + 1].kurs)
				|| (s[i1].kurs == s[i1 + 1].kurs && s[i1].matematic > s[i1 + 1].matematic)
				|| (s[i1].kurs == s[i1 + 1].kurs && s[i1].matematic == s[i1 + 1].matematic && s[i1].surname < s[i1 + 1].surname)
				)
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
		}
}

int* IndexSort(student* s, const int kilkist)
{
	int* I = new int[kilkist];

	for (int i = 0; i < kilkist; i++)
		I[i] = i;

	int i, j, value;
	for (i = 1; i < kilkist; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (
				(s[I[j]].kurs > s[value].kurs)
				||
				(s[I[j]].kurs == s[value].kurs && s[I[j]].matematic > s[value].matematic)
				||
				(s[I[j]].kurs == s[value].kurs && s[I[j]].matematic == s[value].matematic && s[I[j]].surname > s[value].surname)
				);
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(student* s, int* I, const int kilkist)
{
	cout << "==================================================================================================="
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність                   | Фізика | Математика  | Інформатика |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[I[i]].surname
			<< "| " << setw(3) << right << s[I[i]].kurs << "  "
			<< "| " << setw(22) << left << s_special[s[I[i]].specialization] << ""
			<< "| " << setw(30) << right << s[I[i]].phisuka << "   "
			<< "| " << setw(6) << right << s[I[i]].matematic << "      "
			<< "| " << setw(6) << right << s[I[i]].informatic << "     |" << endl;
	}
	cout << "===================================================================================================" << endl;
}

int BinSearch(student* s, const int kilkist, const string surname, const int kurs, const int matematic)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].kurs == kurs && s[m].matematic == matematic && s[m].surname == surname)
			return m;
		if (
			(s[m].kurs < kurs)
			|| (s[m].kurs == kurs && s[m].matematic < matematic)
			|| (s[m].kurs == kurs && s[m].matematic == matematic && s[m].surname < surname)
			)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}
