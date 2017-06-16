/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <boardwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QHBoxLayout *horizontalLayout_4;
    BoardWidget *boardView;
    QGroupBox *panel1;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    QPushButton *fillAndPivots;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *fillBoard;
    QPushButton *articulationPoint;
    QGridLayout *gridLayout_9;
    QSpinBox *mainX;
    QComboBox *mainType;
    QLabel *label_10;
    QLabel *label_11;
    QGridLayout *gridLayout_4;
    QSpinBox *mainProb;
    QSpinBox *mainSize;
    QLabel *label;
    QLabel *label_2;
    QWidget *tab2;
    QGridLayout *gridLayout_2;
    BoardWidget *boardViewSim;
    QGroupBox *panel2;
    QVBoxLayout *verticalLayout;
    QPushButton *simulatePivot;
    QGridLayout *gridLayout_10;
    QSpinBox *simX;
    QComboBox *simType;
    QLabel *label_9;
    QLabel *label_12;
    QGridLayout *gridLayout_6;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *simSize;
    QSpinBox *waitTimeSim;
    QProgressBar *progressBarSim;
    QWidget *tab4;
    QGridLayout *gridLayout;
    BoardWidget *gameView;
    QGroupBox *panel3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *startRandom;
    QPushButton *startAlternative;
    QFrame *line;
    QPushButton *nextRandomTurn;
    QPushButton *resetGame;
    QFrame *line_3;
    QGridLayout *gridLayout_11;
    QSpinBox *gameX;
    QComboBox *gameType;
    QLabel *label_13;
    QLabel *label_14;
    QGridLayout *gridLayout_7;
    QSpinBox *gameWaitTime;
    QLabel *label_7;
    QLabel *label_3;
    QSpinBox *gameProb;
    QFrame *line_2;
    QPushButton *moveWhite;
    QPushButton *moveBlack;
    QGridLayout *gridLayout_5;
    QSpinBox *gameSize;
    QLabel *label_4;
    QProgressBar *gameProgress;
    BoardWidget *gameViewSim;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 800);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        horizontalLayout_4 = new QHBoxLayout(tab1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        boardView = new BoardWidget(tab1);
        boardView->setObjectName(QString::fromUtf8("boardView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(boardView->sizePolicy().hasHeightForWidth());
        boardView->setSizePolicy(sizePolicy1);
        boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boardView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
        boardView->setCacheMode(QGraphicsView::CacheBackground);

        horizontalLayout_4->addWidget(boardView);

        panel1 = new QGroupBox(tab1);
        panel1->setObjectName(QString::fromUtf8("panel1"));
        verticalLayout_3 = new QVBoxLayout(panel1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(panel1);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        fillAndPivots = new QPushButton(frame);
        fillAndPivots->setObjectName(QString::fromUtf8("fillAndPivots"));

        gridLayout_3->addWidget(fillAndPivots, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        gridLayout_3->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        fillBoard = new QPushButton(frame);
        fillBoard->setObjectName(QString::fromUtf8("fillBoard"));

        verticalLayout_4->addWidget(fillBoard);

        articulationPoint = new QPushButton(frame);
        articulationPoint->setObjectName(QString::fromUtf8("articulationPoint"));

        verticalLayout_4->addWidget(articulationPoint);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        mainX = new QSpinBox(frame);
        mainX->setObjectName(QString::fromUtf8("mainX"));
        mainX->setMinimum(1);
        mainX->setMaximum(19);

        gridLayout_9->addWidget(mainX, 1, 1, 1, 1);

        mainType = new QComboBox(frame);
        mainType->setObjectName(QString::fromUtf8("mainType"));

        gridLayout_9->addWidget(mainType, 0, 1, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_9->addWidget(label_10, 0, 0, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_9->addWidget(label_11, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_9);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        mainProb = new QSpinBox(frame);
        mainProb->setObjectName(QString::fromUtf8("mainProb"));
        mainProb->setMinimum(1);
        mainProb->setMaximum(100);
        mainProb->setValue(50);

        gridLayout_4->addWidget(mainProb, 0, 1, 1, 1);

        mainSize = new QSpinBox(frame);
        mainSize->setObjectName(QString::fromUtf8("mainSize"));
        mainSize->setMinimum(2);
        mainSize->setMaximum(19);
        mainSize->setValue(11);

        gridLayout_4->addWidget(mainSize, 1, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1, Qt::AlignRight);


        verticalLayout_2->addLayout(gridLayout_4);


        verticalLayout_3->addWidget(frame);


        horizontalLayout_4->addWidget(panel1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        gridLayout_2 = new QGridLayout(tab2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        boardViewSim = new BoardWidget(tab2);
        boardViewSim->setObjectName(QString::fromUtf8("boardViewSim"));
        sizePolicy1.setHeightForWidth(boardViewSim->sizePolicy().hasHeightForWidth());
        boardViewSim->setSizePolicy(sizePolicy1);
        boardViewSim->setFrameShape(QFrame::WinPanel);
        boardViewSim->setFrameShadow(QFrame::Raised);
        boardViewSim->setLineWidth(6);
        boardViewSim->setMidLineWidth(6);
        boardViewSim->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boardViewSim->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boardViewSim->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
        boardViewSim->setCacheMode(QGraphicsView::CacheBackground);

        gridLayout_2->addWidget(boardViewSim, 0, 0, 1, 1);

        panel2 = new QGroupBox(tab2);
        panel2->setObjectName(QString::fromUtf8("panel2"));
        panel2->setAutoFillBackground(false);
        panel2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(panel2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        simulatePivot = new QPushButton(panel2);
        simulatePivot->setObjectName(QString::fromUtf8("simulatePivot"));
        simulatePivot->setAutoFillBackground(false);

        verticalLayout->addWidget(simulatePivot);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        simX = new QSpinBox(panel2);
        simX->setObjectName(QString::fromUtf8("simX"));
        simX->setMinimum(1);
        simX->setMaximum(19);

        gridLayout_10->addWidget(simX, 1, 1, 1, 1);

        simType = new QComboBox(panel2);
        simType->setObjectName(QString::fromUtf8("simType"));

        gridLayout_10->addWidget(simType, 0, 1, 1, 1);

        label_9 = new QLabel(panel2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_10->addWidget(label_9, 0, 0, 1, 1);

        label_12 = new QLabel(panel2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_10->addWidget(label_12, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_10);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_5 = new QLabel(panel2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_6->addWidget(label_5, 0, 0, 1, 1, Qt::AlignRight);

        label_6 = new QLabel(panel2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_6->addWidget(label_6, 1, 0, 1, 1, Qt::AlignRight);

        simSize = new QSpinBox(panel2);
        simSize->setObjectName(QString::fromUtf8("simSize"));
        simSize->setMinimum(1);
        simSize->setMaximum(19);
        simSize->setValue(11);

        gridLayout_6->addWidget(simSize, 0, 2, 1, 1);

        waitTimeSim = new QSpinBox(panel2);
        waitTimeSim->setObjectName(QString::fromUtf8("waitTimeSim"));
        waitTimeSim->setMaximum(2000);
        waitTimeSim->setSingleStep(100);

        gridLayout_6->addWidget(waitTimeSim, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_6);


        gridLayout_2->addWidget(panel2, 0, 1, 1, 1);

        progressBarSim = new QProgressBar(tab2);
        progressBarSim->setObjectName(QString::fromUtf8("progressBarSim"));
        progressBarSim->setEnabled(true);
        progressBarSim->setAutoFillBackground(false);
        progressBarSim->setStyleSheet(QString::fromUtf8(""));
        progressBarSim->setValue(24);
        progressBarSim->setTextVisible(true);
        progressBarSim->setInvertedAppearance(false);

        gridLayout_2->addWidget(progressBarSim, 1, 0, 1, 1);

        tabWidget->addTab(tab2, QString());
        tab4 = new QWidget();
        tab4->setObjectName(QString::fromUtf8("tab4"));
        tab4->setEnabled(true);
        gridLayout = new QGridLayout(tab4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gameView = new BoardWidget(tab4);
        gameView->setObjectName(QString::fromUtf8("gameView"));
        gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gameView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);

        gridLayout->addWidget(gameView, 0, 0, 1, 1);

        panel3 = new QGroupBox(tab4);
        panel3->setObjectName(QString::fromUtf8("panel3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(panel3->sizePolicy().hasHeightForWidth());
        panel3->setSizePolicy(sizePolicy3);
        panel3->setMinimumSize(QSize(200, 686));
        verticalLayout_5 = new QVBoxLayout(panel3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        startRandom = new QPushButton(panel3);
        startRandom->setObjectName(QString::fromUtf8("startRandom"));

        verticalLayout_5->addWidget(startRandom);

        startAlternative = new QPushButton(panel3);
        startAlternative->setObjectName(QString::fromUtf8("startAlternative"));

        verticalLayout_5->addWidget(startAlternative);

        line = new QFrame(panel3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        nextRandomTurn = new QPushButton(panel3);
        nextRandomTurn->setObjectName(QString::fromUtf8("nextRandomTurn"));

        verticalLayout_5->addWidget(nextRandomTurn);

        resetGame = new QPushButton(panel3);
        resetGame->setObjectName(QString::fromUtf8("resetGame"));

        verticalLayout_5->addWidget(resetGame);

        line_3 = new QFrame(panel3);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_3);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gameX = new QSpinBox(panel3);
        gameX->setObjectName(QString::fromUtf8("gameX"));
        gameX->setMinimum(1);
        gameX->setMaximum(19);

        gridLayout_11->addWidget(gameX, 1, 1, 1, 1);

        gameType = new QComboBox(panel3);
        gameType->setObjectName(QString::fromUtf8("gameType"));

        gridLayout_11->addWidget(gameType, 0, 1, 1, 1);

        label_13 = new QLabel(panel3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_11->addWidget(label_13, 0, 0, 1, 1);

        label_14 = new QLabel(panel3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_11->addWidget(label_14, 1, 0, 1, 1);


        verticalLayout_5->addLayout(gridLayout_11);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gameWaitTime = new QSpinBox(panel3);
        gameWaitTime->setObjectName(QString::fromUtf8("gameWaitTime"));

        gridLayout_7->addWidget(gameWaitTime, 0, 1, 1, 1);

        label_7 = new QLabel(panel3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_7->addWidget(label_7, 0, 0, 1, 1, Qt::AlignRight);

        label_3 = new QLabel(panel3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(label_3, 1, 0, 1, 1);

        gameProb = new QSpinBox(panel3);
        gameProb->setObjectName(QString::fromUtf8("gameProb"));
        gameProb->setMinimum(1);
        gameProb->setMaximum(100);
        gameProb->setValue(50);

        gridLayout_7->addWidget(gameProb, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_7);

        line_2 = new QFrame(panel3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        moveWhite = new QPushButton(panel3);
        moveWhite->setObjectName(QString::fromUtf8("moveWhite"));

        verticalLayout_5->addWidget(moveWhite);

        moveBlack = new QPushButton(panel3);
        moveBlack->setObjectName(QString::fromUtf8("moveBlack"));

        verticalLayout_5->addWidget(moveBlack);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gameSize = new QSpinBox(panel3);
        gameSize->setObjectName(QString::fromUtf8("gameSize"));
        gameSize->setMinimum(2);
        gameSize->setMaximum(19);
        gameSize->setValue(11);

        gridLayout_5->addWidget(gameSize, 1, 2, 1, 1);

        label_4 = new QLabel(panel3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_4, 1, 0, 1, 1, Qt::AlignRight);


        verticalLayout_5->addLayout(gridLayout_5);


        gridLayout->addWidget(panel3, 0, 4, 3, 1);

        gameProgress = new QProgressBar(tab4);
        gameProgress->setObjectName(QString::fromUtf8("gameProgress"));
        gameProgress->setValue(24);

        gridLayout->addWidget(gameProgress, 2, 0, 1, 1);

        gameViewSim = new BoardWidget(tab4);
        gameViewSim->setObjectName(QString::fromUtf8("gameViewSim"));
        gameViewSim->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gameViewSim->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gameViewSim->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);

        gridLayout->addWidget(gameViewSim, 1, 0, 1, 1);

        tabWidget->addTab(tab4, QString());

        verticalLayout_6->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 24));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        panel1->setTitle(QApplication::translate("MainWindow", "Control Panel", 0, QApplication::UnicodeUTF8));
        fillAndPivots->setText(QApplication::translate("MainWindow", "Board and Pivots", 0, QApplication::UnicodeUTF8));
        fillBoard->setText(QApplication::translate("MainWindow", "Fill Board", 0, QApplication::UnicodeUTF8));
        articulationPoint->setText(QApplication::translate("MainWindow", "Find Pivots", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Board Type", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "X = ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Probability p=", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Board size n=", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Main", 0, QApplication::UnicodeUTF8));
        panel2->setTitle(QApplication::translate("MainWindow", "Control Panel", 0, QApplication::UnicodeUTF8));
        simulatePivot->setText(QApplication::translate("MainWindow", "Most Pivotal Hexes", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Game Type", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "X = ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Board Size n= ", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Waiting time t=", 0, QApplication::UnicodeUTF8));
        progressBarSim->setFormat(QApplication::translate("MainWindow", "%p%", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Pivots", 0, QApplication::UnicodeUTF8));
        panel3->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        startRandom->setText(QApplication::translate("MainWindow", "Start Random Game", 0, QApplication::UnicodeUTF8));
        startAlternative->setText(QApplication::translate("MainWindow", "Start Alternative Game", 0, QApplication::UnicodeUTF8));
        nextRandomTurn->setText(QApplication::translate("MainWindow", "Next Random Move", 0, QApplication::UnicodeUTF8));
        resetGame->setText(QApplication::translate("MainWindow", "Reset Game", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Game Type", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "X = ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Waiting time t=", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Move probability p=", 0, QApplication::UnicodeUTF8));
        moveWhite->setText(QApplication::translate("MainWindow", "Move White", 0, QApplication::UnicodeUTF8));
        moveBlack->setText(QApplication::translate("MainWindow", "Move Black", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Board size n=", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab4), QApplication::translate("MainWindow", "Two Players", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
