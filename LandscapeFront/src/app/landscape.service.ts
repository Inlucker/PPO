import Point from 'src/LandscapeClasses/point';
import { Resolution } from './canvas/canvas.component';
import { Params } from './params.service';
import { Canvas } from './canvas.service';
import { Injectable } from '@angular/core';
import HeightsMapPoints from 'src/LandscapeClasses/heights-map-points';
import TriPolArray from 'src/LandscapeClasses/tri-pol-array';

@Injectable({
  providedIn: 'root'
})
export class LandscapeService {
  static canvas: Canvas | undefined;
  static hmp: HeightsMapPoints | undefined;
  static tpa: TriPolArray = new TriPolArray();
  static params: Params = new Params();

  constructor() { }


  static move(p: Point) {
    this.hmp?.move(p);
    this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static scale(p: Point) {
    this.hmp?.scale(p);
    this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static rotate(p: Point) {
    this.hmp?.rotate(p);
    this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static updateResolution(resol: Resolution) {
    this.params.width = resol.width;
    this.params.height = resol.height;
    this.params.updateResolution();

    /*var can = document.getElementsByTagName('canvas')[0];
    can.width  = resol.width;
    can.height = resol.height;*/

    if (this.hmp)
    {
      let c: Point = this.hmp.map_points_center;
      this.hmp.move(new Point(-c.x + (resol.width / (2 * this.params.mult)), -c.y + (resol.height / (2 * this.params.mult)), -c.z));
    }
  }
  static updateMult(m: number) {
    this.params.mult = m;
    localStorage.setItem('mult', m.toString());
  }
  static updateRange(r: number) {
    this.params.range = r;
    localStorage.setItem('range', r.toString());
  }
  static updateSize(s: number) {
    this.params.size = s;
    localStorage.setItem('size', s.toString());
  }
  static updateSmooth(s: boolean) {
    this.params.smooth = s;
    if (s)
      localStorage.setItem('smooth', '1');
    else
      localStorage.setItem('smooth', '0');
  }
  static updateColor(ch: string) {
    this.params.color_hex = ch;
    var col = this.params.hexToRgb(ch);
    if (col)
      this.tpa.setColor(col);
    localStorage.setItem('color_hex', ch);
  }

  static setCanvas(canvas: Canvas) {
    this.canvas = canvas;
    this.hmp = new HeightsMapPoints(canvas.heights_map_points);
    this.tpa = this.hmp.createTriPolArray(canvas.red, canvas.green, canvas.blue);
  }

  static reset() {
    localStorage.setItem('width', '960');
    localStorage.setItem('height', '540');
    localStorage.setItem('range', '24');
    localStorage.setItem('smooth', '0');
    localStorage.setItem('mult', '1');
    localStorage.setItem('color_hex', '#149614');
    /*localStorage.setItem('red', '20');
    localStorage.setItem('green', '150');
    localStorage.setItem('blue', '20');*/
    localStorage.setItem('size', '33');
    this.canvas = undefined;
    this.hmp = undefined;
    this.tpa = new TriPolArray();
    this.params = new Params();
  }
}
