#include "ModeratorWindow.h"
#include "ui_ModeratorWindow.h"
#include "Settings.h"

#include <QMessageBox>

ModeratorWindow::ModeratorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeratorWindow)
{
    ui->setupUi(this);

    moderator_controller = make_unique<ModeratorController>();
    users_repository = make_shared<USER_REP>();
    canvas_repository = make_shared<CANVAS_REP>();
    //users_repository = users_rep;
    //canvas_repository = canvas_rep;
    mod_can_win = make_unique<ModeratorCanvasWindow>();
    connect(mod_can_win.get(), SIGNAL(exit()), this, SLOT(show()));
}

ModeratorWindow::~ModeratorWindow()
{
    delete ui;
}

void ModeratorWindow::login(shared_ptr<UserBL> user_bl)
{
    moderator_controller->login(user_bl);
    //users_repository->setRole(user_bl->getRole(), user_bl->getRole());
    QVariant r(QString::fromStdString(user_bl->getRole()));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    updateFreeCanvasUsersList();
    updateMyCanvasUsersList();
}

void ModeratorWindow::addUser(string name)
{
    shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
    UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), moderator_controller->getUser()->getId());
    users_repository->updateUser(new_user_bl, user_bl->getId());
    updateLists();
}

void ModeratorWindow::deleteUser(string name)
{
    shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
    UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), -1);
    users_repository->updateUser(new_user_bl, user_bl->getId());
    updateLists();
}

void ModeratorWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button";
    this->hide();
    moderator_controller->logout();
    emit exit();
}

void ModeratorWindow::updateFreeCanvasUsersList()
{
    ui->free_users_listWidget->clear();
    vector<string> free_users_names = users_repository->getFreeCanvasUsers();
    for (auto &elem : free_users_names)
        ui->free_users_listWidget->addItem(QString::fromStdString(elem));
}

#include "Essensities/UserBL.h"
#include "Controllers/ModeratorController.h"

void ModeratorWindow::updateMyCanvasUsersList()
{
    if (moderator_controller->getUser())
    {
        ui->my_users_listWidget->clear();
        vector<string> my_users_names = users_repository->getCanvasUsersByMid(moderator_controller->getUser()->getId());
        for (auto &elem : my_users_names)
            ui->my_users_listWidget->addItem(QString::fromStdString(elem));
    }
}

void ModeratorWindow::updateLists()
{
    try
    {
        updateFreeCanvasUsersList();
        updateMyCanvasUsersList();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_add_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed add user button";
        QList<QListWidgetItem*> list = ui->free_users_listWidget->selectedItems();
        for (auto &elem : list)
        {
            addUser(elem->text().toStdString());
        }
        updateLists();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_delete_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed delete user button";
        QList<QListWidgetItem*> list = ui->my_users_listWidget->selectedItems();
        for (auto &elem : list)
        {
            deleteUser(elem->text().toStdString());
        }
        updateLists();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_delete_user_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed DELETE THIS USER button";
        users_repository->deleteUser(moderator_controller->getUser()->getId());
        this->hide();
        moderator_controller->logout();
        emit exit();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_add_btn_2_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed Watch User Canvases button";
        QList<QListWidgetItem*> list = ui->my_users_listWidget->selectedItems();
        if (list.size() > 0)
        {
            shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(list[0]->text().toStdString());
            mod_can_win->setId(user_bl->getId());
            this->hide();
            mod_can_win->show();
        }
        else
        {
            QMessageBox::information(this, "Error", "This user has no canvases");
        }
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}

