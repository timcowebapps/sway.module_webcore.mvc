#include <sway/webcore/nodeelementupdater.hpp>

#include <sway/webcore/mvc/view/advanced/stackview.h>

namespace sway::webcore::mvc {

EMSCRIPTEN_BINDING_BEGIN(StackView) {
  emscripten::class_<StackView, emscripten::base<TreeNodeElement>>("StackView")
      .constructor<core::NodePtr_t, std::string, TreeNodeElementDescriptor>()
      .function("addItem", &StackView::addItem, emscripten::allow_raw_pointers())
      .function("removeItem", &StackView::removeItem, emscripten::allow_raw_pointers())
      .function("getCurrentItem", &StackView::getCurrentItem)
      .function("setCurrentItem", &StackView::setCurrentItem);
}
EMSCRIPTEN_BINDING_END()

StackView::StackView(core::NodePtr_t parent,
    // const core::NodeIndex & nodeIndex,
    const std::string &nodeId, const TreeNodeElementDescriptor &createInfo)
    : TreeNodeElement(
          // parent, core::NodeIndex(), nodeId,
          createInfo) {
  // Empty
}

auto StackView::traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t {
  return core::toBase(core::TraverserAction::Enum::NONE);
}
// void StackView::accept(ITreeVisitor * visitor) {
// 	visitor->visitOnEnter(this);

// 	for (core::NodePtr_t node : getChildren())
// 		static_cast<StackView *>(node)->accept(visitor);
// }

void StackView::addItem(TreeNodeElement *item) {
  // item->setVisible(false);
  // add(item, std::bind(&StackView::handleItemAdded, this, std::placeholders::_1));
}

void StackView::handleItemAdded(const core::NodeIndex &nodeIndex) { EM_ASM({console.log("STACK_VIEW ITEM ADDED")}); }

void StackView::removeItem(TreeNodeElement *item) {
  // removeChild(item);
}

u32_t StackView::getCurrentItem() { return _current; }

void StackView::setCurrentItem(u32_t nodeIdex) {
  _current = nodeIdex;

  // for (core::NodePtr_t child : getChildren())
  // 	static_cast<TreeNodeElement *>(child)->setVisible(false);

  // TreeNodeElement * item = getChildAt<TreeNodeElement *>(nodeIdex);
  // item->setVisible(true);

  // for (TreeListener * listener : getHostTree()->getListeners())
  // 	listener->onNodeUpdated(item->getNodeIndex());
}

}  // namespace sway::webcore::mvc
