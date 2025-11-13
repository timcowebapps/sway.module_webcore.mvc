"use strict";

import * as _ from "underscore";

export class StackView {
	public wasm_module: any = null;

	/**
	 * Конструктор представления.
	 * 
	 * @method constructor
	 * @param {any} wasm_context Контекст.
	 * @param {any} parent Родительский узел.
	 * @param {any} nodeId Уникальный идентификатор узла.
	 * @param {any} nodeCreateInfo Свойства представления.
	 */
	constructor(public wasm_context: any = null, parent: any, nodeId: string, nodeCreateInfo?: any) {
		this.wasm_module = new wasm_context.module.StackView(parent, nodeId, _.defaults(nodeCreateInfo, {
			stylesheet: null,
			classes: []
		}));
	}
};
