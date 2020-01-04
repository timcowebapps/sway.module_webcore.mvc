#include <sway/webcore/mvc/controller.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

AController::AController(AItemModel */*model::ModelSmartPtr_t*/ model)
	: _model(model) {
	// Empty
}

AItemModel */*model::ModelSmartPtr_t*/ AController::getModel() {
	return _model;
}

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
