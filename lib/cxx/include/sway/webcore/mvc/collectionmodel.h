#ifndef _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H
#define _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H

#include <sway/webcore.h>
#include <sway/webcore/mvc/itemmodel.h>

namespace sway::webcore::mvc {

class ACollectionModel : public core::Observable {
  DECLARE_EMSCRIPTEN_BINDING()

public:
#pragma region "Constructor / Destructor"

  /**
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   */
  ACollectionModel();

  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~ACollectionModel();

#pragma endregion

  u32_t getCountItems() const;

#pragma region "Getters / Setters"

  AItemModel *getItem(u32_t index) const;

  void setItem(AItemModel *value);

  std::vector<AItemModel *> getItems() const;

  void setItems(std::vector<AItemModel *> value);

  void setItems(const emscripten::val &value);

#pragma endregion

private:
  std::vector<AItemModel *> _items;
};

}  // namespace sway::webcore::mvc

#endif  // _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H
