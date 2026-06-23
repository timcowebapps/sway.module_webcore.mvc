#ifndef _SWAY_WEBCORE_MVC_VIEW_H
#define _SWAY_WEBCORE_MVC_VIEW_H

#include <sway/webcore/css/stylesheet.hpp>
#include <sway/webcore/prereqs.hpp>
#include <sway/webcore/treenodeelement.hpp>

#ifdef EMSCRIPTEN_PLATFORM
#  include <emscripten/emscripten.h>
#  include <emscripten/val.h>
#  ifdef EMSCRIPTEN_USE_BINDINGS
#    include <emscripten/bind.h>
#  endif
#endif

namespace sway::webcore::mvc {

/**
 * @brief Абстрактное представление.
 */
class AView : public TreeNodeElement {
  DECLARE_EMSCRIPTEN_BINDING()

public:
#pragma region "Constructor / Destructor"

  /**
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] name Имя представления.
   * @param[in] options Опции представления.
   */
  AView(core::NodePtr_t parent, const core::NodeIndex &nodeIndex, const std::string &nodeId,
      const TreeNodeElementDescriptor &createInfo);

  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~AView() = default;

#pragma endregion

#pragma region "Visitable > HierarchyNode > TreeNodeElement implementation"

  // virtual void accept(ITreeVisitor * visitor) override;
  virtual auto traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t override;

#pragma endregion

  virtual void initialize();

#pragma region "Observer implementation"

  /**
   * @brief Обновляет состояние наблюдателя.
   */
  virtual void update();  // override;

#pragma endregion

#pragma region "Getters / Setters"

  auto getStyleSheet() const -> StyleSheet;

  void setStyleSheet(const emscripten::val &mapper);

  void appendStyle();

  void addSelector(std::shared_ptr<Selector> selector);

  auto getSelectors() -> std::vector<std::shared_ptr<Selector>>;

  /**
   * \brief Возвращает модель данных.
   */
  auto getModel() -> core::Observable *;

  /**
   * @brief Устанавливает модель данных.
   * @param[in] model Модель данных.
   */
  void setModel(core::Observable *model);

#pragma endregion

private:
  StyleSheet _styleSheet;
  std::vector<std::shared_ptr<Selector>> _selectors;
  core::Observable *_model = nullptr;  //!< Модель данных.
};

}  // namespace sway::webcore::mvc

#endif  // _SWAY_WEBCORE_MVC_VIEW_H
