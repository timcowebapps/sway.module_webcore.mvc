#include <sway/webcore/mvc/view/itemcollectionview.h>
#include <sway/webcore/mvc/view/itemcollectionviewcomponentwrapper.h>
#include <sway/webcore/mvc/view/itemview.h>
#include <sway/webcore/mvc/model/abstractitemmodel.h>
#include <sway/webcore/base/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)

void AItemCollectionView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AItemCollectionView, emscripten::base<base::TreeNodeElement>>(classname)
		.allow_subclass<AItemCollectionViewComponentWrapper>("AItemCollectionViewComponentWrapper", emscripten::constructor<core::containers::HierarchyNodePtr_t, std::string, base::TreeNodeElementCreateInfo>())
		.constructor<core::containers::HierarchyNodePtr_t, std::string, base::TreeNodeElementCreateInfo>()
		.function("initialize", emscripten::optional_override([](AItemCollectionView & self) {
			return self.AItemCollectionView::initialize();
		}))
		.function("update", emscripten::optional_override([](AItemCollectionView & self) {
			return self.AItemCollectionView::update();
		}))
		.function("makeItem", &AItemCollectionView::makeItem, emscripten::allow_raw_pointers())
		.function("getModel", &AItemCollectionView::getModel, emscripten::allow_raw_pointers())
		.function("setModel", &AItemCollectionView::setModel, emscripten::allow_raw_pointers());
}

AItemCollectionView::AItemCollectionView(core::containers::HierarchyNodePtr_t parent,
	//const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const base::TreeNodeElementCreateInfo & createInfo)
	: base::TreeNodeElement(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo)
	, _model(nullptr) {
	// Empty
}

void AItemCollectionView::initialize() {
	// Empty
}

void AItemCollectionView::update() {
	// Empty
}

void AItemCollectionView::makeItem(u32_t index, base::TreeNodeElement * child) {
	auto collection = static_cast<model::AbstractItemCollection *>(getModel());
	auto item = static_cast<AItemView *>(child);
	item->setNodeId(core::misc::format("%s_%i", item->getNodeId().c_str(), index));
	item->setModel(collection->getItem(index));
	item->initialize();
	addChild(item);
}

void AItemCollectionView::accept(base::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<AItemCollectionView *>(node)->accept(visitor);
}

core::utilities::Observable * AItemCollectionView::getModel() {
	return _model;
}

void AItemCollectionView::setModel(core::utilities::Observable * model) {
	_model = model;
	_model->registerObserver(this);
}

NAMESPACE_END(view)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
