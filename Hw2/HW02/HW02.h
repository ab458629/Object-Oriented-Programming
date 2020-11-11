#ifndef	HW02_H
#define HW02_H
#include <iostream>

class Point{
private:									// 二維點座標
	float x;
	float y;

public:
	Point() :x(0.f), y(0.f){};					// 預設(0,0)，這樣寫比較簡短且快速 (member initializer list)
	Point(float _x, float _y) :x(_x), y(_y) {};	// 參數建構子
	~Point();									// 解構子
	// void Set_data(float, float);				// 如有需要設定data使用
	float operator[](int i) const;				// Subscript operator [0]為x [1]為y
	friend std::istream & operator >> (std::istream &, Point &);			// 重載 >> 讀檔使用
	friend std::ostream & operator << (std::ostream &, const Point &);		// 重載 << 輸出使用
};

class QuadtreeNode{
private:
	const Point *data;						// 記錄此節點的點資料
	QuadtreeNode *nextNode[4];				// 指向此節點的四個子節點 
	const Point separate_point;				// 節點的分割中心 
	const float size;						// 記錄此節點的分割邊界長度

public:
	QuadtreeNode() :size(0.f) {};			// 基底建構子，於本類別將不使用，請調整使其無法被呼叫，這是因為root直接用(0,0)即可
	QuadtreeNode(const Point &, const Point &, const float);			// 三個參數建構子 (data, separate_point, size)
	QuadtreeNode(const QuadtreeNode &);									// 複製建構子 (deep copy) 注意不需在後面加上const
	~QuadtreeNode();													// 解構子，釋放動態空間
	bool InsertPoint(const Point &);									// 將點傳入並插入四元樹中
	const Point *FindClosestPoint(const Point &);					    // 將點傳入，尋找傳入點所屬的子節點，並將已屬於該子節點的點回傳
};

#endif // HW02_H
