#ifndef _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H
#define _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H

#include <sway/webcore/treenodeelement.hpp>
#include <sway/webcore/prereqs.hpp>

namespace sway::webcore::mvc {

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
	StackView(core::NodePtr_t parent,
		//const core::NodeIndex & nodeIndex,
		const std::string & nodeId, const TreeNodeElementDescriptor & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~StackView() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement implementation"

	// virtual void accept(ITreeVisitor * visitor);
	 virtual auto traverse(core::typedefs::TraverserPtr_t traverser) -> u32_t override;

#pragma endregion

#pragma region "General methods"

	void addItem(TreeNodeElement * item);

	void handleItemAdded(const core::NodeIndex & nodeIndex);

	void removeItem(TreeNodeElement * item);

#pragma endregion

#pragma region "Getters / Setters"

	u32_t getCurrentItem();

	void setCurrentItem(u32_t nodeIdex);

#pragma endregion

private:
	u32_t _current = 0;
};

} // namespace sway::webcore::mvc

#endif // _SWAY_WEBCORE_MVC_VIEW_ADVANCED_STACKVIEW_H
