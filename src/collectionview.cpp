#include <sway/webcore/mvc/collectionview.h>
#include <sway/webcore/mvc/itemview.h>
#include <sway/webcore/mvc/itemmodel.h>
#include <sway/webcore/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

void ACollectionView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<ACollectionView, emscripten::base<AVisualComponent>>(classname)
		.allow_subclass<ACollectionViewWrapper>("ACollectionViewWrapper", emscripten::constructor<core::containers::HierarchyNodePtr_t, std::string, TreeNodeElementCreateInfo>())
		.constructor<core::containers::HierarchyNodePtr_t, std::string, TreeNodeElementCreateInfo>()
		.function("initialize", emscripten::optional_override([](ACollectionView & self) {
			return self.ACollectionView::initialize();
		}))
		.function("update", emscripten::optional_override([](ACollectionView & self) {
			return self.ACollectionView::update();
		}))
		.function("makeItem", &ACollectionView::makeItem, emscripten::allow_raw_pointers());
}

ACollectionView::ACollectionView(core::containers::HierarchyNodePtr_t parent,
	//const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo)
	: AVisualComponent(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void ACollectionView::initialize() {
	// Empty
}

void ACollectionView::update() {
	// Empty
}

void ACollectionView::makeItem(u32_t index, TreeNodeElement * child) {
	auto collection = static_cast<ACollectionModel *>(getModel());
	auto item = static_cast<AItemView *>(child);
	item->setNodeId(core::misc::format("%s_%i", item->getNodeId().c_str(), index));
	item->setModel(collection->getItem(index));
	item->initialize();
	addChild(item);
}

void ACollectionView::accept(ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<ACollectionView *>(node)->accept(visitor);
}

void ACollectionViewWrapper::initialize() {
	return call<void>("initialize");
}

void ACollectionViewWrapper::update() {
	return call<void>("update");
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
