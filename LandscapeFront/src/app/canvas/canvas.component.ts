import { Component, ViewChild, ElementRef, OnInit} from '@angular/core';
import { Input } from '@angular/core';

import { Canvas } from './../canvas.service';

@Component({
  selector: 'app-canvas',
  templateUrl: './canvas.component.html',
  styleUrls: ['./canvas.component.css']
})
export class CanvasComponent implements OnInit {
  @Input() width: number = 981;
  @Input() height: number = 561;
  width_str: string = this.width + 'px';
  height_str: string = this.height + 'px';
  private landscape: Canvas | undefined;
  @Input()
  set _canvas(val: Canvas | undefined) {
    if (val) {
      this.landscape = val;
      
      this.hmp = new HeightsMapPoints(this.landscape?.heights_map_points!);
      this.tpa = this.hmp.createTriPolArray(val?.red, val?.green, val?.blue);
      this.animate();
    }
  }

  //hmp: HeightsMapPoints = new HeightsMapPoints();
  private tpa: TriPolArray = new TriPolArray();
  private hmp: HeightsMapPoints | undefined;

  @ViewChild('canvas', { static: true })
  canvas: ElementRef<HTMLCanvasElement> | undefined;  

  private ctx: CanvasRenderingContext2D | undefined;

  constructor() { }

  ngOnInit(): void {
    this.ctx = this.canvas!.nativeElement.getContext('2d')!;
    
    var c = document.getElementsByTagName('canvas')[0];
    c.width  = this.width;
    c.height = this.height;
    /*c.style.width  = this.width;
    c.style.height = this.height;*/
  }

  plot(x: number, y: number, c: string = 'green', m: number = 1) {
    if (this.ctx) {
      this.ctx.fillStyle = c;
      this.ctx.fillRect(x, y, m, m);
    }
  }

  drawLine(x1: number, y1: number, x2: number, y2: number, c: string = 'black') {
    if (this.ctx) {
      this.ctx.beginPath();
      this.ctx.strokeStyle = c;
      this.ctx.moveTo(x1, y1);
      this.ctx.lineTo(x2, y2);
      this.ctx.stroke();
    }
  }

  drawTriPolArray(tpa: TriPolArray) {

  }

  animate() {
    if (this.ctx) {
      this.clearCanvas();

      let counter: number = 0;
      
      let style: string = this.rgbToStyle(this.tpa.red, this.tpa.green, this.tpa.blue);
      this.tpa.data.forEach(tp => {
        counter++;
        this.drawLine(tp.p1.x, tp.p1.y, tp.p2.x, tp.p2.y, style);
        this.drawLine(tp.p2.x, tp.p2.y, tp.p3.x, tp.p3.y, style);
        this.drawLine(tp.p3.x, tp.p3.y, tp.p1.x, tp.p1.y, style);
      })
      //window.alert(this.canvas?.nativeElement.toDataURL());
      //this.plot(4, 10, 'green', 20)
      //this.plot(50, 100, 'green', 10)
    }
  }

  clearCanvas() {
    if (this.ctx) {
      this.ctx.clearRect(0, 0, this.width, this.height);
      //this.ctx = this.canvas!.nativeElement.getContext('2d')!;
    }
  }

  private rgbToStyle(r: number, g: number, b: number): string {
    return 'rgb(' + r + ',' + g + ',' + b + ')';
  }
}

class Point {
  x: number = 0;
  y: number = 0;
  z: number = 0;

  constructor(_x?: number, _y?: number, _z?: number) {
    this.x = _x ?? 0;
    this.y = _y ?? 0;
    this.z = _z ?? 0;
  }

  getStr(): string {
    let res: string = '';
    res = '(' + this.x + '; ' + this.y + '; ' + this.z + ')';
    return res;
  }
}

class HeightsMapPoints {
  points: Point[][] = [];
  width: number = 0;
  height: number = 0;
  elems_num: number = 0;

