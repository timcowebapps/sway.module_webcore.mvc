"use strict";

export class AbstractController {
	public _wasm_controller: any = null;

	constructor(context: any, model: any) {
		this._wasm_controller = new context.module.AbstractController(model._wasm_model);
	}
};
