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
	void addItemToScene(const CStripItemConfig& stripItem);
	void overwriteItemFromScene(const CStripItemConfig& stripItem);
	void deleteItemFromScene(const CStripItemConfig& stripItem);
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
	void AddInteractionMenu();
	QPushButton* createSaveButton();
	QPushButton* createLoadButton();
	void clearLayout(QLayout *layout);
private:
	CStripItemConfig m_itemConfigs;
	QPushButton* m_saveItemButton;
	QPushButton* m_deleteItemButton;
	QWidget* m_paramsWdgMenu;
};

#endif // CWDGSELECTIONMENU_H
