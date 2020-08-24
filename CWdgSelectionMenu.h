#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H

#include <StableDeclaration.h>
#include <CStripItemConfig.h>
#include <QComboBox>
#include <QWidget>

using namespace UUserPolicies;

class CItemComboBox : public QComboBox
{
public:
	CItemComboBox(QWidget* parent = nullptr) : QComboBox::QComboBox(parent) {}
	virtual ~CItemComboBox() {}
	void setCurrentItem(const CBaseItem& stripItem)
	{
		auto paramIndex = findText(QString::fromStdString(stripItem.GetData()));
		setCurrentIndex(paramIndex);
	}

};

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
	void setStripItemConfig(const CStripItemConfig& stripItemConfigs);
private:
	QStringList getListByType(const TypeItemParam typeParam);
	QGroupBox* createInteractionBox(CInteraction& interaction);
	CItemComboBox* createComboBox(const TypeItemParam typeParam);
	CItemComboBox* createComboBox(const QStringList& typeItemsList);
	void fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet);
	QLayout* createDescription(const QString &textDescription);
	QLayout* createItemNamesComboBox(const CBaseItem& currentItem = CStripItem());
	QLayout* createItemTools();
	QPushButton* createAddItemButton();
	QPushButton* createSaveItemButton();
	QPushButton* createDeleteItemButton();
	QPushButton* createAddInteractionButton();
	QPushButton* createSaveButton();
	QPushButton* createLoadButton();
	void clearLayout(QLayout *layout);
	bool setDataByType(const TypeItemParam type, const std::string& paramData);
private:
	CStripItemConfig m_itemConfigs;
	QPushButton* m_saveItemButton;
	QPushButton* m_deleteItemButton;
	QWidget* m_paramsWdgMenu;
};

#endif // CWDGSELECTIONMENU_H
