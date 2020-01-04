#ifndef _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMMODEL_H
#define _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMMODEL_H

#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(model)

typedef std::shared_ptr<class AbstractItemModel> ModelSmartPtr_t;

class AbstractItemModel : public core::utilities::Observable {
public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t name);

	static ModelSmartPtr_t create();

#pragma endregion // Static methods

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	AbstractItemModel();

	AbstractItemModel(emscripten::val object);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~AbstractItemModel();

#pragma endregion // Constructor / Destructor

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

#pragma endregion // Getters / Setters

private:
	emscripten::val _properties;
};

NAMESPACE_END(model)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_MODEL_ABSTRACTITEMMODEL_H
