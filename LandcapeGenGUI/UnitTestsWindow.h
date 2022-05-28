#ifndef UNITTESTSWINDOW_H
#define UNITTESTSWINDOW_H

#include <QWidget>
#include "Controllers/UserControllerTest.h"
#include "Controllers/BaseControllerTest.h"
#include "Repositorys/CanvasRepositoryTest.h"


namespace Ui {
class UnitTestsWindow;
}

class UnitTestsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UnitTestsWindow(QWidget *parent = nullptr);
    ~UnitTestsWindow();

private slots:
    void on_user_controller_test_btn_clicked();

    void on_base_controller_test_btn_clicked();

    void on_canvas_repository_test_btn_clicked();

private:
    Ui::UnitTestsWindow *ui;
};

#endif // UNITTESTSWINDOW_H
