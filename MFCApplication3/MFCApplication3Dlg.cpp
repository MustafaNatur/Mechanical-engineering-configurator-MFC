
// MFCApplication3Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import <D:\Inventor 2022\Bin\RxInventor.tlb>\
rename_namespace("InventorNative") \
named_guids raw_dispinterfaces \
high_method_prefix("Method") \
rename("DeleteFile", "APIDeleteFile") \
rename("CopyFile", "APICopyFile") \
rename("MoveFile", "APIMoveFile") \
rename("SetEnvironmentVariable", "APISetEnvironmentVariable") \
rename("GetObject", "APIGetObject") \
exclude("_FILETIME", "IStream", "ISequentialStream", \
"_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", \
"IEnumUnknown", "IPersistFile", "IPersist", "IPictureDisp")


using namespace InventorNative;

CComPtr<Application> pInvApp; //приложение

PartDocumentPtr pPartDoc;  //документ
PartComponentDefinitionPtr pPartComDef;//компоненты детали
TransientGeometryPtr pTransGeom; //геометрия детали
TransactionPtr pTrans; //операции

TransactionManagerPtr pTransManager; //менеджер операций


PlanarSketchesPtr sketches; // эскизы
PartFeaturesPtr ft; //элементы детали 

WorkPlanesPtr wp; //рабочие плоскости
WorkAxesPtr wax;//рабочие оси
WorkPointsPtr wpt;//рабочие точки

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CMFCApplication3Dlg



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
	// p_d1(0)
	, D1(50.0)
	, D2(34.0)
	, D3(24.0)
	//, D4(0)
	, H1(10.0)
	, H2(10.0)
	, H3(35.0)
	, H5(3.0)
	, H4(20.0)
	, H6(25.0)
	, S1(4.1)
	, D4(16.0)

	, L1(0.5)
	, H7(1.0)
	, R12(0.5)
	, RR(0.8)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//float l1 = 0.5;
