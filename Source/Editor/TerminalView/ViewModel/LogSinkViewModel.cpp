#include "LogSinkViewModel.h"

namespace Strand
{
	LogSinkViewModel::LogSinkViewModel(QObject* pParent) : ViewModelBase(pParent)
	{
		connect(this, &LogSinkViewModel::LogCommandExecuted, this, &LogSinkViewModel::OnLogCommandExecuted);
	}


	void LogSinkViewModel::OnLogCommandExecuted(const QString& command, const QString& value)
	{
		Log::Debug(LogType::Editor, "Command: {} || Value: {}", command.toStdString(), value.toStdString());
	}

	struct LogSinkViewModelRegister
	{
		LogSinkViewModelRegister() { ViewModelRegistry::Get().RegisterVM<LogSinkViewModel>(); }
	};

	static LogSinkViewModelRegister gb_logSinkViewModelRegister;
}
