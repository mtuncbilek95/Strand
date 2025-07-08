#include "EditorWindowViewModel.h"

#include <magic_enum/magic_enum.hpp>

namespace Flax
{
	EditorWindowViewModel::EditorWindowViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
	}

	EditorWindowViewModel::~EditorWindowViewModel()
	{
	}

	void EditorWindowViewModel::Construct()
	{
		for (usize i = 0; i < magic_enum::enum_count<EditorDirection>(); i++)
			m_deck.insert({ EditorDirection(i), new QTabWidget() });
	}

	void EditorWindowViewModel::AddTab(EditorDirection dir, QWidget* pWidget, const QString& printedName)
	{
		auto it = m_deck.find(dir);

		if (it == m_deck.end())
		{
			Log::Error(LogType::Editor, "Could not find the QTabWidget in the '{}'", magic_enum::enum_name<EditorDirection>(dir));
			return;
		}

		it->second->addTab(pWidget, printedName);
	}

	struct EditorWindowViewModelRegister
	{
		EditorWindowViewModelRegister() { ViewModelRegistry::Get().RegisterVM<EditorWindowViewModel>(); }
	};
	static EditorWindowViewModelRegister gb_editorWindowViewModelRegister;
}
