#include <sway/webcore/mvc/model/abstractitemcollection.h>
#include <sway/webcore/mvc/model/abstractitemmodel.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(model)

void AbstractItemCollection::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::register_vector<AbstractItemModel *>("vector<AbstractItemModel>");
	emscripten::class_<AbstractItemCollection, emscripten::base<Observable>>(classname)
		.constructor()
		.function("getCountItems", &AbstractItemCollection::getCountItems)
		.function("getItem", &AbstractItemCollection::getItem, emscripten::allow_raw_pointers())
		.function("setItem", &AbstractItemCollection::setItem, emscripten::allow_raw_pointers())
		.function("getItems", &AbstractItemCollection::getItems, emscripten::allow_raw_pointers())
		.function("setItems", emscripten::select_overload<void(const emscripten::val &)>(&AbstractItemCollection::setItems))
		.function("setItems_alt", emscripten::select_overload<void(std::vector<AbstractItemModel *>)>(&AbstractItemCollection::setItems), emscripten::allow_raw_pointers());
}

AbstractItemCollection::AbstractItemCollection() {
	// Empty
}

AbstractItemCollection::~AbstractItemCollection() {
	// Empty
}

u32_t AbstractItemCollection::getCountItems() const {
	return _items.size();
}

void AbstractItemCollection::setItem(AbstractItemModel * value) {
	_items.push_back(value);
}

AbstractItemModel * AbstractItemCollection::getItem(u32_t index) const {
	return _items[index];
}

void AbstractItemCollection::setItems(std::vector<AbstractItemModel *> value) {
	_items = value;
}

void AbstractItemCollection::setItems(const emscripten::val & value) {
	for(unsigned i = 0; i < value["length"].as<unsigned>(); ++i)
		_items.push_back(new AbstractItemModel(value[i]));
}

std::vector<AbstractItemModel *> AbstractItemCollection::getItems() const {
	return _items;
}

NAMESPACE_END(model)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
