#ifndef _struct
#define _struct
#include <fstream>
using namespace std;

//���������� �����
class film {
public:
	static film* In(ifstream &ifst);
	virtual void InData(ifstream &ifst) = 0;//���� ������ � ������
	virtual void Out(ofstream &ofst) = 0;//����� ������ � ������
	//�����������
	virtual void MultiMethod(film* other,ofstream& ofst) = 0;
	virtual void MGame(ofstream& ofst) = 0;
	virtual void MCartoon(ofstream& ofst) = 0;
};
//���������
class container
{
private:
	class List {
	public:
		List();//������������� ������
		void Del();//������� �������� ������ �� ������
		List* Next;//��������� �� ��������� ������
		List* Priv;//��������� �� ���������� ������
		film* data;//��������� �� ������ � ������
	};
public:
	int add(ifstream &ifst);//������� ���������� ������ ������ � ���������
	void In(ifstream &ifst);//���� ������ � ���������
	void Out(ofstream &ofst);//����� ������ �� ����������
	void Clear();//�������� ������ �� ���������
	container();//������������� ����������
	List* Top;//��������� �� ��������� ������ � ����������
	int count;//����� ������� � ����������
	void MultiMethod( ofstream& ofst);
};

//������� �����
class game : public film {
	char country[100];//������
	char name[100];//�������� ������
	char director[100];//��� ��������
public:
	void InData(ifstream &ifst);//���� ������ � ������
	void Out(ofstream &ofst);//����� ������ � ������
	//�����������
	void MultiMethod(film* other, ofstream& ofst);
	void MGame(ofstream& ofst);
	void MCartoon(ofstream& ofst);
	game() {}//�������� ��� �������������.
};
//����������
class cartoon : public film {
	char country[100];//������
	char name[100];//�������� ������
	int type;//��� �����������
public:
	void InData(ifstream &ifst);//���� ������ � ������
	void Out(ofstream &ofst);//����� ������ � ������
	//�����������
	void MultiMethod(film* other, ofstream& ofst);
	void MGame(ofstream& ofst);
	void MCartoon(ofstream& ofst);
	cartoon() {}//�������� ��� �������������.
};
#endif 