#include <iostream>
#include <vector>
#include <string>
#include <set>
#include<map>


using namespace std;

/****Course �γ���****/
class Course {

public:
	string cour_num;
	string cour_name;
	int cour_credit;
	int cour_score;


	//���캯��
	Course(string cour_num,
		string cour_name,
		int cour_credit,
		int cour_score);

	//��Ա����
	void set_cour_num(string cour_num);
	void set_cour_name(string cour_name);
	void set_cour_credit(int cour_credit);
	void set_cour_score(int cour_score);
	void write_cour_score(int cour_score);

	//get ��Ա����
	string get_cour_num();
	string get_cour_name();
	int get_cour_credit();
	int get_cour_score();
	int write_cour_score();
};

Course::Course(string cour_num, string cour_name, int cour_credit, int cour_score) {
	this->cour_num = cour_num;
	this->cour_name = cour_name;
	this->cour_credit = cour_credit;
	this->cour_score = cour_score;
}

void Course::set_cour_num(string cour_num) {
	this->cour_num = cour_num;
}
void Course::set_cour_name(string cour_name) {
	this->cour_name = cour_name;
}
void Course::set_cour_credit(int cour_credit) {
	this->cour_credit = cour_credit;
}
void Course::set_cour_score(int cour_score) {
	this->cour_score = cour_score;
}
void Course::write_cour_score(int cour_score) {
	this->cour_score = cour_score;
}

string Course::get_cour_num() {
	return this->cour_num;
}
string Course::get_cour_name() {
	return this->cour_name;
}
int Course::get_cour_credit() {
	return this->cour_credit;
}
int Course::get_cour_score() {
	return this->cour_score;
}
int Course::write_cour_score() {
	return this->cour_score;
}
/****Student ѧ����****/
class Student {
public:
	string stu_num;
	string stu_name;
	int stu_sex;
	int stu_age;
	vector<Course> stu_courses;


	// ���캯��
	Student(string stu_num, string stu_name, int stu_age, int stu_sex, vector<Course> stu_courses);
	Student();
	// set ��Ա����
	void set_stu_num(string stu_num);
	void set_stu_name(string stu_name);
	void set_stu_sex(int stu_sex);
	void set_stu_age(int stu_age);
	void add_stu_courses(Course course);

	// get ��Ա����
	string get_stu_num();
	string get_stu_name();
	int get_stu_sex();
	int get_stu_age();
	vector<Course> get_stu_courses();

	// ������Ա����
	//bool delete_stu_courses(string cour_num);
};
Student::Student()
{}
Student::Student(string stu_num, string stu_name, int stu_age, int stu_sex, vector<Course> stu_courses) {
	this->stu_num = stu_num;
	this->stu_name = stu_name;
	this->stu_age = stu_age;
	this->stu_sex = stu_sex;
	this->stu_courses = stu_courses;
}

void Student::set_stu_num(string stu_num) {
	this->stu_num = stu_num;
}
void Student::set_stu_name(string stu_name) {
	this->stu_name = stu_name;
}
void Student::set_stu_sex(int stu_sex) {
	this->stu_sex = stu_sex;
}
void Student::set_stu_age(int stu_age) {
	this->stu_age = stu_age;
}
void Student::add_stu_courses(Course course) {
	this->stu_courses.push_back(course);
}

string Student::get_stu_num() {
	return this->stu_num;
}
string Student::get_stu_name() {
	return this->stu_name;
}
int Student::get_stu_sex() {
	return this->stu_sex;
}
int Student::get_stu_age() {
	return this->stu_age;
}
vector<Course> Student::get_stu_courses() {
	return this->stu_courses;
}
static vector<Student> all_students;
static set<string> all_stu_num;
static map<string, Student> map_all_students;
/********************** �����ܺ��� ******************************/
// ���ѧ������
bool add_student(Student student) {
	bool is_in = all_stu_num.find(student.get_stu_num()) != all_stu_num.end();
	if (is_in) {
		return false;
	}
	all_stu_num.insert(student.get_stu_num());
	all_students.push_back(student);
	map_all_students.insert(make_pair(student.get_stu_num(), student));
	return true;
}

