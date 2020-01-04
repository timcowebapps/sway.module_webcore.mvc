#include <sway/webcore/mvc/view/itemviewcomponentwrapper.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)

void AItemViewComponentWrapper::initialize() {
	return call<void>("initialize");
}

void AItemViewComponentWrapper::update() {
	return call<void>("update");
}

NAMESPACE_END(view)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
