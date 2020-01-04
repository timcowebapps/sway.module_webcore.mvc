#include <sway/webcore/mvc/controller/abstractcontroller.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(controller)

AbstractController::AbstractController(model::AbstractItemModel */*model::ModelSmartPtr_t*/ model)
	: _model(model) {
	// Empty
}

AbstractController::~AbstractController() {
	// Empty
}

model::AbstractItemModel */*model::ModelSmartPtr_t*/ AbstractController::getModel() {
	return _model;
}

NAMESPACE_END(controller)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)
