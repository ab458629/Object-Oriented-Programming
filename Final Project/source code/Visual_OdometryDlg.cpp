
// Visual_OdometryDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "Visual_Odometry.h"
#include "Visual_OdometryDlg.h"
#include "afxdialogex.h"

#include "atlstr.h"
#include <list>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <sophus/se3.hpp>


using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void Config::setParameterFile(const std::string& filename)
{
	if (config_ == nullptr)
		config_ = shared_ptr<Config>(new Config);
	config_->file_ = cv::FileStorage(filename.c_str(), cv::FileStorage::READ);
	if (config_->file_.isOpened() == false)
	{
		std::cerr << "parameter file " << filename << " does not exist." << std::endl;
		config_->file_.release();
		return;
	}
}

Config::~Config()
{
	if (file_.isOpened())
		file_.release();
}

shared_ptr<Config> Config::config_ = nullptr;

Camera::Camera()
{
	fx_ = Config::get<float>("camera.fx");
	fy_ = Config::get<float>("camera.fy");
	cx_ = Config::get<float>("camera.cx");
	cy_ = Config::get<float>("camera.cy");
	depth_scale_ = Config::get<float>("camera.depth_scale");
}

Eigen::Vector3d Camera::world2camera(const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w)
{
	return T_c_w*p_w;
}

Eigen::Vector3d Camera::camera2world(const Eigen::Vector3d& p_c, const Sophus::SE3d& T_c_w)
{
	return T_c_w.inverse() *p_c;
}

Eigen::Vector2d Camera::camera2pixel(const Eigen::Vector3d& p_c)
{
	return Eigen::Vector2d(
		fx_ * p_c(0, 0) / p_c(2, 0) + cx_,
		fy_ * p_c(1, 0) / p_c(2, 0) + cy_
	);
}

Eigen::Vector3d Camera::pixel2camera(const Eigen::Vector2d& p_p, double depth)
{
	return Eigen::Vector3d(
		(p_p(0, 0) - cx_) *depth / fx_,
		(p_p(1, 0) - cy_) *depth / fy_,
		depth
	);
}

Eigen::Vector2d Camera::world2pixel(const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w)
{
	return camera2pixel(world2camera(p_w, T_c_w));
}

Eigen::Vector3d Camera::pixel2world(const Eigen::Vector2d& p_p, const Sophus::SE3d& T_c_w, double depth)
{
	return camera2world(pixel2camera(p_p, depth), T_c_w);
}



static void saveCameraParams(Mat cameraMatrix, Mat distCoeffs){
	string filename = "Calibration_result.yaml";
	cv::FileStorage fs(filename, FileStorage::WRITE);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs.release();
}

typedef vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> VecVector2d;
typedef vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> VecVector3d;

typedef vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>> TrajectoryType;

void DrawTrajectory(const TrajectoryType &gt, const TrajectoryType &esti);

TrajectoryType ReadTrajectory(const string &path);

TrajectoryType ReadTrajectory2(const string &path);

typedef Eigen::Matrix<double, 6, 1> Vector6d;
void showPointCloud(const vector<Vector6d, Eigen::aligned_allocator<Vector6d>> &pointcloud);
// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisual_OdometryDlg 對話方塊



CVisual_OdometryDlg::CVisual_OdometryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISUAL_ODOMETRY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVisual_OdometryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlComb);
}

