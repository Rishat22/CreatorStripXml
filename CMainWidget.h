#ifndef CMAINWIDGET_H
#define CMAINWIDGET_H

#include <StableDeclaration.h>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWidget; }
QT_END_NAMESPACE

class CMainWidget : public QWidget
{
    Q_OBJECT

public:
    CMainWidget(QWidget *parent = nullptr);
    ~CMainWidget();

private slots:

private:
	CWdgScene* m_wdgScene;
};
#endif // CMAINWIDGET_H
