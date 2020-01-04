#ifndef _SWAY_WEBCORE_MVC_VIEW_AITEMVIEWCOMPONENTWRAPPER_H
#define _SWAY_WEBCORE_MVC_VIEW_AITEMVIEWCOMPONENTWRAPPER_H

#include <sway/webcore/mvc/view/itemview.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)

class AItemViewComponentWrapper : public emscripten::wrapper<AItemView> {
public:
	EMSCRIPTEN_WRAPPER(AItemViewComponentWrapper)

	void initialize();
	void update();
};

NAMESPACE_END(view)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_VIEW_AITEMVIEWCOMPONENTWRAPPER_H
