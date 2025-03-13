#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void setupConnections();
    void updateKeyStatus();
    void handleEmergencyStop();
    void loadDirectionIndicator();
    void updateDirectionIndicator();

    Ui::MainWindow *ui;
    bool keyW = false;
    bool keyS = false;
    bool keyUp = false;
    bool keyDown = false;
    bool keyLeft = false;
    bool keyRight = false;
};

#endif // MAINWINDOW_H