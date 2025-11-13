#include <sway/webcore/mvc/itemview.h>
#include <sway/webcore/nodeelementupdater.hpp>

namespace sway::webcore::mvc {

void AItemView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AItemView, emscripten::base<AView>>(classname)
		.allow_subclass<AItemViewWrapper>("AItemViewWrapper", emscripten::constructor<core::NodePtr_t, std::string, TreeNodeElementDescriptor>())
		.constructor<core::NodePtr_t, std::string, TreeNodeElementDescriptor>()
		.function("initialize", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::initialize();
		}))
		.function("update", emscripten::optional_override([](AItemView & self) {
			return self.AItemView::update();
		}));
}

AItemView::AItemView(core::NodePtr_t parent,
	//const core::NodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementDescriptor & createInfo)
	: AView(parent, core::NodeIndex(), nodeId, createInfo) {
	// Empty
}

AItemView::AItemView(core::NodePtr_t parent,
	const core::NodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementDescriptor & createInfo)
	: AView(parent, nodeIndex, nodeId, createInfo) {
	// Empty
}

auto AItemView::traverse(core::typedefs::TraverserPtr_t traverser) -> u32_t {
	return core::toBase(core::TraverserAction::Enum::NONE);
}
// void AItemView::accept(ITreeVisitor * visitor) {
// 	visitor->visitOnEnter(this);

// 	for (core::NodePtr_t node : getChildren())
// 		static_cast<AItemView *>(node)->accept(visitor);
// }

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

} // namespace sway::webcore::mvc
