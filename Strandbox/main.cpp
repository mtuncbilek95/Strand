#include <Runtime/Reflection/Reflection.h>
#include <Runtime/SceneGraph/Components/TransformComponent.h>

using namespace Strand;

int main()
{
	IComponent* testing = new TransformComponent();
	
	auto val = ReflectionRegistry::Get().GetFieldInfo(testing->GetClass(), "Position")->GetValue<Math::Vec3f>(testing);
	printf("X:%f Y:%f Z:%f\n", val->x, val->y, val->z);
	ReflectionRegistry::Get().GetFieldInfo(testing->GetClass(), "Position")->SetValue<Math::Vec3f>(testing, Math::Vec3f(5.f, 6.f, 7.f));
	printf("X:%f Y:%f Z:%f\n", val->x, val->y, val->z);
}