//float h7 = 1;
//float R = 0.8;
//float r1 = 0.5;

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, d1, p_d1);
	DDX_Text(pDX, d1, D1);
	DDX_Text(pDX, d2, D2);
	DDX_Text(pDX, d3, D3);
	//DDX_Text(pDX, d4, D4);
	DDX_Text(pDX, h1, H1);
	DDX_Text(pDX, h2, H2);
	DDX_Text(pDX, h3, H3);
	//  DDX_Text(pDX, h4, D4);
	DDX_Text(pDX, h5, H5);
	DDX_Text(pDX, h4, H4);
	DDX_Text(pDX, h6, H6);
	DDX_Text(pDX, s1, S1);
	//  DDX_Text(pDX, N, N1);
	DDX_Text(pDX, d4, D4);
	//  DDX_Text(pDX, l1, l1);
	//  DDX_Text(pDX, h7, h7);
	//  DDX_Text(pDX, R, R);
	//DDX_Text(pDX, r1, r);
	//  DDX_Text(pDX, r12, r12);
	DDX_Text(pDX, l1, L1);
	DDX_Text(pDX, h7, H7);
	//  DDX_Text(pDX, R, R);
	DDX_Text(pDX, r12, R12);
	DDX_Text(pDX, R, RR);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(CONNECT_BUTTON, &CMFCApplication3Dlg::OnBnClickedButton)
	ON_BN_CLICKED(BILD, &CMFCApplication3Dlg::OnBnClickedBild)
	//ON_BN_CLICKED(NUMBER_DETECTIO, &CMFCApplication3Dlg::OnBnClickedDetectio)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	//ON_EN_CHANGE(h3, &CMFCApplication3Dlg::OnEnChangeh3)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication3Dlg

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton()
{
	CLSID InvAppClsid;
	HRESULT hRes = CLSIDFromProgID(L"Inventor.Application", &InvAppClsid); // для обращения на сервер . Функиция преобразует простое имя в полный адресс

	if (FAILED(hRes)) // макросс для проверки на подключение 
	{
		pInvApp = nullptr;
		return;
	}

	CComPtr<IUnknown> pInvAppUnk = nullptr;
	hRes = ::GetActiveObject(InvAppClsid, NULL, &pInvAppUnk); // проверяем инвентор на запуск. Функция возвращает указатель на главный интерфейс инвентора
	if (FAILED(hRes)) // если инвентор не запустился то запускаем вручную
	{
		hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pInvAppUnk); // прнудительно запускаем инвентор и передаем в переменню pInvAppUnk ссылку 

		if (FAILED(hRes)) // макросс для проверки на подключение 
		{
			pInvApp = nullptr;
			return;
		}
	}

	// получили указатель


	hRes = pInvAppUnk->QueryInterface(__uuidof(Application), (void**)&pInvApp); // 

	pInvApp->put_Visible(TRUE); // получили указатель Имеем на экране окно инвентора

	// СОЗДАНИЕ ДОКУМЕНТА

	//PartDocumentPtr pPartDoc;
	pPartDoc = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true); // добавляем новый документ


	pPartDoc->DisplayName = _T("Конфигуратор"); // получили указатель на наш документ Здаем имя


	pPartDoc->get_ComponentDefinition(&pPartComDef);

	pInvApp->get_TransientGeometry(&pTransGeom);

	pTransManager = pInvApp->GetTransactionManager();

	DocumentPtr Doc = CComQIPtr <Document>(pPartDoc);

	pTransManager->raw_StartTransaction(Doc, _T("Конфигуратор"), &pTrans);

	pPartComDef->get_Sketches(&sketches);

	pPartComDef->get_WorkPlanes(&wp);
	pPartComDef->get_Features(&ft);
	pPartComDef->get_WorkAxes(&wax);
	pPartComDef->get_WorkPoints(&wpt);
    AfxMessageBox(L"Успешное подключение к Autodesk Inventor");

}

bool CMFCApplication3Dlg::CheckData() {
	UpdateData();	
	if (D1*D2*D3*H1*H2*H3*H5*H4*H6*S1*D4*L1*H7*R12*RR <= 0) {
		AfxMessageBox(L"Введены данные меньше или равные 0");
		return false;

	}
	else if (D1<=D2 || D2<=D3 || D3<=D4 || H1<=H5 || H3 <= H4 || H3 < H6) {
		AfxMessageBox(L"Введены данные задающие неправильную геомметрию детали");
		return false;
	}
	else {
		return true;
	}
}

