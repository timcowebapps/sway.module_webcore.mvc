#ifndef _SWAY_WEBCORE_MVC_VIEW_H
#define _SWAY_WEBCORE_MVC_VIEW_H

#include <sway/webcore/css/stylesheet.h>
#include <sway/webcore/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

/*!
 * \brief
 *    Абстрактное представление.
 */
class AView
	: public TreeNodeElement
	, public virtual core::utilities::IObserver {
public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t classname);

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] name
	 *    Имя представления.
	 * 
	 * \param[in] options
	 *    Опции представления.
	 */
	AView(core::containers::HierarchyNodePtr_t parent,
		const core::containers::HierarchyNodeIndex & nodeIndex,
		const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~AView() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement implementation"

	virtual void accept(ITreeVisitor * visitor) override;

#pragma endregion

	virtual void initialize();

#pragma region "IObserver implementation"

	/*!
	 * \brief
	 *    Обновляет состояние наблюдателя.
	 */
	virtual void update() override;

#pragma endregion

#pragma region "Getters / Setters"

	css::StyleSheet getStyleSheet() const;

	void setStyleSheet(const emscripten::val & mapper);
	
	void appendStyle();

	void addSelector(css::SelectorSmartPtr_t selector);
	
	css::SelectorVec_t getSelectors();

	/*!
	 * \brief
	 *    Возвращает модель данных.
	 */
	core::utilities::Observable * getModel();

	/*!
	 * \brief
	 *    Устанавливает модель данных.
	 * 
	 * \param[in] model
	 *    Модель данных.
	 */
	void setModel(core::utilities::Observable * model);

#pragma endregion

private:
	css::StyleSheet _styleSheet;
	css::SelectorVec_t _selectors;
	core::utilities::Observable * _model = nullptr; /*!< Модель данных. */
};

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_VIEW_H
