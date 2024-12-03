
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  return WinMain_0(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}


int __stdcall WinMain_0(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  int v4; // ebx
  const WCHAR *CommandLineW; // rax
  LPWSTR *v6; // rdi
  _QWORD *v8; // r14
  int v9; // eax
  CHAR **v10; // r12
  signed __int64 v11; // r13
  int v12; // r14d
  const WCHAR *v13; // rbp
  int cbMultiByte; // edi
  CHAR *lpMultiByteStr; // rsi
  int v16; // esi
  void **v17; // rdi
  int pNumArgs; // [rsp+90h] [rbp+8h] BYREF
  _QWORD *v19; // [rsp+A0h] [rbp+18h]
  LPWSTR *v20; // [rsp+A8h] [rbp+20h]

  v4 = 0;
  pNumArgs = 0;
  CommandLineW = GetCommandLineW();
  v20 = CommandLineToArgvW(CommandLineW, &pNumArgs);
  v6 = v20;
  if ( !v20 )
    return -1;
  v8 = operator new(saturated_mul(pNumArgs + 1, 8ui64));
  v19 = v8;
  v9 = pNumArgs;
  if ( pNumArgs )
  {
    v10 = (CHAR **)v8;
    v11 = (char *)v6 - (char *)v8;
    v12 = 0;
    do
    {
      v13 = *(const WCHAR **)((char *)v10 + v11);
      cbMultiByte = WideCharToMultiByte(0, 0, v13, -1, 0i64, 0, 0i64, 0i64);
      lpMultiByteStr = (CHAR *)operator new(cbMultiByte);
      WideCharToMultiByte(0, 0, v13, -1, lpMultiByteStr, cbMultiByte, 0i64, 0i64);
      *v10++ = lpMultiByteStr;
      v9 = pNumArgs;
      ++v12;
    }
    while ( v12 != pNumArgs );
    v8 = v19;
    v6 = v20;
  }
  v8[v9] = 0i64;
  LocalFree(v6);
  v16 = sub_140001000((unsigned int)pNumArgs, v8);
  if ( pNumArgs )
  {
    v17 = (void **)v8;
    do
    {
      if ( !*v17 )
        break;
      j_j_free(*v17);
      ++v4;
      ++v17;
    }
    while ( v4 != pNumArgs );
  }
  j_j_free(v8);
  return v16;
}

__int64 __fastcall sub_140001000(int a1, char **a2)     //好像就是展示窗口
{
  unsigned int v2; // ebx
  int v4; // [rsp+20h] [rbp-E8h] BYREF
  char v5[24]; // [rsp+28h] [rbp-E0h] BYREF
  int v6[44]; // [rsp+40h] [rbp-C8h] BYREF

  v4 = a1;
  QApplication::QApplication((QApplication *)v5, &v4, a2, 394497);
  sub_140001090((__int64)v6, 0i64);
  QWidget::show((QWidget *)v6);
  v2 = QApplication::exec();
  sub_1400011D0((__int64)v6);
  QApplication::~QApplication((QApplication *)v5);
  return v2;
}

__int64 __fastcall sub_140001090(__int64 a1, __int64 a2)//好像是主窗口的准备工作
{
  QTime *v3; // rax
  unsigned int v4; // eax
  char v6[40]; // [rsp+20h] [rbp-28h] BYREF
  char v7; // [rsp+60h] [rbp+18h] BYREF

  QMainWindow::QMainWindow(a1, a2, 0i64);       
  *(_QWORD *)a1 = &MainWindow::`vftable';
  *(_QWORD *)(a1 + 16) = &MainWindow::`vftable';
  *(_QWORD *)(a1 + 40) = operator new(0x40ui64);
  *(_DWORD *)(a1 + 48) = 0;
  *(_DWORD *)(a1 + 52) = 2;
  QString::QString((QString *)(a1 + 56), "aHFrcWstMjE4MjMtamNoZGts");
  QString::QString((QString *)(a1 + 80), "YWJjZGUtMzg0ODMta2RraHly");
  QString::QString((QString *)(a1 + 104), "YWJjZGUtMTIzNDUtZ2hpamts");
  QString::QString((QString *)(a1 + 128), "eHh4eXktMTIzNDUtamtvcG1w");
  QString::QString((QString *)(a1 + 152), "UXRmdW4tMTAwODYtR1VJdG9v");
  sub_1400015E0(*(struct QWidget ***)(a1 + 40), (QWidget *)a1);
  QLineEdit::setReadOnly(*(QLineEdit **)(*(_QWORD *)(a1 + 40) + 8i64), 1);
  QLineEdit::setReadOnly(*(QLineEdit **)(*(_QWORD *)(a1 + 40) + 24i64), 1);
  QString::QString((QString *)v6, "Click");
  QWidget::setWindowTitle((QWidget *)a1, (const struct QString *)v6);
  QString::~QString(v6);
  v3 = (QTime *)QTime::currentTime(&v7);
  v4 = QTime::msec(v3);
  srand(v4);
  *(_DWORD *)(a1 + 52) = rand() % 4;
  return a1;
}

