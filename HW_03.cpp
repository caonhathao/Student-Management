#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>

using std::cin;
using std::cout;
using std::setw;
using std::left;
using std::right;
using std::endl;
using std::to_string;
using std::find;
using std::string;
using std::stringstream;
using std::vector;
using std::ios;
using std::ofstream;
using std::ifstream;

ofstream fileOutput("Data_OUT.txt", ios::out);
ifstream fileInput("Data_INP.txt", ios::in);

string strName, strDay = "";
#pragma region checkingFuncs
bool isLeapYear(int y);
bool validDay(int d, int m, int y);
bool validMonth(int m);
bool validYear(int y);
bool isIDEsixt(node_list* l, string mID);
#pragma endregion
struct DATE {
	int day = 0;
	int month = 0;
	int year = 0;
	DATE() {};

	DATE(string date) {
		string tmp[3] = {};
		int k = 0;
		for (int i = 0; i < date.size(); i++)
		{
			if (date[i] >= '0' && date[i] <= '9')
			{
				tmp[k] += date[i];
			}
			else
			{
				k++;
			}
		};
		stringstream ss;
		ss << tmp[2];
		ss >> year;
		while (validYear(year) == false)
		{
			cout << "WRONG FORMAT! PLEASE WRITE AGAIN!";
			cin >> year;
		}

		ss.clear();
		ss << tmp[1];
		ss >> month;
		while (validMonth(month) == false)
		{
			cout << "WRONG FORMAT! PLEASE WRITE AGAIN!";
			cin >> month;
		}

		ss.clear();
		ss << tmp[0];
		ss >> day;
		while (validDay(day, month, year) == false)
		{
			cout << "WRONG FORMAT! PLEASE WRITE AGAIN!";
			cin >> day;
		}
	}
};

struct NAME {
	string lName = "";//ho
	string mName = "";//ten lot
	string fName = "";//ten
	NAME() {};
	NAME(string name) {
		vector<string> tmp;
		string temp = "";

		for (int i = 0; i < name.size(); i++)
		{
			if (name[i] != ' ')
			{
				temp += name[i];
			}
			else
			{
				tmp.push_back(temp);
				temp = "";
			}
		};

		lName = tmp[0];
		for (int i = 1; i <= tmp.size() - 2; i++)
		{
			mName += tmp[i] + ' ';
		};
		fName = tmp[tmp.size() - 1];
	}
};

struct Student {
	string idStu = "";
	NAME nameStu;
	DATE birthday;
	float point{};
	Student() {};
	Student(string id, NAME name, DATE birth, float p) {
		idStu = id;
		nameStu = name;
		birthday = birth;
		point = p;
	}
};

typedef Student St;

struct node {
	St Data;
	node* next = NULL;
};

struct node_list {
	node* head = NULL;
	node* tail = NULL;
};
#pragma region listFuncs
node* init_node(St a);
node_list* add_new_node(node_list* l, St a);
node_list* init_list();
node_list* ReadFromFile();

void WriteToFile(node* l);
int amountStudent(node* l);
void student_with_max_point(node* l);

void sortPoint(node_list* l);
void sortByName(node_list* l);
void sortByID(node_list* l);

void separateStr(string inp, string& id, string& name, string& birthday, float& point);

node* findStuByID(node_list* l, string ID);

void printDate(DATE d);
void printName(NAME n);
void printInfo(node* d);
void printList(node_list* l);
#pragma endregion

#pragma region checkingEvent
bool isLeapYear(int y) {
	if (y % 100 == 0)
	{
		if (y % 400 == 0)
		{
			return true;
		}
		else return false;
	}
	else if (y % 4 == 0)
	{
		return true;
	}
	else return false;
}
bool validYear(int m) {
	if (m < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
};
bool validMonth(int m) {
	if (m < 0 || m>12)
	{
		return false;
	}
	else return true;
};
bool validDay(int d, int m, int y) {
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d < 0 || d>31)
		{
			return false;
		}
		else return true;
	}
	else if (m == 2)
	{
		if (isLeapYear(y)) {
			if (d < 0 || d>29)
			{
				return false;
			}
			else return true;
		}
		else if (d < 0 || d>28)
		{
			return false;
		}
		else return true;

	}
	else if (d < 0 || d>30)
	{
		return false;
	}return true;
}
bool isIDEsixt(node_list* l, string mID) {
	node* p = l->head;
	while (p != NULL) {
		if (p->Data.idStu == mID)
		{
			return true;
		}
	};
	return false;
}
#pragma endregion

#pragma region buildSLL
node* init_node(St a) {
	node* p = new node;
	p->Data = a;
	p->next = NULL;
	return p;
}

node_list* add_new_node(node_list* l, St a) {
	node* temp = init_node(a);
	node_list* p = l;
	p->tail->next = temp;
	p->tail = temp;
	return p;
}

node_list* init_list() {
	int size = 0;
	cin >> size;

	string id, name = "";
	string birthday = "";
	float point = 0.0;

	cin >> id >> name >> birthday >> point;
	St a = St(id, NAME(name), DATE(birthday), point);
	node_list* l = new node_list;
	l->head = init_node(a);
	l->tail = l->head;

	node_list* p = l;
	for (int i = 1; i < size; i++)
	{
		cin >> id >> name >> birthday >> point;
		a = St(id, NAME(name), DATE(birthday), point);
		p = add_new_node(p, a);
	}
	return l;
}

