
// Visual_OdometryDlg.h : 標頭檔
//
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Core>
#include <sophus/se3.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <algorithm>

// CVisual_OdometryDlg 對話方塊
class CVisual_OdometryDlg : public CDialogEx
{
// 建構
public:
	CVisual_OdometryDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISUAL_ODOMETRY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	CComboBox m_ctrlComb;

	CEdit* pBoxOne;
	CEdit* pBoxTwo;
	CEdit* pBoxThree;
	CEdit* pBoxFour;
	CEdit* pBoxFive;
	CEdit* pBoxSix;
	CEdit* pBoxSeven;
	CEdit* pBoxEight;
	CEdit* pBoxNine;
	CEdit* pBoxTen;
	unsigned int thre;
	unsigned int _Type;
	unsigned int winSize, pyrLayer;	// for LK optical flow
	unsigned int numCornersHor, numCornersVer, numBoards;	// for Camera calibration
	cv::Mat intrinsics, distCoeffs;
	std::vector< cv::Mat > rvecs, tvecs;

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();

	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
};

class Config{
private:
	static std::shared_ptr<Config> config_;
	cv::FileStorage file_;

	Config() {} 
public:
	~Config(); 

	static void setParameterFile(const std::string& filename);

	template< typename T >
	static T get(const std::string& key){
		return T(Config::config_->file_[key]);
	}
};

class Camera
{
public:
	typedef std::shared_ptr<Camera> Ptr;
	float   fx_, fy_, cx_, cy_, depth_scale_;


	Camera();
	Camera(float fx, float fy, float cx, float cy, float depth_scale = 0) :
		fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale)
	{}

	Eigen::Vector3d world2camera(const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w);
	Eigen::Vector3d camera2world(const Eigen::Vector3d& p_c, const Sophus::SE3d& T_c_w);
	Eigen::Vector2d camera2pixel(const Eigen::Vector3d& p_c);
	Eigen::Vector3d pixel2camera(const Eigen::Vector2d& p_p, double depth = 1);
	Eigen::Vector3d pixel2world(const Eigen::Vector2d& p_p, const Sophus::SE3d& T_c_w, double depth = 1);
	Eigen::Vector2d world2pixel(const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w);

};
