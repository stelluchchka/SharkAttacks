#ifndef NEWS_H
#define NEWS_H

#include <QDialog>

namespace Ui {
class News;
}

class News : public QDialog
{
    Q_OBJECT

public:
    explicit News(QWidget *parent = nullptr);
    ~News();

private:
    Ui::News *ui;
};

#endif // NEWS_H
