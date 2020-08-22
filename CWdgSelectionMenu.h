#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H

#include <StableDeclaration.h>
#include <CStripItemConfig.h>
#include <QWidget>

using namespace UUserPolicies;

class CWdgSelectionMenu : public QWidget
{
	Q_OBJECT
public:
	CWdgSelectionMenu(QWidget *parent = nullptr);
signals:
	void addElementToScene(const CStripItemConfig& stripItem);
	void saveData(const std::string& strFileName);
	void loadData(const std::string& strFileName);
public slots:
	//ToDo rename stripItemParams to stripItemConfigs at all
	void setStripItemParams(CStripItemConfig& stripItemParams);
private:
	QStringList getListByType(const TypeItemParam typeParam);
	QGroupBox* createInteractionBox(CInteraction& interaction);
	QComboBox* createComboBox(const TypeItemParam typeParam);
	QComboBox* createComboBox(const QStringList& typeItemsList);
	void fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet);
	QLayout* createDescription(const QString &textDescription);
	QPushButton* createItemButton();
	QPushButton* createSaveButton();
	QPushButton* createLoadButton();
	void clearLayout(QLayout *layout);
	bool setDataByType(const TypeItemParam type, const std::string& paramData);
private:
	CStripItemConfig m_itemParams;
	QWidget* m_paramsWdgMenu;
};

#endif // CWDGSELECTIONMENU_H
