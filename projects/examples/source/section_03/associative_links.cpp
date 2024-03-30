#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// =================================================================================================

class Lecture; // good: class forward declaration

class Student
{
public:

	Student(const std::string & name) : m_name(name) {}

public:

	[[nodiscard]] const std::string & name() const { return m_name; }

	void add_lecture(const Lecture & lecture)
	{
		m_lectures.push_back(&lecture);
	}

	void show_lectures() const;

private:

	const std::string m_name;

	std::vector < const Lecture * > m_lectures;

}; // class Student

// =================================================================================================

class Lecture
{
public:

	Lecture(const std::string & name) : m_name(name) {}

public:

	[[nodiscard]] const std::string & name() const { return m_name; }

	void add_student(const Student & student)
	{
		m_students.push_back(&student);
	}

	void show_students() const;

private:

	const std::string m_name;

	std::vector < const Student * > m_students;

}; // class Lecture

// =================================================================================================

void Student::show_lectures() const
{
	std::cout << "Student " << m_name << " visits: " << std::endl;

	for (std::size_t i = 1; const auto lecture : m_lectures)
	{
		std::cout << i++ << ": " << lecture->name() << std::endl;
	}
}

void Lecture::show_students() const
{
	std::cout << "Lecture " << m_name << " is visited by: " << std::endl;

	for (std::size_t i = 1; const auto student : m_students)
	{
		std::cout << i++ << ": " << student->name() << std::endl;
	}
}

// =================================================================================================

inline void connect(Student & student, Lecture & lecture)
{
	student.add_lecture(lecture); 
	lecture.add_student(student);
}

// =================================================================================================

int main()
{
	Student student_1("Alex");
	Student student_2("Nick");
	Student student_3("Paul");

	Lecture lecture_1("Astronomy");
	Lecture lecture_2("Chemistry");
	Lecture lecture_3("Geograhpy");	

	connect(student_1, lecture_1);
	connect(student_2, lecture_2);
	connect(student_3, lecture_3);
	connect(student_1, lecture_3);
	connect(student_2, lecture_1);
	connect(student_3, lecture_2);

	student_1.show_lectures();
	lecture_1.show_students();

	return 0;
}