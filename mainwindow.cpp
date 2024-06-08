#include "mainwindow.h"
#include "ui_mainwindow.h"

QString previousSring = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    previousSring = ui->txtTestData->toPlainText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_etRegex_textEdited(const QString &text)
{
    executeExpression(text);
}

void MainWindow::on_txtTestData_textChanged()
{
    // update as per the regex
    if (previousSring.compare(ui->txtTestData->toPlainText()) != 0) {
        previousSring = ui->txtTestData->toPlainText();
        QString expression = ui->etRegex->text();
        executeExpression(expression);
    }
}

void MainWindow::executeExpression(QString expression)
{
    QString sanitizedString = expression.replace("\\", "\\");
    //QRegularExpression::escape(expression); // not working as expected
    // qDebug() << "RegEx: " << sanitizedString;
    QString demoText = ui->txtTestData->toPlainText();

    QRegularExpression re(sanitizedString);
    QRegularExpressionMatchIterator matches = re.globalMatch(demoText);

    QTextCursor cursor = ui->txtTestData->textCursor();
    QTextCharFormat textFormat;

    textFormat.setForeground(Qt::black);
    // reset color to black
    cursor.setPosition(0);
    cursor.setPosition(demoText.length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(textFormat);

    textFormat.setForeground(Qt::cyan);

    QTextDocument *doc = ui->txtTestData->document();
    int pos = 0;

    int counter = 0;
    while (pos >= 0) {
        QRegularExpressionMatch match = re.match(doc->toPlainText(), pos);
        if (match.hasMatch()) {
            int start = match.capturedStart();
            int end = match.capturedEnd();
            cursor.setPosition(start);
            cursor.setPosition(end, QTextCursor::KeepAnchor);
            cursor.setCharFormat(textFormat);
            pos = end;
        } else {
            break;
        }

        // FIXME: without this, the program crashes
        counter++;
        /* 3- Any number suitable that will not deplete the program memory */
        if (counter > demoText.length() * 3) {
            break;
        }
    }
}
