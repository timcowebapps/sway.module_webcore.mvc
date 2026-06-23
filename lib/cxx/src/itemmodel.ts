"use strict";

export class AItemModel {
	public _module: any = null;

	constructor(context: any) {
		this._module = new context.module.AItemModel();
	}
};
