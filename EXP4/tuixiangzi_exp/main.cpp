 #include <QApplication>
 #include <QLabel>
 #include "mainwindow.h"

 int main(int argc, char **argv)
 {
  QApplication app(argc, argv);

  MainWindow* mygl = new MainWindow;
  mygl->show();
  return app.exec();
 }
