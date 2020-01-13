#include <sway/webcore/mvc/itemview.h>
#include <sway/webcore/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

void AItemView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AItemView, emscripten::base<AView>>(classname)
		.allow_subclass<AItemViewWrapper>("AItemViewWrapper", emscripten::constructor<core::containers::HierarchyNodePtr_t, std::string, TreeNodeElementCreateInfo>())
		.constructor<core::containers::HierarchyNodePtr_t, std::string, TreeNodeElementCreateInfo>()
		.function("initialize", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::initialize();
		}))
		.function("update", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::update();
		}));
}

AItemView::AItemView(core::containers::HierarchyNodePtr_t parent,
	//const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo)
	: AView(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

AItemView::AItemView(core::containers::HierarchyNodePtr_t parent,
	const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo)
	: AView(parent, nodeIndex, nodeId, createInfo) {
	// Empty
}

void AItemView::accept(ITreeVisitor * visitor) {
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

void AItemViewWrapper::initialize() {
	return call<void>("initialize");
}

void AItemViewWrapper::update() {
	return call<void>("update");
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
