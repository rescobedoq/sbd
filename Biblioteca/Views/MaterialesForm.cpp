#include "MaterialesForm.h"
#include "ui_MaterialesForm.h"

MaterialesForm::MaterialesForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaterialesForm)
{
    ui->setupUi(this);
}

MaterialesForm::~MaterialesForm()
{
    delete ui;
}