// ��ӡѧ������
void print_all_student() {
	cout << endl;
	cout << "**********************" << "ѧ������" << "**********************" << endl;
	cout << "ѧ��" << "\t" << "\t" << "����" << "\t" << "\t" << "����" << "\t" << "\t" << "�Ա�" << endl;
	for (int i = 0; i < all_students.size(); i++) {
		string sex;
		if (all_students[i].get_stu_sex() == 1) {
			sex = "��";
		}
		else {
			sex = "Ů";
		}
		cout << all_students[i].get_stu_num() << "\t" << all_students[i].get_stu_name() << "\t" << "\t" << all_students[i].get_stu_age() << "\t" << "\t" << sex << endl;
	}
	cout << endl;
}
// ɾ��ѧ����Ϣ
bool del_student(string stu_num) {
	bool is_in = all_stu_num.find(stu_num) != all_stu_num.end();
	if (!is_in) {
		return false;
	}
	map<string, Student>::iterator it;
	it = map_all_students.find(stu_num);
	string temp = it->first;
	int index = 0;
	for (int i = 0; i < all_students.size(); i++) {
		if (temp == all_students[i].get_stu_num()) {
			index = i;
			break;
		}
	}
	map_all_students.erase(it);
	all_students.erase(all_students.begin() + index);
	all_stu_num.erase(stu_num);
	return true;
}
// �޸�ѧ���ɼ�
bool write_cour_score(string stu_num) {
	bool is_in = all_stu_num.find(stu_num) != all_stu_num.end();
	if (!is_in) {
		return false;
	}


}
// ����ѧ����Ϣ
Student search_student(string stu_num) {
	return map_all_students.find(stu_num)->second;
}

void print_student_course(Student student) {
	cout << endl;
	cout << "**********************" << "�γ���Ϣ" << "**********************" << endl;
	cout << "ѧ������:" << "\t" << student.get_stu_name() << endl << endl;
	cout << "���" << "\t" << "\t" << "����" << "\t" << "\t" << "ѧ��" << "\t" << "\t" << "�ɼ�" << endl;
	vector<Course> courses = student.get_stu_courses();
	for (Course course : courses) {
		cout << course.get_cour_num() << "\t" << "\t" << course.get_cour_name() << "\t" << "\t" << course.get_cour_credit() << "\t" << "\t" << course.get_cour_score() << endl;

	}
	cout << endl;
}

