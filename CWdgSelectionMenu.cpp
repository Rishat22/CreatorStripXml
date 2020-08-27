#include <QPushButton>
#include <QCompleter>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <Galaxy/CItemInfoGetter.h>
#include <CItemComboBox.h>
#include "CWdgSelectionMenu.h"

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent),
	  m_paramsWdgMenu(new QWidget)
{
	auto paramsMenuLayout = new QVBoxLayout;
	m_paramsWdgMenu->setLayout(paramsMenuLayout);

	paramsMenuLayout->addLayout(createItemNamesComboBox());

	//ToDo get to method
	auto& interactions = m_itemConfigs.GetInteractions();
	interactions.AddInteraction(CInteraction());
	auto& interaction = m_itemConfigs.GetInteractionByIndex(interactions.Size() - 1);
	paramsMenuLayout->addWidget(createInteractionBox(interaction));

	auto vBoxLayout = new QVBoxLayout;
	vBoxLayout->addWidget(m_paramsWdgMenu);
	vBoxLayout->addWidget(createAddInteractionButton());
	vBoxLayout->addLayout(createItemTools());
	vBoxLayout->addStretch();
	vBoxLayout->addWidget(createSaveButton());
	vBoxLayout->addWidget(createLoadButton());

	setLayout(vBoxLayout);
}

QLayout* CWdgSelectionMenu::createItemNamesComboBox(const CBaseItem& currentItem)
{
	auto itemNamesBoxLayout = createDescription("Select item type:");
	auto itemNamesBox = createComboBox(TypeItemParam::Name);
	itemNamesBox->setCurrentItem(currentItem);
	itemNamesBoxLayout->addWidget(itemNamesBox);
	connect(itemNamesBox, &CItemComboBox::editTextChanged,
			[=](const QString& curValue)
	{
		m_itemConfigs.SetItemData(m_itemConfigs.Item().GetTag(CBaseItem::Name), curValue.toStdString());
	});
	return itemNamesBoxLayout;
}

QGroupBox* CWdgSelectionMenu::createInteractionBox(CInteraction& interaction)
{
	auto groupBox = new QGroupBox;
	auto vInteractionLayout = new QVBoxLayout;

	auto actionsBoxLayout = createDescription("Select action name:");
	auto actionsBox = createComboBox(TypeItemParam::Action);
	actionsBox->setCurrentItem(interaction.CAction());
	connect(actionsBox, &CItemComboBox::editTextChanged,
			[=, &interaction](const QString& curValue)
	{
		interaction.Action().SetData(interaction.Action().GetTag(CBaseItem::Name), curValue.toStdString());
	});
	actionsBoxLayout->addWidget(actionsBox);

	auto triggersBoxLayout = createDescription("Select trigger:");
	auto triggersBox = createComboBox(TypeItemParam::Trigger);
	triggersBox->setCurrentItem(interaction.CTrigger());
	connect(triggersBox, &CItemComboBox::editTextChanged,
			[=, &interaction](const QString& curValue)
	{
		interaction.Trigger().SetData(interaction.Trigger().GetTag(CBaseItem::Name), curValue.toStdString());
	});

	triggersBoxLayout->addWidget(triggersBox);

	vInteractionLayout->addLayout(actionsBoxLayout);
	vInteractionLayout->addLayout(triggersBoxLayout);
	groupBox->setLayout(vInteractionLayout);
	return groupBox;
}

QLayout* CWdgSelectionMenu::createDescription(const QString& textDescription)
{
	auto descriptionLayout = new QVBoxLayout;
	descriptionLayout->setSizeConstraint(QLayout::SetMinimumSize);
	auto descriptionLabel = new QLabel(textDescription);
	descriptionLabel->setFixedHeight(20);
	descriptionLayout->addWidget(descriptionLabel);
	return descriptionLayout;
}

CItemComboBox* CWdgSelectionMenu::createComboBox(const TypeItemParam typeParam)
{
	QStringList parameterNamesList = std::move(getListByType(typeParam));
	auto comboBox = createComboBox(parameterNamesList);
	return comboBox;
}

QStringList CWdgSelectionMenu::getListByType(const TypeItemParam typeParam)
{
	CItemInfoGetter itemInfoGetter;
	std::vector<std::string> vecParams;
	switch (typeParam)
	{
		case TypeItemParam::Name:
		{
			vecParams = std::move(itemInfoGetter.getListWithTypeNames());
			break;
		}
		case TypeItemParam::Action:
		{
			vecParams = std::move(itemInfoGetter.getListWithActionNames());
			break;
		}
		case TypeItemParam::Trigger:
		{
			vecParams = std::move(itemInfoGetter.getListWithTriggers());
			break;
		}
		default: break;
	}
	QStringList listParams;
	fillStringListByVector(listParams, vecParams);
	return listParams;
}

void CWdgSelectionMenu::fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet)
{
	for(auto& typeNames : vecFromGet)
	{
		listToFill.push_back(QString::fromStdString(std::move(typeNames)));
	}
}

