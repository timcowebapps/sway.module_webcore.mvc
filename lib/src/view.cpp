#include <sway/webcore/mvc/view.h>
#include <sway/webcore/nodeelementupdater.hpp>
#include <sway/webcore/css/selectors/cnselectorchain.hpp>
#include <sway/webcore/css/selectors/cnselectordescriptor.hpp>
#include <sway/webcore/css/selectors/idselector.hpp>
#include <sway/webcore/css/selectors/cnselector.hpp>

namespace sway::webcore::mvc {

void AView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AView, emscripten::base<TreeNodeElement>>(classname)
		.constructor<core::NodePtr_t,
			core::NodeIndex, std::string, TreeNodeElementDescriptor>()
		.function("setStyleSheet", &AView::setStyleSheet)
		.function("appendStyle", &AView::appendStyle)
		.function("getModel", &AView::getModel, emscripten::allow_raw_pointers())
		.function("setModel", &AView::setModel, emscripten::allow_raw_pointers())
		.function("addSelector", &AView::addSelector, emscripten::allow_raw_pointers())
		.function("getSelectors", &AView::getSelectors, emscripten::allow_raw_pointers());
}

AView::AView(core::NodePtr_t parent,
	const core::NodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementDescriptor & createInfo)
	: TreeNodeElement(
		// parent, nodeIndex, nodeId, 
		createInfo), _styleSheet(createInfo.stylesheet) {

	addSelector(std::make_shared<IdSelector>(createInfo.id));

	auto classes = emscripten::vecFromJSArray<CnSelectorDescriptor>(createInfo.classes);
	for (CnSelectorDescriptor desc : classes)
		addSelector(std::make_shared<CnSelector>(desc.chain));

	if (EmscriptenUtil::isNone(createInfo.stylesheet)) {
		EM_ASM({console.warn("'stylesheet' must be not null")});
	}
	else {
		setStyleSheet(createInfo.stylesheet);
		appendStyle();
	}
}

auto AView::traverse(core::typedefs::TraverserPtr_t traverser) -> u32_t {
	return core::toBase(core::TraverserAction::Enum::NONE);
}
// void AView::accept(ITreeVisitor * visitor) {
// 	visitor->visitOnEnter(this);

// 	for (core::NodePtr_t node : getChildren())
// 		static_cast<AView *>(node)->accept(visitor);
// }

void AView::initialize() {
	// Empty
}

void AView::update() {
	// Empty
}

StyleSheet AView::getStyleSheet() const {
	return _styleSheet;
}

void AView::setStyleSheet(const emscripten::val & mapper) {
	_styleSheet = StyleSheet(mapper);
}

void AView::appendStyle() {
	std::vector<std::string> classnameList;
	for (std::shared_ptr<Selector> selector : getSelectors()) {
		if (selector->getType() == SelectorType::CN) {
			CnSelector * cnSelector = (CnSelector *) selector.get();
			classnameList.push_back(_styleSheet.getClassName(cnSelector->getName()));

			for (std::string mod : cnSelector->getMods())
				classnameList.push_back(_styleSheet.getClassName(
					core::format("%s--%s", cnSelector->getName().c_str(), mod.c_str())));
		}
	}

	setHtmlElementClasses(classnameList);
}

void AView::addSelector(std::shared_ptr<Selector> selector) {
	_selectors.push_back(selector);
}

auto AView::getSelectors() -> std::vector<std::shared_ptr<Selector>> {
	return _selectors;
}

core::Observable * AView::getModel() {
	return _model;
}

void AView::setModel(core::Observable * model) {
	_model = model;
	// _model->addObserver(this);
}

} // namespace sway::webcore::mvc
