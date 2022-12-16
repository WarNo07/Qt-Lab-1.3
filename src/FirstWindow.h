#ifndef firstwindow_h
#define firstwindow_h

#include "Playlist.h"
#include <QDialog>

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QDialog {
  Q_OBJECT

public:
  explicit FirstWindow(QWidget *parent = nullptr);
  ~FirstWindow();
private slots:
  void on_pushButton_13_clicked();

  void on_pushButton_14_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_clicked();

private:
  Playlist plt;
  Ui::FirstWindow *ui;
};

#endif
