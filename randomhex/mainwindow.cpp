#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

#include <unistd.h>
#include <cmath>
#include <iomanip>

#include <iostream>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainBoard(NULL),
    mainBoardSim(NULL),
    gameBoard(NULL)
{

    mainType = 0;
    mainX = 1;
    mainSize = 11;

    simType = 0;
    simX = 1;
    simSize = 11;

    gameType = 0;
    gameX = 1;
    gameSize = 11;

    ui->setupUi(this);

    resetMain();
    ui->boardView->getItem()->setStyle(1, 1, 0, 0);

    resetSim();
    ui->boardViewSim->getItem()->setStyle(0, 0, 0, 0);

    resetGame();
    ui->gameView->getItem()->setStyle(1, 1, 0, 0);
    ui->gameViewSim->getItem()->setStyle(0, 0, 1, 1);

    ui->mainType->addItem(QString("Standard"));
    ui->mainType->addItem(QString("Triangle"));
    ui->mainType->addItem(QString("Trapezium"));
    ui->mainType->addItem(QString("Center"));
    ui->mainType->setCurrentIndex(0);
    
    ui->simType->addItem(QString("Standard"));
    ui->simType->addItem(QString("Triangle"));
    ui->simType->addItem(QString("Trapezium"));
    ui->simType->addItem(QString("Center"));
    ui->mainType->setCurrentIndex(0);

    ui->gameType->addItem(QString("Standard"));
    ui->gameType->addItem(QString("Triangle"));
    ui->gameType->addItem(QString("Trapezium"));
    ui->gameType->addItem(QString("Center"));
    ui->mainType->setCurrentIndex(0);

    connect(ui->mainType, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setMainType(int)));
    connect(ui->simType, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setSimType(int)));
    connect(ui->gameType, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setGameType(int)));

    ui->progressBarSim->setOrientation(Qt::Horizontal);
    ui->progressBarSim->setRange(1, 5000);
    ui->progressBarSim->setValue(1);
    ui->progressBarSim->setVisible(0);

    ui->gameProgress->setOrientation(Qt::Horizontal);
    ui->gameProgress->setVisible(0);

    mProb = 50;
    waitTimeSim = 0;
    gameProb = 50;
    gameWaitTime = 0;

    connect(ui->mainProb, SIGNAL(valueChanged(int)),
        this, SLOT(setMProb(int)));

    connect(ui->mainSize, SIGNAL(valueChanged(int)),
        this, SLOT(setMainSize(int)));
    connect(ui->simSize, SIGNAL(valueChanged(int)),
        this, SLOT(setSimSize(int)));

    connect(ui->waitTimeSim, SIGNAL(valueChanged(int)),
        this, SLOT(setWaitTimeSim(int)));

    connect(ui->gameWaitTime, SIGNAL(valueChanged(int)),
        this, SLOT(setGameWaitTime(int)));

    connect(ui->gameProb, SIGNAL(valueChanged(int)),
        this, SLOT(setGameProb(int)));

    connect(ui->gameSize, SIGNAL(valueChanged(int)),
        this, SLOT(setGameSize(int)));

    connect(ui->mainX, SIGNAL(valueChanged(int)),
        this, SLOT(setMainX(int)));
    connect(ui->simX, SIGNAL(valueChanged(int)),
        this, SLOT(setSimX(int)));
    connect(ui->gameX, SIGNAL(valueChanged(int)),
        this, SLOT(setGameX(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setGameWaitTime(int v){
  this->gameWaitTime = v;
}

void MainWindow::setGameProb(int v){
  this->gameProb = v;
}

void MainWindow::setGameSize(int v){
  gameSize = v;
  resetGame();
}

void MainWindow::setMainType(int k){
  mainType = k;
  resetMain();
}
void MainWindow::setSimType(int k){
  simType = k;
  resetSim();
}
void MainWindow::setGameType(int k){
  gameType = k;
  resetGame();
}

void MainWindow::setMainX(int k){
  mainX = k;
  resetMain();
}
void MainWindow::setSimX(int k){
  simX = k;
  resetSim();
}
void MainWindow::setGameX(int k){
  gameX = k;
  resetGame();
}
void MainWindow::setWaitTimeSim(int v){
  this->waitTimeSim = v;
}

void MainWindow::setMProb(int v){
  this->mProb = v;
}

void MainWindow::setMainSize(int v){
  mainSize = v;
  resetMain();
}

void MainWindow::setSimSize(int v){
  simSize = v;
  resetSim();
}

void MainWindow::resetMain(){
  if(mainBoard)
    delete mainBoard;
  mainBoard = new Board(mainSize, mainType, mainX);
  ui->boardView->setBoard(mainBoard);
}

void MainWindow::resetSim(){
  if(mainBoardSim)
    delete mainBoardSim;
  mainBoardSim = new Board(simSize, simType, simX);
  ui->boardViewSim->setBoard(mainBoardSim);
}

void MainWindow::resetGame(){
  if(gameBoard)
    delete gameBoard;
  gameBoard = new Board(gameSize, gameType, gameX);
  ui->gameView->setBoard(gameBoard);
  ui->gameViewSim->setBoard(gameBoard);
}

void MainWindow::on_fillBoard_clicked()
{
   mainBoard->fillRandom(mProb);

   ui->boardView->scene()->update();
}

void MainWindow::on_articulationPoint_clicked()
{

   mainBoard->findArticulationPoints(2);
   ui->boardView->scene()->update();
}

void MainWindow::on_fillAndPivots_clicked()
{
   mainBoard->fillRandom(mProb);
   mainBoard->findArticulationPoints(2);
   ui->boardView->scene()->update();
}

void MainWindow::on_simulatePivot_clicked()
{

    ui->boardViewSim->getItem()->setStyle(0, 0, 1, 1);

    int tt = 50000;
    ui->progressBarSim->setRange(1, 100);
    ui->progressBarSim->setVisible(1);


    QApplication::setOverrideCursor(Qt::WaitCursor);
    for(int i=1; i<=100; ++i){
      ui->progressBarSim->setValue(i);
      mainBoardSim->generateMove(tt/100, 0);
      ui->boardViewSim->scene()->update();
      qApp->processEvents();
      usleep(1000*waitTimeSim);
    }

    mainBoardSim->resetMove();

    QApplication::restoreOverrideCursor();

    ui->progressBarSim->setVisible(0);
}

void MainWindow::on_nextRandomTurn_clicked()
{
  makeMove((rand()%100)<gameProb);
}

void MainWindow::on_moveBlack_clicked()
{
  makeMove(1);
}

void MainWindow::on_moveWhite_clicked()
{
  makeMove(0);
}

void MainWindow::on_startAlternative_clicked(){
  on_resetGame_clicked();
  int curr = 0;
  int nrmoves = 50000;
  std::pair<int, int> rs = {1, 1};
  while(rs != std::make_pair(-1, -1))
  {
    rs = makeMove(curr, nrmoves);
    curr = !curr;
  }
}

void MainWindow::on_startRandom_clicked(){
  resetGame();
  int nrmoves = 50000;
  std::pair<int, int> rs = {1, 1};
  bool ft = (rand()%100)<gameProb;
  int n = gameBoard->boardSize();
  gameBoard->move(n/2+n%2, n/2+n%2, ft);
  ui->gameView->scene()->update();
  while(rs != std::make_pair(-1, -1))
  {
    rs = makeMove((rand()%100)<gameProb, nrmoves);
  }
}

void MainWindow::on_resetGame_clicked()
{
  resetGame();
}

std::pair<int, int> MainWindow::makeMove(bool col, int tt){

    ui->gameViewSim->getItem()->setStyle(0, 0, 1, 1);

    ui->gameProgress->setRange(1, 100);
    ui->gameProgress->setVisible(1);


    QApplication::setOverrideCursor(Qt::WaitCursor);

    std::pair<int, int> rs;

    for(int i=1; i<=100; ++i){
      ui->gameProgress->setValue(i);
      rs = gameBoard->generateMove(tt/100, col);
      int n = gameBoard->boardSize();

      double diff = 0;
      for(int j=1; j<=n; ++j)
          for(int k=1; k<=n; ++k)
            diff = std::max(gameBoard->getProb(j, k)
                - gameBoard->getProbPr(j, k), diff);


      ui->gameViewSim->scene()->update();
      qApp->processEvents();
      usleep(1000*gameWaitTime);
      if(diff<game_eps)
        break;
    }

    gameBoard->marked = rs;
    gameBoard->resetMove();

    gameBoard->findArticulationPoints(2);

    gameBoard->move(rs.first, rs.second, col);
    ui->gameView->scene()->update();

    QApplication::restoreOverrideCursor();

    ui->gameProgress->setVisible(0);

    return rs;
}
