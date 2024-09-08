#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include "qcustomplot.h"
#include "mainwindow.h"

class Graph : public QDialog
{
    Q_OBJECT

public:
    Graph(QWidget *parent = nullptr);
    ~Graph();
private:
    QCustomPlot *plot;
public slots:
    void buildGraph(QVector<double> mas, QVector<double> num);
};

#endif // GRAPH_H