BEGIN_MESSAGE_MAP(CVisual_OdometryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CVisual_OdometryDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CVisual_OdometryDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CVisual_OdometryDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CVisual_OdometryDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CVisual_OdometryDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CVisual_OdometryDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON6, &CVisual_OdometryDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CVisual_OdometryDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CVisual_OdometryDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CVisual_OdometryDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CVisual_OdometryDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON12, &CVisual_OdometryDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CVisual_OdometryDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CVisual_OdometryDlg::OnBnClickedButton14)

	ON_BN_CLICKED(IDC_BUTTON18, &CVisual_OdometryDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CVisual_OdometryDlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// CVisual_OdometryDlg 訊息處理常式

BOOL CVisual_OdometryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	thre = 10;
	_Type = 2;
	winSize = 21;	// default 
	pyrLayer = 3;
	numCornersHor = 6;
	numCornersVer = 9;
	numBoards = 5;

	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	pBoxOne->SetWindowText(_T("Window size"));

	pBoxTwo = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo->SetWindowText(_T("Pyramid layer"));

	pBoxThree = (CEdit*)GetDlgItem(IDC_EDIT3);
	pBoxThree->SetWindowText(_T("Output"));

	pBoxFour = (CEdit*)GetDlgItem(IDC_EDIT4);
	pBoxFour->SetWindowText(_T("Hor_corners"));

	pBoxFive = (CEdit*)GetDlgItem(IDC_EDIT5);
	pBoxFive->SetWindowText(_T("Ver_corners"));

	pBoxSix = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxSix->SetWindowText(_T("num_Boards"));

	pBoxSeven = (CEdit*)GetDlgItem(IDC_EDIT7);
	pBoxSeven->SetWindowText(_T("Threshold"));

	CString strName;
	strName.Empty();
	m_ctrlComb.SetWindowTextW(_T("Type"));
	strName.Format(_T("TYPE_5_8"));
	m_ctrlComb.AddString(strName);
	strName.Format(_T("TYPE_7_12"));
	m_ctrlComb.AddString(strName);
	strName.Format(_T("TYPE_9_16"));
	m_ctrlComb.AddString(strName);
	
	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CVisual_OdometryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CVisual_OdometryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CVisual_OdometryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVisual_OdometryDlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	static int LastIndex = -1;

	const TCHAR szFilter[] = _T("Video Files (*.mp4, *.avi)|*.mp4;*.avi||All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("Select Vedio File"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter, this);

	if (LastIndex != -1) dlg.m_ofn.nFilterIndex = LastIndex; // restore last used index 
															 // from last time
	string filename;

	if (dlg.DoModal() == IDOK) {
		LastIndex = dlg.m_ofn.nFilterIndex; // Store last used index for next time
		CString path = dlg.GetPathName();
		filename = CW2A(path.GetBuffer(0));
	}

	VideoCapture capture(filename);
	if (!capture.isOpened()) {
		return;
	}

	int n = (int)capture.get(CAP_PROP_FRAME_COUNT);
	int FPS = (int)capture.get(CAP_PROP_FPS);


	vector<Point2f> p0, p1;
	cv::Mat old_frame, old_gray;

	capture >> old_frame;
	cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
	vector<cv::KeyPoint> kps;
	cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create(thre, _Type);
	detector->detect(old_gray, kps);

	for (int i = 0; i < kps.size(); i++) {
		p0.push_back(kps[i].pt);
	}
	Mat mask = Mat::zeros(old_frame.size(), old_frame.type());

	namedWindow("LK optical flow", 0);
	resizeWindow("LK optical flow", 1280, 760);

	for (int index = 0; index < n; index++) {
		Mat frame, frame_gray;
		capture >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

		vector<unsigned char> status;
		vector<float> error;

		// 計算光流花了多少時間
		chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
		cv::calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, error, Size(winSize, winSize), pyrLayer);
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
		chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		CString str;
		str.Format(_T("LK Flow use time: %g seconds."), time_used.count());
		pBoxThree->SetWindowText(str);

		vector<Point2f> good_new;
		for (uint i = 0; i < p0.size(); i++){
			// Select good points
			if (status[i] == 1) {
				good_new.push_back(p1[i]);
				// draw the tracks
				circle(frame, p1[i], 5, cv::Scalar(0, 255, 0), -1);
			}
		}
		Mat img;
		add(frame, mask, img);
		imshow("LK optical flow", img);
		waitKey(1000 / FPS);
		old_gray = frame_gray.clone();
		p0 = good_new;

		int key = waitKey(1);
		if (key == 27)	// 輸入ESC離開
			break;
	}
	destroyAllWindows();
	capture.release();

	/*
	注意：
	（1）沿著邊緣移動時,特徵內容基本不變,但不是角點也不是邊緣,會跳動
	（2）光流可以減少計算量與時間,要用光流或是描述子,case by case
	（3）相機運動較大時,不可使用,否則採集頻率要調高,高fps
	*/
}


void CVisual_OdometryDlg::OnBnClickedButton2()
{

	VideoCapture capture(0);
	if (!capture.isOpened()) {
		MessageBox(_T("Can not activate Camera!"), _T("Error"), MB_ICONEXCLAMATION);
		return;
	}

	vector<Point2f> p0, p1;
	cv::Mat old_frame, old_gray;

	capture >> old_frame;
	cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
	vector<cv::KeyPoint> kps;
	cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create(thre, _Type);
	detector->detect(old_gray, kps);

	for (int i = 0; i < kps.size(); i++) {
		p0.push_back(kps[i].pt);
	}
	Mat mask = Mat::zeros(old_frame.size(), old_frame.type());

	namedWindow("LK optical flow", 0);
	resizeWindow("LK optical flow", 1280, 760);

	while(1){
		Mat frame, frame_gray;
		capture >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

		vector<unsigned char> status;
		vector<float> error;

		if (p0.size() == 0) {
			// cout << "all keypoints are lost." << endl;
			break;
		}

		// 計算光流花了多少時間
		chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
		cv::calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, error, Size(winSize, winSize), pyrLayer);
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
		chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		CString str;
		str.Format(_T("LK Flow use time: %g seconds."), time_used.count());
		pBoxThree->SetWindowText(str);


		vector<Point2f> good_new;
		for (uint i = 0; i < p0.size(); i++) {
			// Select good points
			if (status[i] == 1) {
				good_new.push_back(p1[i]);
				// draw the tracks
				circle(frame, p1[i], 2, cv::Scalar(0, 255, 0), -1);
				line(frame, p0[i], p1[i], cv::Scalar(0, 255, 0), 2);
			}
		}
		int key = waitKey(1);
		if (key == 27)	// 輸入ESC離開
			break;
		Mat img;
		add(frame, mask, img);
		imshow("LK optical flow", img);
		waitKey(1000 / 20);	// 20fps
		old_gray = frame_gray.clone();
		p0 = good_new;
	}
	capture.release();
	destroyAllWindows();

	/*
	注意：
	（1）沿著邊緣移動時,特徵內容基本不變,但不是角點也不是邊緣,會跳動
	（2）光流可以減少計算量與時間,要用光流或是描述子,case by case
	（3）相機運動較大時,不可使用,否則採集頻率要調高,高fps
	*/
}


