import { Resolution } from './canvas/canvas.component';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ParamsService {

  constructor() { }
}

export class Params {
  constructor() {
    if (localStorage.getItem('width'))
      this.width = +localStorage.getItem('width')!;
    if (localStorage.getItem('height'))
      this.height = +localStorage.getItem('height')!;
    if (localStorage.getItem('range'))
      this.range = +localStorage.getItem('range')!;
    if (localStorage.getItem('smooth'))
      this.smooth = (localStorage.getItem('smooth')!) == '1';
    if (localStorage.getItem('mult'))
      this.mult = +localStorage.getItem('mult')!;
    /*if (localStorage.getItem('red'))
      this.red = +localStorage.getItem('red')!;
    if (localStorage.getItem('green'))
      this.green = +localStorage.getItem('green')!;
    if (localStorage.getItem('blue'))
      this.blue = +localStorage.getItem('blue')!;*/
    if (localStorage.getItem('color_hex')) {
      var rgb = this.hexToRgb(localStorage.getItem('color_hex')!)
      if (rgb) {
        this.red = rgb.r;
        this.green = rgb.g;
        this.blue = rgb.b;
      }
    }
    if (localStorage.getItem('size'))
      this.size = +localStorage.getItem('size')!;
    
    this.updateResolution();
    this.updateColorStyle();
  }

  canvas_id: number = 0;
  width: number = 960;
  height: number = 540;
  range: number = 24.;
  smooth: boolean = false;
  mult: number = 1;
  red: number = 20;
  green: number = 150;
  blue: number = 20;
  size: number = 33;

  resolution: Resolution = { width: this.width, height: this.height };
  resolution_str: string = this.width + 'x' + this.height;
  color_hex: string = this.rgbToHex(this.red, this.green, this.blue); 
  //color_style: string = 'rgb(' + this.red + ',' + this.green + ',' + this.blue + ')';

  updateResolution() {
    this.resolution = { width: this.width, height: this.height };
    this.resolution_str = this.width + 'x' + this.height;
    
    localStorage.setItem('width', this.width.toString());
    localStorage.setItem('height', this.height.toString());
  }
  
  updateResolutionByStr() {
    this.resolution = new Resolution(this.resolution_str);
    this.width = this.resolution.width;
    this.height = this.resolution.height;
  }

  updateColorStyle() {
    this.color_hex = this.rgbToHex(this.red, this.green, this.blue);
    
    /*localStorage.setItem('red', this.red.toString());
    localStorage.setItem('green', this.green.toString());
    localStorage.setItem('blue', this.blue.toString());*/
  }

  componentToHex(c: number) {
    var hex = c.toString(16);
    return hex.length == 1 ? "0" + hex : hex;
  }
  
  rgbToHex(r: number, g: number, b: number) {
    return "#" + this.componentToHex(r) + this.componentToHex(g) + this.componentToHex(b);
  }

  hexToRgb(hex: string) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16)
    } : null;
  }
}