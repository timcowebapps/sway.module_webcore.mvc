#include <sway/webcore/mvc/itemmodel.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

void AItemModel::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AItemModel, emscripten::base<Observable>>(classname)
		.constructor()
		.smart_ptr<ModelSmartPtr_t>(core::misc::format("shared_ptr<%s>", classname).c_str())
		.class_function("create", &AItemModel::create)
		.function("setProperty", &AItemModel::setProperty)
		.function("getProperty", &AItemModel::getProperty)
		.function("setProperties", &AItemModel::setProperties)
		.function("getProperties", &AItemModel::getProperties);
}

ModelSmartPtr_t AItemModel::create() {
	return std::make_shared<AItemModel>();
}

AItemModel::AItemModel(emscripten::val object)
	: _properties(object) {
	// Empty
}

AItemModel::AItemModel()
	: _properties(emscripten::val::object()) {
	// Empty
}

AItemModel::~AItemModel() {
	// Empty
}

emscripten::val AItemModel::getProperty(const std::string & key) const {
	return _properties[key];
}

void AItemModel::setProperty(const std::string & key, const emscripten::val & value) {
	_properties.set(key, value);
	notify();
}

emscripten::val AItemModel::getProperties() const {
	return _properties;
}

void AItemModel::setProperties(emscripten::val value) {
	_properties = value;
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