void CVisual_OdometryDlg::OnBnClickedButton4(){

	Size board_sz = Size(numCornersHor, numCornersVer);

	VideoCapture capture = VideoCapture(0);
	if (!capture.isOpened()) {
		MessageBox(_T("Can not activate Camera!") , _T("Error"), MB_ICONEXCLAMATION);
		return;
	}

	vector<vector<Point3f>> object_points;
	vector<vector<Point2f>> image_points;
	vector<Point2f> corners;

	int successes = 0;
	Mat image;
	Mat gray_image;
	vector<Point3f> obj;
	capture >> image;

	int numSquares = numCornersHor * numCornersVer;
	for (int j = 0; j < numSquares; j++)
		obj.push_back(Point3f(j / numCornersHor, j%numCornersHor, 0.0f));


	while (successes < numBoards) {
		cvtColor(image, gray_image, CV_BGR2GRAY);
		bool found = findChessboardCorners(image, board_sz, corners,
			CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		if (found){
			cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			drawChessboardCorners(gray_image, board_sz, corners, found);
		}
		imshow("Calibration", gray_image);
		capture >> image;

		int key = waitKey(1);
		if (key == 27)	// 輸入ESC離開
			return;

		if (key == ' ' && found != 0){
			image_points.push_back(corners);
			object_points.push_back(obj);
			successes++;

			char pName[50];
			sprintf_s(pName, sizeof(pName), "Calibration %d.bmp", successes);
			char str[] = "calibration/";
			strcat_s(str, sizeof(pName), pName);
			imwrite(str, image);

			if (successes >= numBoards)
				break;
		}
	}
	capture.release();
	destroyAllWindows();
	calibrateCamera(object_points, image_points, Size(gray_image.rows, gray_image.cols), intrinsics, distCoeffs, rvecs, tvecs);// calibrateCamera()給的世界座標方向是由obj_points的檢查順序與findChessboardCorners的檢查順序共同決定
	saveCameraParams(intrinsics, distCoeffs);
}


void CVisual_OdometryDlg::OnBnClickedButton5()
{
	CString str1;
	pBoxOne->GetWindowText(str1);
	winSize = _ttoi(str1);

	CString str2;
	pBoxTwo->GetWindowText(str2);
	pyrLayer = _ttoi(str2);

	CString str3;
	pBoxSeven->GetWindowText(str3);
	thre = _ttoi(str3);

	CString str4;
	_Type = m_ctrlComb.GetCurSel();
	switch(_Type){
	case 0:
		str4 = _T("TYPE_5_8 ");
	case 1:
		str4 = _T("TYPE_7_12  ");
	case 2:
		str4 = _T("TYPE_9_16   ");
	}

	MessageBox(_T("Threshold : ") + str3
		+ _T("\nType : ") + str4
		+ _T("\nWindow size : ") + str1 
		+ _T("\nPyramid layer : ") + str2 
		, _T("Parameter setting"), MB_OK);
}


void CVisual_OdometryDlg::OnBnClickedButton1()
{
	CString str1;
	pBoxFour->GetWindowText(str1);
	numCornersHor = _ttoi(str1);

	CString str2;
	pBoxFive->GetWindowText(str2);
	numCornersVer = _ttoi(str2);

	CString str3;
	pBoxSix->GetWindowText(str3);
	numBoards = _ttoi(str3);

	MessageBox(_T("numCornersHor : ") + str1 
		+ _T("\nnumCornersVer : ") + str2
		+ _T("\nnumBoards : ") + str3
		, _T("Parameter setting"), MB_OK);
	/*
	Config::setParameterFile("default.yaml");
	double fx = Config::get<double>("camera.fx");
	cout << fx;
	*/
}


void CVisual_OdometryDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void CVisual_OdometryDlg::OnBnClickedButton6()
{	
	if (&intrinsics == nullptr) return;
	Mat imageUndistorted;
	VideoCapture capture(0);
	Mat image;
	while (1){
		capture >> image;
		undistort(image, imageUndistorted, intrinsics, distCoeffs);
		cv::imshow("Original", image);
		cv::imshow("Undistorted", imageUndistorted);
		int key = waitKey(1);
		if (key == 27)	// 輸入ESC離開
			return;
	}
	destroyAllWindows();
	capture.release();

}


void CVisual_OdometryDlg::OnBnClickedButton7()
{	
	VideoCapture capture(0);
	if (capture.isOpened()) {
		int num_image = 0;
		char pName[20];
		while (1) {
			Mat frame;
			capture >> frame;
			int key = waitKey(1);
			if (key == 27)	// 輸入ESC離開
				return;
			if (key == ' ') {
				char pName[50];
				sprintf_s(pName, sizeof(pName), "ORB %d.jpg", num_image);
				char str[] = "test/";
				strcat_s(str, sizeof(pName), pName);
				imwrite(str, frame);
				num_image++;
			}
			if (num_image == 2) break;
			imshow("Image capture", frame);
		}
		capture.release();
		destroyAllWindows();
	}
	Mat img_1 = imread("test/ORB 0.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_2 = imread("test/ORB 1.jpg", CV_LOAD_IMAGE_COLOR);
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;
	Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

	orb->detect(img_1, keypoints_1);
	orb->detect(img_2, keypoints_2);

	orb->compute(img_1, keypoints_1, descriptors_1);
	orb->compute(img_2, keypoints_2, descriptors_2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptors_1, descriptors_2, matches);

	double min_dist = 10000, max_dist = 0;

	for (int i = 0; i < descriptors_1.rows; i++){
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	CString str;
	str.Format(_T("min_dist = %g   max_dist = %g"), min_dist, max_dist);


	pBoxEight = (CEdit*)GetDlgItem(IDC_EDIT8);
	pBoxEight->SetWindowText(str);

	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptors_1.rows; i++){
		if (matches[i].distance <= max(2 * min_dist, 30.0)){
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_goodmatch;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
	imshow("Optimized feature points", img_goodmatch);
	waitKey(0);
}


void CVisual_OdometryDlg::OnBnClickedButton8()
{
	string groundtruth_file = "associate_with_groundtruth.txt";
	string estimated_file = "estimated.txt";

	TrajectoryType groundtruth = ReadTrajectory(groundtruth_file);
	TrajectoryType estimated = ReadTrajectory2(estimated_file);
	// assert(!groundtruth.empty() && !estimated.empty());
	// assert(groundtruth.size() == estimated.size());

	// compute rmse
	double rmse = 0;
	for (size_t i = 0; i < estimated.size(); i++) {
		Sophus::SE3d p1 = estimated[i], p2 = groundtruth[i];
		double error = (p2.inverse() * p1).log().norm();
		rmse += error * error;
	}
	rmse = rmse / double(estimated.size());
	rmse = sqrt(rmse);

	CString str;
	str.Format(_T("RMSE = %g"), rmse);
	pBoxNine = (CEdit*)GetDlgItem(IDC_EDIT9);
	pBoxNine->SetWindowText(str);

	DrawTrajectory(groundtruth, estimated);

}

void find_feature_matches(const Mat& img_1, const Mat& img_2,
	std::vector<KeyPoint>& keypoints_1,
	std::vector<KeyPoint>& keypoints_2,
	std::vector< DMatch >& matches) {

	Mat descriptors_1, descriptors_2;

	Ptr<FeatureDetector> detector = ORB::create();
	Ptr<DescriptorExtractor> descriptor = ORB::create();

	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

	detector->detect(img_1, keypoints_1);
	detector->detect(img_2, keypoints_2);

	descriptor->compute(img_1, keypoints_1, descriptors_1);
	descriptor->compute(img_2, keypoints_2, descriptors_2);

	vector<DMatch> match;

	matcher->match(descriptors_1, descriptors_2, match);

	double min_dist = 10000, max_dist = 0;

	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = match[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}


	for (int i = 0; i < descriptors_1.rows; i++) {
		if (match[i].distance <= max(2 * min_dist, 30.0)) {
			matches.push_back(match[i]);
		}
	}

	vector<DMatch> m_Matches;
	m_Matches = matches;

	// 座標轉換成float類型
	vector <KeyPoint> RAN_KP1, RAN_KP2;
	for (int i = 0; i < m_Matches.size(); i++) {
		RAN_KP1.push_back(keypoints_1[matches[i].queryIdx]);
		RAN_KP2.push_back(keypoints_2[matches[i].trainIdx]);
	}

	// 座標轉換
	vector <Point2f> p01, p02;
	for (int i = 0; i < m_Matches.size(); i++) {
		p01.push_back(RAN_KP1[i].pt);
		p02.push_back(RAN_KP2[i].pt);
	}

	// 求轉換矩陣
	vector<uchar> RansacStatus;
	Mat Fundamental = findFundamentalMat(p01, p02, RansacStatus, FM_RANSAC);

	vector <KeyPoint> RR_KP1, RR_KP2;
	vector <DMatch> RR_matches;
	int index = 0;

	for (int i = 0; i < m_Matches.size(); i++) {
		if (RansacStatus[i] != 0) {
			RR_KP1.push_back(RAN_KP1[i]);
			RR_KP2.push_back(RAN_KP2[i]);
			m_Matches[i].queryIdx = index;
			m_Matches[i].trainIdx = index;
			RR_matches.push_back(m_Matches[i]);
			index++;
		}
	}

	Mat img_RR_matches;
	drawMatches(img_1, RR_KP1, img_2, RR_KP2, RR_matches, img_RR_matches);
	imshow("ORB_Matches(By Ransac)", img_RR_matches);

	keypoints_1 = RR_KP1;
	keypoints_2 = RR_KP2;
	matches = RR_matches;
}

Point2d pixel2cam(const Point2d& p, const Mat& K) {
	return Point2d(
		(p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
		(p.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
	);
}

void bundleAdjustmentGaussNewton(
	const VecVector3d &points_3d,
	const VecVector2d &points_2d,
	const Mat &K,
	Sophus::SE3d &pose) {
	typedef Eigen::Matrix<double, 6, 1> Vector6d;
	const int iterations = 10;
	double cost = 0, lastCost = 0;
	double fx = K.at<double>(0, 0);
	double fy = K.at<double>(1, 1);
	double cx = K.at<double>(0, 2);
	double cy = K.at<double>(1, 2);

	for (int iter = 0; iter < iterations; iter++) {
		Eigen::Matrix<double, 6, 6> H = Eigen::Matrix<double, 6, 6>::Zero();
		Vector6d b = Vector6d::Zero();

		cost = 0;
		// compute cost
		for (int i = 0; i < points_3d.size(); i++) {
			Eigen::Vector3d pc = pose * points_3d[i];
			double inv_z = 1.0 / pc[2];
			double inv_z2 = inv_z * inv_z;
			Eigen::Vector2d proj(fx * pc[0] / pc[2] + cx, fy * pc[1] / pc[2] + cy);

			Eigen::Vector2d e = points_2d[i] - proj;

			cost += e.squaredNorm();
			Eigen::Matrix<double, 2, 6> J;
			J << -fx * inv_z,
				0,
				fx * pc[0] * inv_z2,
				fx * pc[0] * pc[1] * inv_z2,
				-fx - fx * pc[0] * pc[0] * inv_z2,
				fx * pc[1] * inv_z,
				0,
				-fy * inv_z,
				fy * pc[1] * inv_z2,
				fy + fy * pc[1] * pc[1] * inv_z2,
				-fy * pc[0] * pc[1] * inv_z2,
				-fy * pc[0] * inv_z;

			H += J.transpose() * J;
			b += -J.transpose() * e;
		}

		Vector6d dx;
		dx = H.ldlt().solve(b);

		if (isnan(dx[0])) {
			cout << "result is nan!" << endl;
			break;
		}

		if (iter > 0 && cost >= lastCost) {
			// cost increase, update is not good
			cout << "cost: " << cost << ", last cost: " << lastCost << endl;
			break;
		}

		// update your estimation
		pose = Sophus::SE3d::exp(dx) * pose;
		lastCost = cost;

		cout << "iteration " << iter << " cost=" << std::setprecision(12) << cost << endl;
		if (dx.norm() < 1e-6) {
			// converge
			break;
		}
	}

	cout << "pose by g-n: \n" << pose.matrix() << endl;
}

void CVisual_OdometryDlg::OnBnClickedButton9()
{	
	string associate_file = "associate.txt";
	ifstream fin("associate.txt");
	if (!fin.is_open()) { return; }

	string rgb_file, depth_file, time_rgb, time_depth;
	cv::Mat color, depth;
	vector<cv::Mat> colorImgs, depthImgs;

	ofstream out_file("estimated.txt");

	for (int i = 0; i < 830; i++) {
		fin >> time_rgb >> rgb_file >> time_depth >> depth_file;
		color = cv::imread(rgb_file, CV_LOAD_IMAGE_COLOR);
		colorImgs.push_back(color);
		depth = cv::imread(depth_file, CV_LOAD_IMAGE_UNCHANGED);
		depthImgs.push_back(depth);
	}

	fin.close();

	Eigen::Vector3d t_(-1.8199, -0.7560, 0.5686);
	Eigen::Quaterniond q_(-0.1360, 0.1559, 0.7218, -0.6604);
	Eigen::Matrix3d R_ = q_.toRotationMatrix();
	out_file << setiosflags(ios::fixed | ios::showpoint) << setprecision(4);
	cout << q_.coeffs().transpose() << endl;
	out_file << t_.transpose() << " " << q_.x() << " " << q_.y() << " " << q_.z() << " " << q_.w() << endl;

	Eigen::Isometry3d Twc = Eigen::Isometry3d::Identity();
	Twc.rotate(R_);
	Twc.pretranslate(t_);

	for (int i = 0; i < 131; i++) {
		Mat img_1 = colorImgs[i];
		Mat img_2 = colorImgs[i+1];
		vector<KeyPoint> keypoints_1, keypoints_2;
		vector<DMatch> matches;
		find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, matches);
		cout << "一共找到了" << matches.size() << "组匹配點" << endl;

		Mat d1 = depthImgs[i];
		Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
		vector<Point3f> pts_3d;
		vector<Point2f> pts_2d;
		for (DMatch m : matches) {
			ushort d = d1.ptr<unsigned short>(int(keypoints_1[m.queryIdx].pt.y))[int(keypoints_1[m.queryIdx].pt.x)];
			if (d == 0)   // bad depth
				continue;
			float dd = d / 5000.0;
			Point2d p1 = pixel2cam(keypoints_1[m.queryIdx].pt, K);
			pts_3d.push_back(Point3f(p1.x * dd, p1.y * dd, dd));
			pts_2d.push_back(keypoints_2[m.trainIdx].pt);
		}

		cout << "3d-2d pairs: " << pts_3d.size() << endl;

		chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
		Mat r, t;
		solvePnP(pts_3d, pts_2d, K, Mat(), r, t, false, CV_EPNP);
		Mat R;
		cv::Rodrigues(r, R); 
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
		chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		cout << "solve pnp in opencv cost time: " << time_used.count() << " seconds." << endl;

		cout << "R=" << endl << R << endl;
		cout << "t=" << endl << t << endl;

		VecVector3d pts_3d_eigen;
		VecVector2d pts_2d_eigen;
		for (size_t i = 0; i < pts_3d.size(); ++i) {
			pts_3d_eigen.push_back(Eigen::Vector3d(pts_3d[i].x, pts_3d[i].y, pts_3d[i].z));
			pts_2d_eigen.push_back(Eigen::Vector2d(pts_2d[i].x, pts_2d[i].y));
		}

		cout << "calling bundle adjustment by gauss newton" << endl;
		Sophus::SE3d pose_gn;
		t1 = chrono::steady_clock::now();
		bundleAdjustmentGaussNewton(pts_3d_eigen, pts_2d_eigen, K, pose_gn);
		t2 = chrono::steady_clock::now();
		time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		cout << "solve pnp by gauss newton cost time: " << time_used.count() << " seconds." << endl;

		Twc = Twc * pose_gn.matrix().inverse();

		q_ = Eigen::Quaterniond(Twc.rotation());
		t_ = Twc.translation();

		out_file << t_.transpose() << " " << q_.x() << " " << q_.y() << " " << q_.z() << " " << q_.w() << endl;
	}

}


void CVisual_OdometryDlg::OnBnClickedButton10()
{
	Mat img_1 = imread("test/ORB 0.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_2 = imread("test/ORB 1.jpg", CV_LOAD_IMAGE_COLOR);
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;
	Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

	orb->detect(img_1, keypoints_1);
	orb->detect(img_2, keypoints_2);

	orb->compute(img_1, keypoints_1, descriptors_1);
	orb->compute(img_2, keypoints_2, descriptors_2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptors_1, descriptors_2, matches);

	double min_dist = 10000, max_dist = 0;

	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	CString str;
	str.Format(_T("min_dist = %g   max_dist = %g"), min_dist, max_dist);

	pBoxEight = (CEdit*)GetDlgItem(IDC_EDIT8);
	pBoxEight->SetWindowText(str);

	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance <= max(2 * min_dist, 30.0)) {
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_goodmatch;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
	imshow("Optimized feature points", img_goodmatch);
	waitKey(0);
	/*
	可用python將圖片轉成影片檔
	outputFile = "test.avi"
	vid_writer = cv.VideoWriter(outputFile, cv.VideoWriter_fourcc('M', 'J', 'P', 'G'), 20, (640, 480))

	for filename in glob.glob("rgb\\*.png"):
	img = cv2.imread(filename)
	vid_writer.write(img.astype(np.uint8))
	*/
}

TrajectoryType ReadTrajectory(const string &path) {
	ifstream fin(path);
	TrajectoryType trajectory;
	if (!fin) {
		cerr << "trajectory " << path << " not found." << endl;
		return trajectory;
	}

	while (!fin.eof()) {
		string rgb_file, depth_file, time_rgb, time_depth;
		double time, tx, ty, tz, qx, qy, qz, qw;
		fin >> time_rgb >> rgb_file >> time_depth >> depth_file >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
		Sophus::SE3d p1(Eigen::Quaterniond(qw, qx, qy, qz), Eigen::Vector3d(tx, ty, tz));
		trajectory.push_back(p1);
	}
	return trajectory;
}

TrajectoryType ReadTrajectory2(const string &path) {
	ifstream fin(path);
	TrajectoryType trajectory;
	if (!fin) {
		cerr << "trajectory " << path << " not found." << endl;
		return trajectory;
	}

	while (!fin.eof()) {
		double tx, ty, tz, qx, qy, qz, qw;
		fin >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
		std::cout << tx << " " << ty << " " << tz << " " << qx << " " << qy << " " << qz  << " " << qw << std::endl;
		Sophus::SE3d p1(Eigen::Quaterniond(qw, qx, qy, qz), Eigen::Vector3d(tx, ty, tz));
		trajectory.push_back(p1);
	}
	return trajectory;
}


void DrawTrajectory(const TrajectoryType &gt, const TrajectoryType &esti) {
	// create pangolin window and plot the trajectory
	pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pangolin::OpenGlRenderState s_cam(
		pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
		pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
	);

	pangolin::View &d_cam = pangolin::CreateDisplay()
		.SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
		.SetHandler(new pangolin::Handler3D(s_cam));


	while (pangolin::ShouldQuit() == false) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		d_cam.Activate(s_cam);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glLineWidth(3);
		for (size_t i = 0; i < gt.size() - 1; i++) {
			glColor3f(0.0f, 0.0f, 1.0f);  // blue for ground truth
			glBegin(GL_LINES);
			auto p1 = gt[i], p2 = gt[i + 1];
			glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
			glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
			glEnd();
		}
		glLineWidth(5);
		std::cout << esti.size() << std::endl;

		for (size_t i = 0; i < esti.size() - 1; i++) {
			glColor3f(1.0f, 0.0f, 0.0f);  // red for estimated
			glBegin(GL_LINES);
			auto p1 = esti[i], p2 = esti[(i + 1)];
			glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
			// std::cout << "測試" << p1.translation() << std::endl;
			glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
			glEnd();
		}
		pangolin::FinishFrame();
	}

}



void CVisual_OdometryDlg::OnBnClickedButton12() {
	vector<cv::Mat> colorImgs, depthImgs;   
	TrajectoryType poses; 
	ifstream fin("test/pose.txt");
	vector<String> img_images;
	vector<String> depth_images;
	string img_path = "test/rgbd/color/*.png";
	string depth_path = "test/rgbd/depth/*.pgm";
	glob(img_path, img_images);			// cv可以很方便的尋訪整個資料夾的檔案
	glob(depth_path, depth_images);	
	for (int i = 0; i < 4; i++) {
		colorImgs.push_back(cv::imread(img_images[i]));
		depthImgs.push_back(cv::imread(depth_images[i], -1));

		double data[7] = { 0 };
		for (auto &d : data)
			fin >> d;
		Sophus::SE3d pose(Eigen::Quaterniond(data[6], data[3], data[4], data[5]),
			Eigen::Vector3d(data[0], data[1], data[2]));
		poses.push_back(pose);
	}

	double cx = 325.5;
	double cy = 253.5;
	double fx = 518.0;
	double fy = 519.0;
	double depthScale = 5000.0;

	vector<Vector6d, Eigen::aligned_allocator<Vector6d>> pointcloud;
	pointcloud.reserve(1000000);

	for (int i = 0; i < 4; i++) {
		cv::Mat color = colorImgs[i];
		cv::Mat depth = depthImgs[i];
		Sophus::SE3d T = poses[i];
		for (int v = 0; v < color.rows; v++)
			for (int u = 0; u < color.cols; u++) {
				unsigned int d = depth.ptr<unsigned short>(v)[u]; 
				if (d == 0) continue; 
				Eigen::Vector3d point;
				point[2] = double(d) / depthScale;
				point[0] = (u - cx) * point[2] / fx;
				point[1] = (v - cy) * point[2] / fy;
				Eigen::Vector3d pointWorld = T * point;

				Vector6d p;
				p.head<3>() = pointWorld;
				p[5] = color.data[v * color.step + u * color.channels()];   // blue
				p[4] = color.data[v * color.step + u * color.channels() + 1]; // green
				p[3] = color.data[v * color.step + u * color.channels() + 2]; // red
				pointcloud.push_back(p);
			}
	}

	showPointCloud(pointcloud);
}

void CVisual_OdometryDlg::OnBnClickedButton13()
{	
	static int LastIndex = -1;

	const TCHAR szFilter[] = _T("Picture Files (*.jpg, *.png)|*.jpg;*.png||All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("Select Picture File"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter, this);

	if (LastIndex != -1) dlg.m_ofn.nFilterIndex = LastIndex; // restore last used index 
															 // from last time
	string filename;

	if (dlg.DoModal() == IDOK) {
		LastIndex = dlg.m_ofn.nFilterIndex; // Store last used index for next time
		CString path = dlg.GetPathName();
		filename = CW2A(path.GetBuffer(0));
	}

	cv::Mat bgr_image = cv::imread(filename);
	cv::Mat lab_image;
	cv::cvtColor(bgr_image, lab_image, CV_BGR2Lab);

	std::vector<cv::Mat> lab_planes(3);
	cv::split(lab_image, lab_planes); 
								  
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst);

	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, lab_image);

	cv::Mat image_clahe;
	cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

	cv::imshow("image original", bgr_image);
	cv::imshow("image CLAHE", image_clahe);
	cv::waitKey();
}


void showPointCloud(const vector<Vector6d, Eigen::aligned_allocator<Vector6d>> &pointcloud) {

	if (pointcloud.empty()) {
		return;
	}

	pangolin::CreateWindowAndBind("Point Cloud Viewer", 1024, 768);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pangolin::OpenGlRenderState s_cam(
		pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
		pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
	);

	pangolin::View &d_cam = pangolin::CreateDisplay()
		.SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
		.SetHandler(new pangolin::Handler3D(s_cam));

	while (pangolin::ShouldQuit() == false) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		d_cam.Activate(s_cam);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glPointSize(2);
		glBegin(GL_POINTS);
		for (auto &p : pointcloud) {
			glColor3d(p[3] / 255.0, p[4] / 255.0, p[5] / 255.0);
			glVertex3d(p[0], p[1], p[2]);
		}
		glEnd();
		pangolin::FinishFrame();
	}
	return;
}


void CVisual_OdometryDlg::OnBnClickedButton14()
{
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		MessageBox(_T("Can not activate Camera!"), _T("Error"), MB_ICONEXCLAMATION);
		return;
	}
	while (1) {
		cv::Mat bgr_image;
		capture >> bgr_image;
		cv::Mat lab_image;
		cv::cvtColor(bgr_image, lab_image, CV_BGR2Lab);


		std::vector<cv::Mat> lab_planes(3);
		cv::split(lab_image, lab_planes); 
						
		cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
		clahe->setClipLimit(4);
		cv::Mat dst;
		clahe->apply(lab_planes[0], dst);
	
		dst.copyTo(lab_planes[0]);
		cv::merge(lab_planes, lab_image);

		cv::Mat image_clahe;
		cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

		cv::imshow("image original", bgr_image);
		cv::imshow("image CLAHE", image_clahe);

		int key = waitKey(1);
		if (key == 27)	// 輸入ESC離開
			break;
	}

}


void CVisual_OdometryDlg::OnBnClickedButton18()
{	
	if (&intrinsics == nullptr) return;
	vector<String> images;
	string path = "calibration/*.bmp";
	glob(path, images);			// cv可以很方便的尋訪整個資料夾的檔案

	namedWindow("Draw a tetrahedron", 0);
	resizeWindow("Draw a tetrahedron", 640, 480);

	Mat rmatrix, RT;

	vector<Point3f> Points;
	int x, y, z;

	x = 4; y = 3; z = -3;
	Points.push_back(Point3f(x, y, z));

	x = 6; y = 1; z = 0;
	Points.push_back(Point3f(x, y, z));

	x = 2; y = 3; z = 0;
	Points.push_back(Point3f(x, y, z));

	x = 6; y = 5; z = 0;
	Points.push_back(Point3f(x, y, z));

	Scalar colorLine(0, 0, 255);
	int thicknessLine = 3;

	vector<Point2f> undistortMatrix;
	Mat frame;


	for (int i = 0; i < images.size(); i++) {
		frame = imread(images[i]);

		Rodrigues(rvecs[i], rmatrix);
		// cout << "No. " << i + 1 << "Extrinsic Matrix : " << endl;
		Mat mat_tvec = Mat(tvecs[i]).clone();
		hconcat(rmatrix, mat_tvec, RT);	// extrinsic parameters [R|T]


		projectPoints(Points, rmatrix, tvecs[i], intrinsics, distCoeffs, undistortMatrix);

		line(frame, undistortMatrix[0], undistortMatrix[1], colorLine, thicknessLine);
		line(frame, undistortMatrix[0], undistortMatrix[2], colorLine, thicknessLine);
		line(frame, undistortMatrix[0], undistortMatrix[3], colorLine, thicknessLine);
		line(frame, undistortMatrix[1], undistortMatrix[2], colorLine, thicknessLine);
		line(frame, undistortMatrix[2], undistortMatrix[3], colorLine, thicknessLine);
		line(frame, undistortMatrix[3], undistortMatrix[1], colorLine, thicknessLine);

		imshow("Draw a tetrahedron", frame);
		waitKey(2000);

		/* 以下可以計算誤差
		double err = 0.0;
		vector<Point2f>undistortMatrix;
		projectPoints(obj_points[i], rmatrix, tvecs[i], intrinsics, distCoeffs, undistortMatrix);
		err = norm(undistortMatrix, img_points[i]);
		cout << "第" << i << "張圖的誤差：" << err << endl;
		cout << undistortMatrix << endl;
		*/
	}
	destroyAllWindows();
}


void CVisual_OdometryDlg::OnBnClickedButton19()
{
	VideoCapture capture(0);
	if (capture.isOpened()) {
		int num_image = 0;
		char pName[20];
		while (1) {
			Mat frame;
			capture >> frame;
			int key = waitKey(1);
			if (key == 27)	// 輸入ESC離開
				return;
			if (key == ' ') {
				char pName[50];
				sprintf_s(pName, sizeof(pName), "ORB %d.jpg", num_image);
				char str[] = "test/";
				strcat_s(str, sizeof(pName), pName);
				imwrite(str, frame);
				num_image++;
			}
			if (num_image == 2) break;
			imshow("Image capture", frame);
		}
		capture.release();
		destroyAllWindows();
	}

	cv::Mat bgr_image1 = cv::imread("test/ORB 0.jpg");
	cv::Mat bgr_image2 = cv::imread("test/ORB 1.jpg");

	cv::Mat lab_image1;
	cv::Mat lab_image2;
	cv::cvtColor(bgr_image1, lab_image1, CV_BGR2Lab);
	cv::cvtColor(bgr_image2, lab_image2, CV_BGR2Lab);

	std::vector<cv::Mat> lab_planes1(3);
	cv::split(lab_image1, lab_planes1);
	std::vector<cv::Mat> lab_planes2(3);
	cv::split(lab_image2, lab_planes2);

	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	cv::Mat dst1, dst2;

	clahe->apply(lab_planes1[0], dst1);
	clahe->apply(lab_planes2[0], dst2);

	dst1.copyTo(lab_planes1[0]);
	dst2.copyTo(lab_planes2[0]);

	cv::merge(lab_planes1, lab_image1);
	cv::merge(lab_planes2, lab_image2);
	cv::Mat image_clahe1;
	cv::Mat image_clahe2;
	cv::cvtColor(lab_image1, image_clahe1, CV_Lab2BGR);
	cv::cvtColor(lab_image2, image_clahe2, CV_Lab2BGR);

	Mat img_1 = image_clahe1;
	Mat img_2 = image_clahe2;
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;
	Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

	orb->detect(img_1, keypoints_1);
	orb->detect(img_2, keypoints_2);

	orb->compute(img_1, keypoints_1, descriptors_1);
	orb->compute(img_2, keypoints_2, descriptors_2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptors_1, descriptors_2, matches);

	double min_dist = 10000, max_dist = 0;

	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	CString str;
	str.Format(_T("min_dist = %g   max_dist = %g"), min_dist, max_dist);


	pBoxEight = (CEdit*)GetDlgItem(IDC_EDIT8);
	pBoxEight->SetWindowText(str);

	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance <= max(2 * min_dist, 30.0)) {
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_goodmatch;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
	imshow("Optimized feature points", img_goodmatch);
	waitKey(0);


}
