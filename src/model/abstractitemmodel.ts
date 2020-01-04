"use strict";

export class AbstractItemModel {
	public _module: any = null;

	constructor(context: any) {
		this._module = new context.module.AbstractItemModel();
	}
};