void print_info() {
	cout << "����������ѡ���Ӧ�Ĺ���:" << endl;
	cout << "1. ��ӡѧ������" << endl;
	cout << "2. ���ѧ����Ϣ" << endl;
	cout << "3. ɾ��ѧ����Ϣ" << endl;
	cout << "4. ��ӡѧ���γ�" << endl;
	cout << "5. �޸�ѧ���ɼ�" << endl;
	cout << "6. �˳�" << endl;

}
/********************** main ���� ******************************/
int main(int argc, const char * argv[]) {
	vector<Course> course1;
	course1.push_back(Course("1001", "ͨ��ԭ��", 4, 92));
	course1.push_back(Course("1002", "��ѧ����", 2, 95));
	course1.push_back(Course("1003", "���Դ���", 3, 88));
	course1.push_back(Course("1004", "��ѧ����", 6, 99));

	vector<Course> course2;
	course2.push_back(Course("1001", "ͨ��ԭ��", 4, 81));
	course2.push_back(Course("1002", "��ѧ����", 2, 60));
	course2.push_back(Course("1003", "���Դ���", 3, 72));
	course2.push_back(Course("1004", "��ѧ����", 6, 78));

	vector<Course> course3;
	course3.push_back(Course("1001", "ͨ��ԭ��", 4, 77));
	course3.push_back(Course("1002", "��ѧ����", 2, 92));
	course3.push_back(Course("1003", "���Դ���", 3, 96));
	course3.push_back(Course("1004", "��ѧ����", 6, 80));

	vector<Course> course4;
	course4.push_back(Course("1001", "ͨ��ԭ��", 4, 84));
	course4.push_back(Course("1002", "��ѧ����", 2, 82));
	course4.push_back(Course("1003", "���Դ���", 3, 86));
	course4.push_back(Course("1004", "��ѧ����", 6, 88));

	Student stu1 = Student("2016110001", "��һ", 22, 1, course1);
	Student stu2 = Student("2016110002", "��һ", 21, 1, course2);
	Student stu3 = Student("2016110003", "Ǯһ", 20, 1, course3);
	Student stu4 = Student("2016110004", "��һ", 22, 0, course4);

	vector<Course> course_new;
	course_new.push_back(Course("1001", "ͨ��ԭ��", 4, 0));
	course_new.push_back(Course("1002", "��ѧ����", 2, 0));
	course_new.push_back(Course("1003", "���Դ���", 3, 0));
	course_new.push_back(Course("1004", "��ѧ����", 6, 0));
	all_students.push_back(stu1);
	all_students.push_back(stu2);
	all_students.push_back(stu3);
	all_students.push_back(stu4);

	all_stu_num.insert(stu1.get_stu_num());
	all_stu_num.insert(stu2.get_stu_num());
	all_stu_num.insert(stu3.get_stu_num());
	all_stu_num.insert(stu4.get_stu_num());

	map_all_students.insert(make_pair(stu1.get_stu_num(), stu1));
	map_all_students.insert(make_pair(stu2.get_stu_num(), stu2));
	map_all_students.insert(make_pair(stu3.get_stu_num(), stu3));
	map_all_students.insert(make_pair(stu4.get_stu_num(), stu4));

	cout << "===��ӭ����ѧ����Ϣ����ϵͳ===" << endl << endl;

	int input;
	cin >> input;
	while (input != 5) {
		print_info();
		cin >> input;
		if (input == 1) {
			print_all_student();
		}
		else if (input == 2) {
			string stu_num;
			string stu_name;
			int stu_age;
			int stu_sex;
			cout << "������ѧ��ѧ��" << endl;
			cin >> stu_num;
			cout << "������ѧ������" << endl;
			cin >> stu_name;
			cout << "������ѧ������" << endl;
			cin >> stu_age;
			cout << "������ѧ���Ա�1����������0����Ů����" << endl;
			cin >> stu_sex;
			Student new_stu = Student(stu_num, stu_name, stu_age, stu_sex, course_new);
			bool is_in = add_student(new_stu);
			if (is_in) {
				cout << "��ӳɹ�" << endl;
				print_all_student();
			}
			else {
				cout << "ѧ���Ѵ��ڣ�" << endl;
			}
		}
		else if (input == 3) {
			string stu_num;
			cout << "������ɾ����ѧ��ѧ��" << endl;
			cin >> stu_num;
			bool is_in = del_student(stu_num);
			if (is_in) {
				cout << "ɾ���ɹ�" << endl;
				print_all_student();
			}
			else {
				cout << "ѧ�Ų����ڣ�" << endl;
			}
		}
		else if (input == 4) {
			string stu_num;
			cout << "������ѧ��ѧ�Ų�ѯ" << endl;
			cin >> stu_num;
			print_student_course(search_student(stu_num));
		}
		else if (input == 5) {
			string stu_num;
			Student* stuD;
			vector<Course> couR;
			cout << "������ѧ��ѧ��" << endl;
			cin >> stu_num;
			stuD=&search_student(stu_num);
			string cour_num;
			cout << "������γ̱��" << endl;
			cin >> cour_num;
			int cour_score;
			cout << "����ɼ�" << endl;
			cin >> cour_score;
			if (cour_num == "1001")
			{
				cout << "�ҵ��ˣ�" << endl;
				cout << couR.back().cour_score;
				couR = (stuD->get_stu_courses());
				couR.begin()->set_cour_score(cour_score);
			}
			else if (cour_num == "1002")
			{
				couR = (stuD->get_stu_courses());
				couR[2].set_cour_score(cour_score);
			}
			else if (cour_num == "1003")
			{
				couR = (stuD->get_stu_courses());
				couR[3].set_cour_score(cour_score);
			}
			else if (cour_num == "1004")
			{
				couR = (stuD->get_stu_courses());
				couR[4].set_cour_score(cour_score);
			}
			else
			{
				cout << "�������" << endl;
			}

			cout << "�޸ĳɹ�" << endl;
			print_student_course(search_student(stu_num));
		}
		else if (input == 6) {
			break;
		}
		else {
			cout << "������Ǹ�ɶ��" << endl << endl;
		}



	}
	cout << "=====================================================" << endl;
	cout << "���˳�ϵͳ!" << endl;
}



