#ifndef HW05_03_H_
#define HW05_03_H_

class Point {
private:									// �G���I�y��
	float x;
	float y;
	float z;

public:
	Point(float _x = 0, float _y = 0, float _z = 0) :x(_x), y(_y), z(_z){};	
	Point(const Point &);
	Point & operator=(const Point &);
	~Point();									
												
	float operator[](int i) const;	
	bool operator<(Point &) const;
	bool operator>(Point &) const;
	bool operator==(Point &) const;
	bool operator<=(Point &) const;
	bool operator>=(Point &) const;
	friend std::istream & operator >> (std::istream &, Point &);			// ���� >> Ū�ɨϥ�
	friend std::ostream & operator << (std::ostream &, const Point &);		// ���� << ��X�ϥ�
};

#endif // !HW05_03_H_
