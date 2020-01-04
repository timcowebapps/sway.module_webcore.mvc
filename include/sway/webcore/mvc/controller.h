#ifndef _SWAY_WEBCORE_MVC_CONTROLLER_H
#define _SWAY_WEBCORE_MVC_CONTROLLER_H

#include <sway/webcore/mvc/itemmodel.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

class AController {
public:

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] model
	 *    Модель данных.
	 */
	AController(AItemModel */*model::ModelSmartPtr_t*/ model);

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~AController() = default;

#pragma endregion

	/*!
	 * \brief
	 *    Возвращает модель данных.
	 */
	AItemModel * getModel();

private:
	AItemModel * _model; /*!< Модель данных. */
	//view::ViewComponent * _view; /*!< Представление. */
};

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_CONTROLLER_H
