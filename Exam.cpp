//#include<iostream>
//#include<vector>
//#include<string>
//using namespace std;
//struct DATE {
//	int d, m, y = 0;
//	void date() {
//		cout << "Nhap ngay thang nam sinh (cach nhau 1 khoang trong): ";
//		cin >> d >> m >> y;
//	}
//};
//struct NAME {
//	string ho{};
//	string ten{};
//	void name() {
//		cin.ignore();
//		cout << "Nhap ho + ten dem: ";
//		getline(cin, ho);
//
//		cout << "Nhap ten: ";
//		fflush(stdin);
//		cin >> ten;
//	}
//};
//struct DATA {
//	string ID{};
//	NAME name{};
//	string role{};
//	DATE date{};
//	string status{};
//	int baseSalary{};
//	double coefficient{};
//	double salary{};
//	void data() {
//		cout << "Nhap ID: "; cin >> ID;
//		name.name();
//
//		cin.ignore();
//		cout << "Nhap chuc vu: ";
//		getline(cin, role);
//		fflush(stdin);
//
//		date.date();
//
//		cout << "Nhap tinh trang (NGHI/LAM): ";
//		cin >> status;
//
//		cout << "Luong co ban la: ";
//		cin >> baseSalary;
//
//		cout << "He so luong la: ";
//		cin >> coefficient;
//
//		salary = baseSalary * coefficient;
//	}
//};
//struct node {
//	DATA d;
//	node* next = NULL;
//};
//
//struct node_list {
//	node* head = NULL;
//	node* tail = NULL;
//};
//node* init_node(DATA a) {
//	node* p = new node;
//	p->d = a;
//	p->next = NULL;
//	return p;
//};
//node_list* add_new_node(node_list* l, DATA a) {
//	node* temp = init_node(a);
//	node_list* p = l;
//	p->tail->next = temp;
//	p->tail = temp;
//	return p;
//}
//void printInfo(DATA d) {
//	cout << d.ID << " " << d.name.ho << " " << d.name.ten << " " << d.role << " " << d.status << " " << d.date.d << "/" << d.date.m << "/" << d.date.y << endl;
//}
//void printList(node_list* l) {
//	cout << "[ DANH SACH NHAN VIEN ]" << endl;
//	int count = 0;
//	node* p = l->head;
//	while (p != NULL)
//	{
//		count++;
//		printInfo(p->d);
//		p = p->next;
//	}
//	cout << endl;
//	cout << "Danh sach co: " << count << " nhan vien";
//}
//node* searchByID(node_list* l) {
//	cout << endl;
//	node* p = l->head;
//	cout << "Nhap ma nhan vien can tim: ";
//	string mID;
//	cin >> mID;
//
//	while (p!=NULL)
//	{
//		if (p->d.ID == mID)
//		{
//			return p;
//		}
//		else p = p->next;
//	}
//	return NULL;
//}
//void memberWithMaxSalary(node_list* l) {
//	node* p = l->head;
//	double max = 0;
//	while (p!=NULL)
//	{
//		if (p->d.salary > max)
//		{
//			max = p->d.salary;
//		};
//		p = p->next;
//	}
//	p = l->head;
//	while (p != NULL)
//	{
//		if (p->d.salary == max)
//		{
//			printInfo(p->d);
//		};
//		p = p->next;
//	}
//}
//int main() {
//	int size = 0;
//	cout << "Nhap so luong nhan vien can quan ly: ";
//	cin >> size;
//
//	DATA d;
//	d.data();
//	cout << endl;
//
//	node_list* l = new node_list;
//	l->head = init_node(d);
//	l->tail = l->head;
//
//	node_list* p = l;
//	for (int i = 1; i < size; i++)
//	{
//		DATA d;
//		d.data();
//		p = add_new_node(p, d);
//		cout << '\n';
//	}
//	printList(l);
//	node* temp = searchByID(l);
//
//	printInfo(temp->d);
//	return 0;
//}