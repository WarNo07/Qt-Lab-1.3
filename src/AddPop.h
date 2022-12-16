#ifndef addpop_h
#define addpop_h

#include <QDialog>

namespace Ui {
class AddPop;
}

class AddPop : public QDialog {
  Q_OBJECT

public:
  void add(std::string pos);
  explicit AddPop(QWidget *parent = nullptr);
  ~AddPop();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::AddPop *ui;
};

#endif // ADDPAA_H