void CMFCApplication3Dlg::OnBnClickedBild()
{
	UpdateData(TRUE);
	if (!CheckData())
		return;
	// выдавливание для крышки
	PlanarSketchPtr pSketch;								// создаем тип данных для построения эскизов
	sketches->raw_Add(wp->GetItem(2), false, &pSketch);     // выбираем по счету плоскость для построения

	SketchPointsPtr skPoints;								// создаем контейнеры для точек
	//SketchLinesPtr skLines;								// создаем контейнеры для линий
	SketchCirclesPtr skCircles;								// создаем контейнеры для окружностей
	//SketchArcsPtr skArcs;								// создаем контейнеры для дуг
	ProfilesPtr skProfiles;

	// инициализируем соответствующими функциями
	pSketch->get_SketchPoints(&skPoints);
	//pSketch->get_SketchLines(&skLines);
	pSketch->get_SketchCircles(&skCircles);
	pSketch->get_Profiles(&skProfiles);
	//pSketch->get_SketchArcs(&skArcs);
	// сами кок
	SketchPointPtr point[7];
	//SketchLinePtr lines[4];
	SketchCirclePtr circ;
	//SketchArcPtr arc;

	// следует обратить внимание на то что API в качестве размерности линейных величин использует санитиметры
	point[0] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	circ = skCircles->MethodAddByCenterRadius(point[0], D1/20);

	ProfilePtr pProfile;
	try
	{
		pProfile = skProfiles->MethodAddForSolid(true);
	}
	catch (...)
	{
		AfxMessageBox(L"Ошибочный контур!");
		return;
	}

	ExtrudeFeaturesPtr ftExtrude;
	ft->get_ExtrudeFeatures(&ftExtrude);

	ExtrudeFeaturePtr extrude = ftExtrude->MethodAddByDistanceExtent(pProfile, H1/10, kPositiveExtentDirection, kJoinOperation);


	//вырез для пальцев
	PlanarSketchPtr pSketch_2;
	sketches->raw_Add(wp->GetItem(2), false, &pSketch_2);

	SketchPointsPtr skPoints_2;								
	SketchCirclesPtr skCircles_2;								
	SketchArcsPtr skArcs_2;								
	ProfilesPtr skProfiles_2;

	pSketch_2->get_SketchPoints(&skPoints_2);
	pSketch_2->get_SketchCircles(&skCircles_2);
	pSketch_2->get_SketchArcs(&skArcs_2);
	pSketch_2->get_Profiles(&skProfiles_2);


	SketchPointPtr point_2[1];
	SketchCirclePtr circ_2;
	SketchArcPtr arc_2;

	point_2[0] = skPoints_2->MethodAdd(pTransGeom->MethodCreatePoint2d(0, D1/20+0.9), false);
	circ_2 = skCircles_2->MethodAddByCenterRadius(point_2[0], 1);

	
	ProfilePtr pProfile_2;
	try
	{
		pProfile_2 = skProfiles_2->MethodAddForSolid(true);
	}
	catch (...)
	{
		AfxMessageBox(L"Ошибочный контур!");
		return;
	}
	ExtrudeFeaturePtr extrude_2 = ftExtrude->MethodAddByThroughAllExtent(pProfile_2, kSymmetricExtentDirection, kCutOperation);


	

	// вращение
	ObjectCollection* pCollection;

	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pCollection);

	pCollection->MethodAdd(extrude_2);
	
	CircularPatternFeatures* pCircPatFeat;

	ft->get_CircularPatternFeatures(&pCircPatFeat);

	CircularPatternFeature* circFeat = pCircPatFeat->MethodAdd(pCollection, wax->GetItem(2), true, 8, "360 град", true, kIdenticalCompute);


	// оболочка
	SurfaceBodyPtr SurfBody;
	SurfaceBodiesPtr SurfBodies1;
	pPartComDef->get_SurfaceBodies(&SurfBodies1);

	SurfBodies1->get_Item(1, &SurfBody);


	Face* edge;
	Faces* edges;

	

	SurfBody->get_Faces(&edges);

	edges->get_Item(17, &edge);

	

	ShellDefinitionPtr shptr;
	ShellFeaturesPtr shells;
	ft->get_ShellFeatures(&shells);

	FaceCollectionPtr facecoll;
	pInvApp->TransientObjects->raw_CreateFaceCollection(vtMissing, &facecoll);
	facecoll->MethodAdd(edge);

	shptr = shells->MethodCreateShellDefinition(vtMissing, H5/10, kInsideShellDirection);

	shptr->put_InputFaces(facecoll);

	shptr->put_Direction(kInsideShellDirection);

	shptr = shells->MethodAdd(shptr);


	//постоение опоры для стойки

	PlanarSketchPtr pSketch_3;								
	sketches->raw_Add(wp->GetItem(2), false, &pSketch_3);
	SketchPointsPtr skPoints_3;								
	SketchCirclesPtr skCircles_3;								
	ProfilesPtr skProfiles_3;
	pSketch_3->get_SketchPoints(&skPoints_3);
	pSketch_3->get_SketchCircles(&skCircles_3);
	pSketch_3->get_Profiles(&skProfiles_3);
	SketchPointPtr point_3[1];
	SketchCirclePtr circ_3;
	point_3[0] = skPoints_3->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	circ_3 = skCircles_3->MethodAddByCenterRadius(point_3[0], D2/20);
	ProfilePtr pProfile_3;
	try
	{
		pProfile_3 = skProfiles_3->MethodAddForSolid(true);
	}
	catch (...)
	{
		AfxMessageBox(L"Ошибочный контур!");
		return;
	}
	ExtrudeFeaturePtr extrude_3 = ftExtrude->MethodAddByDistanceExtent(pProfile_3, H2/10, kPositiveExtentDirection, kJoinOperation);

	//построение стойки
	PlanarSketchPtr pSketch_4;								
	sketches->raw_Add(wp->GetItem(2), false, &pSketch_4);
	SketchPointsPtr skPoints_4;								
	SketchCirclesPtr skCircles_4;								
	ProfilesPtr skProfiles_4;
	pSketch_4->get_SketchPoints(&skPoints_4);
	pSketch_4->get_SketchCircles(&skCircles_4);
	pSketch_4->get_Profiles(&skProfiles_4);
	SketchPointPtr point_4[1];
	SketchCirclePtr circ_4;
	point_4[0] = skPoints_4->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	circ_4 = skCircles_4->MethodAddByCenterRadius(point_4[0], D3/20);
	ProfilePtr pProfile_4;
	try
	{
		pProfile_4 = skProfiles_4->MethodAddForSolid(true);
	}
	catch (...)
	{
		AfxMessageBox(L"Ошибочный контур!");
		return;
	}
	ExtrudeFeaturePtr extrude_4 = ftExtrude->MethodAddByDistanceExtent(pProfile_4, H3/10, kPositiveExtentDirection, kJoinOperation);

	// построение отверстия
	PlanarSketchPtr pSketch_5;
	wp->MethodAddByPlaneAndOffset(wp->GetItem(2), H3 / 10, true);
	sketches->raw_Add(wp->GetItem(4), false, &pSketch_5);
	SketchPointsPtr skPoints_5;								
	SketchCirclesPtr skCircles_5;								
	ProfilesPtr skProfiles_5;
	pSketch_5->get_SketchPoints(&skPoints_5);
	pSketch_5->get_SketchCircles(&skCircles_5);
	pSketch_5->get_Profiles(&skProfiles_5);
	SketchPointPtr point_5[1];
	SketchCirclePtr circ_5;
	point_5[0] = skPoints_5->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	circ_5 = skCircles_5->MethodAddByCenterRadius(point_5[0], D4/20);

	ProfilePtr pProfile_5;
	try
	{
		pProfile_5 = skProfiles_5->MethodAddForSolid(true);
	}
	catch (...)
	{
		AfxMessageBox(L"Ошибочный контур!");
		return;
	}
	ExtrudeFeaturePtr extrude_5 = ftExtrude->MethodAddByDistanceExtent(pProfile_5, H4/10, kNegativeExtentDirection, kCutOperation);


	PlanarSketchPtr pSketch_6;
	sketches->raw_Add(wp->GetItem(1), false, &pSketch_6);

	SketchPointsPtr skPoints_6;
	SketchCirclesPtr skCircles_6;
	SketchLinesPtr skLines_6;
	SketchArcsPtr skArcs_6;
	ProfilesPtr skProfiles_6;

	pSketch_6->get_SketchPoints(&skPoints_6);
	pSketch_6->get_SketchCircles(&skCircles_6);
	pSketch_6->get_SketchArcs(&skArcs_6);
	pSketch_6->get_SketchLines(&skLines_6);
	pSketch_6->get_Profiles(&skProfiles_6);


	SketchPointPtr point_6[12];
	SketchCirclePtr circ_6;
	SketchArcPtr arc_6[4];
	SketchLinePtr lines_6[4];


	point_6[0] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3/10, D3/20), false);
	point_6[1] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10, D3/20+RR/10), false);
	point_6[2] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR /10, D3 / 20 + RR / 10), false);
	arc_6[0] = skArcs_6->MethodAddByCenterStartEndPoint(point_6[1], point_6[0], point_6[2], false);

	point_6[3] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10, D3 / 20 + RR / 10 + L1/10), false);
	point_6[4] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10, D3 / 20 + RR / 10 + L1 / 10 ), false);
	point_6[5] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10), false);
	arc_6[1] = skArcs_6->MethodAddByCenterStartEndPoint(point_6[4], point_6[3], point_6[5], true);

	point_6[6] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7/10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10), false);
	point_6[7] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7 / 10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10 - R12/10), false);
	point_6[8] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7 / 10 - R12/10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10 - R12 / 10), false);
	arc_6[2] = skArcs_6->MethodAddByCenterStartEndPoint(point_6[7], point_6[6], point_6[8], true);

	point_6[9] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7 / 10 - R12 / 10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10 - R12 / 10 - L1/10), false);
	point_6[10] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7 / 10 - R12 / 10 - RR/10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10 - R12 / 10 - L1 / 10 ), false);
	point_6[11] = skPoints_6->MethodAdd(pTransGeom->MethodCreatePoint2d(H3 / 10 - RR / 10 - R12 / 10 - H7 / 10 - R12 / 10 - RR/10, D3 / 20 + RR / 10 + L1 / 10 + R12 / 10 - R12 / 10 - L1 / 10 - RR / 10), false);
	arc_6[3] = skArcs_6->MethodAddByCenterStartEndPoint(point_6[10], point_6[9], point_6[11], false);


	lines_6[0] = skLines_6->MethodAddByTwoPoints(point_6[0], point_6[11]);
	lines_6[1] = skLines_6->MethodAddByTwoPoints(point_6[2], point_6[3]);
	lines_6[2] = skLines_6->MethodAddByTwoPoints(point_6[5], point_6[6]);
	lines_6[3] = skLines_6->MethodAddByTwoPoints(point_6[8], point_6[9]);

	ProfilePtr pProfile_6;
