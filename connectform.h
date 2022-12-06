#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include <QWidget>

namespace Ui {
class ConnectForm;
}

class ConnectForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectForm(QWidget *parent = nullptr);
    ~ConnectForm();

private:
    Ui::ConnectForm *ui;
};

#endif // CONNECTFORM_H
