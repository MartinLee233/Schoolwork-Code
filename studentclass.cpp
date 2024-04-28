/**/
using namespace std;
#include<iostream>
#include<cstring>
#include<iomanip>

#define SMAX 10 // The maxium number of the students one grade object could hold.



template<class T>
void imBubble(T arr[],int total,bool inverse = false)//default small to big.Inversewise,big to small.
{
	int i = 0;
	int j = 0;
	int t = 0;
	T temp;
	if(inverse)
	{
		while(i<total-1)
		{
			j = 0;
			t = 0;
			while(j<total-1)
			{
				if(arr[j]<arr[j+1])
				{
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
					t++;
				}
				j++;
			}
			if(t == 0)
				break;
			i++;
		}
	}
	else
	{
		while(i<total-1)
                {
                        j = 0;
                        t = 0;
                        while(j<total-1)
                        {
                                if(arr[j]>arr[j+1])
                                {
                                        temp = arr[j];
                                        arr[j] = arr[j+1];
                                        arr[j+1] = temp;
                                        t++;
                                }
                                j++;
                        }
                        if(t == 0)
                                break;
                        i++;
                }
	}
}

class Base{
	private:
		string base_name;//I don't know whether I should have this according to the example code.
				 //Supposing it's for distinguish each Base object from each other.
				 //also done this in the menu definition for the same reason. 
	public:
		Base(char *p):base_name(p){};
		Base(string s = "\0"):base_name(s){};
		string Getname() {return base_name;} ;
		virtual void selectionlist(){};//print selection list
		virtual bool selection(int num){ return false;};//used to decide which fuction do you need.
};

class student{
	private:
		string ID;
		string cla;
		string name;
		float score1;
		float score2;
		float score3;
		float total;
	public:
		//constructor
		student();
		student(string id, string clas, string na, float s1 = 0, float s2 = 0, float s3 = 0):ID(id),cla(clas),name(na),score1(s1),score2(s2),score3(s3),total(s1+s2+s3){};
		student(char *id, char *clas, char * na, float s1 = 0, float s2 = 0, float s3 = 0):ID(id),cla(clas),name(na),score1(s1),score2(s2),score3(s3),total(s1+s2+s3){};
		//get certain data
		string GetID() { return ID; };
		string Getclass() { return cla; };
		string Getname() { return name; };
		float Getscore1() { return score1; };
	       	float Getscore2() { return score2; };
		float Getscore3() { return score3; };
		//edit a student object
		void edit(char *id, char *clas, char * na, float s1 = 0, float s2 = 0, float s3 = 0);
		void edit(string id, string clas, string na, float s1 = 0, float s2 = 0, float s3 = 0);	
		//operator overloading
		friend ostream & operator<<(ostream & os,const student &stu);
		friend bool operator<(const student & s1, const student & s2);
		friend bool operator>(const student & s1, const student & s2){ return (s2<s1); };
};

void student::edit(string id, string clas, string na, float s1, float s2, float s3)
{
	ID=id; cla=clas; name=na; score1=s1; score2=s2; score3=s3; total = s1 + s2 + s3;
}

void student::edit(char *id, char *clas, char * na, float s1, float s2, float s3)
{
	ID=id; cla=clas; name=na; score1=s1; score2=s2; score3=s3; total = s1 + s2 + s3;
}

student::student()
{
	ID = cla = name = "\0";score1 = score2 = score3 = total = 0;
}

ostream & operator<<(ostream & os, const student & stu)
{
	os << stu.ID << ',' << stu.cla << ',' << stu.name << ',' << stu.score1 << ',' << stu.score2 << ',' << stu.score3 << ',' << stu.total << '\n';
	return os;
}

bool operator<(const student & s1, const student & s2)
{
	if(s1.cla<s2.cla)
		return true;
	if(s1.cla==s2.cla&&s1.total>s2.total)
		return true;
	return false;
}

class Grade:public Base{
	private:
		student s[SMAX];
		int stutotal;
	public:
		//constructor
		Grade(string s = "\0"):Base::Base(s),stutotal(0) {};
		Grade(char *p):Base::Base(p),stutotal(0) {};
		virtual void selectionlist();
		virtual bool selection(int num);
		//function
		void Input();
		void Delete();
		void Select();
		void Order();
		void Output();
};

