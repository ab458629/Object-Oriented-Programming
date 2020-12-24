#ifndef  EMPLOY_H_
#define EMPLOY_H_

class Employee {
private:
	char * firstname;
	char * lastname;
public:
	Employee(char *, char *);
	Employee(const Employee &);
	virtual ~Employee();
	Employee & operator=(const Employee &);
	virtual double earning() const = 0;	// pure virtual function
	virtual void print() const;
};

#endif // ! EMPLOY_H_
