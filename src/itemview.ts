"use strict";

import * as _ from "underscore";
import * as Handlebars from "handlebars";

export class AItemView {
	public wasm_module: any = null;

	/**
	 * Конструктор представления.
	 * 
	 * @method constructor
	 * @param {any} wasm_context Контекст.
	 * @param {any} wasm_parent Родительский узел.
	 * @param {string} nodeId Уникальный идентификатор узла.
	 * @param {any} nodeCreateInfo Свойства представления.
	 */
	constructor(public wasm_context: any = null, public wasm_parent: any = null, nodeId: string, nodeCreateInfo?: any) {
		this.wasm_module = function (self: any) {
			var AItemViewObject = wasm_context.module.AItemView.extend("AItemView", {
				__construct: function(parent: any, nodeId: string, nodeCreateInfo: any) {
					this.__parent.__construct.call(this, parent, nodeId, _.defaults(nodeCreateInfo, {
						stylesheet: null,
						classes: []
					}));
				},
				__destruct: function() {
					this.__parent.__destruct.call(this);
				},
				initialize: _.bind(self.initialize, self),
				update: _.bind(self.update, self)
			});

			return new AItemViewObject(wasm_parent, nodeId, nodeCreateInfo);
		}(this) as any;
	}

	public initialize(): void {
		// Empty
	}

	public update(): void {
		// Empty
	}
};
