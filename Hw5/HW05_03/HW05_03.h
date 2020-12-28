#ifndef HW05_03_H_
#define HW05_03_H_

class Point {
private:									// 二維點座標
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
	friend std::istream & operator >> (std::istream &, Point &);			// 重載 >> 讀檔使用
	friend std::ostream & operator << (std::ostream &, const Point &);		// 重載 << 輸出使用
};

#endif // !HW05_03_H_
