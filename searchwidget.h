#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
class QLineEdit;
#include <QTimer>

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = nullptr);

signals:

public:
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QLineEdit* lineEdit = nullptr;
    QWidget* mPopup = nullptr;
    QWidget* topLevelWidget = nullptr;
    QTimer initTimer;

    bool isInFocus = false;

    void showPopup();
};

#endif // SEARCHWIDGET_H