  constructor(hmp: string) {
    var i: number = 0;
    var x: string = '', y: string = '', z: string = '';

    while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
    {
      x += hmp[i];
      i++;
    }
    this.width = +x;
    i++;
    x = '';

    while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
    {
      x += hmp[i];
      i++;
    }
    this.height = +x;
    i++;
    x = '';

    this.elems_num = this.width*this.height;
    
    var j: number = 0;
    var k: number = 0;
    for (j = 0; j < this.height; j++) {
      var tmp_arr: Point[] = [];
      for (k = 0; k < this.width; k++) {
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            x += hmp[i];
            i++;
        }
        i++;
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            y += hmp[i];
            i++;
        }
        i++;
        while (hmp[i] != ' ' && hmp[i] != '\n' && hmp[i] != '\0')
        {
            z += hmp[i];
            i++;
        }
        i++;
        tmp_arr.push(new Point(+x, +y, +z))
        x = '', y = '', z = '';
      }
      this.points.push(tmp_arr)
    }
  }

  createTriPolArray(r?: number, g?: number, b?: number): TriPolArray
  {
    var new_tri_pol_mas: TriPolArray = new TriPolArray((this.width - 1) * 2 * (this.height - 1), r, g, b);
    
    var tpa_i: number = 0;
    
    for (let i: number = 0; i < (this.height-1); i++)
    {
      for (let j: number = 0; j < (this.width-1); j++)
      {
        if ((j+i) % 2 == 1)
        {
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i][j+1], this.points[i+1][j]);
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i+1][j], this.points[i][j+1], this.points[i+1][j+1]);
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i][j + 1], this.points[i + 1][j]));
          tpa_i++;
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i+1][j], this.points[i][j+1], this.points[i+1][j+1]));
          tpa_i++;
        }
        else
        {
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i+1][j+1], this.points[i][j+1]);
          //new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j], this.points[i+1][j], this.points[i+1][j+1]);
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i+1][j+1], this.points[i][j+1]));
          tpa_i++;
          new_tri_pol_mas.data.push(new TriangularPolygon(this.points[i][j], this.points[i+1][j], this.points[i+1][j+1]));
          tpa_i++;
        }
      }
    }

    /*this.points.forEach((val, ind) => {
      if (ind % 2 == 1)
        new_tri_pol_mas.data[tpa_i++] = new TriangularPolygon(this.points[i][j])
    })*/

    return new_tri_pol_mas;
  }

  getStr(): string {
    let res: string = '';
    this.points.forEach(arr => arr.forEach(val => res += val.getStr() + '\n'))
    return res;
  }

  print() {
    window.alert(this.getStr());
  }
}

class TriPolArray {
  data: TriangularPolygon[] = [];
  elems_num: number = 0;
  red: number = 0;
  green: number = 0;
  blue: number = 0;

  constructor(new_size?: number, new_r?: number, new_g?: number, new_b?: number) {
    this.elems_num = new_size ?? 0;
    /*for (let i: number = 0; i < this.elems_num; i++) {
      this.data.push(new TriangularPolygon(new Point(), new Point(), new Point()));
    }*/
    this.red = new_r ?? 0;
    this.green = new_g ?? 0;
    this.blue = new_b ?? 0;
  }

  getStr(): string {
    let res: string = '';
    this.data.forEach(tp => { res += tp.getStr() + '\n'} )
    return res;
  }

  print() {
    window.alert(this.getStr());
  }
}

class TriangularPolygon {
  p1: Point = new Point(); p2: Point = new Point(); p3: Point = new Point();
  min_x: number | undefined; max_x: number | undefined; min_y: number | undefined; max_y: number | undefined;
  norm_vec1: Vector = new Vector(); norm_vec2: Vector = new Vector(); norm_vec3: Vector = new Vector();
  A: number | undefined; B: number | undefined; C: number | undefined; D: number | undefined;
  intensity: number | undefined;

  constructor(new_p1: Point, new_p2: Point, new_p3: Point) {
    this.p1 = new_p1;
    this.p2 = new_p2;
    this.p3 = new_p3;
    this.calcRect();
    this.calcNormals();
    this.calcSurface();
    this.calcIntensity();
  }

  public udpate() {
    this.calcRect();
    this.calcNormals();
    this.calcSurface();
  }

  private calcRect() {
    this.min_x = this.p1.x;
    this.max_x = this.p1.x;
    this.min_y = this.p1.y;
    this.max_y = this.p1.y;

    if (this.p2.x < this.min_x)
        this.min_x = this.p2.x;
    if (this.p2.x > this.max_x)
        this.max_x = this.p2.x;
    if (this.p2.y < this.min_y)
        this.min_y = this.p2.y;
    if (this.p2.y > this.max_y)
        this.max_y = this.p2.y;

    if (this.p3.x < this.min_x)
        this.min_x = this.p3.x;
    if (this.p3.x > this.max_x)
        this.max_x = this.p3.x;
    if (this.p3.y < this.min_y)
        this.min_y = this.p3.y;
    if (this.p3.y > this.max_y)
        this.max_y = this.p3.y;
  }
  
