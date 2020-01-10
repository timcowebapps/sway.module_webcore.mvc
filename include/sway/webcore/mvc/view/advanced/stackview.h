#ifndef _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H
#define _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H

#include <sway/webcore/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webcore)
NAMESPACE_BEGIN(mvc)
NAMESPACE_BEGIN(view)
NAMESPACE_BEGIN(advanced)

class StackView
	: public TreeNodeElement {

public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t classname);

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	StackView(core::containers::HierarchyNodePtr_t parent,
		//const core::containers::HierarchyNodeIndex & nodeIndex,
		const std::string & nodeId, const TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~StackView() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement implementation"

	virtual void accept(ITreeVisitor * visitor);

#pragma endregion

#pragma region "General methods"

	void addItem(TreeNodeElement * item);

	void handleItemAdded(const core::containers::HierarchyNodeIndex & nodeIndex);

	void removeItem(TreeNodeElement * item);

#pragma endregion

#pragma region "Getters / Setters"

	u32_t getCurrentItem();

	void setCurrentItem(u32_t nodeIdex);

#pragma endregion

private:
	u32_t _current = 0;
};

NAMESPACE_END(advanced)
NAMESPACE_END(view)
NAMESPACE_END(mvc)
NAMESPACE_END(webcore)
NAMESPACE_END(sway)

#endif // _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H
