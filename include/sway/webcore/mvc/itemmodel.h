#ifndef _SWAY_WEBCORE_MVC_ITEMMODEL_H
#define _SWAY_WEBCORE_MVC_ITEMMODEL_H

#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

typedef std::shared_ptr<class AItemModel> ModelSmartPtr_t;

class AItemModel : public core::utilities::Observable {
public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t name);

	static ModelSmartPtr_t create();

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	AItemModel();

	AItemModel(emscripten::val object);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~AItemModel();

#pragma endregion

#pragma region "Getters / Setters"

	emscripten::val getProperty(const std::string & key) const;

	/*!
	 * \brief
	 *    Устанавливает свойство модели данных.
	 * 
	 * \param[in] key
	 *    Ключ.
	 * 
	 * \param[in] value
	 *    Значение.
	 */
	void setProperty(const std::string & key, const emscripten::val & value);

	emscripten::val getProperties() const;

	void setProperties(emscripten::val value);

#pragma endregion

private:
	emscripten::val _properties;
};

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_ITEMMODEL_H
