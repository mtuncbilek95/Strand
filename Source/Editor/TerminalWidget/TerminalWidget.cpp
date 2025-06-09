#include "TerminalWidget.h"

namespace Flax
{
	TerminalWidget::TerminalWidget(QWidget* pParent) : QWidget(pParent)
	{
		auto sink = NewRef<QSink>();
		sink->set_pattern("[%Y-%m-%d][%H:%M:%S.%e][%^%l%$][%n] %v");

		for (auto& [type, logger] : LoggerWorker::Get().m_loggers)
			logger->sinks().push_back(sink);

		m_textEdit = new QTextEdit(this);
		m_textEdit->setReadOnly(true);

		auto layout = new QVBoxLayout(this);
		layout->addWidget(m_textEdit);
		layout->setContentsMargins(0, 0, 0, 0);
		setLayout(layout);

		connect(LogReceiver::Get(), &LogReceiver::LogMessageReceived,
			this, &TerminalWidget::OnLogMessageReceived);
	}

	TerminalWidget::~TerminalWidget()
	{
	}

	void TerminalWidget::OnLogMessageReceived(const QString& msg, const QString& category, int level)
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
