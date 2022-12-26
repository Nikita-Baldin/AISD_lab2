#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Plenty{
private:
	size_t size;
	T* data;
public:
	Plenty() : data(nullptr), size(0) {}
	Plenty(size_t size) : data(new T[size]), size(size) {}
	Plenty <T>(const Plenty& second);
	~Plenty();

	T operator[](const size_t index);

	Plenty operator+(const Plenty& second);
	Plenty operator-(const Plenty& second);

	Plenty operator+(T num);
	Plenty operator-(T num);

	Plenty& operator+=(T num);
	Plenty& operator-=(T num);
	Plenty& add(T num);

	Plenty intersection(const Plenty& second);
	Plenty ungeneral(const Plenty& second);

	bool check_num(T num);
	bool operator!=(const Plenty& second);

	bool operator==(const Plenty& second);
	Plenty<T> operator=(const Plenty<T>& a);

	friend std::ostream& operator<<(std::ostream& s, const Plenty& set) {
		for (size_t i = 0; i < set.size; i++) {
			s << set.data[i] << " ";
		}
		return s;
	}
	
};

template <typename T>
Plenty <T>::Plenty(const Plenty& second) {
	size = second.size;
	data = new T[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = second.data[i];
	}
}

template <typename T>
Plenty <T>:: ~Plenty() {
	if (!data)
		delete[] data;
}
template <typename T>
T Plenty <T>:: operator[](const size_t index) {
	if (!data)
		throw std::logic_error("arr == nullptr");
	if (index > size - 1 || index < 0)
		throw std::logic_error("invalide index");
	return data[index];
}
template <typename T>
Plenty <T> Plenty <T>:: operator+(const Plenty& second) {
	Plenty tmp(size + second.size);
	tmp.size = 0;
	for (size_t i = 0; i < size; i++) {
		tmp.data[i] = data[i];
		tmp.size++;
	}
	for (size_t i = 0; i < second.size; i++) {
		if (check_num(second.data[i]) == false)
		{
			tmp.data[tmp.size] = second.data[i];
			tmp.size++;
		}
	}
	return tmp;
}
template <typename T>
Plenty <T> Plenty <T>:: operator-(const Plenty& second) {
	Plenty tmp(size);
	tmp.size = 0;
	bool flag = false;
	for (size_t i = 0; i < size; i++) {
		flag = false;
		for (size_t j = 0; j < second.size; j++) {
			if (data[i] == second.data[j])
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			tmp.data[tmp.size] = data[i];
			tmp.size++;
		}
	}
	return tmp;
}
template <typename T>
Plenty <T> Plenty <T>:: operator+(T num) {
	if (!data)
	{
		Plenty tmp(size);
		tmp.data[0] = num;
		tmp.size++;
		return tmp;
	}
	else {
		if (check_num(num) == false)
		{
			Plenty tmp(size);
			for (size_t i = 0; i < tmp.size; i++) {
				tmp.data[i] = data[i];
			}
			tmp.data[tmp.size] = num;
			tmp.size++;
			return tmp;
		}
		else {
			return *this;
		}
	}
}
template <typename T>
Plenty <T> Plenty <T>:: operator-(T num)
{
	Plenty data_n(size);
	for (size_t i = 0; i < data_n.size; i++) {
		data_n.data[i] = data[i];
	}
	if (check_num(num) == true) {
		for (size_t i = 0; i < data_n.size; i++) {
			if (data_n.data[i] == num)
			{
				for (size_t j = i; j < data_n.size - 1; j++) {
					data_n.data[j] = data_n.data[j + 1];
				}
				data_n.size--;
				break;
			}
		}
	}
	else std::cout << "Set have not got this num" << std::endl;
	return data_n;
}
template <typename T>
Plenty <T>& Plenty <T>::add(T num) {
	for (int i = 0; i < size; i++)
	{
		if (data[i] == num) throw "Element already eixst!";
	}
	T* tmp = new T[size + 1];
	for (int i = 0; i < size; i++) { tmp[i] = data[i]; }
	tmp[size] = num;
	delete[] data;
	data = tmp;
	size++;
	return *this;
}

