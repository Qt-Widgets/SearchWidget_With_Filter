#include "searchwidget.h"
#include <QApplication>
#include <QDebug>

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QLabel>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget{parent}
{

//    QWidget *pwidget=NULL;
//    foreach(pwidget, QApplication::topLevelWidgets())
//    {
//        if (pwidget->isWindow() && pwidget->children().contains(this))
//        {
//            //qDebug()<<pwidget->objectName();
//        }
//        qDebug()<<pwidget->objectName();
//    }
//return;

    initTimer.setInterval(100);
    initTimer.setSingleShot(true);
    connect(&initTimer, &QTimer::timeout, this, [=]()
    {
        //lineEdit->installEventFilter(this);
        qApp->installEventFilter(this);
        /* A->installEventFilter(B);
         * A: It's widget of which you want to monitor events.
         * B: It's widget in which events monitoring function i.e. event filter is defined.
         *
         * widget B can now watch and intercept events generated for widget A. In event filter
         * function, widget B can return 'true' if B wants to eat an event intended for A or return
         * 'false' if widget B doesn't care if that event reaches to widget A.
         *
         * If you want to monitor all events generated for any widget, you can use qApp in
         * place of A.
         */

        QWidget *pwidget=NULL;
        foreach(pwidget, QApplication::topLevelWidgets())
        {
            if (pwidget->isWindow() && pwidget->children().contains(this))
            {
                //qDebug()<<pwidget->objectName();
            }
            //qDebug()<<pwidget->objectName();
        }

        qDebug()<<this->window()->objectName();
        /* All QWidgets have a pointer to the containing window(QWidget::window()), as of Qt 5.
         * Returns the window for this widget, i.e. the next ancestor widget that has (or could
         * have) a window-system frame.
         * If the widget is a window, the widget itself is returned.
         * Typical usage is changing the window title:
         * aWidget->window()->setWindowTitle("New Window Title");
         */
    });
    initTimer.start();



    lineEdit = new QLineEdit;
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(lineEdit);
    this->setLayout(layout);

    mPopup = new QWidget(this);
    mPopup->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);

    QHBoxLayout* tlayout = new QHBoxLayout;
    QLabel* label = new QLabel("Search by");
    QRadioButton* radioButton1 = new QRadioButton("NAME");
    QRadioButton* radioButton2 = new QRadioButton("CNIC");
    QRadioButton* radioButton3 = new QRadioButton("PHONE");
    tlayout->addWidget(radioButton1);
    tlayout->addWidget(radioButton2);
    tlayout->addWidget(radioButton3);
    mPopup->setLayout(tlayout);
}


bool SearchWidget::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug()<<topLevelWidget->objectName();
    qDebug()<<"SearchWidget::eventFilter: "<< event->type()<< " "<< obj->objectName();

    if (obj == lineEdit && event->type() == QEvent::KeyPress)
    {
        auto keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_Down:
            isInFocus = true;
            showPopup();
            //emit handleKey(keyEvent);
            return true;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            //emit handleKey(keyEvent);
            return true;
        case Qt::Key_Escape:
            isInFocus = false;
            mPopup->hide();
            return true;
        default:
            break;
        }
    }
     else if (obj == lineEdit && event->type() == QEvent::FocusOut)
    {
        isInFocus = false;
        mPopup->hide();
    }
    else if (obj == lineEdit && event->type() == QEvent::FocusIn)
    {
        auto fev = static_cast<QFocusEvent *>(event);
        if (fev->reason() != Qt::ActiveWindowFocusReason)
        {
            isInFocus = true;
            showPopup();
        }
    }
    else if (obj == lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        isInFocus = true;
        showPopup();
    }
    else if(isInFocus == true)
    {
        if(obj == this->window() && event->type() == QEvent::MouseButtonPress)
        {
            mPopup->hide();
        }
    }

    return false;
}

void SearchWidget::showPopup()
{
    QPoint localPos = mapToGlobal(lineEdit->pos() + QPoint(0, lineEdit->height() + 1));
    mPopup->move(localPos);
    mPopup->setMinimumWidth(lineEdit->width());
    mPopup->setMinimumHeight(lineEdit->height());
    mPopup->setVisible(true);
}
