#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class Lecture;

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

void Student::show_lectures() const
{
	std::cout << "Student " << m_name << " visits: " << std::endl;

	for (std::size_t i = 0; i < std::size(m_lectures); ++i)
	{
		std::cout << i + 1 << ": " << m_lectures[i]->name() << std::endl;
	}
}

void Lecture::show_students() const
{
	std::cout << "Lecture " << m_name << " is visited by: " << std::endl;

	for (std::size_t i = 0; i < std::size(m_students); ++i)
	{
		std::cout << i + 1 << ": " << m_students[i]->name() << std::endl;
	}
}

inline void connect(Student & s, Lecture & l)
{
	s.add_lecture(l); l.add_student(s);
}

int main()
{
	Student s1("Ivan");
	Student s2("Dmitriy");
	Student s3("Alexander");

	Lecture l1("Math");
	Lecture l2("Physics");
	Lecture l3("Literature");

	connect(s1, l1);
	connect(s2, l2);
	connect(s3, l3);
	connect(s1, l3);
	connect(s2, l1);
	connect(s3, l2);

	s1.show_lectures();

	l1.show_students();

	return 0;
}