#include "ProjectContentService.h"

#include <Editor/Models/Content/ContentItemModel.h>

namespace Flax
{
	namespace
	{
		struct ProjectContentServiceRegister
		{
			ProjectContentServiceRegister()
			{
				UIService::Register<ProjectContentService>(new ProjectContentService());
			}
		};

		static ProjectContentServiceRegister gbProjectContentService;
	}

	ProjectContentService::ProjectContentService(QObject* parent)
	{
		m_cModel = NewRef<ContentItemModel>(this);
	}
}
