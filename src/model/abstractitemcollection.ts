"use strict";

export class AItemCollection {
	public _module: any = null;

	constructor(wasm_context: any) {
		this._module = new wasm_context.module.AbstractItemCollection();
	}

	public setItem(value: any): void {
		this._module.setItem(value);
	}

	public getItem(index: number): any {
		return this._module.getItem(index);
	}

	public setItems(value: any): void {
		this._module.setItems(value);
	}

	public getItems(): any {
		return this._module.getItems();
	}
};
