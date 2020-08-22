#include <QPushButton>
#include <QCompleter>
#include <QVBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <Galaxy/CItemInfoGetter.h>
#include "CWdgSelectionMenu.h"

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent),
	  m_paramsWdgMenu(new QWidget)
{
	auto vBoxLayout = new QVBoxLayout;

	auto paramsMenuLayout = new QVBoxLayout;
	auto itemNamesBoxLayout = createDescription("Select item type:");
	auto itemNamesBox = createComboBox(TypeItemParam::Name);
	itemNamesBoxLayout->addWidget(itemNamesBox);
	connect(itemNamesBox, &QComboBox::editTextChanged,
			[=](const QString& curValue)
	{
		m_itemParams.SetItemData(m_itemParams.Item().GetTag(CBaseItem::Name), curValue.toStdString());
	});
	paramsMenuLayout->addLayout(itemNamesBoxLayout);

	//ToDo get to method
	auto& interactions = m_itemParams.GetInteractions();
	interactions.AddInteraction(CInteraction());
	auto& interaction = m_itemParams.GetInteractionByIndex(interactions.Size() - 1);
	paramsMenuLayout->addWidget(createInteractionBox(interaction));

	paramsMenuLayout->addWidget(createItemButton());
	m_paramsWdgMenu->setLayout(paramsMenuLayout);
	vBoxLayout->addWidget(m_paramsWdgMenu);
	vBoxLayout->addStretch();
	vBoxLayout->addWidget(createSaveButton());
	vBoxLayout->addWidget(createLoadButton());

	setLayout(vBoxLayout);
}

QGroupBox* CWdgSelectionMenu::createInteractionBox(CInteraction& interaction)
{
	auto groupBox = new QGroupBox;
	auto vInteractionLayout = new QVBoxLayout;

	auto actionsBoxLayout = createDescription("Select action name:");
	auto actionsBox = createComboBox(TypeItemParam::Action);
	actionsBox->setCurrentIndex(interaction.CAction().Id());
	connect(actionsBox, &QComboBox::editTextChanged,
			[=, &interaction](const QString& curValue)
	{
		interaction.Action().SetData(interaction.Action().GetTag(CBaseItem::Name), curValue.toStdString());
	});
	actionsBoxLayout->addWidget(actionsBox);

	auto triggersBoxLayout = createDescription("Select trigger:");
	auto triggersBox = createComboBox(TypeItemParam::Trigger);
	triggersBox->setCurrentIndex(interaction.CTrigger().Id());
	connect(triggersBox, &QComboBox::editTextChanged,
			[=, &interaction](const QString& curValue)
	{
		interaction.Action().SetData(interaction.Trigger().GetTag(CBaseItem::Name), curValue.toStdString());
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

QComboBox* CWdgSelectionMenu::createComboBox(const TypeItemParam typeParam)
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
			vecParams = itemInfoGetter.getListWithTypeNames();
			break;
		}
		case TypeItemParam::Action:
		{
			vecParams = itemInfoGetter.getListWithActionNames();
			break;
		}
		case TypeItemParam::Trigger:
		{
			vecParams = itemInfoGetter.getListWithTriggers();
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

QComboBox* CWdgSelectionMenu::createComboBox(const QStringList& typeItemsList)
{
	QCompleter* completer = new QCompleter(typeItemsList, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	auto comboBox = new QComboBox();
	comboBox->addItems(typeItemsList);
	comboBox->setEditable(true);
	comboBox->setCompleter(completer);
	return comboBox;
}

QPushButton* CWdgSelectionMenu::createItemButton()
{
	auto createItemButton = new QPushButton("Add Item");
	connect(createItemButton, &QPushButton::pressed, [=]()
	{
		addElementToScene(m_itemParams);
	});
	return createItemButton;
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
//ToDo refactoring copy-paste
void CWdgSelectionMenu::setStripItemParams(CStripItemConfig& stripItemParams)
{
	m_itemParams = stripItemParams;

	auto paramsMenuLayout = dynamic_cast<QVBoxLayout*>(m_paramsWdgMenu->layout());
	m_paramsWdgMenu->setLayout(paramsMenuLayout);
	clearLayout(paramsMenuLayout);

	auto itemNamesBoxLayout = createDescription("Select item type:");
	auto itemNamesBox = createComboBox(TypeItemParam::Name);
	itemNamesBoxLayout->addWidget(itemNamesBox);
	paramsMenuLayout->addLayout(itemNamesBoxLayout);
	for(size_t interactionIndex = 0; interactionIndex < m_itemParams.GetInteractions().Size(); interactionIndex++)
	{
		auto& interaction = m_itemParams.GetInteractionByIndex(interactionIndex);
		paramsMenuLayout->addWidget(createInteractionBox(interaction));
	}
	paramsMenuLayout->addWidget(createItemButton());

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

bool CWdgSelectionMenu::setDataByType(const TypeItemParam type, const std::string& paramData)
{
	bool result = true;
	switch (type)
	{
		case TypeItemParam::Name:
		{
			m_itemParams.SetItemData(m_itemParams.Item().GetTag(CBaseItem::Name), paramData);
			break;
		}
		case TypeItemParam::Action:
		{
			auto& interaction =  m_itemParams.GetInteractionByIndex(0);
			interaction.Action().SetData(interaction.Action().GetTag(CBaseItem::Name), paramData);
			break;
		}
		case TypeItemParam::Trigger:
		{
			auto& interaction =  m_itemParams.GetInteractionByIndex(0);
			interaction.Trigger().SetData(interaction.Trigger().GetTag(CBaseItem::Name), paramData);
			break;
		}
		default:
		{
			result = false;
			break;
		}
	}
	return result;
}