void WriteToFile(node* l) {
	node* p = l;
	while (p != NULL)
	{
		fileOutput << p->Data.idStu << " ";
		printName(p->Data.nameStu);
		fileOutput << strName << " ";
		printDate(p->Data.birthday);
		fileOutput << strDay << " " << p->Data.point << endl;
		p = p->next;
	}
	fileOutput.close();
}

void separateStr(string inp, string& id, string& name, string& birthday, float& point) {
	vector<string>temp = {};
	string tmp = "";
	for (int i = 0; i < inp.size(); i++)
	{
		if (inp[i] != ' ')
		{
			tmp += inp[i];
		}
		else
		{
			temp.push_back(tmp);
			tmp = "";
		}
	};
	temp.push_back(tmp);

	id = temp[0];
	name = "";
	for (int i = 1; i <= temp.size() - 3; i++)
	{
		name += temp[i] + " ";
	};
	birthday = temp[temp.size() - 2];

	stringstream ss;
	ss << temp[temp.size() - 1];
	ss >> point;
}

node_list* ReadFromFile() {
	string id, name;
	string birthday = "";
	float point;

	string t = "";
	getline(fileInput, t);
	separateStr(t, id, name, birthday, point);

	St a = St(id, NAME(name), DATE(birthday), point);
	node_list* l = new node_list;
	l->head = init_node(a);
	l->tail = l->head;

	node_list* p = l;

	while (!fileInput.eof()) {
		getline(fileInput, t);
		separateStr(t, id, name, birthday, point);
		a = St(id, NAME(name), DATE(birthday), point);
		p = add_new_node(p, a);
	};
	fileInput.close();
	return l;
}
#pragma endregion

#pragma region features
int amountStudent(node* l) {
	node* p = l;
	int count(0);
	while (p != NULL) {
		count += 1;
	};
	return count;
}

void student_with_max_point(node* l) {
	node* p = l;
	int max = 0;
	while (p != NULL)
	{
		if (p->Data.point > max)
		{
			max = p->Data.point;
		}
		p = p->next;
	};

	p = l;
	while (p != NULL)
	{
		if (p->Data.point == max)
		{
			fileOutput << p->Data.idStu << " ";
			printName(p->Data.nameStu);
			fileOutput << strName << " ";
			printDate(p->Data.birthday);
			fileOutput << strDay << " " << p->Data.point << endl;
		};
		p = p->next;
	}
	fileOutput.close();
};

node* findStuByID(node_list* l, string ID) {
	node* p = l->head;
	while (p != NULL)
	{
		if (p->Data.idStu == ID)
		{
			return p;
		}
	};
	return NULL;
}
#pragma endregion

#pragma region sort
void sortPoint(node_list* l) {
	node* temp = l->head;

	while (temp != NULL)
	{
		node* tmp = temp->next;
		while (tmp != NULL)
		{
			if (temp->Data.point > tmp->Data.point)
			{
				St p = temp->Data;
				temp->Data = tmp->Data;
				tmp->Data = p;
			}
			tmp = tmp->next;
		};
		temp = temp->next;
	};

	temp = l->head;
	while (temp != NULL)
	{
		fileOutput << temp->Data.idStu << " ";
		printName(temp->Data.nameStu);
		fileOutput << strName << " ";
		printDate(temp->Data.birthday);
		fileOutput << strDay << " " << temp->Data.point << endl;

		temp = temp->next;
	}
}

void sortByName(node_list* l) {
	node* p = l->head;

	while (p != NULL)
	{
		node* temp = p->next;
		while (temp != NULL)
		{
			if (p->Data.nameStu.fName > temp->Data.nameStu.fName)
			{
				St s = p->Data;
				p->Data = temp->Data;
				temp->Data = s;
			};
			temp = temp->next;
		};
		p = p->next;
	}
}

void sortByID(node_list* l) {
	node* p = l->head;
	node* nStep = l->head->next;
	while (p != NULL)
	{
		while (nStep != NULL)
		{
			if (p->Data.idStu > nStep->Data.idStu)
			{
				St temp = p->Data;
				p->Data = nStep->Data;
				nStep->Data = temp;
			};
			nStep = nStep->next;
		}
		p = p->next;
	}
}
#pragma endregion

#pragma region print
void printDate(DATE d) {
	cout << setw(3) << right << d.day;
	cout << setw(3) << right << d.month;
	cout << setw(5) << right << d.year;
	strDay = to_string(d.day) + " " + to_string(d.month) + " " + to_string(d.year);
}

void printName(NAME n) {
	cout << setw(8) << left << n.lName;
	cout << setw(16) << left << n.mName;
	cout << setw(8) << left << n.fName;
	strName = n.lName + " " + n.mName + " " + n.fName;
}

void printInfo(node* d) {

	cout << setw(15) << left << d->Data.idStu;
	printName(d->Data.nameStu);
	printDate(d->Data.birthday);
	cout << setw(4) << right << d->Data.point << endl;
}

void printList(node_list* l) {
	node* p = l->head;
	while (p != NULL)
	{
		printInfo(p);
		p = p->next;
	};
}
#pragma endregion
int main() {
	node_list* l = ReadFromFile();
	sortByName(l);
	printList(l);
	return 0;
}