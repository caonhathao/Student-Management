#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<algorithm>

using namespace std;

ofstream fileOutput("Data_OUT.txt", ios::out);
ifstream fileInput("Data_INP.txt", ios::in);

string strName, strDay = "";

#pragma region checkDate
bool isLeapYear(string y);
bool validDay(string d, string m, string y);
bool validMonth(string m);
bool validYear(string y);
#pragma endregion

struct DATE {
	string day = "";
	string month = "";
	string year = "";
	string fullType = "";
	DATE() {};

	DATE(string date) {
		string tmp[3] = {};
		int k = 0;
		for (size_t i = 0; i < date.size(); i++)
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
			cout << "WRONG YEAR'S FORMAT! PLEASE WRITE AGAIN!";
			cin >> year;
		};

		ss.clear();
		ss << tmp[1];
		ss >> month;
		while (validMonth(month) == false)
		{
			cout << "WRONG MONTH'S FORMAT! PLEASE WRITE AGAIN!";
			cin >> month;
		};
		if (month.size() < 2)
		{
			month = "0" + month;
		}

		ss.clear();
		ss << tmp[0];
		ss >> day;
		while (validDay(day, month, year) == false)
		{
			cout << "WRONG DAY'S FORMAT! PLEASE WRITE AGAIN!";
			cin >> day;
		};
		if (day.size() < 2)
		{
			day = "0" + day;
		}

		fullType = day + "/" + month + "/" + year;
	}
};

struct NAME {
	string lName = "";//ho
	string mName = "";//ten lot
	string fName = "";//ten
	string fullName = "";
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
		fullName = lName + " " + mName + " " + fName;
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

#pragma region checkingEvent
bool isLeapYear(string y) {
	int year = stoi(y);
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			return true;
		}
		else return false;
	}
	else if (year % 4 == 0)
	{
		return true;
	}
	else return false;
}
bool validYear(string y) {
	int year = stoi(y);
	if (year < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
};
bool validMonth(string m) {
	int month = stoi(m);
	if (month < 0 || month > 12)
	{
		return false;
	}
	else return true;
};
bool validDay(string d, string m, string y) {
	int day = stoi(d);
	int month = stoi(m);
	int year = stoi(y);
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day < 0 || day > 31)
		{
			return false;
		}
		else return true;
	}
	else if (month == 2)
	{
		if (isLeapYear(y)) {
			if (day < 0 || day > 29)
			{
				return false;
			}
			else return true;
		}
		else if (day < 0 || day > 28)
		{
			return false;
		}
		else return true;

	}
	else if (day < 0 || day > 30)
	{
		return false;
	};
	return true;
};
bool isIDEsixt(node_list* l, string mID) {
	node* p = l->head;
	while (p != NULL) {
		if (p->Data.idStu == mID)
		{
			return true;
		}
		p = p->next;
	};
	return false;
}
#pragma endregion

#pragma region checkingFuncs
bool isIDEsixt(node_list* l, string mID);
#pragma endregion

#pragma region listFuncs
node* init_node(St a);
node_list* add_new_node(node_list* l, St a);
node_list* init_list();
node_list* ReadFromFile();

void WriteToFile(node_list* l);
int amountStudent(node* l);
void student_with_max_point(node* l);

void sortPoint(node_list* l);
void sortByName(node_list* l);
void sortByID(node_list* l);

void swap(node* a, node* b);
void selectionSort(node_list* l, string o);

void separateStr(string inp, string& id, string& name, string& birthday, float& point);
bool compare(St a, St b);

node* findStuByID(node_list* l, string ID);
vector<node*> findStuByName(node_list* l, string name);

void removeStuByID(node_list* l, string ID);
void removeStuByName(node_list* l, string ID);

void addNewStudent(node_list* l);
void editInfoStudent(node_list* l);
void destroy(node_list* l);

void printDate(DATE d);
void printName(NAME n);
void printInfo(node* d);
void printList(node_list* l);
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

	string t = "";
	getline(cin, t);
	separateStr(t, id, name, birthday, point);

	St a = St(id, NAME(name), DATE(birthday), point);
	node_list* l = new node_list;
	l->head = init_node(a);
	l->tail = l->head;

	node_list* p = l;
	for (int i = 1; i < size; i++)
	{
		cin >> id >> name >> birthday >> point;
		while (isIDEsixt(l, id))
		{
			cout << "This ID is exist, please enter again" << endl;
			cin >> id;
		}
		a = St(id, NAME(name), DATE(birthday), point);
		p = add_new_node(p, a);
	}
	return l;
}

void WriteToFile(node_list* l) {
	node* p = l->head;
	while (p != NULL)
	{
		fileOutput << p->Data.idStu << " ";

		strName = p->Data.nameStu.fullName;
		fileOutput << strName << " ";

		strDay = p->Data.birthday.fullType;
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

bool compare(St a, St b) {
	for (int i = 0; i < (a.idStu.size() > b.idStu.size() ? a.idStu.size() : b.idStu.size()); i++)
	{
		if (a.idStu[i] != b.idStu[i])
		{
			if (a.idStu[i] > b.idStu[i])
			{
				return true;
			}
			else return false;
		}
	};
	return false;
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
	float max = 0;
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

vector<node*> findStuByName(node_list* l, string name) {
	vector<node*>list = {};
	string temp, correct_name = "";
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] != ' ')
		{
			temp += toupper(name[i]);
		}
		else
		{
			correct_name += temp + " ";
			temp = "";
		}
	};

	node* p = l->head;
	while (p != NULL)
	{
		size_t index = p->Data.nameStu.fullName.find(correct_name);
		if (index != string::npos)
		{
			node* temp = p;
			list.push_back(temp);
		}
		p = p->next;
	}
	return list;
}

