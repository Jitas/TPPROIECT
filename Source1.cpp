#include <windows.h>
#include "resource1.h"
#include <string>
#include <time.h>
#define play 1
#define exit 2
#define instructiuni 3
#define solve 4
#define create 5
#define rezolva 6


const char g_szClassName[] = "myWindowClass";

HINSTANCE ghist;
HWND playb, exitb, instructiunib, img, solveb, createb;
HWND puzzle, solvebt;
HANDLE hBitmap;
HDC  hDC;
PAINTSTRUCT Ps;
HFONT font;
BOOL rec;
WNDCLASSW rwc = { 0 };
HWND hwnd;
HWND perspico[4][4];
int choice;

///////////////////////////////////////////////

//crearea ferestrei "puzzle"
void crearepuzzle()
{
	puzzle = CreateWindowW(rwc.lpszClassName,
		L"Puzzle",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
		790, 340, 400, 400,
		NULL, NULL, NULL, NULL);
}
//incarca imaginea de fundal
void LoadMyImage() {

	hBitmap = LoadImageW(NULL, L"F:\\proiect.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
}
//adauga imaginea incarcata ca fundal al paginii principale
void AdaugaImagine(HWND hwnd)
{
	LoadMyImage();

	img = CreateWindowW(L"Static", L"",
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		0, 100, 800, 600, hwnd, (HMENU)1, NULL, NULL);

	SendMessage(img, STM_SETIMAGE,
		(WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
}
//adauga textul din partea superioara a paginii principale
void AdaugaText(HWND hwnd)
{
	hDC = BeginPaint(hwnd, &Ps);

	font = CreateFont(46, 28, 0, 200,
		FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_ROMAN,
		"Times New Roman");

	SelectObject(hDC, font);
	TextOut(hDC, 0, 0, "Welcome to Perspico Solver", 30);
	DeleteObject(font);
	EndPaint(hwnd, &Ps);
}
//diferitele butoane ce se afla in componenta ferestrelor
void Butoanefereastraprincipala(HWND hwnd)
{
	createb = CreateWindowW(L"BUTTON", L"Create a new puzzle", WS_CHILD | WS_BORDER, 330, 280, 140, 30, hwnd, (HMENU)create, NULL, NULL);
	solveb = CreateWindowW(L"BUTTON", L"Solve a puzzle", WS_CHILD | WS_BORDER, 345, 330, 110, 30, hwnd, (HMENU)solve, NULL, NULL);
	playb = CreateWindowW(L"BUTTON", L"Play", WS_CHILD | WS_BORDER | WS_VISIBLE, 385, 280, 40, 30, hwnd, (HMENU)play, NULL, NULL);
	exitb = CreateWindowW(L"BUTTON", L"Exit", WS_CHILD | WS_BORDER | WS_VISIBLE, 385, 330, 40, 30, hwnd, (HMENU)exit, NULL, NULL);
	instructiunib = CreateWindowW(L"BUTTON", L"Help", WS_CHILD | WS_BORDER, 700, 650, 80, 30, hwnd, (HMENU)instructiuni, NULL, NULL);
	
}
void Butoanepuzzle(HWND puzzle)
{
	solvebt = CreateWindowW(L"BUTTON", L"Solve", WS_CHILD | WS_BORDER|WS_VISIBLE, 300, 10, 50, 30, puzzle, (HMENU)rezolva, NULL, NULL);

}
// actiunile defasurate la apasarea fiecarui buton
void NewGame()
{
	ShowWindow(createb, SW_HIDE);
	ShowWindow(solveb, SW_HIDE);
	ShowWindow(exitb, SW_SHOW);
	ShowWindow(playb, SW_SHOW);
}
void Play()
{
	ShowWindow(instructiunib, SW_SHOW);
	ShowWindow(exitb, SW_HIDE);
	ShowWindow(playb, SW_HIDE);
	ShowWindow(createb, SW_SHOW);
	ShowWindow(solveb, SW_SHOW);

}
void Create(HWND hwnd)
{
	ShowWindow(createb, SW_HIDE);
	ShowWindow(solveb, SW_HIDE);
	ShowWindow(hwnd, SW_HIDE);
	choice = 1;
	crearepuzzle();
}
void Solve(HWND hwnd)
{
	ShowWindow(createb, SW_HIDE);
	ShowWindow(solveb, SW_HIDE);
	ShowWindow(hwnd, SW_HIDE);
	crearepuzzle();
}

/////////////////////////////////////////////////////////////
int mat[4][4];
int configuratie[4][4] = { {1,2,3,4},
                           {5,6,7,8},
                           {9,10,11,12},
                           {13,14,15,0},
                          };
int miscari[4][2] = {
	 {1,0},
	{0,-1},
	{-1,0},
	{0,1},
};
//convertim textul introdus in tabla de joc in numere si verificam daca acestea au fost introduse corect de catre utilizator
struct tree
{
	int x;
	tree* dr;
	tree* stg;
};

tree* creare(int y)
{
	tree* p = (tree*)malloc(sizeof(tree));
	p->x = y;
	p->dr = NULL;
	p->stg = NULL;
	return p;
}

int verificare(tree* root, int y)
{
	if (root == NULL) return 1;
	if (root->x == y) return 0;
	if (verificare(root->stg, y) == 0) return 0;
	if (verificare(root->dr, y) == 0) return 0;
	return 1;
}

tree* adaugare(tree* root, int y)
{

		if (root == NULL)
		{
			root = creare(y);
		}
		else

			if (root->x > y)
			{
				root->stg = adaugare(root->stg, y);
			}
			else
			{
				root->dr = adaugare(root->dr, y);
			}

	
	
	return root;
}

void initializarematrice_solvepuzzle()
{
	int i, j,out=0,k=0;
	char retin[10];
	tree* root = NULL;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			GetWindowText(perspico[i][j], retin, 10);
			mat[i][j] = atoi(retin);
			if (mat[i][j] == 0)
			{
				k++;
			}
			if (k > 1)
			{
				MessageBox(NULL, "NU ati completat tot puzzle-lul", "Error!",
					MB_ICONEXCLAMATION | MB_OK);
				out = 1;
				break;
			}
			else

			if (verificare(root, mat[i][j]))
				root = adaugare(root, mat[i][j]);
			else
			{
				MessageBox(NULL, "Ati introdus un numar de 2 sau mai multe ori", "Error!",
					MB_ICONEXCLAMATION | MB_OK);
				out = 1;
				break;
			}

		}
		if (out == 1) break;
	}
}
void initializarematrice_crearenewgame()
{
	int i, j;
	tree *root = NULL;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
		back: srand(time(NULL));

			mat[i][j] = rand() % 20;
			if (!verificare(root, mat[i][j]))
			{
				goto back;
			}
			else
			{
				root = adaugare(root, mat[i][j]);
			}
		}
}

