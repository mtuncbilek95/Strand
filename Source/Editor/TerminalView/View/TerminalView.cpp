#include "TerminalView.h"

#include <Editor/TerminalView/Model/LogSinkModel.h>
#include <Editor/TerminalView/ViewModel/LogSinkViewModel.h>

namespace Flax
{
	TerminalView::TerminalView(QWidget* pParent) : QWidget(pParent)
	{
		Ref<LogSinkModel<Mutex>> sink = NewRef<LogSinkModel<Mutex>>();
		sink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%^%l%$][%n] %v");

		for (auto& [type, logger] : LoggerWorker::Get().m_loggers)
			logger->sinks().push_back(sink);

		m_textEdit = new QTextEdit(this);
		m_textEdit->setReadOnly(true);

		m_lineEdit = new QLineEdit(this);
		m_lineEdit->setPlaceholderText("Type command here...");
		m_lineEdit->setFocusPolicy(Qt::StrongFocus);
		m_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		m_lineEdit->setClearButtonEnabled(true);
		m_lineEdit->setFixedHeight(32);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(m_textEdit);
		layout->addWidget(m_lineEdit);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);

		setLayout(layout);

		connectSignals();
	}

	TerminalView::~TerminalView()
	{
	}

	void TerminalView::OnCommandEntered()
	{
		Ref<LogSinkViewModel> vm = ViewModelRegistry::Get().ViewModel<LogSinkViewModel>();

		QString input = m_lineEdit->text().trimmed();

		i32 spaceIndex = input.indexOf(' ');
		QString command, argument;

		if (spaceIndex != -1)
		{
			command = input.left(spaceIndex);
			argument = input.mid(spaceIndex + 1).trimmed();
		}
		else
		{
			command = input;
			argument = "";
		}

		emit vm->LogCommandExecuted(command, argument);
		m_lineEdit->clear();
	}

	void TerminalView::connectSignals()
	{
		Ref<LogSinkViewModel> vm = ViewModelRegistry::Get().ViewModel<LogSinkViewModel>();
		connect(vm.get(), &LogSinkViewModel::LogMessageReceived, this, &TerminalView::OnLogMessageReceived);
		connect(m_lineEdit, &QLineEdit::returnPressed, this, &TerminalView::OnCommandEntered);
	}

	void TerminalView::OnLogMessageReceived(const QString& msg, const QString& category, int level)
	{
		QColor color;

		switch (spdlog::level::level_enum(level))
		{
		case spdlog::level::trace: color = QColor("#7f8c8d");  break;
		case spdlog::level::debug: color = QColor("#95a5a6");  break;
		case spdlog::level::info: color = QColor("#2ecc71");  break;
		case spdlog::level::warn: color = QColor("#f39c12");  break;
		case spdlog::level::err: color = QColor("#e74c3c");  break;
		case spdlog::level::critical: color = QColor("#9b59b6");  break;
		default: color = QColor("#ecf0f1");  break;
		}

		m_textEdit->setTextColor(color);
		m_textEdit->append(msg.trimmed());
	}
}