try
{
	pProfile_6 = skProfiles_6->MethodAddForSolid(true);
}
catch (...)
{
	AfxMessageBox(L"Ошибочный контур!");
	return;
}


	CoilFeaturesPtr Featuresptr;
	ft->get_CoilFeatures(&Featuresptr);


	CoilFeaturePtr Coil = Featuresptr->MethodAddByPitchAndHeight(pProfile_6, wax->GetItem(2), S1/10, H6/10, kJoinOperation, true, true, 0, true, 0, 0, true, 0, 0);

}





void CMFCApplication3Dlg::OnBnClickedButton1()
{
	//SelectSetPtr pSelect;
	//pPartDoc->get_SelectSet(&pSelect);

	//if (pSelect->GetCount() > 0)
	//{
	//	FacePtr Seekface = pSelect->GetItem(1);

	//	int seeknumber = -1;
	//	for (int i = 1; i <= pPartComDef->SurfaceBodies->GetCount(); i++)
	//	{
	//		SurfaceBodyPtr SurfBody;
	//		SurfaceBodiesPtr SurfBodies;

	//		pPartComDef->get_SurfaceBodies(&SurfBodies);

	//		SurfBodies->get_Item(i, &SurfBody);

	//		FacePtr face;
	//		FacesPtr faces;

	//		SurfBody->get_Faces(&faces);
	//		int N = 0;
	//		int N = SurfBody->Faces->GetCount();
	//		for (int j = 1; j <= SurfBody->Faces->GetCount(); j++) {
	//			faces->get_Item(j, &face);

	//			if (Seekface == face)
	//			{
	//				seeknumber = j;
	//				CString str;
	//				str.Format(L"%i", j);
	//				MessageBox(str);
	//			}
	//		}

	//	}

	//}
}







