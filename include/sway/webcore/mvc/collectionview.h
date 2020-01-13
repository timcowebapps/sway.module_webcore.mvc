#ifndef _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H
#define _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H

#include <sway/webcore/mvc/collectionmodel.h>
#include <sway/webcore/mvc/view.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)

/*!
 * \brief
 *    Абстрактное представление.
 */
class ACollectionView
	: public AView {
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
	ACollectionView(core::containers::HierarchyNodePtr_t parent,
		//const core::containers::HierarchyNodeIndex & nodeIndex,
		const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~ACollectionView() = default;

#pragma endregion

	void makeItem(u32_t index, TreeNodeElement * child);

#pragma region "IVisitable > HierarchyNode > TreeNodeElement > AView implementation"

	virtual void accept(ITreeVisitor * visitor) override;

#pragma endregion

	virtual void initialize();

#pragma region "IObserver > AView implementation"

	/*!
	 * \brief
	 *    Обновляет состояние наблюдателя.
	 */
	virtual void update() override;

#pragma endregion
};

class ACollectionViewWrapper : public emscripten::wrapper<ACollectionView> {
public:
	EMSCRIPTEN_WRAPPER(ACollectionViewWrapper)

	void initialize();
	void update();
};

NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H