void removeStuByID(node_list* l, string ID) {
	node* preNode = nullptr;
	node* currNode = l->head;
	while (currNode != NULL)
	{
		if (currNode->Data.idStu == ID)
		{
			if (preNode == nullptr) //first element
			{
				preNode = currNode->next;
				l->head = preNode;
				currNode->next = NULL;
				delete currNode;
				break;
			}
			else if (currNode->next == nullptr) // at the end of list
			{
				l->tail = preNode;
				preNode->next = nullptr;
				delete currNode;
				break;
			}
			else
			{
				preNode->next = currNode->next;
				currNode->next = nullptr;
				delete currNode;
				break;
			}
		};
		preNode = currNode;
		currNode = currNode->next;
	}
}

void removeStuByName(node_list* l, string name) {
	string temp, correct_name = "";
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] != ' ')
		{
			temp += toupper(name[i]);
		}
		else
		{
			correct_name += temp + " ";
			temp = "";
		}
	};

	node* currNode = l->head;
	node* preNode = nullptr;
	while (currNode != NULL)
	{
		size_t index = currNode->Data.nameStu.fullName.find(correct_name);
		if (index != string::npos)
		{
			if (preNode == nullptr)
			{
				preNode = currNode->next;
				l->head = preNode;
				currNode->next = nullptr;
				delete currNode;
				break;
			}
			else if (currNode->next = nullptr)
			{
				l->tail = preNode;
				preNode->next = nullptr;
				delete currNode;
				break;
			}
			else
			{
				preNode->next = currNode->next;
				currNode->next = nullptr;
				delete currNode;
				break;
			}
		}
	}
}

void addNewStudent(node_list* l) {
	string id, name = "";
	string birthday = "";
	float point = 0.0;

	string t = "";
	getline(cin, t);
	separateStr(t, id, name, birthday, point);

	while (isIDEsixt(l, id))
	{
		cout << "This ID is exist, please enter again" << endl;
		cin >> id;
	}
	St a = St(id, NAME(name), DATE(birthday), point);

	node* p = l->head;
	node* preNode = nullptr;

	while (p != nullptr) {
		if (compare(a, p->Data) == false)
		{
			if (preNode == nullptr)//pointer at head
			{
				node* temp = init_node(a);
				temp->next = p;
				l->head = temp;
				break;
			}
			else if (preNode->next == nullptr)//pointer at tail
			{
				node* temp = init_node(a);
				p->next = temp;
				l->tail = temp;
				break;
			}
			else {//pointer at any where axcept head and tail
				node* temp = init_node(a);
				temp->next = p;
				preNode->next = temp;
				break;
			}
		}
		preNode = p;
		p = p->next;
	}
}

void editInfoStudent(node_list* l) {
	system("cls");
	string sID = "";
	cout << "Enter Student's ID: ";
	cin >> sID;

	node* p = l->head;
	while (p != nullptr)
	{
		if (p->Data.idStu == sID)
		{
			break;
		}
	};

	if (p == nullptr)
	{
		cout << "WRONG ACCESS: ID DOES NOT EXIST!";
		return;
	}
	else {
		cout << "Enter new info ( If it has no change, just enter '0'):" << '\n';

		string birthday, point = "";
		cout << "Birthday: ";
		cin >> birthday;
		cout << "Point: ";
		cin >> point;

		if (birthday != "0")
		{
			p->Data.birthday = DATE(birthday);
		};
		if (point != "0")
		{
			p->Data.point = stof(point);
		}
	};
}

void destroy(node_list* l) {
	node* p = nullptr;
	while (l->head != nullptr)
	{
		p = l->head->next;
		delete l->head;
		l->head = p;
	};
	delete l;
}
#pragma endregion

#pragma region features:selectionSort
void swap(node* a, node* b) {
	St temp = a->Data;
	a->Data = b->Data;
	b->Data = temp;
};
void selectionSort(node_list* l, string o) {
	node* i = l->head;
	node* j = i->next;
	node* min = nullptr;
	while (i != nullptr)
	{
		min = i;
		j = i->next;
		while (j != nullptr)
		{
			if (o == "point")
			{
				if (min->Data.point > j->Data.point)
				{
					min = j;
				}
			}
			else if (o == "name")
			{
				if (min->Data.nameStu.fName > j->Data.nameStu.fName)
				{
					min = j;
				}
			}
			else if (o == "id")
			{
				if (compare(min->Data, j->Data))//increase
				{
					min = j;
				}
			}
			j = j->next;
		};
		if (min != i)
		{
			swap(min, i);
		};
		i = i->next;
	};
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
	node* nStep = nullptr;
	while (p != nullptr)
	{
		nStep = p->next;
		while (nStep != nullptr)
		{
			if (compare(p->Data, nStep->Data)) {
				St temp = p->Data;
				p->Data = nStep->Data;
				nStep->Data = temp;
			}
			nStep = nStep->next;
		}
		p = p->next;
	}
}
#pragma endregion

#pragma region print
void printDate(DATE d) {
	cout << setw(10) << right << d.day << '/' << d.month << '/' << d.year;
}

void printName(NAME n) {
	cout << setw(8) << left << n.lName;
	cout << setw(16) << left << n.mName;
	cout << setw(8) << left << n.fName;
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

//DH334112015 TRAN VAN ON 15/9/2002 8.0
//CD002131001 NGUYEN DUY KHOI 12/12/2003 8.3
//CD004001001 TRAN NGUYEN TRUNG KIEN 23/11/2004 8.5
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	node_list* l = ReadFromFile();
	
	selectionSort(l, "id");
	printList(l);
	return 0;
}