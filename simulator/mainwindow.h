#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <utility>
#include <board.h>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::pair<int,int> makeMove(bool col, int tt = 50000);
private slots:
    void on_fillBoard_clicked();

    void on_articulationPoint_clicked();

    void on_simulatePivot_clicked();
    void on_fillAndPivots_clicked();

    void on_nextRandomTurn_clicked();
    void on_resetGame_clicked();

    void on_startAlternative_clicked();
    void on_startRandom_clicked();

    void on_moveBlack_clicked();
    void on_moveWhite_clicked();

    void on_takeScreenshot_clicked();

    void on_takeGameBoard_clicked();
    void on_takeProbabilityBoard_clicked();

    void setMProb(int v);
    void setMainSize(int v);
    void setSimSize(int v);
    void setWaitTimeSim(int v);

    void setGameWaitTime(int v);
    void setGameProb(int v);
    void setGameSize(int v);

    void resetMain();
    void resetSim();
    void resetGame();

    void setMainType(int k);
    void setMainX(int x);

    void setSimType(int k);
    void setSimX(int x);

    void setGameType(int k);
    void setGameX(int x);

private:
    Ui::MainWindow *ui;

    Board * mainBoard;
    Board * mainBoardSim;

    Board* gameBoard;

    int mProb;
    int waitTimeSim;

    const double game_eps = 0.005;
    int gameWaitTime;
    int gameProb;
    int gameSize;
    int gameCenter;

    int mainSize;
    int simSize;

    int mainType;
    int mainX;
    int simType;
    int simX;
    int gameType;
    int gameX;
};

#endif // MAINWINDOW_H
