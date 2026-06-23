#include <sway/webcore/mvc/collectionmodel.h>
#include <sway/webcore/mvc/itemmodel.h>

namespace sway::webcore::mvc {

EMSCRIPTEN_BINDING_BEGIN(ACollectionModel) {
  emscripten::register_vector<AItemModel *>("vector<AItemModel>");
  emscripten::class_<ACollectionModel, emscripten::base<Observable>>("ACollectionModel")
      .constructor()
      .function("getCountItems", &ACollectionModel::getCountItems)
      .function("getItem", &ACollectionModel::getItem, emscripten::allow_raw_pointers())
      .function("setItem", &ACollectionModel::setItem, emscripten::allow_raw_pointers())
      .function("getItems", &ACollectionModel::getItems, emscripten::allow_raw_pointers())
      .function("setItems", emscripten::select_overload<void(const emscripten::val &)>(&ACollectionModel::setItems))
      .function("setItems_alt",
          emscripten::select_overload<void(std::vector<AItemModel *>)>(&ACollectionModel::setItems),
          emscripten::allow_raw_pointers());
}
EMSCRIPTEN_BINDING_END()

ACollectionModel::ACollectionModel() {
  // Empty
}

ACollectionModel::~ACollectionModel() {
  // Empty
}

u32_t ACollectionModel::getCountItems() const { return _items.size(); }

void ACollectionModel::setItem(AItemModel *value) { _items.push_back(value); }

AItemModel *ACollectionModel::getItem(u32_t index) const { return _items[index]; }

void ACollectionModel::setItems(std::vector<AItemModel *> value) { _items = value; }

void ACollectionModel::setItems(const emscripten::val &value) {
  for (unsigned i = 0; i < value["length"].as<unsigned>(); ++i)
    _items.push_back(new AItemModel(value[i]));
}

std::vector<AItemModel *> ACollectionModel::getItems() const { return _items; }

}  // namespace sway::webcore::mvc
