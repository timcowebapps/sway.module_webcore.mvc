#ifndef _SWAY_WEBCORE_MVC_CONTROLLER_ABSTRACTCONTROLLER_H
#define _SWAY_WEBCORE_MVC_CONTROLLER_ABSTRACTCONTROLLER_H

#include <sway/webcore/mvc/model/abstractitemmodel.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(controller)

class AbstractController {
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
	AbstractController(model::AbstractItemModel */*model::ModelSmartPtr_t*/ model);

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~AbstractController();

#pragma endregion // Constructor / Destructor

	/*!
	 * \brief
	 *    Возвращает модель данных.
	 */
	model::AbstractItemModel * getModel();

private:
	model::AbstractItemModel * _model; /*!< Модель данных. */
	//view::ViewComponent * _view; /*!< Представление. */
};

NAMESPACE_END(controller)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_CONTROLLER_ABSTRACTCONTROLLER_H
