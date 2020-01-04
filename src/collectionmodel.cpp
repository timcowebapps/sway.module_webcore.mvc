#include <sway/webcore/mvc/collectionmodel.h>
#include <sway/webcore/mvc/itemmodel.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

void ACollectionModel::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::register_vector<AItemModel *>("vector<AItemModel>");
	emscripten::class_<ACollectionModel, emscripten::base<Observable>>(classname)
		.constructor()
		.function("getCountItems", &ACollectionModel::getCountItems)
		.function("getItem", &ACollectionModel::getItem, emscripten::allow_raw_pointers())
		.function("setItem", &ACollectionModel::setItem, emscripten::allow_raw_pointers())
		.function("getItems", &ACollectionModel::getItems, emscripten::allow_raw_pointers())
		.function("setItems", emscripten::select_overload<void(const emscripten::val &)>(&ACollectionModel::setItems))
		.function("setItems_alt", emscripten::select_overload<void(std::vector<AItemModel *>)>(&ACollectionModel::setItems), emscripten::allow_raw_pointers());
}

ACollectionModel::ACollectionModel() {
	// Empty
}

ACollectionModel::~ACollectionModel() {
	// Empty
}

u32_t ACollectionModel::getCountItems() const {
	return _items.size();
}

void ACollectionModel::setItem(AItemModel * value) {
	_items.push_back(value);
}

AItemModel * ACollectionModel::getItem(u32_t index) const {
	return _items[index];
}

void ACollectionModel::setItems(std::vector<AItemModel *> value) {
	_items = value;
}

void ACollectionModel::setItems(const emscripten::val & value) {
	for(unsigned i = 0; i < value["length"].as<unsigned>(); ++i)
		_items.push_back(new AItemModel(value[i]));
}

std::vector<AItemModel *> ACollectionModel::getItems() const {
	return _items;
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
