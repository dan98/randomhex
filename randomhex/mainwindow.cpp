#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

#include <unistd.h>

#include <iostream>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    mainBoard = new Board(11);
    ui->boardView->setBoard(mainBoard);
    ui->boardView->getItem()->setStyle(1, 1, 0, 0);

    mainBoardSim = new Board(11);
    ui->boardViewSim->setBoard(mainBoardSim);
    ui->boardViewSim->getItem()->setStyle(0, 0, 0, 0);

    gameBoard = new Board(11);
    ui->gameView->setBoard(gameBoard);
    ui->gameViewSim->setBoard(gameBoard);
    ui->gameView->getItem()->setStyle(1, 1, 0, 0);
    ui->gameViewSim->getItem()->setStyle(0, 0, 1, 1);


    ui->progressBarSim->setOrientation(Qt::Horizontal);
    ui->progressBarSim->setRange(1, 5000);
    ui->progressBarSim->setValue(1);
    ui->progressBarSim->setVisible(0);

    ui->gameProgress->setOrientation(Qt::Horizontal);
    ui->gameProgress->setVisible(0);

    mProb = 50;
    waitTimeSim = 0;
    gameProb = 50;
    gameSize = 11;
    gameWaitTime = 0;

    connect(ui->mainProb, SIGNAL(valueChanged(int)),
        this, SLOT(setMProb(int)));

    connect(ui->mainSize, SIGNAL(valueChanged(int)),
        this, SLOT(setMSize(int)));
    connect(ui->simSize, SIGNAL(valueChanged(int)),
        this, SLOT(setSSize(int)));

    connect(ui->waitTimeSim, SIGNAL(valueChanged(int)),
        this, SLOT(setWaitTimeSim(int)));

    connect(ui->gameWaitTime, SIGNAL(valueChanged(int)),
        this, SLOT(setGameWaitTime(int)));

    connect(ui->gameProb, SIGNAL(valueChanged(int)),
        this, SLOT(setGameProb(int)));

    connect(ui->gameSize, SIGNAL(valueChanged(int)),
        this, SLOT(setGameSize(int)));
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
  this->gameSize = v;
  delete gameBoard;
  gameBoard = new Board(v);
  ui->gameView->setBoard(gameBoard);
  ui->gameViewSim->setBoard(gameBoard);
}

void MainWindow::setWaitTimeSim(int v){
  this->waitTimeSim = v;
}

void MainWindow::setMProb(int v){
  this->mProb = v;
}

void MainWindow::setMSize(int v){
  delete mainBoard;
  mainBoard = new Board(v);
  ui->boardView->setBoard(mainBoard);
}

void MainWindow::setSSize(int v){
  delete mainBoardSim;
  mainBoardSim = new Board(v);
  ui->boardViewSim->setBoard(mainBoardSim);
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
  std::pair<int, int> rs = std::make_pair(1, 1);
  while(rs != std::make_pair(0, 0))
  {
    rs = makeMove(curr, nrmoves);
    curr = !curr;
  }
}

void MainWindow::on_startRandom_clicked(){
  on_resetGame_clicked();
  int nrmoves = 50000;
  std::pair<int, int> rs = std::make_pair(1, 1);
  while(rs != std::make_pair(0, 0))
  {
    rs = makeMove((rand()%100)<gameProb, nrmoves);
    nrmoves -= 700;
  }
}

void MainWindow::on_resetGame_clicked()
{
  delete gameBoard;
  gameBoard = new Board(gameSize);
  ui->gameView->setBoard(gameBoard);
  ui->gameViewSim->setBoard(gameBoard);
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
      ui->gameViewSim->scene()->update();
      qApp->processEvents();
      usleep(1000*gameWaitTime);
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