CItemComboBox* CWdgSelectionMenu::createComboBox(const QStringList& typeItemsList)
{
	QCompleter* completer = new QCompleter(typeItemsList, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	auto comboBox = new CItemComboBox();
	comboBox->addItems(typeItemsList);
	comboBox->setEditable(true);
	comboBox->setCompleter(completer);
	return comboBox;
}

QPushButton* CWdgSelectionMenu::createAddInteractionButton()
{
	auto createAddInteraction = new QPushButton("Add Interaction");
	connect(createAddInteraction, &QPushButton::pressed, [=]()
	{
		auto& interactions = m_itemConfigs.GetInteractions();
		interactions.AddInteraction(CInteraction());
		auto& interaction = m_itemConfigs.GetInteractionByIndex(m_itemConfigs.GetInteractions().Size() - 1);
		auto paramsMenuLayout = dynamic_cast<QVBoxLayout*>(m_paramsWdgMenu->layout());
		paramsMenuLayout->addWidget(createInteractionBox(interaction));
	});
	return createAddInteraction;
}

QLayout* CWdgSelectionMenu::createItemTools()
{
	auto hToolsLayout = new QHBoxLayout();
	hToolsLayout->addWidget(createAddItemButton());
	auto saveItemButton = createSaveItemButton();
	saveItemButton->setDisabled(true);
	hToolsLayout->addWidget(saveItemButton);
	auto delteItemButton = createDeleteItemButton();
	delteItemButton->setDisabled(true);
	hToolsLayout->addWidget(delteItemButton);
	return hToolsLayout;
}

QPushButton* CWdgSelectionMenu::createAddItemButton()
{
	auto addItemButton = new QPushButton("Add");
	connect(addItemButton, &QPushButton::pressed, [=]()
	{
		addItemToScene(m_itemConfigs);
	});
	return addItemButton;
}

QPushButton* CWdgSelectionMenu::createSaveItemButton()
{
	m_saveItemButton = new QPushButton("Save");
	connect(m_saveItemButton, &QPushButton::pressed, [=]()
	{
		overwriteItemFromScene(m_itemConfigs);
	});
	return m_saveItemButton;
}

QPushButton* CWdgSelectionMenu::createDeleteItemButton()
{
	m_deleteItemButton = new QPushButton("Delete");
	connect(m_deleteItemButton, &QPushButton::pressed, [=]()
	{
		deleteItemFromScene(m_itemConfigs);
	});
	return m_deleteItemButton;
}

QPushButton* CWdgSelectionMenu::createSaveButton()
{
	auto saveAllButton = new QPushButton("Save strip items");
	connect(saveAllButton, &QPushButton::pressed,
			[=]()
	{
		QString filter = "XML files (*.xml)";
		QString fileName = QFileDialog::getSaveFileName(this, "Select the path to save", "../", filter);
		saveData(std::move(fileName.toStdString()));
	});
	return saveAllButton;
}

QPushButton* CWdgSelectionMenu::createLoadButton()
{
	auto loadItemsButton = new QPushButton("Load strip items");
	connect(loadItemsButton, &QPushButton::pressed,
			[=]()
	{
		QString filter = "XML files (*.xml)";
		QString fileName = QFileDialog::getOpenFileName(this, "Open file", "../", filter);
		loadData(std::move(fileName.toStdString()));
	});
	return loadItemsButton;
}

void CWdgSelectionMenu::setStripItemConfig(const CStripItemConfig& stripItemConfigs)
{
	if(!stripItemConfigs.isValid())
	{
		m_deleteItemButton->setDisabled(true);
		m_saveItemButton->setDisabled(true);
		return;
	}
	m_itemConfigs = stripItemConfigs;
	m_deleteItemButton->setEnabled(true);
	m_saveItemButton->setEnabled(true);

	auto paramsMenuLayout = dynamic_cast<QVBoxLayout*>(m_paramsWdgMenu->layout());
	m_paramsWdgMenu->setLayout(paramsMenuLayout);
	clearLayout(paramsMenuLayout);

	auto itemNamesLayoutWithBox = createItemNamesComboBox(m_itemConfigs.Item());
	paramsMenuLayout->addLayout(itemNamesLayoutWithBox);

	for(size_t interactionIndex = 0; interactionIndex < m_itemConfigs.GetInteractions().Size(); interactionIndex++)
	{
		auto& interaction = m_itemConfigs.GetInteractionByIndex(interactionIndex);
		paramsMenuLayout->addWidget(createInteractionBox(interaction));
	}

	m_paramsWdgMenu->setLayout(paramsMenuLayout);
}

void CWdgSelectionMenu::clearLayout(QLayout* layout)
{
	   QLayoutItem *item;
	   while((item = layout->takeAt(0)))
	   {
		   if (item->layout()) {
			   clearLayout(item->layout());
			   delete item->layout();
		   }
		   if (item->widget()) {
			  delete item->widget();
		   }
		   if(!item)
			   delete item;
	   }
}
