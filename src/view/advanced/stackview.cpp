#include <sway/webcore/mvc/view/advanced/stackview.h>
#include <sway/webcore/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)
NAMESPACE_BEGIN(advanced)

void StackView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<StackView, emscripten::base<TreeNodeElement>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, TreeNodeElementCreateInfo>()
		.function("addItem", &StackView::addItem, emscripten::allow_raw_pointers())
		.function("removeItem", &StackView::removeItem, emscripten::allow_raw_pointers())
		.function("getCurrentItem", &StackView::getCurrentItem)
		.function("setCurrentItem", &StackView::setCurrentItem);
}

StackView::StackView(core::containers::HierarchyNodePtr_t parent,
	//const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo)
	: TreeNodeElement(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void StackView::accept(ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<StackView *>(node)->accept(visitor);
}

void StackView::addItem(TreeNodeElement * item) {
	item->setVisible(false);
	add(item, std::bind(&StackView::handleItemAdded, this, std::placeholders::_1));
}

void StackView::handleItemAdded(const core::containers::HierarchyNodeIndex & nodeIndex) {
	EM_ASM({console.log("STACK_VIEW ITEM ADDED")});
}

void StackView::removeItem(TreeNodeElement * item) {
	removeChild(item);
}

u32_t StackView::getCurrentItem() {
	return _current;
}

void StackView::setCurrentItem(u32_t nodeIdex) {
	_current = nodeIdex;

	for (core::containers::HierarchyNodePtr_t child : getChildren())
		static_cast<TreeNodeElement *>(child)->setVisible(false);

	TreeNodeElement * item = getChildAt<TreeNodeElement *>(nodeIdex);
	item->setVisible(true);

	for (core::containers::HierarchyListener * listener : getHostTree()->getListeners())
		listener->onNodeUpdated(item->getNodeIndex());
}

NAMESPACE_END(advanced)
NAMESPACE_END(view)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
