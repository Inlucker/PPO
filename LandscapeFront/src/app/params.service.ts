import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ParamsService {

  constructor() { }
}

export class Params {
  canvas_id: number = 0;
  width: number = 0;
  height: number = 0;
  range: number = 0;
  smooth: boolean = false;
  mult: number = 1;
  red: number = 0;
  green: number = 0;
  blue: number = 0;
  size: number = 0;
}