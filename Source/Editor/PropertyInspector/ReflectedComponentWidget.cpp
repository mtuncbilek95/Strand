#include "ReflectedComponentWidget.h"

#include <Runtime/SceneGraph/IComponent.h>

#include <Editor/Data/Vector/Vector1Widget.h>
#include <Editor/Data/Vector/Vector2Widget.h>
#include <Editor/Data/Vector/Vector3Widget.h>
#include <Editor/Data/Vector/Vector4Widget.h>

#include <Editor/PropertyInspector/ComponentTabWidget.h>

namespace Strand
{
	ReflectedComponentWidget::ReflectedComponentWidget(IComponent* pComponent, QWidget* pParent) : QWidget(pParent),
		m_component(pComponent)
	{
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		m_titleWidget = new ComponentTabWidget(QString::fromStdString(pComponent->GetClass()->className), this);

		mainLayout->addWidget(m_titleWidget);

		for (auto& field : pComponent->GetClass()->fields)
		{
			if (field.second.fieldTypeInfo.typeName == typeid(Math::Vec3f).name())
			{
				auto* vectorWidget = new Vector3Widget(QString::fromStdString(field.second.fieldName), this);
				mainLayout->addWidget(vectorWidget);
			}
		}

		connect(m_titleWidget, &ComponentTabWidget::onComponentChecked, this, &ReflectedComponentWidget::onComponentChecked);
	}

	ReflectedComponentWidget::~ReflectedComponentWidget()
	{
		for (auto& conn : m_connections)
			disconnect(conn);

		m_connections.clear();
	}

	void ReflectedComponentWidget::onComponentChecked(b8 state)
	{
		m_component->SetEnabled(state);

		if (layout())
		{
			for (int i = 0; i < layout()->count(); ++i)
			{
				QWidget* widget = layout()->itemAt(i)->widget();
				if (widget && widget != m_titleWidget)
					widget->setEnabled(state);
			}
		}
	}
}