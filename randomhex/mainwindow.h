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

    void setMProb(int v);
    void setMSize(int v);
    void setSSize(int v);
    void setWaitTimeSim(int v);
    void setSimCenter(int k);

    void setGameWaitTime(int v);
    void setGameProb(int v);
    void setGameSize(int v);
    void setGameCenter(int k);

private:
    Ui::MainWindow *ui;

    Board * mainBoard;
    Board * mainBoardSim;

    Board* gameBoard;

    int mProb;
    int waitTimeSim;
    int simCenter;

    const double game_eps = 0.005;
    int gameWaitTime;
    int gameProb;
    int gameSize;
    int gameCenter;
};

#endif // MAINWINDOW_H
