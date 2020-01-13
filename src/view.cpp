#include <sway/webcore/mvc/view.h>
#include <sway/webcore/treeupdater.h>
#include <sway/webcore/css/selectors/cnselectorchain.h>
#include <sway/webcore/css/selectors/cnselectordescriptor.h>
#include <sway/webcore/css/selectors/idselector.h>
#include <sway/webcore/css/selectors/cnselector.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

void AView::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<AView, emscripten::base<TreeNodeElement>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t,
			core::containers::HierarchyNodeIndex, std::string, TreeNodeElementCreateInfo>()
		.function("setStyleSheet", &AView::setStyleSheet)
		.function("appendStyle", &AView::appendStyle)
		.function("getModel", &AView::getModel, emscripten::allow_raw_pointers())
		.function("setModel", &AView::setModel, emscripten::allow_raw_pointers())
		.function("addSelector", &AView::addSelector, emscripten::allow_raw_pointers())
		.function("getSelectors", &AView::getSelectors, emscripten::allow_raw_pointers());
}

AView::AView(core::containers::HierarchyNodePtr_t parent,
	const core::containers::HierarchyNodeIndex & nodeIndex,
	const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo)
	: TreeNodeElement(parent, nodeIndex, nodeId, createInfo) {

	addSelector(std::make_shared<css::IdSelector>(createInfo.id));

	auto classes = emscripten::vecFromJSArray<css::CnSelectorDescriptor>(createInfo.classes);
	for (css::CnSelectorDescriptor desc : classes)
		addSelector(std::make_shared<css::CnSelector>(desc.chain));

	if (EmscriptenUtil::isNone(createInfo.stylesheet)) {
		EM_ASM({console.warn("'stylesheet' must be not null")});
	}
	else {
		setStyleSheet(createInfo.stylesheet);
		appendStyle();
	}
}

void AView::accept(ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<AView *>(node)->accept(visitor);
}

void AView::initialize() {
	// Empty
}

void AView::update() {
	// Empty
}

css::StyleSheet AView::getStyleSheet() const {
	return _styleSheet;
}

void AView::setStyleSheet(const emscripten::val & mapper) {
	_styleSheet = css::StyleSheet(mapper);
}

void AView::appendStyle() {
	std::vector<std::string> classnameList;
	for (css::SelectorSmartPtr_t selector : getSelectors()) {
		if (selector->getType() == css::SelectorTypes_t::kCn) {
			css::CnSelector * cnSelector = (css::CnSelector *) selector.get();
			classnameList.push_back(_styleSheet.getClassName(cnSelector->getName()));

			for (std::string mod : cnSelector->getMods())
				classnameList.push_back(_styleSheet.getClassName(
					core::misc::format("%s--%s", cnSelector->getName().c_str(), mod.c_str())));
		}
	}

	setHtmlElementClasses(classnameList);
}

void AView::addSelector(css::SelectorSmartPtr_t selector) {
	_selectors.push_back(selector);
}

css::SelectorVec_t AView::getSelectors() {
	return _selectors;
}

core::utilities::Observable * AView::getModel() {
	return _model;
}

void AView::setModel(core::utilities::Observable * model) {
	_model = model;
	_model->registerObserver(this);
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
