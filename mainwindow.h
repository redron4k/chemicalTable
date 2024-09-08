#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <fstream>
#include <QStandardItemModel>

#include "adddialog.h"
#include "deldialog.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct elem {
    QString number;
    QString name;
    QString mass;
    QString conductivity;
};
class AddDialog;
class Graph;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveToFile(const std::string& filename,
                    const std::vector<elem>& data);
    void loadFromFile(const std::string& filename,
                      std::vector<elem>& outData);
    void onUpdate();

private:
    Ui::MainWindow *ui;
    AddDialog *add;
    DelDialog *del;
    Graph *graph;
    QStandardItemModel *model;
    std::vector<elem> vec;
    std::vector<elem> found;

signals:
    void toBuildGraph(QVector<double> mas, QVector<double> num);

private slots:
    void onCheckBoxTicked();
    void onAddButtonClicked();
    void onDelButtonClicked();
    void onGraphButtonClicked();
    void addElem(elem e);
    void delElem(int i);
};
#endif // MAINWINDOW_H
