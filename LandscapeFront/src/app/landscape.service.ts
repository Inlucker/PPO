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

  static updateResolution(resol: Resolution) {
    this.params.width = resol.width;
    this.params.height = resol.height;
    /*var can = document.getElementsByTagName('canvas')[0];
    can.width  = resol.width;
    can.height = resol.height;*/

    if (this.hmp)
    {
      let c: Point = this.hmp.map_points_center;
      this.hmp.move(new Point(-c.x + (resol.width / (2 * this.params.mult)), -c.y + (resol.height / (2 * this.params.mult)), -c.z));
    }
  }

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

  static setCanvas(canvas: Canvas) {
    this.canvas = canvas;
    this.hmp = new HeightsMapPoints(canvas.heights_map_points);
    this.tpa = this.hmp.createTriPolArray(canvas.red, canvas.green, canvas.blue);
  }

  static reset() {
    this.canvas = undefined;
    this.hmp = undefined;
    this.tpa = new TriPolArray();
    this.params = new Params();
  }
}