void __fastcall sub_1400011D0(__int64 a1)       //像是析构函数
{
  *(_QWORD *)a1 = &MainWindow::`vftable';
  *(_QWORD *)(a1 + 16) = &MainWindow::`vftable';
  j_j_free(*(void **)(a1 + 40));
  `eh vector destructor iterator'((char *)(a1 + 56), 24i64, 5i64, QString::~QString);
  QMainWindow::~QMainWindow((QMainWindow *)a1);
}


void __fastcall sub_140001480(__int64 a1)       //我猜这玩意是判断点击次数
{
  __int64 v2; // rdx
  QLabel *v3; // rbx
  const struct QString *v4; // rax
  QLineEdit *v5; // rbx
  const struct QByteArray *v6; // rax
  char v7[24]; // [rsp+30h] [rbp-58h] BYREF
  char v8[24]; // [rsp+48h] [rbp-40h] BYREF
  char v9[40]; // [rsp+60h] [rbp-28h] BYREF

  v2 = (unsigned int)(*(_DWORD *)(a1 + 48) + 1);
  *(_DWORD *)(a1 + 48) = v2;
  v3 = *(QLabel **)(*(_QWORD *)(a1 + 40) + 40i64);
  v4 = (const struct QString *)QString::number(v9, v2, 10i64);
  QLabel::setText(v3, v4);
  QString::~QString(v9);
  if ( *(_DWORD *)(a1 + 48) == 1000 )
  {
    QString::toLatin1(a1 + 8 * (*(int *)(a1 + 52) + 2i64 * *(int *)(a1 + 52) + 7), v9);
    v5 = *(QLineEdit **)(*(_QWORD *)(a1 + 40) + 24i64);
    v6 = (const struct QByteArray *)QByteArrayw::fromBase64(v8, v9, 0i64);
    QString::QString((QString *)v7, v6);
    QLineEdit::setText(v5, (const struct QString *)v7);
    QString::~QString(v7);
    QByteArray::~QByteArray((QByteArray *)v8);
    QWidget::setEnabled(*(QWidget **)(*(_QWORD *)(a1 + 40) + 16i64), 0);
    QString::QString((QString *)v8, "You got a flag now, but is it true?");
    QString::QString((QString *)v7, "Oops");
    QMessageBox::warning(a1, v7, v8, 1024i64, 0);
    QString::~QString(v7);
    QString::~QString(v8);
    QByteArray::~QByteArray((QByteArray *)v9);
  }
}


__int64 __fastcall sub_140001E10(__int64 a1, int a2, __int64 a3, _QWORD **a4)
{
  __int64 result; // rax
  unsigned int v8; // ebx
  __int64 v9[3]; // [rsp+20h] [rbp-18h] BYREF

  result = QMainWindow::qt_metacall();
  v8 = result;
  if ( (int)result >= 0 )
  {
    if ( a2 )
    {
      if ( a2 != 7 )
        return v8;
      if ( (int)result < 1 )
      {
        v9[0] = 0i64;
        **a4 = *(_QWORD *)QMetaType::QMetaType((QMetaType *)v9);
      }
    }
    else if ( (int)result < 1 )
    {
      sub_140001480(a1);
    }
    --v8;
    return v8;
  }
  return result;
}

__int64 sub_140003080()
{
  int v5; // r11d
  int v6; // r9d
  int v7; // esi
  int v9; // r10d
  int v14; // edi
  int v15; // eax
  unsigned __int64 v16; // rax
  __int64 v17; // rcx
  int v18; // r8d
  int v23; // eax
  char v25; // [rsp+20h] [rbp+8h]

  _RAX = 0i64;
  __asm { cpuid }
  v5 = 0;
  v6 = _RBX;
  v7 = _RAX;
  _RAX = 1i64;
  v9 = _RCX ^ 0x6C65746E | _RDX ^ 0x49656E69;
  __asm { cpuid }
  v14 = _RCX;
  if ( !(v6 ^ 0x756E6547 | v9)
    && ((qword_14000A110 = -1i64, v15 = _RAX & 0xFFF3FF0, qword_14000A108 = 0x8000i64, v15 == 67264)
     || v15 == 132704
     || v15 == 132720
     || (v16 = (unsigned int)(v15 - 198224), (unsigned int)v16 <= 0x20) && (v17 = 0x100010001i64, _bittest64(&v17, v16))) )
  {
    v18 = dword_14000A954 | 1;
    dword_14000A954 |= 1u;
  }
  else
  {
    v18 = dword_14000A954;
  }
  _RAX = 7i64;
  if ( v7 >= 7 )
  {
    __asm { cpuid }
    v5 = _RBX;
    if ( (_RBX & 0x200) != 0 )
      dword_14000A954 = v18 | 2;
  }
  dword_14000A100 = 1;
  dword_14000A104 = 2;
  if ( (v14 & 0x100000) != 0 )
  {
    dword_14000A100 = 2;
    dword_14000A104 = 6;
    if ( (v14 & 0x8000000) != 0 && (v14 & 0x10000000) != 0 )
    {
      __asm { xgetbv }
      v25 = _RAX;
      if ( (_RAX & 6) == 6 )
      {
        v23 = dword_14000A104 | 8;
        dword_14000A100 = 3;
        dword_14000A104 |= 8u;
        if ( (v5 & 0x20) != 0 )
        {
          dword_14000A100 = 5;
          dword_14000A104 = v23 | 0x20;
          if ( (v5 & 0xD0030000) == -805109760 && (v25 & 0xE0) == 0xE0 )
          {
            dword_14000A104 |= 0x40u;
            dword_14000A100 = 6;
          }
        }
      }
    }
  }
  return 0i64;
}

void __fastcall sub_1400015E0(struct QWidget **a1, QWidget *a2)     //好像就是构建主窗口
{
  __int64 v4; // rbx
  _BYTE *v5; // rax
  _BYTE *v6; // rcx
  struct QWidget *v7; // rbx
  _BYTE *v8; // rax
  _BYTE *v9; // rcx
  QLineEdit *v10; // rbx
  _BYTE *v11; // rax
  _BYTE *v12; // rcx
  QWidget *v13; // rbx
  const struct QRect *v14; // rax
  QPushButton *v15; // rbx
  _BYTE *v16; // rax
  _BYTE *v17; // rcx
  QWidget *v18; // rbx
  const struct QRect *v19; // rax
  QLineEdit *v20; // rbx
  _BYTE *v21; // rax
  _BYTE *v22; // rcx
  QWidget *v23; // rbx
  const struct QRect *v24; // rax
  struct QWidget *v25; // rbx
  _BYTE *v26; // rax
  _BYTE *v27; // rcx
  QWidget *v28; // rbx
  const struct QRect *v29; // rax
  struct QWidget *v30; // rbx
  const char *v31; // rax
  const char *v32; // rcx
  QWidget *v33; // rbx
  const struct QRect *v34; // rax
  QMenuBar *v35; // rbx
  const char *v36; // rax
  const char *v37; // rcx
  QWidget *v38; // rbx
  const struct QRect *v39; // rax
  QStatusBar *v40; // rbx
  _BYTE *v41; // rax
  _BYTE *v42; // rcx
  const struct QString *v43; // rax
  QLineEdit *v44; // rbx
  const struct QString *v45; // rax
  QAbstractButton *v46; // rbx
  const struct QString *v47; // rax
  QLineEdit *v48; // rbx
  const struct QString *v49; // rax
  QLabel *v50; // rbx
  const struct QString *v51; // rax
  QLabel *v52; // rbx
  const struct QString *v53; // rax
  char v54[16]; // [rsp+30h] [rbp-40h] BYREF
  char v55[16]; // [rsp+40h] [rbp-30h] BYREF
  const char *v56; // [rsp+50h] [rbp-20h] BYREF
  signed __int64 v57; // [rsp+58h] [rbp-18h]

  v4 = *(_QWORD *)(QObject::objectName(a2, &v56) + 16);
  QString::~QString(&v56);
  if ( !v4 )
  {
    v5 = memchr("MainWindow", 0, 0xBui64);
    v6 = &unk_14000552B;
    if ( v5 )
      v6 = v5;
    v56 = "MainWindow";
    v57 = v6 - "MainWindow";
    QObject::setObjectName(a2, &v56);
  }
  QWidget::resize(a2, 548, 396);
  v7 = (struct QWidget *)operator new(0x28ui64);
  QWidget::QWidget(v7, a2, 0i64);
  *(_QWORD *)v7 = &QWidget::`vftable';
  *((_QWORD *)v7 + 2) = &QWidget::`vftable';
  *a1 = v7;
  v8 = memchr("centralwidget", 0, 0xEui64);
  v9 = &unk_14000553E;
  if ( v8 )
    v9 = v8;
  v56 = "centralwidget";
  v57 = v9 - "centralwidget";
  QObject::setObjectName(v7, &v56);
  v10 = (QLineEdit *)operator new(0x28ui64);
  QLineEdit::QLineEdit(v10, *a1);
  *(_QWORD *)v10 = &QLineEdit::`vftable';
  *((_QWORD *)v10 + 2) = &QLineEdit::`vftable';
  a1[1] = v10;
  v11 = memchr("lineEdit", 0, 9ui64);
  v12 = &unk_140005549;
  if ( v11 )
    v12 = v11;
  v56 = "lineEdit";
  v57 = v12 - "lineEdit";
  QObject::setObjectName(v10, &v56);
  v13 = a1[1];
  v14 = QRect::QRect((QRect *)&v56, 40, 50, 471, 41);
  QWidget::setGeometry(v13, v14);
  QFont::QFont((QFont *)v55);
  QFont::setPointSize((QFont *)v55, 16);
  QWidget::setFont(a1[1], (const struct QFont *)v55);
  QLineEdit::setAlignment(a1[1], 132i64);
  v15 = (QPushButton *)operator new(0x28ui64);
  QPushButton::QPushButton(v15, *a1);
  *(_QWORD *)v15 = &QPushButton::`vftable';
  *((_QWORD *)v15 + 2) = &QPushButton::`vftable';
  a1[2] = v15;
  v16 = memchr("pushButton", 0, 0xBui64);
  v17 = &unk_14000555B;
  if ( v16 )
    v17 = v16;
  v56 = "pushButton";
  v57 = v17 - "pushButton";
  QObject::setObjectName(v15, &v56);
  v18 = a1[2];
  v19 = QRect::QRect((QRect *)&v56, 170, 270, 201, 61);
  QWidget::setGeometry(v18, v19);
  QFont::QFont((QFont *)v54);
  QFont::setPointSize((QFont *)v54, 12);
  QWidget::setFont(a1[2], (const struct QFont *)v54);
  v20 = (QLineEdit *)operator new(0x28ui64);
  QLineEdit::QLineEdit(v20, *a1);
  *(_QWORD *)v20 = &QLineEdit::`vftable';
  *((_QWORD *)v20 + 2) = &QLineEdit::`vftable';
  a1[3] = v20;
  v21 = memchr("flag", 0, 5ui64);
  v22 = &unk_140005561;
  if ( v21 )
    v22 = v21;
  v56 = "flag";
  v57 = v22 - "flag";
  QObject::setObjectName(v20, &v56);
  v23 = a1[3];
  v24 = QRect::QRect((QRect *)&v56, 40, 140, 471, 41);
  QWidget::setGeometry(v23, v24);
  QWidget::setFont(a1[3], (const struct QFont *)v55);
  QLineEdit::setAlignment(a1[3], 132i64);
  v25 = (struct QWidget *)operator new(0x28ui64);
  QLabel::QLabel(v25, *a1, 0i64);
  *(_QWORD *)v25 = &QLabel::`vftable';
  *((_QWORD *)v25 + 2) = &QLabel::`vftable';
  a1[4] = v25;
  v26 = memchr("label", 0, 6ui64);
  v27 = &unk_14000556A;
  if ( v26 )
    v27 = v26;
  v56 = "label";
  v57 = v27 - "label";
  QObject::setObjectName(v25, &v56);
  v28 = a1[4];
  v29 = QRect::QRect((QRect *)&v56, 100, 210, 141, 41);
  QWidget::setGeometry(v28, v29);
  QWidget::setFont(a1[4], (const struct QFont *)v54);
  QLabel::setAlignment(a1[4], 132i64);
  v30 = (struct QWidget *)operator new(0x28ui64);
  QLabel::QLabel(v30, *a1, 0i64);
  *(_QWORD *)v30 = &QLabel::`vftable';
  *((_QWORD *)v30 + 2) = &QLabel::`vftable';
  a1[5] = v30;
  v31 = (const char *)memchr("label_2", 0, 8ui64);
  v32 = "menubar";
  if ( v31 )
    v32 = v31;
  v56 = "label_2";
  v57 = v32 - "label_2";
  QObject::setObjectName(v30, &v56);
  v33 = a1[5];
  v34 = QRect::QRect((QRect *)&v56, 240, 210, 141, 41);
  QWidget::setGeometry(v33, v34);
  QWidget::setFont(a1[5], (const struct QFont *)v54);
  QLabel::setAlignment(a1[5], 129i64);
  QMainWindow::setCentralWidget(a2, *a1);
  v35 = (QMenuBar *)operator new(0x28ui64);
  QMenuBar::QMenuBar(v35, a2);
  *(_QWORD *)v35 = &QMenuBar::`vftable';
  *((_QWORD *)v35 + 2) = &QMenuBar::`vftable';
  a1[6] = v35;
  v36 = (const char *)memchr("menubar", 0, 8ui64);
  v37 = "statusbar";
  if ( v36 )
    v37 = v36;
  v56 = "menubar";
  v57 = v37 - "menubar";
  QObject::setObjectName(v35, &v56);
  v38 = a1[6];
  v39 = QRect::QRect((QRect *)&v56, 0, 0, 548, 19);
  QWidget::setGeometry(v38, v39);
  QMainWindow::setMenuBar(a2, a1[6]);
  v40 = (QStatusBar *)operator new(0x28ui64);
  QStatusBar::QStatusBar(v40, a2);
  *(_QWORD *)v40 = &QStatusBar::`vftable';
  *((_QWORD *)v40 + 2) = &QStatusBar::`vftable';
  a1[7] = v40;
  v41 = memchr("statusbar", 0, 0xAui64);
  v42 = &unk_14000558A;
  if ( v41 )
    v42 = v41;
  v56 = "statusbar";
  v57 = v42 - "statusbar";
  QObject::setObjectName(v40, &v56);
  QMainWindow::setStatusBar(a2, a1[7]);
  v43 = (const struct QString *)QCoreApplication::translate(&v56, "MainWindow", "MainWindow", 0i64, -1);
  QWidget::setWindowTitle(a2, v43);
  QString::~QString(&v56);
  v44 = a1[1];
  v45 = (const struct QString *)QCoreApplication::translate(
                                  &v56,
                                  "MainWindow",
                                  "Click 1000 times and you will get the flag!",
                                  0i64,
                                  -1);
  QLineEdit::setText(v44, v45);
  QString::~QString(&v56);
  v46 = a1[2];
  v47 = (const struct QString *)QCoreApplication::translate(&v56, "MainWindow", "Click", 0i64, -1);
  QAbstractButton::setText(v46, v47);
  QString::~QString(&v56);
  v48 = a1[3];
  v49 = QString::QString((QString *)&v56);
  QLineEdit::setText(v48, v49);
  QString::~QString(&v56);
  v50 = a1[4];
  v51 = (const struct QString *)QCoreApplication::translate(&v56, "MainWindow", "Current hits:", 0i64, -1);
  QLabel::setText(v50, v51);
  QString::~QString(&v56);
  v52 = a1[5];
  v53 = QString::QString((QString *)&v56);
  QLabel::setText(v52, v53);
  QString::~QString(&v56);
  QMetaObject::connectSlotsByName(a2);
  QFont::~QFont((QFont *)v54);
  QFont::~QFont((QFont *)v55);
}


4*char = 1*Dword
          //1 Qword
a1 虚函数表
a1 + 40
a1 + 48   点击次数
a1 + 56,  "aH Fr cW st   Mj E4 Mj Mt   am No ZG ts";
a1 + 80,  "YW Jj ZG Ut   Mz g0 OD Mt   a2 Rr aH ly";
a1 + 104, "YW Jj ZG Ut   MT Iz ND Ut   Z2 hp am ts";
a1 + 128, "eH h4 eX kt   MT Iz ND Ut   am tv cG 1w";
a1 + 152, "UX Rm dW 4t   MT Aw OD Yt   R1 VJ dG 9v";

//本文档收录的函数有 main 1480 1090 1e10 15e0 11d0 1000 3080

//main-1000-1090-15e0
//        \
//         -11d0


Qtfun-10086-GUItoo