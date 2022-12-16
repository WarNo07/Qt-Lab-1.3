#ifndef addcomp_h
#define addcomp_h

#include <QDialog>

namespace Ui {
class AddComp;
}

class AddComp : public QDialog {
  Q_OBJECT

public:
  void add(std::string pos);
  explicit AddComp(QWidget *parent = nullptr);
  ~AddComp();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

private:
  Ui::AddComp *ui;
};

#endif // ADDNAA_H