  private calcNormals() {
    var vec1_x: number = this.p2.x - this.p1.x, vec1_y: number = this.p2.y - this.p1.y;
    var vec2_x: number = this.p3.x - this.p2.x, vec2_y: number = this.p3.y - this.p2.y;
    var vec3_x: number = this.p1.x - this.p3.x, vec3_y: number = this.p1.y - this.p3.y;

    if (vec1_y != 0)
      this.norm_vec1 = new Vector([1, -vec1_x/vec1_y]);
    else
      this.norm_vec1 = new Vector([0, 1]);
    if (this.norm_vec1.at(0)*vec2_x + this.norm_vec1.at(1)*vec2_y < 0)
      this.norm_vec1 = this.norm_vec1.negate(); //this.norm_vec1.multiply(new Vector([-1.]));
    
    if (vec2_y != 0)
      this.norm_vec2 = new Vector([1, -vec2_x/vec2_y]);
    else
      this.norm_vec2 = new Vector([0, 1]);
    if (this.norm_vec2.at(0) * vec3_x + this.norm_vec2.at(1) * vec3_y < 0)
      this.norm_vec2 = this.norm_vec2.negate(); //this.norm_vec2.multiply(new Vector([-1.]));
    
    if (vec3_y != 0)
      this.norm_vec3 = new Vector([1, -vec3_x/vec3_y]);
    else
      this.norm_vec3 = new Vector([0, 1]);
    if (this.norm_vec3.at(0)*vec1_x + this.norm_vec3.at(1)*vec1_y < 0)
      this.norm_vec3 = this.norm_vec3.negate();
  }

  private calcSurface() {
    var x1: number = this.p1.x, y1 = this.p1.y, z1 = this.p1.z;
    var x2: number = this.p2.x, y2 = this.p2.y, z2 = this.p2.z;
    var x3: number = this.p3.x, y3 = this.p3.y, z3 = this.p3.z;
    this.A = y1 *(z2 - z3) + y2 *(z3 - z1) + y3 *(z1 - z2);
    this.B = z1 *(x2 - x3) + z2 *(x3 - x1) + z3 *(x1 - x2);
    this.C = x1 *(y2 - y3) + x2 *(y3 - y1) + x3 *(y1 - y2);
    this.D = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
  }

  private calcIntensity() {
    if (this.A && this.B && this.C && this.D) {
      if (this.A != 0 || this.B != 0 || this.C != 0)
        this.intensity = Math.abs(this.B / Math.sqrt(this.A * this.A + this.B * this.B + this.C * this.C));
      else
        this.intensity = 1;
    }
  }

  getStr(): string {
    var res: string = '';
    res += "p1 = " + this.p1.getStr() + "; ";
    res += "p2 = " + this.p2.getStr() + "; ";
    res += "p3 = " + this.p3.getStr() + "; ";
    return res;
  }
}

export default class Vector {

  /** Values of the vector */
  private _values: number[];

  constructor(values?: number[]) {
      // Create matrix filled with 0 by default
      this._values = new Array<number>((values || [0]).length).fill(0);

      if (values) {
          this.values = values;
      }
  }

  get rows() {
      return this.values.length;
  }

  get values() {
      return this._values;
  }

  /**
   * Set values into the vector.
   * If the parameters vector is to wide, the values are cropped to the current vector size.
   * It the parameters vector is to small, remaining cells will be filled with 0.
   * @param newValues Arrays of new values.
   */
  set values(newValues: number[]) {
      const minSize = Math.min(this.values.length, newValues.length);
      for (let i = 0; i < minSize; i++) {
          this.values[i] = newValues[i];
      }
  }

  /**
   * Get a matrix value, from its position
   * @param row Matrix line, from 0 to `rows`
   */
  at(row: number): number {
      return this.values[row];
  }

  /**
   * Sets all matrix values to 0
   */
  reset(): void {
      this.values = this.values.fill(0);
  }

  /**
   * Add an new row to the matrix, filled with 0
   */
  addAValue(): Vector {
      this.values.push(0);
      return new Vector(this.values);
  }

