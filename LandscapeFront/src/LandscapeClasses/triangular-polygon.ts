import Vector from 'src/app/vector';
import Point from './point';

export default class TriangularPolygon {
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
  