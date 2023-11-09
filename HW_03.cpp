#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>

using std::setw;
using std::left;
using std::right;
using std::cin;
using std::cout;
using std::string;
using std::to_string;
using std::stringstream;
using std::vector;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;

ofstream fileOutput("Data_OUT.txt", ios::out);
ifstream fileInput("Data_INP.txt", ios::in);

string strName, strDay = "";

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
		ss << tmp[0];
		ss >> day;

		ss.clear();
		ss << tmp[1];
		ss >> month;

		ss.clear();
		ss << tmp[2];
		ss >> year;
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
void WriteToFile(node* l);
void separateStr(string inp, string& id, string& name, string& birthday, float& point);
node_list* ReadFromFile();
int amountStudent(node* l);
void student_with_max_point(node* l);
void printDate(DATE d);
void printName(NAME n);
void printInfo(node* d);
void printList(node_list* l);
#pragma endregion

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

int amountStudent(node* l) {
	node* p = l;
	int count = 0;
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

void sortName(node_list* l) {
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
int main() {
	node_list* l = ReadFromFile();
	sortName(l);
	printList(l);
	return 0;
}