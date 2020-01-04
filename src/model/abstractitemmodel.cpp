#include <sway/webcore/mvc/model/abstractitemmodel.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(model)

void AbstractItemModel::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AbstractItemModel, emscripten::base<Observable>>(classname)
		.constructor()
		.smart_ptr<ModelSmartPtr_t>(core::misc::format("shared_ptr<%s>", classname).c_str())
		.class_function("create", &AbstractItemModel::create)
		.function("setProperty", &AbstractItemModel::setProperty)
		.function("getProperty", &AbstractItemModel::getProperty)
		.function("setProperties", &AbstractItemModel::setProperties)
		.function("getProperties", &AbstractItemModel::getProperties);
}

ModelSmartPtr_t AbstractItemModel::create() {
	return std::make_shared<AbstractItemModel>();
}

AbstractItemModel::AbstractItemModel(emscripten::val object)
	: _properties(object) {
	// Empty
}

AbstractItemModel::AbstractItemModel()
	: _properties(emscripten::val::object()) {
	// Empty
}

AbstractItemModel::~AbstractItemModel() {
	// Empty
}

emscripten::val AbstractItemModel::getProperty(const std::string & key) const {
	return _properties[key];
}

void AbstractItemModel::setProperty(const std::string & key, const emscripten::val & value) {
	_properties.set(key, value);
	notify();
}

emscripten::val AbstractItemModel::getProperties() const {
	return _properties;
}

void AbstractItemModel::setProperties(emscripten::val value) {
	_properties = value;
}

NAMESPACE_END(model)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