template <typename T>
Plenty <T> & Plenty <T>::operator+=(T num)
{
	if (!data)
	{
		Plenty tmp(1);
		tmp.data[0] = num;
		data = tmp.data;
		size++;

	}
	if (check_num(num) == false) {
		Plenty tmp(size);
		for (size_t i = 0; i < size; i++) {
			tmp.data[i] = data[i];
		}
		tmp.data[tmp.size] = num;
		data = tmp.data;
		size++;
	}
	return *this;
}
template <typename T>
Plenty <T> & Plenty <T>:: operator-=(T num) {
	if (check_num(num) == false)
		throw std::logic_error("Set have not got this num");
	for (size_t i = 0; i < size; i++) {
		if (data[i] == num)
		{
			for (size_t j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			size--;
			break;
		}
	}
	return *this;
}
template <typename T>
Plenty <T> Plenty <T>::intersection(const Plenty& second) {
	Plenty tmp(size);
	tmp.size = 0;
	bool flag = false;
	for (size_t i = 0; i < size; i++) {
		flag = false;
		for (size_t j = 0; j < second.size; j++) {
			if (data[i] == second.data[j])
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			tmp.data[tmp.size] = data[i];
			tmp.size++;
		}
	}
	return tmp;
}
template <typename T>
bool Plenty <T>::check_num(T num) {
	if (!data)
		throw std::logic_error("data == nullptr in check_num");
	for (size_t i = 0; i < size; i++) {
		if (num == data[i])
			return true;
	}
	return false;
}
template <typename T>
bool Plenty <T>:: operator==(const Plenty& second) {
	if (second.size != size)
		return false;
	else
	{
		bool flag = false;
		for (size_t i = 0; i < size; i++)
		{
			flag = false;
			for (size_t j = 0; j < second.size; j++) {
				if (data[i] == second.data[j]) {
					flag = true;
					break;
				}
			}
			if (flag == false)
				return false;
		}
		return true;
	}
}
template <typename T>
bool Plenty <T>:: operator!=(const Plenty& second) {
	if (second.size != size)
		return true;
	else
	{
		bool flag = true;
		for (size_t i = 0; i < size; i++)
		{
			flag = true;
			for (size_t j = 0; j < second.size; j++) {
				if (data[i] == second.data[j]) {
					flag = false;
					break;
				}
			}
			if (flag == true)
				return true;
		}
		return false;
	}
}
template <typename T>
Plenty<T> Plenty<T>:: operator=(const Plenty<T>& a)
{
	size = a.size;
	data = new T[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = a.data[i];
	}
	return *this;
}
/*std::ostream& operator<< (std::ostream& out, const std::pair<int, double>& pair)
{
	out << "(" << pair.first << ", " << pair.second << ')';
	return out;
}
*/


void menu() {
	cout << "1.Add elements" << endl;
	cout << "2.Delete elements" << endl;
	cout << "3.Sum plenty" << endl;
	cout << "4.Div plenty" << endl;
	cout << "5.Element by index" << endl;
	cout << "6.Intersection" << endl;
	cout << "7.Find num in plenty" << endl;
	cout << "8.Ungeneral" << endl;
	cout << "9.Compare" << endl;
	cout << "0.Add in plenty plenty with num" << endl;
}
void menu_1() {
	cout << "1.int" << endl;
	cout << "2.float" << endl;
	cout << "3.std::string" << endl;
	cout << "4.std::pair<int,double>" << endl;

}
void menu_2() {
	cout << "1.plenty" << endl;
	cout << "2.plenty" << endl;
}
void menu_3() {
	cout << "1.p1-p2" << endl;
	cout << "2.p2-p1" << endl;
}
void menu_4() {
	cout << "1.p1 with i" << endl;
	cout << "2.p2 with i" << endl;
}

int main() {
	try {
		while (true) {
			system("cls");
			menu_1();
			size_t flag_1;
			cin >> flag_1;
			switch (flag_1)
			{
			case 1:
			{
				Plenty <int> p1;
				Plenty <int> p2;
				Plenty <int> p3;
				
				while (true)
				{
					system("cls");
					menu();
					size_t flag;
					cin >> flag;
					switch (flag)
					{
					case 1:
					{
						bool fg = true;
						while (fg) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								p1 += i;
								cout << "p1= " << p1 << endl;
								system("pause");
								fg = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								p2 += i;
								cout << "p2= " << p2 << endl;
								system("pause");
								fg = false;
								break;
							}
							}
						} break;
					}
					case 2:
					{
						bool fg2 = true;
						while (fg2) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								p1 -= i;
								cout << "p1= " << p1 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								p2 -= i;
								cout << "p2= " << p2 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							}

						} break;
					}
					case 3:
					{
						cout << "p3= " << p1 + p2 << endl;
						system("pause");
						break;
					}
					case 4:
					{
						bool fg3 = true;
						while (fg3) {
							system("cls");
							menu_3();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								cout << "p3= " << p1 - p2 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							case 2:
							{
								cout << "p3= " << p2 - p1 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							}

						} break;
					}
					case 5:
					{
						bool fg4 = true;
						while (fg4) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p1[i]= " << p1[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p2= " << p2[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							}

						} break;
					}
					case 6:
					{
						cout << "intersection : " << p1.intersection(p2) << endl;
						system("pause");
						break;
					}
					case 7:
					{
						bool fg7 = true;
						while (fg7) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								bool p = p1.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								bool p = p2.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							}

						} break;
					}
					case 8:
					{
						cout << "ungeneral: " << (p1 - p2) + (p2 - p1) << endl;
						system("pause");
						break;
					}
					case 9:
					{
						bool p = p1 != p2;
						cout << "Result : " << p << endl;
						system("pause");
						break;
					}
					case 0:
					{
						bool fg8 = true;
						while (fg8) {
							system("cls");
							menu_4();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								p3 = p1 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								p3 = p2 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							}
						}

					}
					}
				}
			}
			case 2: {
				Plenty <float> p1;
				Plenty <float> p2;
				Plenty <float> p3;

				while (true)
				{
					system("cls");
					menu();
					size_t flag;
					cin >> flag;
					switch (flag)
					{
					case 1:
					{
						bool fg = true;
						while (fg) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								float i;
								cout << "i=";
								cin >> i;
								p1 += i;
								cout << "p1= " << p1 << endl;
								system("pause");
								fg = false;
								break;
							}
							case 2:
							{
								float i;
								cout << "i=";
								cin >> i;
								p2 += i;
								cout << "p2= " << p2 << endl;
								system("pause");
								fg = false;
								break;
							}
							}
						} break;
					}
					case 2:
					{
						bool fg2 = true;
						while (fg2) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								float i;
								cout << "i=";
								cin >> i;
								p1 -= i;
								cout << "p1= " << p1 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							case 2:
							{
								float i;
								cout << "i=";
								cin >> i;
								p2 -= i;
								cout << "p2= " << p2 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							}

						} break;
					}
					case 3:
					{
						cout << "p3= " << p1 + p2 << endl;
						system("pause");
						break;
					}
					case 4:
					{
						bool fg3 = true;
						while (fg3) {
							system("cls");
							menu_3();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								cout << "p3= " << p1 - p2 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							case 2:
							{
								cout << "p3= " << p2 - p1 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							}

						} break;
					}
					case 5:
					{
						bool fg4 = true;
						while (fg4) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p1[i]= " << p1[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p2= " << p2[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							}

						} break;
					}
					case 6:
					{
						cout << "intersection : " << p1.intersection(p2) << endl;
						system("pause");
						break;
					}
					case 7:
					{
						bool fg7 = true;
						while (fg7) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								float i;
								cout << "i=";
								cin >> i;
								bool p = p1.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							case 2:
							{
								float i;
								cout << "i=";
								cin >> i;
								bool p = p2.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							}

						} break;
					}
					case 8:
					{
						cout << "ungeneral: " << (p1 - p2) + (p2 - p1) << endl;
						system("pause");
						break;
					}
					case 9:
					{
						bool p = p1 != p2;
						cout << "Result : " << p << endl;
						system("pause");
						break;
					}
					case 0:
					{
						bool fg8 = true;
						while (fg8) {
							system("cls");
							menu_4();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								float i;
								cout << "i=";
								cin >> i;
								p3 = p1 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							case 2:
							{
								float i;
								cout << "i=";
								cin >> i;
								p3 = p2 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							}
						}

					}
					}
				}
			}
			case 3:
			{
				Plenty <string> p1;
				Plenty <string> p2;
				Plenty <string> p3;

				while (true)
				{
					system("cls");
					menu();
					size_t flag;
					cin >> flag;
					switch (flag)
					{
					case 1:
					{
						bool fg = true;
						while (fg) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								string i;
								cout << "i=";
								cin >> i;
								p1.add(i);
								cout << "p1= " << p1 << endl;
								system("pause");
								fg = false;
								break;
							}
							case 2:
							{
								string i;
								cout << "i=";
								cin >> i;
								p2.add(i);
								cout << "p2= " << p2 << endl;
								system("pause");
								fg = false;
								break;
							}
							}
						} break;
					}
					case 2:
					{
						bool fg2 = true;
						while (fg2) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								string i;
								cout << "i=";
								cin >> i;
								p1 -= i;
								cout << "p1= " << p1 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							case 2:
							{
								string i;
								cout << "i=";
								cin >> i;
								p2 -= i;
								cout << "p2= " << p2 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							}

						} break;
					}
					case 3:
					{
						cout << "p3= " << p1 + p2 << endl;
						system("pause");
						break;
					}
					case 4:
					{
						bool fg3 = true;
						while (fg3) {
							system("cls");
							menu_3();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								cout << "p3= " << p1 - p2 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							case 2:
							{
								cout << "p3= " << p2 - p1 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							}

						} break;
					}
					case 5:
					{
						bool fg4 = true;
						while (fg4) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p1[i]= " << p1[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p2= " << p2[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							}

						} break;
					}
					case 6:
					{
						cout << "intersection : " << p1.intersection(p2) << endl;
						system("pause");
						break;
					}
					case 7:
					{
						bool fg7 = true;
						while (fg7) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								string i;
								cout << "i=";
								cin >> i;
								bool p = p1.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							case 2:
							{
								string i;
								cout << "i=";
								cin >> i;
								bool p = p2.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								system("pause");
								fg7 = false;
								break;
							}
							}

						} break;
					}
					case 8:
					{
						cout << "ungeneral: " << (p1 - p2) + (p2 - p1) << endl;
						system("pause");
						break;
					}
					case 9:
					{
						bool p = p1 != p2;
						cout << "Result : " << p << endl;
						system("pause");
						break;
					}
					case 0:
					{
						bool fg8 = true;
						while (fg8) {
							system("cls");
							menu_4();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								string i;
								cout << "i=";
								cin >> i;
								p3 = p1 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							case 2:
							{
								string i;
								cout << "i=";
								cin >> i;
								p3 = p2 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							}
						}

					}
					}
				}
			}
			case 4:
			{/*
				Plenty <pair<int, double>> p1;
				Plenty <pair<int, double>> p2;
				Plenty <pair<int, double>> p3;

				while (true)
				{
					system("cls");
					menu();
					size_t flag;
					cin >> flag;
					switch (flag)
					{
					case 1:
					{
						bool fg = true;
						while (fg) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								double j;
								cout << "i=";
								cin >> i;
								cout << "j=";
								cin >> j;
								p1 += {i, j};
								cout << "p1= " << p1 << endl;
								system("pause");
								fg = false;
								break;
							}
							case 2:
							{
								int i;
								double j;
								cout << "i=";
								cin >> i;
								cout << "j=";
								cin >> j;
								p2 += {i, j};
								cout << "p2= " << p2 << endl;
								system("pause");
								fg = false;
								break;
							}
							}
						} break;
					}
					case 2:
					{
						bool fg2 = true;
						while (fg2) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								double j;
								cout << "i=";
								cin >> i;
								cout << "j=";
								cin >> j;
								p1 -= {i, j};
								cout << "p1= " << p1 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							case 2:
							{
								int i;
								double j;
								cout << "i=";
								cin >> i;
								cout << "j=";
								cin >> j;
								p2 -= {i, j};
								cout << "p2= " << p2 << endl;
								system("pause");
								fg2 = false;
								break;
							}
							}

						} break;
					}
					case 3:
					{
						cout << "p3= " << p1 + p2 << endl;
						system("pause");
						break;
					}
					case 4:
					{
						bool fg3 = true;
						while (fg3) {
							system("cls");
							menu_3();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								cout << "p3= " << p1 - p2 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							case 2:
							{
								cout << "p3= " << p2 - p1 << endl;
								system("pause");
								fg3 = false;
								break;
							}
							}

						} break;
					}
					case 5:
					{
						bool fg4 = true;
						while (fg4) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p1[i]= " << p1[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								cout << "p2= " << p2[i] << endl;
								system("pause");
								fg4 = false;
								break;
							}
							}

						} break;
					}
					case 6:
					{
						cout << "intersection : " << p1.intersection(p2) << endl;
						system("pause");
						break;
					}
					case 7:
					{
						bool fg7 = true;
						while (fg7) {
							system("cls");
							menu_2();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								bool p = p1.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								
								
								system("pause");
								fg7 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								bool p = p2.check_num(i);
								if (p == true) {
									cout << "plenty has num" << endl;
								}
								else {
									cout << "plenty has not num" << endl;
								}
								
								
								system("pause");
								fg7 = false;
								break;
							}
							}

						} break;
						
					}
					case 8:
					{
						cout << "ungeneral: " << (p1 - p2) + (p2 - p1) << endl;
						system("pause");
						break;
					}
					case 9:
					{
						bool p = p1 != p2;
						cout << "Result : " << p << endl;
						system("pause");
						break;
					}
					case 0:
					{
						bool fg8 = true;
						while (fg8) {
							system("cls");
							menu_4();
							size_t flag_2;
							cin >> flag_2;
							switch (flag_2)
							{
							case 1:
							{
								int i;
								cout << "i=";
								cin >> i;
								p3 = p1 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							case 2:
							{
								int i;
								cout << "i=";
								cin >> i;
								p3 = p2 + i;
								cout << "p3 :" << p3 << endl;
								system("pause");
								fg8 = false;
								break;
							}
							}
						}
					
						

					}
					}
				}
				*/
				
			}
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
