#ifndef _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H
#define _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H

#include <sway/webcore/mvc/collectionmodel.h>
#include <sway/webcore/mvc/view.h>
#include <sway/webcore/prereqs.hpp>

#ifdef EMSCRIPTEN_PLATFORM
#  include <emscripten/emscripten.h>
#  include <emscripten/val.h>
#  ifdef EMSCRIPTEN_USE_BINDINGS
#    include <emscripten/bind.h>
#  endif
#endif

namespace sway::webcore::mvc {

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
	ACollectionView(core::NodePtr_t parent,
		//const core::NodeIndex & nodeIndex,
		const std::string & nodeId, const TreeNodeElementDescriptor & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~ACollectionView() = default;

#pragma endregion

	void makeItem(u32_t index, TreeNodeElement * child);

#pragma region "Visitable > HierarchyNode > TreeNodeElement > AView implementation"

	// virtual void accept(ITreeVisitor * visitor) override;
	 virtual auto traverse(core::typedefs::TraverserPtr_t traverser) -> u32_t override;

#pragma endregion

	virtual void initialize();

#pragma region "Observer > AView implementation"

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

} // namespace sway::webcore::mvc

#endif // _SWAY_WEBCORE_MVC_COLLECTIONVIEW_H