void Grade::Input()
{
	int i = 0;
	while(i<SMAX&&s[i].GetID()!="\0")
	{
		i++;
	}
	string idd,cl,nam;
	float sc1,sc2,sc3;
	string input;
	while(1)
	{
		if(i>SMAX-1)
		{
			cout << "grade already full\n";//avoid over input
			break;
		}
		cout << "Id "; cin >> idd;
		cout << "class "; cin >> cl;
		cout << "name "; cin >> nam;
		cout << "score1 "; cin >> sc1;
		cout << "score2 "; cin >> sc2;
		cout << "score3 "; cin >> sc3;
		s[i].edit(idd,cl,nam,sc1,sc2,sc3);
		stutotal++;
		i++;
	BACK1://I know it's not good to use goto but it really works well.
		cout << "continue?\n";
		cin >> input;
		if(input=="yes")
			continue;
		else if(input=="no")
			break;
		else
		{
			cout << "Wrong Input.(Please input 'yes' or 'no')\n";//avoid wrong input
			goto BACK1;
		}
	}
}

void Grade::Delete()
{
	string input;
	int i = 0;
	int trigger = 0;
	student temp;
	while(1){
		cin >> input;
		trigger = 0;
		i = 0;
	if(isdigit(input[0]))
	{
		while(i<stutotal)
		{
			if(input==s[i].GetID())
			{
				if(stutotal==1)
				{
					cout << "Need at least 1 student remained.\n";//avoid over delete
					break;
				}
				s[i] = temp;
				stutotal--;
				trigger++;
				break;
			}
			i++;
		}
	}
	else
	{
		while(i<stutotal)
                {
                        if(input==s[i].Getname())
                        {
                                if(stutotal==1)
				{
					cout << "Need at least 1 student remained.\n";
					break;
				}
				s[i] = temp;
                                stutotal--;
                                trigger++;
                                break;
                        }
                        i++;
                }
        }
	if(trigger==1)
	{
		while(i<stutotal)
		{
			s[i] = s[i+1];
			i++;
		}
	}
	Output();
	BACK2:
                cout << "continue?\n";
                cin >> input;
                if(input=="yes")
                        continue;
                else if(input=="no")
                        break;
                else
                {
                        cout << "Wrong Input.(Please input 'yes' or 'no')\n";
                        goto BACK2;
                }
        }
}

void Grade::Select()
{
	cout.setf(ios_base::showpoint);
	cout << fixed;
	cout.precision(1);
	string input;
	int i = 0;
	int trigger = 0;
	while(1)
	{
		i = 0;
		trigger = 0;
		cin >> input;
		if(input.length()==s[i].GetID().length())
		{
			while(i<stutotal)
			{
				if(input==s[i].GetID())
				{
					cout << s[i];
					trigger++;
				}
				i++;
			}
		}
		else if(input.length()==s[i].Getclass().length())
		{
			while(i<stutotal)
                        {
                                if(input==s[i].Getclass())
                                {
                                        cout << s[i];
                                        trigger++;
                                }
                                i++;
                        }
                }
		if(trigger==0)
		{
			cout << "there is no eligible student\n";
			break;
		}
		BACK3:
                cout << "continue?\n";
                cin >> input;
                if(input=="yes")
                        continue;
                else if(input=="no")
                        break;
                else
                {
                        cout << "Wrong Input.(Please input 'yes' or 'no')\n";
                        goto BACK3;
                }
        }
}

void Grade::Order()
{
	imBubble(s,stutotal);
	Output();
}

void Grade::Output()
{
	int i = 0;
	cout.setf(ios_base::showpoint);
    	cout << fixed;
    	cout.precision(1);
	while(i<stutotal)
	{
		cout << s[i];
		i++;
	}
}

void Grade::selectionlist()
{
	cout << "1.input\n";
        cout << "2.delete\n";
        cout << "3.select\n";
        cout << "4.order\n";
        cout << "5.output\n";
        cout << "6.quit\n";
        cout << "please input your option\n";
}

bool Grade::selection(int num)
{
	switch(num)
	{
		case 1:
			Input();
			return true;
		case 2:
			Delete();
			return true;
		case 3:
			Select();
			return true;
		case 4:
			Order();
			return true;
		case 5:
			Output();
			return true;
		case 6:
			return false;
		default:
			cout << "Wrong input.\nPlease input the number of the option you wanted to choose.\n";//avoid wrong input
			return true;
	}
}



class Menu{
	private:
		string menu_name;
	public:
		Menu(char *p):menu_name(p) {} ;
		Menu(string s = "\0"):menu_name(s) {} ;
		string Getname() { return menu_name; };
		void run(Base *ba);
};

void Menu::run(Base *ba)
{
	ba->selectionlist();
	char in;
	cin >> in;
	int input = (int)in - 48;//avoid strange (non-number) input.
	while(ba->selection(input))
	{	
		ba->selectionlist();
		cin >> in;
		input = (int)in - 48;
	}
};

int main()
{
	Grade G1;
	Menu M1;
	Base *b = &G1;
	M1.run(b);
}
