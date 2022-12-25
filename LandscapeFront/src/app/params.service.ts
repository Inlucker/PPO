import { Observable } from 'rxjs';
import { environment } from './../environments/environment';
import { HttpClient } from '@angular/common/http';
import { Resolution } from './canvas/canvas.component';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ParamsService {
  options = { withCredentials: true };
  paramsUrl: string = environment.baseApiUrl + '/params'

  constructor(private http: HttpClient) { }

  get(canvas_id: number): Observable<GetParams> {
    return this.http.get<GetParams>(this.paramsUrl + '/' + canvas_id, this.options);
  }
  
  post(p: Params): Observable<void> {
    return this.http.post<void>(this.paramsUrl, p, this.options);
  }

  put(p: Params): Observable<void> {
    return this.http.put<void>(this.paramsUrl, p, this.options);
  }
}

export interface GetParams {
  canvas_id: number;
  width: number;
  height: number ;
  range: number;
  smooth: boolean;
  mult: number;
  red: number;
  green: number;
  blue: number;
  size: number;
}

export class Params {
  constructor() {
      this.canvas_name = localStorage.getItem('canvas_name') ?? 'Canvas Name';
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
    this.updateColorHex();
  }

  updateGetParams(gp: GetParams) {
    this.width = gp.width;
    this.height = gp.height;
    this.updateResolution();
    this.range = gp.range;
    //localStorage.setItem('range', gp.range.toString());
    this.smooth = gp.smooth;
    this.mult = gp.mult;
    localStorage.setItem('mult', gp.mult.toString());
    this.red = gp.red;
    this.green = gp.green;
    this.blue = gp.blue;
    this.updateColorHex();
    this.size = gp.size;
    //localStorage.setItem('size', gp.size.toString());
  }

  canvas_id: number = 0;
  canvas_name: string = 'Canvas Name';
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

  updateRGB(ch: string) {
    var col = this.hexToRgb(ch);
    if (col) {
      this.red = col.r;
      this.green = col.g;
      this.blue = col.b;
    }
  }

  updateColorHex() {
    this.color_hex = this.rgbToHex(this.red, this.green, this.blue);
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