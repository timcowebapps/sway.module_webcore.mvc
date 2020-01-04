#ifndef _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMCOLLECTION_H
#define _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMCOLLECTION_H

#include <sway/webcore/mvc/model/abstractitemmodel.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(model)

class AbstractItemCollection : public core::utilities::Observable {
public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t name);

#pragma endregion // Static methods

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	AbstractItemCollection();

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~AbstractItemCollection();

#pragma endregion // Constructor / Destructor

	u32_t getCountItems() const;

#pragma region "Getters / Setters"

	AbstractItemModel * getItem(u32_t index) const;

	void setItem(AbstractItemModel * value);

	std::vector<AbstractItemModel *> getItems() const;

	void setItems(std::vector<AbstractItemModel *> value);

	void setItems(const emscripten::val & value);

#pragma endregion // Getters / Setters

private:
	std::vector<AbstractItemModel *> _items;
};

NAMESPACE_END(model)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMCOLLECTION_H
