#include <sway/webcore/mvc/collectionview.hpp>
#include <sway/webcore/mvc/itemmodel.hpp>
#include <sway/webcore/mvc/itemview.hpp>
#include <sway/webcore/nodeelementupdater.hpp>

namespace sway::webcore::mvc {

EMSCRIPTEN_BINDING_BEGIN(ACollectionView) {
  emscripten::class_<ACollectionView, emscripten::base<AView>>("ACollectionView")
      .allow_subclass<ACollectionViewWrapper>(
          "ACollectionViewWrapper", emscripten::constructor<core::NodePtr_t, std::string, TreeNodeElementDescriptor>())
      .constructor<core::NodePtr_t, std::string, TreeNodeElementDescriptor>()
      .function("initialize",
          emscripten::optional_override([](ACollectionView &self) { return self.ACollectionView::initialize(); }))
      .function(
          "update", emscripten::optional_override([](ACollectionView &self) { return self.ACollectionView::update(); }))
      .function("makeItem", &ACollectionView::makeItem, emscripten::allow_raw_pointers());
}
EMSCRIPTEN_BINDING_END()

ACollectionView::ACollectionView(core::NodePtr_t parent,
    // const core::NodeIndex & nodeIndex,
    const std::string &nodeId, const TreeNodeElementDescriptor &createInfo)
    : AView(parent, core::NodeIndex(), nodeId, createInfo) {
  // Empty
}

void ACollectionView::initialize() {
  // Empty
}

void ACollectionView::update() {
  // Empty
}

void ACollectionView::makeItem(u32_t index, TreeNodeElement *child) {
  auto collection = static_cast<ACollectionModel *>(getModel());
  auto item = static_cast<AItemView *>(child);
  // item->setNodeId(core::format("%s_%i", item->getNodeId().c_str(), index));
  item->setModel(collection->getItem(index));
  item->initialize();
  addChildNode(std::shared_ptr<AItemView>(item));
}

auto ACollectionView::traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t {
  return core::toBase(core::TraverserAction::Enum::NONE);
}
// void ACollectionView::accept(ITreeVisitor * visitor) {
// 	visitor->visitOnEnter(this);

// 	for (core::NodePtr_t node : getChildren())
// 		static_cast<ACollectionView *>(node)->accept(visitor);
// }

void ACollectionViewWrapper::initialize() { return call<void>("initialize"); }

void ACollectionViewWrapper::update() { return call<void>("update"); }

}  // namespace sway::webcore::mvc