  /**
   * Check if two matrix are equals, value by value
   * @param mat The matrix against to check equality
   */
  equals(vec: Vector): boolean {
      return (this.rows === vec.rows)
          && this.values.reduce((eql: boolean, val, i) => eql && vec.at(i) === val, true);
  }

  /**
   * Negate all values of the vector (get the opposite sign)
   * @return A new vector whose all values have the opposed sign
   */
  negate(): Vector {
      return new Vector(this.values.map((val) => -val));
  }

  /** Get the length of the vector */
  length(): number {
      return Math.sqrt(this.squaredLength());
  }

  /** Get the squared length of the vector */
  squaredLength(): number {
      return this.dot(this);
  }

  /**
   * Add all vector values with the same position value of the operand vector
   * @param vector The operand vector
   * @throws Error if the two vectors don't have the same dimension
   * @return a new Vector with the result values
   */
  add(vector: Vector): Vector {
      if (this.rows !== vector.rows) throw new Error("Vectors don't have the same dimension!");
      return this.operateOnAllValues((val, i) => (val + vector.at(i)));
  }

  /**
   * Sunstract all vector values with the same position value of the operand vector
   * @param vector The operand vector
   * @throws Error if the two vectors don't have the same dimension
   * @return a new Vector with the result values
   */
  substract(vector: Vector): Vector {
      if (this.rows !== vector.rows) throw new Error("Vectors don't have the same dimension!");
      return this.operateOnAllValues((val, i) => (val - vector.at(i)));
  }

  /**
   * Multiply all vector values with the same position value of the operand vector
   * @param vector The operand vector
   * @throws Error if the two vectors don't have the same dimension
   * @return a new Vector with the result values
   */
  multiply(vector: Vector): Vector {
      if (this.rows !== vector.rows) throw new Error("Vectors don't have the same dimension!");
      return this.operateOnAllValues((val, i) => (val * vector.at(i)));
  }

  /**
   * Divide all vector values with the same position value of the operand vector
   * Be aware of divisions by 0!
   * @param vector The operand vector
   * @throws Error if the two vectors don't have the same dimension
   * @return a new Vector with the result values
   */
  divide(vector: Vector): Vector {
      if (this.rows !== vector.rows) throw new Error("Vectors don't have the same dimension!");
      return this.operateOnAllValues((val, i) => {
          if (vector.at(i) === 0) return val;
          return (val / vector.at(i));
      });
  }

  /**
   * Multiply all vector values by the given number
   * @param scale The number to multiply with the values
   */
  scale(scale: number): Vector {
      return this.operateOnAllValues((val) => (val * scale));
  }

  /**
   * Run a function on all vector values, as a map.
   * @param operation The mapping method
   * @return a new Vector with the operation done on all its values
   */
  private operateOnAllValues(operation: (val: number, index: number) => number): Vector {
      return new Vector(this.values.map(operation));
  }

  /**
   * Computes the normalized vector
   * @return The normalized vector
   */
  normalize(): Vector {
      const vectorLength = this.length();
      return this.operateOnAllValues((val) => val / vectorLength);
  }

  /**
   * Computes the dot product of vectors
   * @param vector The operand vector
   */
  dot(vector: Vector): number {
      return this.values.reduce((res, val, i) => res + (val * vector.at(i)), 0);
  }

  /**
   * Computes the cross product of vectors
   * @param vector The operand vector
   */
  cross(vector: Vector): Vector {
      if (this.rows < 3 || vector.rows < 3) throw new Error('Cross product is possible on 3D vectors only');
      const crossValues = new Array<number>(3);
      crossValues[0] = this.at(1) * vector.at(2) - this.at(2) * vector.at(1);
      crossValues[1] = this.at(2) * vector.at(0) - this.at(0) * vector.at(2);
      crossValues[2] = this.at(0) * vector.at(1) - this.at(1) * vector.at(0);
      return new Vector(crossValues);
  }

  mix(vector: Vector, time: number): Vector {
      return new Vector(this.values.map((val, i) => val + time * (vector.at(i) - val)));
  }

  static get360angle(Va: Vector, Vb: Vector) {
      if (Va.rows !== 3 || Vb.rows !== 3) throw new Error('Vectors must be in 3D!. You can add a 1 dimension if it is missing.');
      return -Math.atan2(
        Vb.cross(Va).dot(new Vector([0, 0, 1]).normalize()),
        Va.dot(Vb)
      );
    }
}

