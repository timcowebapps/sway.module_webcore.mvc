#ifndef _SWAY_WEBCORE_MVC_ITEMVIEW_H
#define _SWAY_WEBCORE_MVC_ITEMVIEW_H

#include <sway/webcore/prereqs.hpp>
#include <sway/webcore/treenodeelement.hpp>

#include <sway/webcore/mvc/view.h>

namespace sway::webcore::mvc {

/**
 * @brief Абстрактное представление.
 */
class AItemView : public AView {
  DECLARE_EMSCRIPTEN_BINDING()

public:
#pragma region "Constructor / Destructor"

  /**
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] name Имя представления.
   * @param[in] options Опции представления.
   */
  AItemView(core::NodePtr_t parent,
      // const core::NodeIndex & nodeIndex,
      const std::string &nodeId, const TreeNodeElementDescriptor &createInfo);

  AItemView(core::NodePtr_t parent, const core::NodeIndex &nodeIndex, const std::string &nodeId,
      const TreeNodeElementDescriptor &createInfo);

  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~AItemView() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement > AView implementation"

  // virtual void accept(ITreeVisitor * visitor) override;
  virtual auto traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t override;

#pragma endregion

  virtual void initialize();

#pragma region "IObserver > AView implementation"

  /**
   * @brief Обновляет состояние наблюдателя.
   */
  virtual void update() override;

#pragma endregion
};

class AItemViewWrapper : public emscripten::wrapper<AItemView> {
public:
  EMSCRIPTEN_WRAPPER(AItemViewWrapper)

  void initialize();
  void update();
};

}  // namespace sway::webcore::mvc

#endif  // _SWAY_WEBCORE_MVC_ITEMVIEW_H
