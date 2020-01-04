#include <sway/webcore/mvc/view/itemview.h>
#include <sway/webcore/mvc/view/itemviewcomponentwrapper.h>
#include <sway/webcore/base/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)

void AItemView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AItemView, emscripten::base<AVisualComponent>>(classname)
		.allow_subclass<AItemViewComponentWrapper>("AItemViewComponentWrapper", emscripten::constructor<core::containers::HierarchyNodePtr_t, std::string, base::TreeNodeElementCreateInfo>())
		.constructor<core::containers::HierarchyNodePtr_t, std::string, base::TreeNodeElementCreateInfo>()
		.function("initialize", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::initialize();
		}))
		.function("update", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::update();
		}));
}

AItemView::AItemView(core::containers::HierarchyNodePtr_t parent,
	//const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const base::TreeNodeElementCreateInfo & createInfo)
	: AVisualComponent(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

AItemView::AItemView(core::containers::HierarchyNodePtr_t parent,
	const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const base::TreeNodeElementCreateInfo & createInfo)
	: AVisualComponent(parent, nodeIndex, nodeId, createInfo) {
	// Empty
}

AItemView::~AItemView() {
	//	Empty
}

void AItemView::accept(base::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<AItemView *>(node)->accept(visitor);
}

void AItemView::initialize() {
	// Empty
}

void AItemView::update() {
	//EM_ASM({console.log("ON_ENTRY_CHANGED " + UTF8ToString($0))}, getNodeId().c_str());
}

NAMESPACE_END(base)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
