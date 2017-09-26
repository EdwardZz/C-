#include <iostream>
#include <vector>
#include <string>
#include <set>
#include<map>


using namespace std;

/****Course 课程类****/
class Course {

public:
	string cour_num;
	string cour_name;
	int cour_credit;
	int cour_score;


	//构造函数
	Course(string cour_num,
		string cour_name,
		int cour_credit,
		int cour_score);

	//成员函数
	void set_cour_num(string cour_num);
	void set_cour_name(string cour_name);
	void set_cour_credit(int cour_credit);
	void set_cour_score(int cour_score);
	void write_cour_score(int cour_score);

	//get 成员函数
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
/****Student 学生类****/
class Student {
public:
	string stu_num;
	string stu_name;
	int stu_sex;
	int stu_age;
	vector<Course> stu_courses;


	// 构造函数
	Student(string stu_num, string stu_name, int stu_age, int stu_sex, vector<Course> stu_courses);
	Student();
	// set 成员函数
	void set_stu_num(string stu_num);
	void set_stu_name(string stu_name);
	void set_stu_sex(int stu_sex);
	void set_stu_age(int stu_age);
	void add_stu_courses(Course course);

	// get 成员函数
	string get_stu_num();
	string get_stu_name();
	int get_stu_sex();
	int get_stu_age();
	vector<Course> get_stu_courses();

	// 其他成员函数
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
/********************** 程序功能函数 ******************************/
// 添加学生数据
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

// 打印学生名单
void print_all_student() {
	cout << endl;
	cout << "**********************" << "学生名单" << "**********************" << endl;
	cout << "学号" << "\t" << "\t" << "姓名" << "\t" << "\t" << "年龄" << "\t" << "\t" << "性别" << endl;
	for (int i = 0; i < all_students.size(); i++) {
		string sex;
		if (all_students[i].get_stu_sex() == 1) {
			sex = "男";
		}
		else {
			sex = "女";
		}
		cout << all_students[i].get_stu_num() << "\t" << all_students[i].get_stu_name() << "\t" << "\t" << all_students[i].get_stu_age() << "\t" << "\t" << sex << endl;
	}
	cout << endl;
}
// 删除学生信息
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
// 修改学生成绩
bool write_cour_score(string stu_num) {
	bool is_in = all_stu_num.find(stu_num) != all_stu_num.end();
	if (!is_in) {
		return false;
	}


}
// 搜索学生信息
Student search_student(string stu_num) {
	return map_all_students.find(stu_num)->second;
}

void print_student_course(Student student) {
	cout << endl;
	cout << "**********************" << "课程信息" << "**********************" << endl;
	cout << "学生姓名:" << "\t" << student.get_stu_name() << endl << endl;
	cout << "编号" << "\t" << "\t" << "名称" << "\t" << "\t" << "学分" << "\t" << "\t" << "成绩" << endl;
	vector<Course> courses = student.get_stu_courses();
	for (Course course : courses) {
		cout << course.get_cour_num() << "\t" << "\t" << course.get_cour_name() << "\t" << "\t" << course.get_cour_credit() << "\t" << "\t" << course.get_cour_score() << endl;

	}
	cout << endl;
}

void print_info() {
	cout << "请输入数字选择对应的功能:" << endl;
	cout << "1. 打印学生名单" << endl;
	cout << "2. 添加学生信息" << endl;
	cout << "3. 删除学生信息" << endl;
	cout << "4. 打印学生课程" << endl;
	cout << "5. 修改学生成绩" << endl;
	cout << "6. 退出" << endl;

}
/********************** main 函数 ******************************/
int main(int argc, const char * argv[]) {
	vector<Course> course1;
	course1.push_back(Course("1001", "通信原理", 4, 92));
	course1.push_back(Course("1002", "大学物理", 2, 95));
	course1.push_back(Course("1003", "线性代数", 3, 88));
	course1.push_back(Course("1004", "数学分析", 6, 99));

	vector<Course> course2;
	course2.push_back(Course("1001", "通信原理", 4, 81));
	course2.push_back(Course("1002", "大学物理", 2, 60));
	course2.push_back(Course("1003", "线性代数", 3, 72));
	course2.push_back(Course("1004", "数学分析", 6, 78));

	vector<Course> course3;
	course3.push_back(Course("1001", "通信原理", 4, 77));
	course3.push_back(Course("1002", "大学物理", 2, 92));
	course3.push_back(Course("1003", "线性代数", 3, 96));
	course3.push_back(Course("1004", "数学分析", 6, 80));

	vector<Course> course4;
	course4.push_back(Course("1001", "通信原理", 4, 84));
	course4.push_back(Course("1002", "大学物理", 2, 82));
	course4.push_back(Course("1003", "线性代数", 3, 86));
	course4.push_back(Course("1004", "数学分析", 6, 88));

	Student stu1 = Student("2016110001", "王一", 22, 1, course1);
	Student stu2 = Student("2016110002", "赵一", 21, 1, course2);
	Student stu3 = Student("2016110003", "钱一", 20, 1, course3);
	Student stu4 = Student("2016110004", "孙一", 22, 0, course4);

	vector<Course> course_new;
	course_new.push_back(Course("1001", "通信原理", 4, 0));
	course_new.push_back(Course("1002", "大学物理", 2, 0));
	course_new.push_back(Course("1003", "线性代数", 3, 0));
	course_new.push_back(Course("1004", "数学分析", 6, 0));
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

	cout << "===欢迎进入学生信息管理系统===" << endl << endl;

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
			cout << "请输入学生学号" << endl;
			cin >> stu_num;
			cout << "请输入学生姓名" << endl;
			cin >> stu_name;
			cout << "请输入学生年龄" << endl;
			cin >> stu_age;
			cout << "请输入学生性别（1代表男生，0代表女生）" << endl;
			cin >> stu_sex;
			Student new_stu = Student(stu_num, stu_name, stu_age, stu_sex, course_new);
			bool is_in = add_student(new_stu);
			if (is_in) {
				cout << "添加成功" << endl;
				print_all_student();
			}
			else {
				cout << "学号已存在！" << endl;
			}
		}
		else if (input == 3) {
			string stu_num;
			cout << "请输入删除的学生学号" << endl;
			cin >> stu_num;
			bool is_in = del_student(stu_num);
			if (is_in) {
				cout << "删除成功" << endl;
				print_all_student();
			}
			else {
				cout << "学号不存在！" << endl;
			}
		}
		else if (input == 4) {
			string stu_num;
			cout << "请输入学生学号查询" << endl;
			cin >> stu_num;
			print_student_course(search_student(stu_num));
		}
		else if (input == 5) {
			string stu_num;
			Student* stuD;
			vector<Course> couR;
			cout << "请输入学生学号" << endl;
			cin >> stu_num;
			stuD=&search_student(stu_num);
			string cour_num;
			cout << "请输入课程编号" << endl;
			cin >> cour_num;
			int cour_score;
			cout << "输入成绩" << endl;
			cin >> cour_score;
			if (cour_num == "1001")
			{
				cout << "找到了！" << endl;
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
				cout << "输入错误！" << endl;
			}

			cout << "修改成功" << endl;
			print_student_course(search_student(stu_num));
		}
		else if (input == 6) {
			break;
		}
		else {
			cout << "输入的是个啥？" << endl << endl;
		}



	}
	cout << "=====================================================" << endl;
	cout << "已退出系统!" << endl;
}



