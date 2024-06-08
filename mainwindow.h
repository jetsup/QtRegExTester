#pragma once

#include <QDebug>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_etRegex_textEdited(const QString &arg1);

    void on_txtTestData_textChanged();

private:
    Ui::MainWindow *ui;
    void executeExpression(QString expression);
};
