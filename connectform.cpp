#include "connectform.h"
#include "ui_connectform.h"

ConnectForm::ConnectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
}

ConnectForm::~ConnectForm()
{
    delete ui;
}
