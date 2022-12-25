import { HeightsMap } from './../LandscapeClasses/heights-map';
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
  static tpa: TriPolArray;
  static params: Params = new Params();

  constructor() { }


  static move(p: Point) {
    this.hmp?.move(p);
    //this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static scale(p: Point) {
    this.hmp?.scale(p);
    //this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static rotate(p: Point) {
    this.hmp?.rotate(p);
    //this.tpa = this.hmp?.createTriPolArray(this.canvas?.red, this.canvas?.green, this.canvas?.blue)!;
  }
  static updateResolution() {
    //this.params.width = resol.width;
    //this.params.height = resol.height;
    //this.params.updateResolution();

    /*var can = document.getElementsByTagName('canvas')[0];
    can.width  = resol.width;
    can.height = resol.height;*/

    if (this.hmp)
    {
      let c: Point = this.hmp.map_points_center;
      this.hmp.move(new Point(-c.x + (this.params.width / (2 * this.params.mult)), -c.y + (this.params.height / (2 * this.params.mult)), -c.z));
    }
  }
  static updateMult(m: number) {
    let old_m: number | undefined;
    if (localStorage.getItem('mult'))
      old_m = +localStorage.getItem('mult')!;
    if (this.hmp && old_m) {
      let c: Point = this.hmp.map_points_center;
      this.hmp.move(new Point(-c.x + (this.params.width / (2 * m)), -c.y + (this.params.height / (2 * m)), -c.z));
      let mk: number = (old_m) / m;
      this.hmp.scale(new Point(mk, mk, mk));
    }

    this.params.mult = m;
    localStorage.setItem('mult', m.toString());
  }
  static updateRange(r: number) {
    //this.params.range = r;
    localStorage.setItem('range', r.toString());
  }
  static updateSize(s: number) {
    //this.params.size = s;
    localStorage.setItem('size', s.toString());
  }
  static updateSmooth(s: boolean) {
    //this.params.smooth = s;
    if (s)
      localStorage.setItem('smooth', '1');
    else
      localStorage.setItem('smooth', '0');
  }
  static updateColor(ch: string) {
    this.params.updateRGB(ch);
    var col = this.params.hexToRgb(ch);
    if (col)
      this.tpa.setColor(col);
    localStorage.setItem('color_hex', ch);
  }
  static updateCanvasName(cn: string) {
    this.params.canvas_name = cn;
    if (this.canvas)
      this.canvas.name = cn;
    localStorage.setItem('canvas_name', this.params.canvas_name);
  }

  static setCanvas(canvas: Canvas) {
    this.canvas = canvas;
    this.hmp = new HeightsMapPoints(canvas.heights_map_points);
    this.tpa = this.hmp.createTriPolArray(canvas.red, canvas.green, canvas.blue);
  }

  static setGenCanvas(c: Canvas) {
    this.canvas = c;
    let hm: HeightsMap = new HeightsMap(c.heights_map);
    let max_h = hm.max_height;
    let k: number = Math.min((0.9*this.params.height)/max_h, ((0.9*this.params.width)/hm.width))
    this.hmp = new HeightsMapPoints(c.heights_map_points);
    this.hmp.scale(new Point(k / this.params.mult, k / this.params.mult, k / this.params.mult));
    max_h *= k / this.params.mult;

    let center: Point = this.hmp.map_points_center;
    this.hmp.move(new Point(-center.x + (this.params.width / (2 * this.params.mult)), -center.y + (this.params.height / (2 * this.params.mult)), -center.z))
    this.hmp.rotate(new Point(0, 0, 180));

    this.tpa = this.hmp.createTriPolArray(c.red, c.green, c.blue);
  }

  static reset() {
    localStorage.setItem('canvas_name', 'Canvas Name');
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
