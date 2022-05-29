#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <iostream>

using namespace std;

#include "Canvas.h"
#include "Essensities/CanvasBL.h"
#include "UnitTestsWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void login(shared_ptr<UserBL> user_bl);

    void updateCanvasesList();

private slots:
    void on_gen_btn_clicked();

    void on_clean_btn_clicked();

    void on_size_up_btn_released();

    void on_size_down_btn_released();

    void on_draw_variant_comboBox_activated(int index);

    void on_mult_spinBox_valueChanged(int arg1);

    void on_scale_doubleSpinBox_valueChanged(double arg1);

    void on_move_btn_clicked();

    void on_scale_btn_clicked();

    void on_rotate_btn_clicked();

    void on_range_doubleSpinBox_valueChanged(double arg1);

    void on_resolution_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_read_file_btn_clicked();

    void on_write_file_btn_clicked();

    void on_load_canvas_btn_clicked();

    void on_write_file_btn_2_clicked();

    void on_delete_canvas_btn_clicked();

    void on_update_canvas_btn_clicked();

    void on_write_file_btn_3_clicked();

    void on_exit_btn_clicked();

    void on_test_user_btn_clicked();

    void on_delete_user_btn_clicked();

signals:
    void exit();

private:
    Ui::MainWindow *ui;

    unique_ptr<Canvas> canvas;
    unique_ptr<UnitTestsWindow> unit_tests_window;
};
#endif // MAINWINDOW_H
