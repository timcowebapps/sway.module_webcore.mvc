#ifndef _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H
#define _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H

#include <sway/webcore/mvc/itemmodel.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

class ACollectionModel : public core::utilities::Observable {
public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t name);

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ACollectionModel();

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~ACollectionModel();

#pragma endregion

	u32_t getCountItems() const;

#pragma region "Getters / Setters"

	AItemModel * getItem(u32_t index) const;

	void setItem(AItemModel * value);

	std::vector<AItemModel *> getItems() const;

	void setItems(std::vector<AItemModel *> value);

	void setItems(const emscripten::val & value);

#pragma endregion

private:
	std::vector<AItemModel *> _items;
};

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_COLLECTIONMODEL_H