/////////////////////////////////////////////////////////

LRESULT CALLBACK PuzzleProc(HWND puzzle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
	case WM_CREATE:
		int i, j;
		if (choice)
		{
			char ret[4];
						
			initializarematrice_crearenewgame();


			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					_itoa_s(mat[i][j], ret, 4);

					perspico[i][j] = CreateWindow("STATIC", ret, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
						10 + i * 50, 10 + j * 50, 50, 50, puzzle, NULL, NULL, NULL);
				}
		 }
		else
		{
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{

					perspico[i][j] = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
						10 + i * 50, 10 + j * 50, 50, 50, puzzle, NULL, NULL, NULL);
				}
		}
		//buttons
		Butoanepuzzle(puzzle);
	
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_GAME_NEWGAME:
			ShowWindow(puzzle, SW_HIDE);
			ShowWindow(hwnd, SW_SHOW);
			NewGame();
			break;
		case rezolva:
			initializarematrice_solvepuzzle();
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(puzzle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(puzzle, msg, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		//Images:
		AdaugaImagine(hwnd);
		//buttons:
		Butoanefereastraprincipala(hwnd);
		break;

	case WM_PAINT:
		AdaugaText(hwnd);
 		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		   case ID_GAME_NEWGAME:
			   NewGame();
		   break;
 
		   case play:
			   Play();
		   break;

		   case create:
			 //genereaza un puzzle random pentru a fi rezolvat
			   Create(hwnd);
		   break;
		   case solve:
			 //il lasa pe utilizator sa introduca el configuratia jocului dorit
			   Solve(hwnd);
		   break;

		   case exit:
			 DestroyWindow(hwnd);
		   break;
			   }
	    break;
	
    case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG Msg;
	//firtwindow;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, NULL);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, NULL);


	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"PERSPICO SOLVER",
		WS_OVERLAPPEDWINDOW,
		590, 165, 800, 750,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//puzzle window
	rwc.lpszMenuName =(LPCWSTR) MAKEINTRESOURCE(IDR_MENU1);
	rwc.lpfnWndProc = PuzzleProc;
	rwc.hInstance = hInstance;
	rwc.hCursor = LoadCursor(NULL, IDC_HAND);
	rwc.hbrBackground =(HBRUSH)CreateSolidBrush(RGB(2,2,128));
	rwc.lpszClassName = L"puzzle";

	RegisterClassW(&rwc);
	

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;

}
