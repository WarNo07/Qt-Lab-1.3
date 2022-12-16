#ifndef viewwindow_h
#define viewwindow_h

#include "Playlist.h"
#include <QDialog>

namespace Ui {
class ViewWindow;
}

class ViewWindow : public QDialog {
  Q_OBJECT

public:
  explicit ViewWindow(QWidget *parent = nullptr);
  void insertData(Playlist collection, int size) const;
  ~ViewWindow();

private slots:
  void on_pushButton_clicked();

private:
  Ui::ViewWindow *ui;
};

#endif
