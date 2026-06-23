"use strict";

export class AController {
	public _wasm_controller: any = null;

	constructor(context: any, model: any) {
		this._wasm_controller = new context.module.AController(model._wasm_model);
	}
};
