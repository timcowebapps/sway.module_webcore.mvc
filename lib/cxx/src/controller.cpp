#include <sway/webcore/mvc/controller.hpp>

namespace sway::webcore::mvc {

AController::AController(AItemModel * /*model::ModelSmartPtr_t*/ model)
    : _model(model) {
  // Empty
}

AItemModel * /*model::ModelSmartPtr_t*/ AController::getModel() { return _model; }

}  // namespace sway::webcore::mvc
